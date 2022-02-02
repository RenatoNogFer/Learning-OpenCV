#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(){
    cv::VideoCapture webcam(0);
    cv::Mat tempImg;

    while(1){
        webcam.read(tempImg);
        cv::imshow("Webcam", tempImg);
        cv::waitKey(1);
    }
}