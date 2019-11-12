#include "basicproc.h"

Tail::Tail(cv::Rect rectangle) {
    border_rect = rectangle;
    padding_rect = cv::Rect(0, 0, rectangle.width, rectangle.height);
}

Tail::Tail(cv::Rect rect1, cv::Rect rect2) {
    border_rect = rect1;
    padding_rect = rect2;
}


BasicProc::BasicProc() {

}

BasicProc::~BasicProc() {

}

