#include <iostream>
#include <string>
#include "cameraocr.h"

int main(int argc, char** argv) {

    cv::VideoCapture cap(0);
    if(!cap.isOpened()) {
        return -1;
    }

    while(1==1) {
        std::cout << camera_ocr(cap) << std::endl;
    }
    return 0;
}

char* camera_ocr(cv::VideoCapture cap) {
    int iLowH = 100;
    int iHighH = 184;

    int iLowS = 107;
    int iHighS = 255;

    int iLowV = 112;
    int iHighV = 255;

    cv::Mat imOrig;
    if(!cap.read(orig)) {
        std::cerr << "Failed to read image" << std::endl;
    }

    // Convert image to HSV format
    cv::Mat imHSV;
    cvtColor(imOrig, imHSV, COLOR_BGR2HSV);

    // Threshold the image
    cv::Mat imThresh;
    inRange(imHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imThresh);

    // morphological opening (remove small objects from the foreground)
    erode(imThresh, imThresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imThresh, imThresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    // morphological closing (fill small holes in the foreground)
    dilate(imThresh, imThresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imThresh, imThresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    // Test code
    imshow("Original", imOrig);
    imshow("Thresholded Image", imThresh);

    // OCR
    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage((uchar*)imThresh.data, imThresh.cols, imThresh.rows, 1, imThresh.cols);

    char* out = tess.GetUTF8Text();
    return out;
}
