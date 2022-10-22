#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const int WIDTH = 215*6;
const int HEIGHT = 72*6;

vector<Point2f> get_blue(const Mat &img);
int dis(int cx, int cy, int tx, int ty);
Mat do_transform(const Mat &img, const vector<Point2f> &pts);
Mat nearestNeighRotate(Mat &img, float angle);

int main() {
	Mat img = imread("../src/1.png");
    // Mat retImg = nearestNeighRotate(img, -30.f);
	auto points = get_blue(img);
	auto res = do_transform(img, points);
	imshow("result", res);
	waitKey(0);
	imwrite("../src/1_result.png", res);
	return 0;
}

int dis(int cx, int cy, int tx, int ty) {
    return pow(pow(cx - tx, 2) + pow(cy - ty, 2), 0.5);

}

vector<Point2f> get_blue(const Mat &img) {
	// vertex
	Mat hsv, blue, open, denoise;
	cvtColor(img, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(105, 80, 60), Scalar(140, 255, 180), blue);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(1,1), Point(-1, -1));
    morphologyEx(blue, open, MORPH_OPEN, kernel);
	GaussianBlur(open, denoise, Size(5, 5), 80, 20, 4);
	// imshow("res", denoise);
	// waitKey(0);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(denoise,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE);

	// find max 
	double MAXarea = 0;
	int ID = 0;
	for(int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		if (MAXarea < area){
			MAXarea = area;
			ID = i;
		}
	}

    int sumx = 0;
    int sumy = 0;
    for (int i = 0; i < contours[ID].size(); ++i) {
        sumx += contours[ID][i].x;
        sumy += contours[ID][i].y;
    }
    int centerx = sumx / contours[ID].size();
    int centery = sumy / contours[ID].size();

 // find vertex
    std::vector<cv::Point> vertex(4);
    int maxdis[4] = {0,0,0,0};
    for (int i = 0; i < contours[ID].size(); i++) {

        if (contours[ID][i].x < centerx && contours[ID][i].y < centery) { // left top point
            if (dis(centerx, centery, contours[ID][i].x, contours[ID][i].y) > maxdis[0]) {
                maxdis[0] = dis(centerx, centery, contours[ID][i].x, contours[ID][i].y);
                vertex[0].x = contours[ID][i].x;
                vertex[0].y = contours[ID][i].y;
            }
        } else if (contours[ID][i].x > centerx && contours[ID][i].y < centery) {  //  right top point
            if (dis(centerx, centery, contours[ID][i].x, contours[ID][i].y) > maxdis[1]) {
                maxdis[1] = dis(centerx, centery, contours[ID][i].x, contours[ID][i].y);
                vertex[1].x = contours[ID][i].x;
                vertex[1].y = contours[ID][i].y;
            }
        } else if (contours[ID][i].x > centerx && contours[ID][i].y > centery) {  //  right down point
            if (dis(centerx, centery, contours[ID][i].x, contours[ID][i].y) > maxdis[2]) {
                maxdis[2] = dis(centerx, centery, contours[ID][i].x, contours[ID][i].y);
                vertex[2].x = contours[ID][i].x;
                vertex[2].y = contours[ID][i].y;
            }
        } else if (contours[ID][i].x < centerx && contours[ID][i].y > centery) {  //  left down point
            if (dis(centerx, centery, contours[ID][i].x, contours[ID][i].y) > maxdis[3]) {
                maxdis[3] = dis(centerx, centery, contours[ID][i].x, contours[ID][i].y);
                vertex[3].x = contours[ID][i].x;
                vertex[3].y = contours[ID][i].y;
            }
        }
    }

	// //point vertex
    // for (auto &p: vertex) {
    //     circle(img, p, 2, Scalar(30, 55, 80), 1);
    // }
    // imshow("img", img);
    // waitKey(0);
	
	return {vertex[0], vertex[3], vertex[2], vertex[1]};

}

Mat do_transform(const Mat &img, const vector<Point2f> &pts) {
	std::vector<Point2f> plate;
	plate.emplace_back(Point(1, 1));
	plate.emplace_back(Point(1, HEIGHT));
	plate.emplace_back(Point(WIDTH, HEIGHT));
	plate.emplace_back(Point(WIDTH, 1));
 
	Mat mat = getPerspectiveTransform(pts, plate);
	Mat res;
	warpPerspective(img, res, mat, Size(WIDTH, HEIGHT));

	return res;
}

Mat nearestNeighRotate(Mat &img, float angle) {
	int len = (int)(sqrtf(pow(img.rows, 2) + pow(img.cols, 2)) + 0.5);

	Mat retMat = Mat::zeros(len, len, CV_8UC3);
	float anglePI = angle * CV_PI / 180;
	int xSm, ySm;

	for(int i = 0; i < retMat.rows; i++)
		for(int j = 0; j < retMat.cols; j++)
		{
			xSm = (int)((i-retMat.rows/2)*cos(anglePI) - (j-retMat.cols/2)*sin(anglePI) + 0.5);
			ySm = (int)((i-retMat.rows/2)*sin(anglePI) + (j-retMat.cols/2)*cos(anglePI) + 0.5);
			xSm += img.rows / 2;
			ySm += img.cols / 2;

			if(xSm >= img.rows || ySm >= img.cols || xSm <= 0 || ySm <= 0){
				retMat.at<Vec3b>(i, j) = Vec3b(0, 0);
			}
			else{
				retMat.at<Vec3b>(i, j) = img.at<Vec3b>(xSm, ySm);
			}
		}

	return retMat;
}