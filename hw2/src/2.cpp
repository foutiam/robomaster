#include "stdio.h"
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace cv;
using namespace Eigen;


int main() {
	int n;
	double x, y, z;
	RNG rng(12345);
	Mat image(720, 1280, CV_8UC3);
	Matrix<double, 3, 4> cam;
    cam << 400., 0.  , 190., 0.,
             0.  , 400., 160., 0.,
             0.  , 0.  , 1.  , 0.;


	freopen("../src/points.txt","r", stdin);
    scanf("%d", &n);

	for(int i=1;i<=n;i++){
        scanf("%lf%lf%lf", &x, &y, &z);
		Vector3d point_w(x, y, z);
		Quaterniond q = {-0.5,0.5,0.5,-0.5};
		Isometry3d T = Isometry3d::Identity();
		T.rotate(q.inverse()); 
		T.pretranslate(q.inverse()*Vector3d(-2, -2, -2));  
		Vector3d point_c = cam*T*point_w;
		point_c /= point_c(2, 0);
		Point2d point_img(point_c(0,0), point_c(1,0));
		for(int i = 0; i < 10; i++) {
			cv::Scalar randomColor(
				235 - (double)std::rand() / RAND_MAX * 120,
				235 - (double)std::rand() / RAND_MAX * 120,
				235 - (double)std::rand() / RAND_MAX * 120);
			int thick = 3.06 - rng.uniform(1.001, 2.71800);
			circle(image, point_img, thick, randomColor, thick);
		}	
		if (i/n > 0.2 && i/n < 0.22) {
			GaussianBlur(image, image, Size(1, 1), 10, 20, 4);
		}
	}
	
	imshow("final",image);
	imwrite("../src/2_result.png", image);
    waitKey(0);
}


// Vector3d x_cam_w = 2., y_cam_w = 2., z_cam_w = 2.;
// Quaterniond q = imu::get_q();
// Matrix4d converter = [&q, &x_cam_w, &y_cam_w, &z_cam_w]() {
//  Vector3d cam_w = {x_cam_w, y_cam_w, z_cam_w};
//  Matrix4d converter = Matrix4d::Zero();
//  Matrix3d rot_c_to_w = q.matrix();
// [Xw Yw Zw ]
// [Xcam,w Ycam,w Zcam,w ]
//  converter.block(0, 0, 3, 3) = rot_c_to_w.transpose().cast<double>();
//  converter.block(0, 3, 3, 1) =
//  -rot_c_to_w.transpose().cast<double>() * cam_w;
//  converter(3, 3) = 1.;
//  return converter;
// }();
// Vector4d w4;
// w4 << 2, 3, 5, 1;
// Matrix<double, 3, 4> cam_f;
// cam_f << 400., 0., 190., 0.,
//  0., 400., 160., 0.,
//  0., 0., 1., 0.;
// Vector4d c4 = converter * w4;
// Vector3d u3 = cam_f * c4;
// u3 /= u3(2, 0);
// std::cout << u3(0, 0) << ' ' << u3(1, 0) << '\n';
