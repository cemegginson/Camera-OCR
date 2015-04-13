#include <iostream>
#include <string>
#include "cameraocr.h"

int main(int argc, char** argv) {

    cv::VideoCapture cap(1);
    if(!cap.isOpened()) {
        return -1;
    }

    // For testing on laptop
    // system("v4l2-ctl -d 1 -c white_balance_temperature_auto=0");

    // For use on Raspberry Pi
    system("v4l2-ctl -c white_balance_temperature_auto=0");

    while(true) {
        std::cout << camera_ocr(cap) << std::endl;
    }
    return 0;
}

char* camera_ocr(cv::VideoCapture cap) {
    // Set values to display only blue and pink panels
    int iLowH = 100;
    int iHighH = 179;

    int iLowS = 107;
    int iHighS = 255;

    int iLowV = 112;
    int iHighV = 255;


    cv::Mat imOrig;
    if(!cap.read(imOrig)) {
        std::cerr << "Failed to read image" << std::endl;
    }

    // Convert image to HSV format
    cv::Mat imHSV;
    cv::cvtColor(imOrig, imHSV, cv::COLOR_BGR2HSV);

    // Threshold the image
    cv::Mat imThresh;
    cv::inRange(imHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imThresh);

    // morphological opening (remove small objects from the foreground)
    cv::erode(imThresh, imThresh, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    cv::dilate(imThresh, imThresh, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

    // morphological closing (fill small holes in the foreground)
    cv::dilate(imThresh, imThresh, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    cv::erode(imThresh, imThresh, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

    // // Test code to display processed images
    // cv::imshow("Original", imOrig);
    // cv::imshow("Thresholded Image", imThresh);
    // // Gotta put this here to make imshow happy
    // if (cv::waitKey(30) == 27) {
    //     std::cout << "esc key is pressed by user" << std::endl;
    //     //break;
    // }

    // OCR
    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage((uchar*)imThresh.data, imThresh.cols, imThresh.rows, 1, imThresh.cols);

    char* out = tess.GetUTF8Text();
    return out;
}
