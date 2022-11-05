#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>

using namespace std;
using namespace cv;
using namespace Eigen;

int main()
{
	std::freopen("../src/hw3_t2/dollar.txt","r",stdin);
    double src;
    std::vector<double> data;
    while(cin >> src){
        data.push_back(src);
		
    }
	// std::cout << data << std::endl;

 // calculate speed
	const int Z_N = 1, X_N = 2;
	Matrix<double, X_N, 1> X;
	Matrix<double, X_N, X_N> A;
	Matrix<double, X_N, X_N> P;
	Matrix<double, X_N, X_N> R;
	Matrix<double, X_N, Z_N> K;
	Matrix<double, Z_N, X_N> C;
	Matrix<double, Z_N, Z_N> Q;
	X << data[0], 0;
	A << 1, 1, 0, 1;
	C << 1, 0;
	R << 2, 0, 0, 2;
	Q << 10;
	// Zk = CXk
	double rate;
	for (int i = 1; i < data.size(); i++) {
		// 更新预测
		Matrix<double, X_N, 1> X_k = A * X;
		P = A * P * A.transpose() + R;
		// 更新观测
		K = P * C.transpose() * (C * P * C.transpose() + Q).inverse();
		Matrix<double, Z_N, 1> Z{data[i]};
		X = X_k + K * (Z - C * X_k);
		P = (Matrix<double, X_N, X_N>::Identity() - K * C) * P;
		std::cout << "day " << i+1 << " predict: " << X[0] << "	predict delta: " << X[1] << std::endl;
		rate = rate + X[1]*( data.size() + i ) / (data.size() + ( data.size() - i ));
		std::cout << "\npredict: " << X_k << "\nrate: " << rate << std::endl;
	}
	rate = rate / data.size();
	Matrix<double, X_N, 1> X_k = A * X;
	std::cout << "predict for day "<< 40 << " : " << X_k[0] + rate * 10 << std::endl;
    std::fclose(stdin);
	return 0;
}
