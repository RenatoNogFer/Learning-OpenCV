#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(){

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));

    std::string imgPath = "../resources/duck.png";
    cv::Mat img = cv::imread(imgPath);
    cv::Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

    // Color Conversion
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // Blur
    cv::GaussianBlur(img, imgBlur, cv::Size(7,7), 5, 0);

    // Edge detection
    cv::Canny(imgBlur, imgCanny, 50, 150);

    // Dilate
    cv::dilate(imgCanny, imgDilate, kernel);

    // Erode
    cv::erode(imgDilate, imgErode, kernel);

    cv::imshow("Normal Duck", img);
    cv::imshow("80s Duck", imgGray);
    cv::imshow("Myopic Duck", imgBlur);
    cv::imshow("Something Duck", imgCanny);
    cv::imshow("Fucking nightmare-ish Duck", imgDilate);
    cv::imshow("Where Duck", imgErode);

    cv::waitKey(0);
}