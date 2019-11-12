#include "gridproc.h"

GridProc::GridProc() {

}

GridProc::~GridProc() {

}

void GridProc::generateTails() {

    int margin = getMargin();
    int padding = getPadding();
    cv::Size num_tails = getNumTails();
    cv::Size size_tails = getSizeTails();
    int margin_ext = getExtMargin();
    
    int main_width = num_tails.width * size_tails.width + (num_tails.width - 1) * margin;
    int main_height = num_tails.height * size_tails.height + (num_tails.height - 1) * margin;
    
    setMainSize(cv::Size(main_width, main_height));
    
    std::vector <Tail> temp_tails;
    for ( int i = 0; i < num_tails.height; ++i) {
        for (int j = 0; j < num_tails.width; ++j) {
            
            cv::Rect temp_rect = cv::Rect(i * (size_tails.width + margin), j * (size_tails.height + margin),
                size_tails.width, size_tails.height);
            cv::Rect temp_rect2 = cv::Rect(padding, padding,
                temp_rect.width - padding * 2, temp_rect.height - padding * 2);
                
            if ( j == 0) {
                temp_rect2.y += margin_ext;
                temp_rect2.height -= margin_ext;
            } else if (j == (num_tails.height - 1)) {
                temp_rect2.height -= margin_ext;
            }
            
            if (i == 0) {
                temp_rect2.x += margin_ext;
                temp_rect2.width -= margin_ext;        
            } else if (i == (num_tails.width - 1)) {
                temp_rect2.width -= margin_ext;
            }
                
            temp_tails.push_back(Tail(temp_rect, temp_rect2));
        }
    }
    setTails(temp_tails);
    
}
