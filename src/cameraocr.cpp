#include "cameraocr.h"

int main(int argc, char** argv) {

    cv::VideoCapture cap(0);
    if(!cap.isOpened()) {
        return -1;
    }
    cv::Mat im;
    cap >> im;
    if (im.empty()) {
        std::cout << "Cannot open source image!" << std::endl;
        return -1;
    }

    cv::Mat gray;
    cv::cvtColor(im, gray, CV_BGR2GRAY);

    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage((uchar*)gray.data, gray.cols, gray.rows, 1, gray.cols);

    char* out = tess.GetUTF8Text();
    std::cout << out << std::endl;

    return 0;
}
