// basicproc.h

#include <vector>
#include <opencv2/core/core.hpp>
#ifndef BASICPROC_H
#define BASICPROC_H


class Tail {
public:
    Tail(cv::Rect);
    Tail(cv::Rect, cv::Rect);
    
    cv::Rect getBorderRect() { return border_rect; }
    cv::Rect getPaddingRect() { return padding_rect; }
    
private:
    cv::Rect border_rect;
    cv::Rect padding_rect;
};


class BasicProc {

public:
    BasicProc();
    virtual ~BasicProc();
    
    void setNumTails(cv::Size num_tails) { _num_tails = num_tails; }
    cv::Size getNumTails() { return _num_tails; };    
    
    void setSizeTails(cv::Size size_tails) { _size_tails = size_tails; }
    cv::Size getSizeTails() { return _size_tails; };
    
    void setPadding(int i) { _padding = i; }
    int getPadding() { return _padding; }
    void setColorPadding(cv::Scalar color_padding) { _color_padding = color_padding; }
    cv::Scalar getColorPadding() { return _color_padding; } 
    
    void setExtMargin(int i) { _ext_margin = i; }
    int getExtMargin() { return _ext_margin; }
    void setColorExtMargin(cv::Scalar ext_color_margin) { _ext_color_margin = ext_color_margin; }
    cv::Scalar getExtColorMargin() { return _ext_color_margin; }
    
    void setMargin(int i) { _margin = i; }
    int getMargin() { return _margin; }
    void setColorMargin(cv::Scalar color_margin) { _color_margin = color_margin; }
    cv::Scalar getColorMargin() { return _color_margin; }
       
    std::vector<Tail> getTails() { return _tails; } 
    virtual void generateTails() = 0;
    
    cv::Size getMainSize() { return _main_size; }
    
protected:

    void setMainSize(cv::Size main_size ) { _main_size = main_size; }
    void setTails(std::vector<Tail> tails ) { _tails = tails; }
    
private:
    
    cv::Size _num_tails;
    cv::Size _size_tails;
    
    int _padding = 0;
    cv::Scalar _color_padding = cv::Scalar(255, 225, 255);
    
    int _margin = 0;
    cv::Scalar _color_margin = cv::Scalar(0, 0, 0);
    
    int _ext_margin = 0;
    cv::Scalar _ext_color_margin = cv::Scalar(0, 0, 0);
    
    cv::Size _main_size;
    
    std::vector<Tail> _tails;
    
};

#endif

