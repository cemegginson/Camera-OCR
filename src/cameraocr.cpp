#include "cameraocr.h"

int main(int argc, char** argv) {

    cv::VideoCapture cap(0);
    if(!cap.isOpened()) {
        return -1;
    }

    while(1==1) {
        cv::Mat im;
        cap >> im;
        if (im.empty()) {
            std::cout << "Cannot open source image!" << std::endl;
            return -1;
        }

        cv::Mat contrast;
        im.convertTo(contrast, -1, 2, 0);
        //cv::imwrite("output.jpg", contrast);

        cv::Mat gray;
        cv::cvtColor(contrast, gray, CV_BGR2GRAY);

        cv::Mat blur;
        cv::GaussianBlur(gray, blur, cv::Size(35.0, 35.0), cv::BORDER_DEFAULT);

        cv::imwrite("output.jpg", blur);

        tesseract::TessBaseAPI tess;
        tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
        tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
        tess.SetImage((uchar*)blur.data, blur.cols, blur.rows, 1, blur.cols);

        char* out = tess.GetUTF8Text();
        std::cout << out << std::endl;
    }
    return 0;
}
