#ifndef PREPROC_HPP
#define PREPROC_HPP


#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

enum TYPE_PREPROC: int {
	PREPROC_2D = 0,
	PREPROC_3D = 1
};

class Preproc{

public:

	Preproc();
	~Preproc();

	void preprocessingFrame(cv::Mat & in, cv::Mat &out);

	void setRotate(int r) { _rotate  = r; }
	int getRotate() { return _rotate; }

	cv::Rect2f getNormROI();
	void setNormROI(cv::Rect2f roi);

	int getChannels();
	void setChannels(int _ch);

	cv::Size getSize();
	void setSize(cv::Size _size);
	
	bool getFitFlag() { return _fit_flag; }
	void setFitFlag(bool flag) { _fit_flag = flag; }

	cv::Rect getROI() { return cv::Rect(_rect->x, _rect->y, _rect->width, _rect->height); }

	void rotateImage(cv::Mat &src, cv::Mat &dst, int rot_image = -1);
	void fitImage(cv::Mat &src, cv::Mat &dst);

	void setDebug(bool _flag) { _debug = _flag; }
	bool getDebug() { return _debug; }

private:

	void setROI( cv::Rect _r);

	cv::Rect2f * _norm_roi = nullptr;
	cv::Rect * _rect = nullptr;
	cv::Size * _size = nullptr;

	int _channels = 1;
	int _rotate = 0;

	bool _debug = false;
	
	bool _fit_flag = false;
};

class Preproc3D: public Preproc{

	void preprocessingFrame(cv::Mat & in3D, cv::Mat &out3D);

};


class BuilderPreproc {

	Preproc * build(int type_preproc) {
		switch (type_preproc) {
			case TYPE_PREPROC::PREPROC_2D:
				return new Preproc();
				break;
			case TYPE_PREPROC::PREPROC_3D:
				return new Preproc3D();
				break;
			default:
				std::cerr << "ERROR: invalid type of preproc.\n";
				throw;
				break;
		}
	}
};


#endif
