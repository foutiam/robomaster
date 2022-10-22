#include "stdio.h"
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <sstream>
#include <fstream>
using namespace std;
using namespace cv;
using namespace Eigen;

void  txt_to_vectordouble(vector<vector<double>>& res, string pathname)
{
	ifstream infile;
	infile.open(pathname.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	vector<double> suanz;
	string s;
	while (getline(infile, s)) {
		istringstream is(s); //将读出的一行转成数据流进行操作
		double d;
		while (!is.eof()) {
			is >> d;
			suanz.push_back(d);
		}
		res.push_back(suanz);
		suanz.clear();
		s.clear();
	}
	infile.close();             //关闭文件输入流 
}
/*
目前已知许多点在世界坐标系下的坐标，然后在目前相机坐标系下的图像
两个运动，一方面点的三位坐标可以先乘一个函数，结束后函数值为1，比如100/i*(x,y,z),100帧
相机的变换矩阵可以进行旋转，最终旋转为q，{-0.5,0.5,0.5,-0.5}/100={-0.01,0.01,0.01,-0.01}*i+{0.5,-0.5,-0.5,0.5}           {-0.01*id+0.5,0.01*id-0.5,0.01*id-0.5,-0.01*id+0.5}

*/
int main()
{
    cv::VideoWriter writer("../dragon.avi",VideoWriter::fourcc('M','J','P','G'),20,cv::Size2d(720,1080),true);
	Eigen::Matrix<double, 3, 4> cam;
    cam<< 400., 0., 190., 0.,
             0., 400., 160., 0.,
             0., 0., 1., 0.;
	vector<vector<double>> data;
	txt_to_vectordouble(data, "../src/points.txt");
	double num=data[0][0];
    RNG rng(12345);
	cv::Mat image(1080,1680,CV_8UC3);
	cv::Mat image2(1080,1680,CV_8UC3);
	//下面就是世界坐标系下的各个点

	for(int id=1;id<=100;id++)
	{
		image2=image.clone();
	for(int i=1;i<data.size()-1;i++)
	{
		Eigen::Vector3d point_w(data[i][0]*10000/id/id,data[i][1]*10000/id/id,data[i][2]*10000/id/id);
		Eigen::Quaterniond q={-0.004*id-0.1,0.004*id+0.1,0.004*id+0.1,-0.004*id-0.1};
		Isometry3d T = Isometry3d::Identity();
		T.rotate(q.inverse()); 
		T.pretranslate(q.inverse()*Vector3d(-3+0.01*id, -3+0.01*id, -3+0.01*id));  
		Eigen::Vector3d point_c = cam*T*point_w;
		cv::Point2d point_img(point_c(0,0)/point_c(2.0),point_c(1,0)/point_c(2,0));
        for(int i = 0; i < 10; i++) {
			cv::Scalar randomColor(
				235 - (double)std::rand() / RAND_MAX * 120,
				235 - (double)std::rand() / RAND_MAX * 120,
				235 - (double)std::rand() / RAND_MAX * 120);
			int thick = 3.06 - rng.uniform(1.001, 2.71800);
			cv::circle(image2, point_img, thick, randomColor, thick);
		}	
		if (i/data.size() > 0.2 && i/data.size() < 0.22) {
			GaussianBlur(image2, image2, Size(1, 1), 10, 20, 4);
		}
	}
	cv::imshow("final",image2);
	cv::waitKey(100); 
	string Img_Name = "/home/wyx/homework/work2/3/" +to_string(id)+".png";
	// cv::imwrite(Img_Name,image2);
	writer.write(image2);
	}
	for(int id=1;id<=40;id++)
	{
		cv::imshow("final",image2);
		cv::waitKey(5); 
		writer.write(image2);
	}
    writer.release();
    cv::destroyAllWindows();
    cv::waitKey(0);
}