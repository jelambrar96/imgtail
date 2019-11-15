#include "preproc.h"



Preproc::Preproc() {
	std::cout << "PREPROC CONSTRUCTOR" << std::endl;
}
Preproc::~Preproc() {
	std::cout << "PREPROC DESTRUCTOR" << std::endl;
	if (_size != nullptr) {
		delete _size;
	}
	if (_norm_roi != nullptr) {
		delete _norm_roi;
	}
	if (_rect != nullptr) {
		delete _rect;
	}
}

void Preproc::preprocessingFrame(cv::Mat & in, cv::Mat &out) {

	bool debug = getDebug();
	if (debug) {
		std::cout << "Init preprocessing...\n";
		std::cout << "in.size(): " << in.size()  << std::endl;
	}

	cv::Mat temp_out;
	int channels = getChannels();

	if (!in.data) {
		std::cerr << "ERROR: No DATA on input frame.\n";
		throw;
	}
	// bool cloned = false;
	if ( channels == 1 && in.channels() == 3) {
		// std::cout << "changing channels" << std::endl;
		if (debug) {
			std::cout << "changing channels" << std::endl;
			std::cout << "temp_out.size(): " << temp_out.size()  << std::endl;
		}
		cv::cvtColor(in, temp_out, CV_BGR2GRAY);
		// cloned = true;
	} else {
		if (debug) {
			std::cout << "same channels" << std::endl;
			std::cout << "temp_out.size(): " << temp_out.size()  << std::endl;
		}
		cv::swap(in, temp_out);
		// cloned = true;
	}
	// std::cout << "temp_out.size(): " << temp_out.size()  << std::endl;
	if (_norm_roi != nullptr) {
		cv::Size _in_size = temp_out.size();
		if (_rect == nullptr) {
			if (debug) {
				std::cout << "setting roi" << std::endl;
				std::cout << "temp_out.size(): " << temp_out.size()  << std::endl;
			}
			cv::Rect roi = cv::Rect(
					static_cast<int>(_norm_roi->x * _in_size.width),
					static_cast<int>(_norm_roi->y * _in_size.height),
					static_cast<int>(_norm_roi->width * _in_size.width),
					static_cast<int>(_norm_roi->height * _in_size.height));
			setROI(roi);
			if (debug) {
                std::cout << "roi: " << roi << std::endl;
            }
		}
		if (debug) {
			std::cout << "selection roi" << std::endl;
		}

		// std::cout << "selection roi" << std::endl;
		temp_out = temp_out(getROI());
		if (debug) {
			std::cout << "temp_out.size(): " << temp_out.size()  << std::endl;
		}
	}

	if (!getRotate()) {
		rotateImage(temp_out, temp_out);
	}

	if (_size != nullptr) {
	
	    if (getFitFlag()) {
	        if (debug) {
	            std::cout << "fitting image...\n";
	        }
	        fitImage(temp_out, temp_out);
	    }
	
		if (debug) {
			std::cout << "resize of image " << std::endl;
		}
		// std::cout << "resize of image " << std::endl;
		cv::resize(temp_out, temp_out, getSize(), getTypeResize());
		// cloned = true;
		if (debug) {
			std::cout << "temp_out.size(): " << temp_out.size()  << std::endl;
		}
		// cv::resize(temp_out, temp_out, getSize());
	}
	if (debug) {
		std::cout << "resize of image " << std::endl;
		std::cout << "final temp_out.size(): " << temp_out.size()  << std::endl;
		std::cout << "swap image " << std::endl;
	}
	cv::swap(temp_out, out);
	if (debug) {
		std::cout << "finish preprocessing image." << std::endl << std::endl;
	}
	// temp_out = temp_out.clone();
}

cv::Rect2f Preproc::getNormROI() {
	if (_norm_roi != nullptr) {
		return cv::Rect2f(_norm_roi->x, _norm_roi->y, _norm_roi->width, _norm_roi->height);
	}
	std::cerr << "ERROR, NO ROILOADED" << std::endl;
	throw;
}
void Preproc::setNormROI(cv::Rect2f roi) {
	// cv::Rect2f temp_roi = roi;
	_norm_roi = new cv::Rect2f(roi);
    _rect = nullptr;
}

int Preproc::getChannels() {
	return _channels;
}
void Preproc::setChannels(int _ch) {
	_channels = _ch;
}

cv::Size Preproc::getSize() {
	if (_size != nullptr) {
		return cv::Size(_size->width, _size->height);
	}
	std::cerr << "ERROR, NO SIZE LOADED" << std::endl;
	throw;
}
void Preproc::setSize(cv::Size size) {
	_size = new cv::Size(size.width, size.height);
	// _size = &_size;
}

void Preproc::setROI(cv::Rect _r) {
	_rect = new cv::Rect(_r.x, _r.y, _r.width, _r.height);
}

void Preproc::rotateImage(cv::Mat &src, cv::Mat &dst, int rotate_flag) {

	if (rotate_flag  == -1) {
		rotate_flag = getRotate();
	}

	switch(rotate_flag) {
	case 0:
		// cv::swap(src, dst);
		dst = src.clone();
		break;

	case 1:
		cv::transpose(src, dst);
		cv::flip(dst, dst, 0);
		break;

	case 2:
		cv::flip(src, dst, -1);
		break;

	case 3:
		cv::transpose(src, dst);
		cv::flip(dst, dst, 1);
		break;

	default:
		break;
	}
	
}

void Preproc::fitImage(cv::Mat &src, cv::Mat &dst) {
    
    cv::Size in_size = src.size();
    cv::Size out_size = getSize();
    
    double ratio_in = static_cast<double>(in_size.height) / in_size.width;
    double ratio_out = static_cast<double>(out_size.height) / out_size.width;
    
    cv::Mat temp;
    
    if (ratio_in < ratio_out) {
        // int hroi = in_size.wi
        int w_roi = in_size.height * out_size.width / out_size.height;
        cv::Rect roi((in_size.width - w_roi) / 2, 0, w_roi, in_size.height );
        temp = src(roi);
        
    } else if (ratio_in > ratio_out) {
        int h_roi = in_size.width * out_size.height / out_size.width;
        cv::Rect roi(0, (in_size.height - h_roi) / 2, in_size.width, h_roi);
        temp = src(roi);
        
    } else {
        temp = src;
    }
    
    cv::swap(temp, dst);
    
}


void Preproc3D::preprocessingFrame(cv::Mat & in, cv::Mat &out) {

	// cv::Mat temp_out;

	cv::Size in_size = in.size();
	int w = in_size.width / 2;

	cv::Mat inl = in(cv::Rect(0, 0, w, in_size.height));
	cv::Mat inr = in(cv::Rect(w, 0, w, in_size.height));

	cv::Mat outl, outr;
	Preproc::preprocessingFrame(inl, outl);
	Preproc::preprocessingFrame(inr, outr);

	cv::hconcat(outl, outr, out);

}

