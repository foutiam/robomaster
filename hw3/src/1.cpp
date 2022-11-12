#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "Eigen/Dense"
#include "opencv2/core/eigen.hpp"

using namespace cv;
using namespace Eigen;

const std::vector<cv::Point3d> PW_BIG{// 灯条坐标，单位：m //inline only available with ‘-std=c++17’ or ‘-std=gnu++17’
                                                {-0.115, 0.0265, 0.},
                                                {-0.115, -0.0265, 0.},
                                                {0.115, -0.0265, 0.},
                                                {0.115, 0.0265, 0.}};

int main() {
	cv::Mat src;
	cv::Mat camera_matrix;
	cv::Mat distort_matrix;
	cv::FileStorage reader("../src/hw3_t1/f_mat_and_c_mat.yml", cv::FileStorage::READ);
	reader["F"] >> camera_matrix;
	reader["C"] >> distort_matrix;


	src = imread("../src/hw3_t1/hero.jpg");
	std::cout << "got src" << std::endl;
	std::vector<cv::Point2f> corners;
	corners.push_back(cv::Point2f(575.508, 282.175));
	corners.push_back(cv::Point2f(573.93 , 331.819));
	corners.push_back(cv::Point2f(764.518, 337.652));
	corners.push_back(cv::Point2f(765.729, 286.741));
	imshow("Opencv Demo", src);
	cv::waitKey(100);

	cv::Mat rvec, tvec;
	cv::solvePnP(PW_BIG, corners, camera_matrix, distort_matrix, rvec, tvec);
	//objectPoints:		std::vector<cv::Point3d>    特征点物理坐标
	//imagePoints:  	std::vector<cv::Point2d>    特征点图像坐标，点对个数必须大于4
	//camera_matrix		相机内参：3*3的float矩阵
	//distort_matrix	相机畸变参数
	//rvec	输出的旋转向量。使坐标点从世界坐标系旋转到相机坐标系
	//tvec	输出的平移向量。使坐标点从世界坐标系平移到相机坐标系
	Eigen::Quaterniond q = { -0.0816168, 0.994363, -0.0676645, -0.00122528 };//w i j k 0.994363i + -0.0676645j + -0.00122528k
	Eigen::Vector3d T_n;
	cv2eigen(tvec, T_n);
	// std::cout << T_n << '\n';
	Vector3d t_imu = q.matrix().cast<double>() * T_n;
	std::cout << t_imu << '\n';
	return 0;
}
