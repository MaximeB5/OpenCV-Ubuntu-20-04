#include "../include/Videos.h"
#include <opencv2/core/core.hpp>        // Mat
#include <opencv2/videoio.hpp>          // VideoCapture, VideoWriter
#include <opencv2/highgui/highgui.hpp>  // Gui
#include <iostream>                     // std::cout

using namespace cv;

int showMyWebcam(void) {
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
    VideoWriter output("../bin/output/out_Webcam.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth, frameHeight));

    while (video.read(frame)) {
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


int showWinrunner(void) {
    // Capture video using a video at the same location that this file and main.cpp
    VideoCapture video("../media/video/Winrunner.mp4");

    // Check that video opened
    if (!video.isOpened()) return -1;

    // For saving the frames from the video
    Mat frame;

    // Get the video resolution
    int frameWidth = video.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = video.get(CAP_PROP_FRAME_HEIGHT);

    // Video writer object - params : name, encodec, fps, video resolution
    // FPS : 60 might be a bit fast as a result in the video output, 30 is decent (but sometimes faster than the real stream)
    VideoWriter output("../bin/output/out_Winrunner.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 60, Size(frameWidth, frameHeight));

    while (video.read(frame)) {
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
