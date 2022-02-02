#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int main(){
    float width = 250, height = 350;
    cv::Mat matrixKing, warpKing;
    cv::Mat matrixQueen, warpQueen;
    cv::Mat matrixNine, warpNine;
    cv::Mat matrixJack, warpJack;

    std::string imgPath = "../resources/cards.jpg";
    cv::Mat img = cv::imread(imgPath);

    cv::Point2f coordsKing[4] = { {529,142}, {771,190}, {405,395}, {674,457} };
    cv::Point2f wKingCoords[4] = { {0, 0}, {width, 0}, {0, height}, {width, height} };

    cv::Point2f coordsQueen[4] = { {62,324}, {338,278}, {88,632}, {404,572} };
    cv::Point2f wQueenCoords[4] = { {0, 0}, {width, 0}, {0, height}, {width, height} };

    cv::Point2f coordsNine[4] = { {740,382}, {1026,438}, {644,710}, {970,784} };
    cv::Point2f wNineCoords[4] = { {0, 0}, {width, 0}, {0, height}, {width, height} };

    cv::Point2f coordsJack[4] = { {774,104}, {1020,84}, {842,360}, {1116,328} };
    cv::Point2f wJackCoords[4] = { {0, 0}, {width, 0}, {0, height}, {width, height} };

    matrixKing = cv::getPerspectiveTransform(coordsKing, wKingCoords);
    cv::warpPerspective(img, warpKing, matrixKing, cv::Point(width, height));

    matrixQueen = cv::getPerspectiveTransform(coordsQueen, wQueenCoords);
    cv::warpPerspective(img, warpQueen, matrixQueen, cv::Point(width, height));

    matrixNine = cv::getPerspectiveTransform(coordsNine, wNineCoords);
    cv::warpPerspective(img, warpNine, matrixNine, cv::Point(width, height));

    matrixJack = cv::getPerspectiveTransform(coordsJack, wJackCoords);
    cv::warpPerspective(img, warpJack, matrixJack, cv::Point(width, height));

    
    for(int i = 0; i < 4; i++){
        cv::circle(img, cv::Point(coordsKing[i]), 10, cv::Scalar(0,0,255), cv::FILLED);
        cv::circle(img, cv::Point(coordsQueen[i]), 10, cv::Scalar(255,0,0), cv::FILLED);
        cv::circle(img, cv::Point(coordsNine[i]), 10, cv::Scalar(0,255,0), cv::FILLED);
        cv::circle(img, cv::Point(coordsJack[i]), 10, cv::Scalar(255,0,128), cv::FILLED);
    }
    

    cv::imshow("Original image", img);
    cv::imshow("King", warpKing);
    cv::imshow("Queen", warpQueen);
    cv::imshow("Nine", warpNine);
    cv::imshow("Jack", warpJack);
    cv::waitKey(0);
}