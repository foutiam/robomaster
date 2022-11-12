#include <opencv2/opencv.hpp>

int main(){
	cv::Mat img = cv::imread("../src/apple.png");
	assert(img.channels()==3);
	
	cv::Mat hsv;
	cv::cvtColor(img,hsv,cv::COLOR_RGB2HSV);
	cv::Mat Y,R1,R2;
	cv::inRange(hsv,cv::Scalar(96,120,100),cv::Scalar(125,255,255),Y);
	cv::inRange(hsv,cv::Scalar(125,43,46),cv::Scalar(154,255,255),R1);
	cv::inRange(hsv,cv::Scalar(100,200,100),cv::Scalar(120,255,160),R2);

	cv::Mat ones_mat=cv::Mat::ones(cv::Size(img.cols,img.rows),CV_8UC1);
	cv::Mat grey = 255 * (ones_mat - (ones_mat - Y/255).mul(ones_mat - R1/255));
	grey = 255 * (ones_mat - (ones_mat - grey/255).mul(ones_mat - R2/255));

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(13, 13), cv::Point(-1, -1));
	cv::morphologyEx(grey, grey, cv::MORPH_OPEN, kernel);

	// find MAX
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(grey,contours,hierarchy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
	double MAXarea = 0;
	int ID = 0;
	for(int i = 0; i < contours.size(); i++){
		double area = cv::contourArea(contours[i]);
		if (MAXarea < area){
			MAXarea = area;
			ID = i;
		}
	}
	cv::Rect rect = cv::boundingRect(contours[ID]);
	cv::rectangle(img,rect,cv::Scalar(255,255,255),3);

	cv::imshow("output", img) ;
	cv::waitKey();
	return 0;
}