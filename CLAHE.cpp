

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <vector>       

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	cv::Mat inp_img = cv::imread("el4.jpg");
	if (!inp_img.data){
		cout << "Something Wrong";
		return -1;
	}
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Input Image", inp_img);
	
	cv::Mat clahe_img;
	cv::cvtColor(inp_img, clahe_img, CV_BGR2Lab);
	std::vector<cv::Mat> channels(3);
	cv::split(clahe_img, channels);  

	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(4);
	cv::Mat dst;
	clahe->apply(channels[0], dst);
	dst.copyTo(channels[0]);
	cv::merge(channels, clahe_img);

	cv::Mat image_clahe;
	cv::cvtColor(clahe_img, image_clahe, CV_Lab2BGR);
	
	namedWindow("CLAHE Image", CV_WINDOW_AUTOSIZE);
	cv::imshow("CLAHE Image", image_clahe);
	imwrite("out.jpg", image_clahe);
	cv::waitKey(0);
	destroyAllWindows();

	return 0;
}