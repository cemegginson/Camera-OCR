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
    cv::Mat im1, im2;
    cap >> im1;

    // Double the contrast
    im1.convertTo(im2, -1, 2, 0);

    // Convert to Grayscale
    cv::cvtColor(im2, im1, CV_BGR2GRAY);

    /*
    Apply adaptive thresholding to isolate text.
    The last two arguments are the really important ones.
    The next to last argument is the size of the neighborhood used
    to calculate the threshold value for the pixel, and the last one
    is the constant that's subtracted from the mean
    */
    cv::adaptiveThreshold(im1, im2, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 65, 15);

    // cv::imwrite("output.jpg", im2);

    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage((uchar*)im2.data, im2.cols, im2.rows, 1, im2.cols);

    char* out = tess.GetUTF8Text();
    return out;
}
