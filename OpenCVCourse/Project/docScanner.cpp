#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

cv::Mat preprocessing(cv::Mat img){
    cv::Mat imgGray, imgBlur, imgCanny, imgDil;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3,3), 3, 0);
    cv::Canny(imgBlur, imgCanny, 25, 75);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::dilate(imgCanny, imgDil, kernel);
    return imgDil;
}

std::vector<cv::Point> getContours(cv::Mat img){
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    std::vector<cv::Point> biggest;

    int area, maxArea = 0;

    for(int i = 0; i < contours.size(); i++){
        area = cv::contourArea(contours[i]);
        std::cout << area << std::endl;

        std::string objectType;

        if(area > 1000){
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
            
            if (area > maxArea && conPoly[i].size() == 4){
                biggest = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;
            }
        }
    }

    return biggest;
}

cv::Mat drawPoints(std::vector<cv::Point> points, cv::Mat img){
    for(int i = 0; i < points.size(); i++){
        cv::circle(img, points[i], 30, cv::Scalar (0, 0, 255), cv::FILLED);
        cv::putText(img, std::to_string(i), points[i], cv::FONT_HERSHEY_PLAIN, 10, cv::Scalar (0, 0, 255), 5);
    }
    return img;
}


int main(){
    std::string imgPath = "../resources/paper.jpg";
    cv::Mat imgOriginal = cv::imread(imgPath);
    std::vector<cv::Point> initialPoints;

    // Temporary scaling for easier image visualization
    cv::resize(imgOriginal, imgOriginal, cv::Size(), 0.5, 0.5);

    cv::Mat imgDil = preprocessing(imgOriginal);
    initialPoints = getContours(imgDil);
    cv::Mat imgPoints = drawPoints(initialPoints, imgOriginal);

    cv::imshow("Image", imgOriginal);
    cv::imshow("Image preprocessed", imgDil);
    cv::imshow("Image w/ points", imgPoints);
    cv::waitKey(0);
}