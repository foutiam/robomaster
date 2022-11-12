#include <opencv2/opencv.hpp>

struct Video {
    cv::Mat Filter(const cv::Mat &img);
    cv::Mat FindBullet(const cv::Mat &img,cv::Mat &src);
};

int main() {
    cv::VideoCapture capture("../src/video.mp4");
	assert(capture.isOpened());
    Video process;
    cv::Mat src;
    cv::VideoWriter writer("../src/3_output.avi",cv::VideoWriter::fourcc('M','J','P','G'),
        20,cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH),
        capture.get(cv::CAP_PROP_FRAME_HEIGHT)), true);

    while (capture.read(src)) {
        src = process.FindBullet(process.Filter(src), src);
        cv::imshow("output", src);
        writer << src;
        cv::waitKey(100);
    }
    writer.release();
    capture.release();
    return 0;
}

cv::Mat Video::Filter(const cv::Mat &img) {
    // grey
    cv::Mat grey;
    cv::cvtColor(img, grey, cv::COLOR_BGR2GRAY);
    // binarization
    cv::Mat binarization;
    cv::threshold(grey, binarization, 125, 155, cv::THRESH_BINARY);
    return binarization;
}

cv::Mat Video::FindBullet(const cv::Mat &img,cv::Mat &src) {
    // finding bullets
    std::vector<std::vector< cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat drawer = cv::Mat::zeros(cv::Size(src.cols, src.rows), CV_8UC3);
    std::vector<cv::RotatedRect> rects;

    cv::findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    for (uint32_t i = 0; i != -1; i = hierarchy[i][0]) {
        cv::drawContours(drawer, contours, i, cv::Scalar(255, 255, 255));
        //filter
        if (cv::arcLength(contours[i], true) >= 20) {
            rects.push_back(cv::minAreaRect(contours[i]));
        }
    } 
    //rect
    for (auto &rect: rects) {
        auto *vertices = new cv::Point2f[4];
        rect.points(vertices);
        for (int i = 0; i < 4; ++i) {
            cv::line(src, vertices[i], vertices[(i + 1) % 4], cv::Scalar(255, 255, 255));
        }
        //mid
        cv::circle(src, rect.center, 3, cv::Scalar(255, 255, 255), 2);
    }
    return src;
}