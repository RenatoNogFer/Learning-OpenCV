#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(){

    cv::Mat imgHSV, mask;
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;

    std::string imgPath = "../resources/lambo.png";
    cv::Mat img = cv::imread(imgPath);

    // Taskbars
    cv::namedWindow("Trackbar", (640, 200));
    cv::createTrackbar("Hue min", "Trackbar", &hmin, 179);
    cv::createTrackbar("Hue max", "Trackbar", &hmax, 179);
    cv::createTrackbar("Sat min", "Trackbar", &smin, 255);
    cv::createTrackbar("Sat max", "Trackbar", &smax, 255);
    cv::createTrackbar("Val min", "Trackbar", &vmin, 255);
    cv::createTrackbar("Val max", "Trackbar", &vmax, 255);

    // Loop for trackbar usage
    while(true){
        // Color detection
        cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(imgHSV, lower, upper, mask);

        cv::imshow("Lambo", img);
        cv::imshow("HSV", imgHSV);
        cv::imshow("Mask", mask);
        cv::waitKey(1);
    }
}
