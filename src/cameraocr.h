#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <tesseract/baseapi.h>
#include <tesseract/strngs.h>
#include <iostream>

char* camera_ocr(cv::VideoCapture cap);
