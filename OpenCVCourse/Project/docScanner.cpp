#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(){
    std::string imgPath = "../resources/paper.jpg/";
    cv::Mat img = cv::imread(imgPath);
    cv::imshow("Document", img);
    cv::waitKey(0);
}