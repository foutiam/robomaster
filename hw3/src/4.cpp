#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void grading(string src, int num, int board_width, int board_height, int c);
vector<Point2f> founding(int board_n, Size board_size, string _src, int i, int c);

int main()
{
	grading("../datapack/calib1/", 19, 11, 8, 0);
	grading("../datapack/calib2/", 23, 9, 6, 1);
    return 0;
}

void grading(string src, int num, int board_width, int board_height, int c) {
	int board_n = board_width * board_height;
    Size board_size(board_width, board_height);
	Mat gray_img;
    vector<vector<Point2f>> points_useful;
    Size img_size;
	img_size.width = 1290;
	img_size.height = 1024;
	vector<Point2f> vec;
    for (int i = 0; i <= num; i++) {
		vec = founding(board_n, board_size, src, i, c);
		if (!vec.empty()) {
			points_useful.push_back(vec);
		}
    }
    cout << points_useful.size() << " useful chess boards" << endl;

    Size square_size(10, 10);
    std::vector<std::vector<Point3f>> point_grid_pos;
    std::vector<Point3f> point_grid_pos_buf;
    std::vector<int> point_count;
    Mat camera_matrix(3, 3, CV_32FC1, Scalar::all(0));
    Mat dist_coeffs(1, 5, CV_32FC1, Scalar::all(0));
    std::vector<Mat> rvecs;
    std::vector<Mat> tvecs;
    for (int i = 0; i < points_useful.size(); i++)
    {
        for (int j = 0; j < board_height; j++)
        {
            for (int k = 0; k < board_width; k++)
            {
                Point3f pt;
                pt.x = k * square_size.width;
                pt.y = j * square_size.height;
                pt.z = 0;
                point_grid_pos_buf.push_back(pt);
            }
        }
        point_grid_pos.push_back(point_grid_pos_buf);
        point_grid_pos_buf.clear();
        point_count.push_back(board_height * board_width);
    }
    std::cout << calibrateCamera(point_grid_pos, points_useful, img_size, camera_matrix, dist_coeffs, rvecs, tvecs) << std::endl;
    std::cout << camera_matrix << std::endl << dist_coeffs << std::endl;
    return;
}

vector<Point2f> founding(int board_n, Size board_size, string _src, int i, int c) {
	Size img_size;	
	Mat gray_img;
	bool found = false;
	vector<Point2f> points;
	string back = ".jpg";
	if (c) {
		back  = "_orig.jpg"; 
	}
	Mat src = imread(_src.append(to_string(i)).append(back));
	if (!i)
	{
		img_size.width = src.cols;
		img_size.height = src.rows;
		// cout << img_size.width <<" "<<img_size.height<< endl;
	}
	found = findChessboardCorners(src, board_size, points);
	// cout << points << endl;
	if (found && points.size() == board_n)
	{
		cvtColor(src, gray_img, COLOR_BGR2GRAY);
		find4QuadCornerSubpix(gray_img, points, Size(5, 5));
		Mat drawn_img = src.clone();
		drawChessboardCorners(drawn_img, board_size, points, found);
		imshow("Corners", drawn_img);
		waitKey(10);
	} else {
		cout << "Not All Corners Are Found In Image " << i << endl;
        points.clear();
	}
	// cout << points << endl;
	return points;
}