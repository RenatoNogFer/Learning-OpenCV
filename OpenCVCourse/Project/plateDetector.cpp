#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

void main(){
    cv::VideoCapture cap(0);
    cv::Mat img;

    cv::CascadeClassifier plateCascade;
    plateCascade.load("resources/haarcascade_russian_plate_number.xml");


}