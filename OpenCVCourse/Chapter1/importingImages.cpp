#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(){

    std::string imgPath = "../resources/duck.png";
    cv::Mat img = cv::imread(imgPath);
    cv::imshow("Round duck", img);
    cv::waitKey(0);

}
