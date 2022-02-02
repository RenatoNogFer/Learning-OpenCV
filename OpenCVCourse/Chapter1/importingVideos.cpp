#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(){
    std::string videoPath = "../resources/cat.mp4";
    cv::VideoCapture video(videoPath);
    cv::Mat image;

    while(1){
        video.read(image);
        cv::imshow("Cat", image);
        cv::waitKey(1);
    }
}
