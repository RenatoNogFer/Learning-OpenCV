#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

int main(){
    /*
    std::string imgPath = "../resources/index.jpeg";
    cv::Mat img = cv::imread(imgPath);
    */

    cv::VideoCapture webcam(0);
    cv::Mat tempImg;

    cv::CascadeClassifier faceCascade;
    faceCascade.load("../resources/haarcascade_frontalface_default.xml");

    if(faceCascade.empty()) {std::cout << "xml file not loaded" << std::endl;};

    std::vector<cv::Rect> faces;
    while(1){
        webcam.read(tempImg);

        faceCascade.detectMultiScale(tempImg, faces, 1.1, 10);

        for(int i = 0; i < faces.size(); i++){
            cv::rectangle(tempImg, faces[i].tl(), faces[i].br(), cv::Scalar(255,0,128), 2);    
        }

        cv::imshow("Face", tempImg);
        cv::waitKey(1);       
    }
    

}
