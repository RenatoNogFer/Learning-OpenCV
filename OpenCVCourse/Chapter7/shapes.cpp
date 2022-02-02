#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

cv::Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

void getContours(cv::Mat imgDil, cv::Mat img){
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    int area, objCor;
    float peri;

    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    //cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 4);

    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());
    std::string objType;

    for(int i = 0; i < contours.size(); i++){
        area = cv::contourArea(contours[i]);

        if(area > 1000){
            peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            boundRect[i] = cv::boundingRect(conPoly[i]);
            
            objCor = (int) conPoly[i].size();

            if(objCor == 3){objType = "Triangle";}
            else if(objCor == 4){objType = "Rectangle";}
            else if(objCor > 4){objType = "Circle";}

            cv::drawContours(img, conPoly, i, cv::Scalar(255,0,255), 2);
            cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0,255,0), 2);
            cv::putText(img, objType, { boundRect[i].x, boundRect[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 0.75, cv::Scalar{255, 0, 128}, 2);

        }
    }
}

int main(){

    std::string imgPath = "../resources/shapes.png";
    cv::Mat img = cv::imread(imgPath);

    // Color Conversion
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // Blur
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3,3), 3, 0);

    // Edge detection
    cv::Canny(imgBlur, imgCanny, 25, 75);

    // Dilate
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::dilate(imgCanny, imgDilate, kernel);

    getContours(imgDilate, img);

    cv::imshow("Shapes", img);
    cv::waitKey(0);

}