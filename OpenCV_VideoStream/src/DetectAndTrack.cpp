#include "../include/DetectAndTrack.h"

#include "../include/Images.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>        // Mat
#include <opencv2/videoio.hpp>          // VideoCapture, VideoWriter
#include <opencv2/highgui/highgui.hpp>  // Gui
#include <opencv4/opencv2/tracking.hpp> // trackers
#include <iostream>                     // std::cout
#include <vector>
#include <string>

using namespace cv;

constexpr char imgName[] = "../media/img/Rue.jpg";

void resizeBoxes(Rect& box);

int detectPeopleUsingHistogramOfOrientedGradients(void) {
	// Load the input
	Mat img = imread(imgName);

	// Check the file is valid
	if (img.empty() or !img.data)
	{
		std::cout << "Could not open or find the image" << "\n";
		return -1;
	}

	// Histogram of Oriented Gradients
	HOGDescriptor hog;

	// People detection : getDefaultPeopleDetector will give us the coefficients of classifying trend for people detection
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	std::vector<Rect> detections;

	// Now we can begin the detection
	// arguments :		 input array image, detection based tracker::tracked object::positions vector found location,
	//					 hit threshold, win stride, padding		--> values to play with for a better detection
	//					 scale, final threshold					--> values to play with for a better detection
	//					 use mean shift grouping
	hog.detectMultiScale(img, detections,
						 0.0, Size(8, 8), Size(32, 32),
						 1.2, 2,
						 false);

	// Draw the boxes around what we've detected
	for (auto& detection : detections) {
		resizeBoxes(detection);
		rectangle(img, detection.tl(), detection.br(), Scalar(255, 0, 0), 2);
	}

	namedWindow("People Detection Results");
	imshow("People Detection Results", img);
	waitKey(0);

	//return 0;
	return showImg(imgName);
}

void resizeBoxes(Rect& box) {
	box.x += cvRound(box.width * 0.1);
	box.width = cvRound(box.width * 0.8);

	box.y += cvRound(box.height * 0.06);
	box.height = cvRound(box.height * 0.8);
}

int DATFVS_SingleTarget() {
    // Capture video using the default video source (i.e. webcam)
    VideoCapture video(0);

    // Check that video opened
    if (!video.isOpened()) return -1;

    // For saving the frames from the video
    Mat frame;

    // Check frames can be read by reading the first one
    if (!video.read(frame)) return -2;

    // Get the video resolution
    int frameWidth = video.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = video.get(CAP_PROP_FRAME_HEIGHT);

    // Video writer object - params : name, encodec, fps, video resolution
    // FPS : 60 might be a bit fast as a result in the video output, 30 is decent (but sometimes faster than the real stream)
    VideoWriter output("output/out_DetectAndTrackSingleTarget.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth, frameHeight));

    // Define initial bounding box
    Rect2d boundingBox(287, 23, 86, 320);

    /// Uncomment the line below to select a different bounding box
    /// boundingBox = selectROI(frame, false);
    
    // Create the tracker
    Ptr<Tracker> tracker = TrackerGOTURN::create();
    tracker->init(frame, boundingBox);

    // Predict the bounding box in a new frame.
    // Finally, we loop over all frames in the videoand find the bounding box for new frames using tracker.update.
    // The rest of the code is simply for timingand displaying.
    while (video.read(frame)) {
        // Start timer
        double timer = (double)getTickCount();

        // Update the tracking result
        bool trackingSuccess = tracker->update(frame, boundingBox);

        // Calculate FPS number
        float fps = getTickFrequency() / ((double)getTickCount() - timer);

        if (trackingSuccess) {
            // Draw the tracked object
            rectangle(frame, boundingBox, Scalar(255, 0, 0), 2, 1);
        }
        else {
            putText(frame, "Tracking failed to detect the target", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
        }

        // Display the tracker type on the frame
        putText(frame, "FPS : " + std::to_string(int(fps)), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

        // Display the frame
        imshow("Tracking", frame);

        // Write video frame
        output.write(frame);

        // Exit if ESC pressed
        if (waitKey(1) == 27) break;
    }

    // Release video capture and writer
    output.release();
    video.release();

    cv::destroyAllWindows();

    return 0;
}