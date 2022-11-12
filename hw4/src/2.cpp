#include <iostream>
#include <opencv2/core/core.hpp>
#include "VO.h"

using namespace std;
using namespace cv;

int main(int argc,char** argv) {
    FileStorage params("../datapack/hw4_t2/camera.yaml", FileStorage::READ);
    Mat camera_matrix = params["K"].mat();
    Mat src1 = imread("../datapack/hw4_t2/stereo-data/0_orig.jpg");
    Mat src2 = imread("../datapack/hw4_t2/stereo-data/1_orig.jpg");
    Mat depth1 = imread("../datapack/hw4_t2/stereo-data/0_dpt.tiff",IMREAD_UNCHANGED);
    Mat depth2 = imread("../datapack/hw4_t2/stereo-data/1_dpt.tiff",IMREAD_UNCHANGED);
    
    Mat rvec, tvec, R;
    find_PnP(src1, depth1, src2, depth2, camera_matrix, rvec, tvec);
    Rodrigues(rvec, R);
    process_Stitch_project(src1, depth1, src2, depth2, camera_matrix, R, tvec, "output");
    return 0;
}