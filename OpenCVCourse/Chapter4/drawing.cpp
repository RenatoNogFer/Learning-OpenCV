#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(){
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::circle(img, cv::Point(256,256), 155, cv::Scalar(255,0,128), cv::FILLED);
    cv::rectangle(img, cv::Point(130,226), cv::Point(382,286), cv::Scalar(255,255,255), cv::FILLED);
    cv::line(img, cv::Point(130,296), cv::Point(382,296), cv::Scalar(255,255,255), 2);
    cv::putText(img, "Sei la", cv::Point(180,270), cv::FONT_HERSHEY_DUPLEX, 1.5, cv::Scalar(255,0,128), 2);

    cv::imshow("Blue", img);

    cv::waitKey(0);
}