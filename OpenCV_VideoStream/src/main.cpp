#include "../include/Images.h"
#include "../include/Videos.h"
#include "../include/Tracking.h"
#include "../include/FaceDetection.h"
#include "../include/DetectAndTrack.h"

#include <iostream>                     // std::cout

int main() {
    int res{ 0 };

    std::cout << "Program started" << "\n";

    // Images.h :
    //res = showLenna();        // OK
    
    // Videos.h :  
    //res = showMyWebcam();     // OK
    //res = showWinrunner();    // OK

    // Tracking.h :
    //res = trackMyWebcam();      // Not working
    //res = trackMyWebcam2();     // OK --> select an area to be tracked using the mouse, then press Enter (more information on the terminal).

    // FaceDetection.h :
    //res = faceDetectionFromDefaultVideoStream();    // Working, but not efficient for : real time/moving target/several targets/etc. Good for a short demo, but that's all.

    // DetectAndTrack.h :
    //res = detectPeopleUsingHistogramOfOrientedGradients();  // OK
    //res = DATFVS_SingleTarget();                            // Not working
    
    std::cout << "Program returned " << res << "\n";

	return res;
}
