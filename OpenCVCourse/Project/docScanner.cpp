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

std::vector<cv::Point> reorder(std::vector<cv::Point> points){
    std::vector<cv::Point> newPoints;
    std::vector<int> sumPoints, subPoints;

    for(int i = 0; i < points.size(); i++){
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }

    newPoints.push_back(points[std::min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
    newPoints.push_back(points[std::max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
    newPoints.push_back(points[std::min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);  
    newPoints.push_back(points[std::max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 3

    return newPoints;
}

cv::Mat drawPoints(std::vector<cv::Point> points, cv::Mat img){
    for(int i = 0; i < points.size(); i++){
        cv::circle(img, points[i], 5, cv::Scalar (0, 0, 255), cv::FILLED);
        cv::putText(img, std::to_string(i), points[i], cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar (0, 0, 255), 2);
    }
    return img;
}

cv::Mat getWarp(cv::Mat img, std::vector<cv::Point> points, float width, float height){
    cv::Mat imgWarp;

    cv::Point2f oCoords[4] = {points[0], points[1], points[2], points[3]};
    cv::Point2f fCoords[4] = { {0.0f, 0.0f}, {width, 0.0f}, {0.0f, height}, {width, height}};

    cv::Mat matrix = cv::getPerspectiveTransform(oCoords, fCoords);
    cv::warpPerspective(img, imgWarp, matrix, cv::Point(width, height));

    return imgWarp;
}


int main(){
    std::string imgPath = "../resources/paper.jpg";
    cv::Mat imgOriginal = cv::imread(imgPath);
    std::vector<cv::Point> initialPoints, docPoints;
    float width = 420, height = 596;

    // Temporary scaling for easier image visualization
    cv::resize(imgOriginal, imgOriginal, cv::Size(), 0.5, 0.5);

    cv::Mat imgDil = preprocessing(imgOriginal);
    initialPoints = getContours(imgDil);
    docPoints = reorder(initialPoints);
    cv::Mat imgWarp = getWarp(imgOriginal, docPoints, width, height);

    // Crop to beautify result
    cv::Rect roi(5, 5, width - (2*5), height - (2*5));
    cv::Mat document = imgWarp(roi);

    cv::imshow("Image", imgOriginal);
    cv::imshow("Document", document);
    cv::waitKey(0);
}