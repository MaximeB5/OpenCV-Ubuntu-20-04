#include "../include/Tracking.h"
#include <opencv2/core/core.hpp>        // Mat
#include <opencv2/core/utility.hpp>
#include <opencv2/videoio.hpp>          // VideoCapture, VideoWriter
#include <opencv2/highgui/highgui.hpp>  // Gui
#include <opencv4/opencv2/tracking.hpp> // trackers
#include <iostream>                     // std::cout
#include <vector>                       // std::vector<T>

using namespace cv;

int trackMyWebcam(void) {
    // Capture video using the default video source (i.e. webcam)
    VideoCapture video(0);

    // Check that video opened
    if (!video.isOpened()) return -1;

    // For saving the frames from the video
    Mat frame;

    // Get the video resolution
    int frameWidth = video.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = video.get(CAP_PROP_FRAME_HEIGHT);

    // Video writer object - params : name, encodec, fps, video resolution
    // FPS : 60 might be a bit fast as a result in the video output, 30 is decent (but sometimes faster than the real stream)
    VideoWriter output("output/out_Tracker.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth, frameHeight));

    // Create the tracker
    video.read(frame);
    Ptr<MultiTracker> multitracker = MultiTracker::create();
    std::vector<Rect> boundingBoxes;
    selectROIs("Video output", frame, boundingBoxes, false);

    // If nothing to be tracked, then we don't need to go further
    if (boundingBoxes.size() < 1) return 0;

    // Else we add all the tracking objects to the tracker
    for (const auto& boundingBox : boundingBoxes) {
        multitracker->add(TrackerKCF::create(), frame, boundingBox);
    }
    

    while (video.read(frame)) {
        // Tracker update
        multitracker->update(frame);
        for (const auto& targetToBeTrack : multitracker->getObjects()) {
            // arguments : frame, trackingbox, rgb color of the rectangle, thickness of the lines of the rectangle, line type, shift
            rectangle(frame, targetToBeTrack, Scalar(0, 255, 0), 2, 8, 0);
        }

        // Display the frame
        imshow("Video output", frame);

        // Write video frame
        output.write(frame);

        // To end the video early
        if (waitKey(25) >= 0) break;
    }

    // Release video capture and writer
    output.release();
    video.release();

    destroyAllWindows();

    return 0;
}

int trackMyWebcam2(void) {
    // declares all required variables
    Rect2d roi;
    Mat    frame;

    // create a tracker object
    Ptr<Tracker> tracker = TrackerKCF::create();

    // set input video
    VideoCapture cap(0);

    // get bounding box
    cap >> frame;
    roi=selectROI("tracker",frame);

    //quit if ROI was not selected
    if(roi.width==0 || roi.height==0)
    { return 0; }
    
    // initialize the tracker
    tracker->init(frame,roi);

    // perform the tracking process
    printf("Start the tracking process, press ESC to quit.\n");

    for ( ;; ) {
        // get frame from the video
        cap >> frame;

        // stop the program if no more images
        if(frame.rows==0 || frame.cols==0)
        { break; }

        // update the tracking result
        tracker->update(frame,roi);

        // draw the tracked object
        rectangle( frame, roi, Scalar( 255, 0, 0 ), 2, 1 );

        // show image with the tracked object
        imshow("tracker",frame);

        //quit on ESC button
        if(waitKey(1)==27)break;
    }

    return 0;
}