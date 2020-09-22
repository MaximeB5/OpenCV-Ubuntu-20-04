
#include "../include/Images.h"
#include <opencv2/core/core.hpp>        // Mat
#include <opencv2/highgui/highgui.hpp>  // Gui
#include <iostream>                     // std::cout
#include <string>                       // std::string

using namespace cv;

int showLenna(void) {
    // Read the file, lenna.jpg is a picture at the same location that this file and main.cpp
    Mat image = imread("../media/img/Lenna.png", IMREAD_COLOR);

    // Check for invalid input
    if (image.empty())
    {
        std::cout << "Could not open or find the image" << "\n";
        return -1;
    }

    // Create a window for display
    namedWindow("Display window", WINDOW_AUTOSIZE);

    // Show our image inside it
    imshow("Display window", image);

    // Wait for a keystroke in the window
    waitKey(0);

    return 0;
}

int showImg(const std::string& imgName) {
    Mat image = imread(imgName, IMREAD_COLOR);

    // Check for invalid input
    if (image.empty())
    {
        std::cout << "Could not open or find the image" << "\n";
        return -1;
    }

    // Create a window for display
    namedWindow("Original Picture " + imgName, WINDOW_AUTOSIZE);

    // Show our image inside it
    imshow("Original Picture " + imgName, image);

    // Wait for a keystroke in the window
    waitKey(0);

    return 0;
}