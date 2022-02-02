#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int main(){
    std::string imgPath = "../resources/duck.png";
    cv::Mat img = cv::imread(imgPath);
    cv::Mat imgResize, imgResize2, imgResizeMult;
    cv::Mat imgCrop;

    // getting image size
    // std::cout << img.size() << std::endl;

    // Resize
    cv::resize(img, imgResize, cv::Size(640, 480));
    cv::resize(img, imgResize2, cv::Size(192, 168));
    cv::resize(img, imgResizeMult, cv::Size(), 0.5, 0.75);

    // Crop
    cv::Rect ROI(100, 100, 100, 100);
    imgCrop = img(ROI);

    cv::imshow("Original Duck", img);
    cv::imshow("Big Duck", imgResize);
    cv::imshow("Smol Duck", imgResize2);
    cv::imshow("Not so smol Duck", imgResizeMult);
    cv::imshow("Cropped Duck (rip)", imgCrop);

    cv::waitKey(0);

}