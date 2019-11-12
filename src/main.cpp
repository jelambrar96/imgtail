


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "jproc/jproc.h"
#include "preproc/preproc.h"

namespace fs = boost::filesystem;

// headers
bool isFileExist (const std::string& name);
void create_dir (std::string);
std::string time_stamp (const char *format);

//main
int main(int argc, char ** argv) {
    
    std::cout << "Init app..\n";
    if (argc < 1) {
        std::cerr << "ERROR: No config file argument.\n";
        return -1;
    }
    std::string confname = argv[1];
    std::cout << std::endl << "Opening file: " << confname << std::endl << std::endl;
    if (!isFileExist(confname)) {
        std::cerr << "ERROR: config file does not exist.\n";
        return -1;
    }
    
    while (true) {
        
        int type_process = 0; // GRID
        int showflag = false;
        int saveflag = false;
        std::string image_filename = "";
        int htails = 0;
        int vtails = 0;
        int width_tails = 0;
        int height_tails = 0;
        int padding = 0;
        int paddingcolor = 255;
        int margincolor = 0;
        int margin = 0;
        int margin_ext = 0;
        int margin_ext_color = 255;
        
        std::vector<float> windows_limits = {};
        
        cv::FileStorage fs(confname, 0);
        fs["image"] >> image_filename;     
        fs["type_process"] >> type_process;
        fs["showflag"] >> showflag;
        fs["saveflag"] >> saveflag;
        fs["htails"] >> htails;
        fs["vtails"] >> vtails;
        fs["width_tails"] >> width_tails;
        fs["height_tails"] >> height_tails;
        fs["padding"] >> padding;
        fs["margin"] >> margin;
        fs["window_limits"] >> windows_limits;
        fs["paddingcolor"] >> paddingcolor;
        fs["margincolor"] >> margincolor;
        fs["margin_ext_color"] >> margin_ext_color;
        fs["margin_ext"] >> margin_ext;
        fs.release();
        
        if (!isFileExist(image_filename)) {
            std::cerr << "ERROR: image file does not exist.\n";
            fs.release();
            return -1;
        }
               
        std::cout << "paddingcolor: " << paddingcolor << "\n";
        
        std::cout << "creating process object.\n";
        BasicProc *process = FactoryProcess::getProcess(type_process);
        
        process->setSizeTails(cv::Size(width_tails, height_tails));
        process->setNumTails(cv::Size(htails, vtails));
        process->setPadding(padding);
        process->setMargin(margin);
        process->setExtMargin(margin_ext);
        
        process->generateTails();
        cv::Size main_size = process->getMainSize();
        std::vector<Tail> tails_image = process->getTails();


        Preproc preproc;
        preproc.setDebug(false);
        preproc.setSize(main_size);
        preproc.setNormROI(cv::Rect2f(cv::Point2f(windows_limits[0], windows_limits[1]),
            cv::Point2f(windows_limits[2], windows_limits[3])));
        preproc.setFitFlag(true);
        preproc.setChannels(3);

        cv::Mat template_image = cv::imread(image_filename);
        preproc.preprocessingFrame(template_image, template_image);
        
        // cv::resize(template_image, template_image, main_size);
        
        cv::Mat final_image(template_image.rows, template_image.cols, CV_8UC3,
            cv::Scalar(margincolor, margincolor, margincolor));
        
        for (Tail item_tail: tails_image) {
            
            cv::Rect item_rect = item_tail.getBorderRect();
            // std::cout << "ITEM RECT\n" << item_rect << "\n";
            
            cv::Mat temp_image(item_rect.height, item_rect.width, CV_8UC3,
                cv::Scalar(paddingcolor, paddingcolor, paddingcolor));
                
            // cv::Rect temp_rect = cv::Rect(item_rect.x + padding, item_rect.y + padding,
            //     item_rect.width - 2 * padding, item_rect.height - 2 * padding); 
            cv::Rect temp_rect = item_tail.getPaddingRect();
                
            // std::cout << "TEMP RECT\n" << temp_rect << "\n\n";
            
            cv::Rect template_rect = temp_rect;
            template_rect.x = item_rect.x + temp_rect.x;
            template_rect.y = item_rect.y + temp_rect.y;
                
            template_image(template_rect).copyTo(temp_image(temp_rect));
            
            // cv::imshow("temp_image", temp_image);
            // cv::waitKey(0);    
            
            temp_image.copyTo(final_image(item_rect));
            
            // cv::namedWindow("final_image", 0);
            // cv::imshow("final_image", final_image);    
            // cv::waitKey(0);
            
        }
        
        if (showflag) {    
            
            cv::namedWindow("final_image", 0);
            cv::imshow("final_image", final_image);    
            char key_pressed = cv::waitKey(0);
            
            if (key_pressed == 'q' || key_pressed == 'k') {
                break;
            } else if (key_pressed == 's' && saveflag) {
                
                std::string output_folder = "output_" + time_stamp("%y%m%d_%H%M%S") + "/";
                create_dir(output_folder);

                int kmax = tails_image.size();
                int cf = std::to_string(kmax).size();
                
                for (int k = 0; k < kmax; ++k) {
                    cv::Rect border_rect = tails_image[k].getBorderRect();
                    cv::Mat tmp_image = final_image(border_rect);
                    //
                    std::string strnum = std::to_string(k);
                    while (strnum.size() < cf ) {
                        strnum = "0" + strnum;
                    }
                    cv::imwrite(output_folder + "image_" + strnum + ".jpg", tmp_image);
                    
                }
                
                cv::Mat temp_image_final;
                preproc.setSize(cv::Size(width_tails, height_tails));
                preproc.setNormROI(cv::Rect2f(0, 0, 1, 1));
                preproc.setFitFlag(false);
                preproc.setDebug(false);
                preproc.preprocessingFrame(final_image, temp_image_final);
                cv::imwrite(output_folder + "final_image.jpg", temp_image_final);
                
                break;
                
            }
            
            cv::destroyAllWindows();

        } else {
            break;
        }
                    


    }
    
    return 0;
}

bool isFileExist (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void create_dir( std::string input ) {
	fs::path p(input);

	try {
		fs::file_status s = fs::status(p);
		std::cout << "boolalpha: " << std::boolalpha << " - isdir: " << fs::is_directory(s) << std::endl;
		fs::create_directory(p);
	} catch (fs::filesystem_error &e) {
		std::cerr << e.what() << std::endl;
	}
}

std::string time_stamp (const char *format)
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,80, format,timeinfo);
	std::string str(buffer);
	return str;
}
