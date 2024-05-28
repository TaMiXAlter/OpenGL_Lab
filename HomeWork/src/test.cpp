#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
	String ImgPath = "/home/tami/Projects/OpenGL_Lab/HomeWork/OpenCVTexture/lena.png";
	Mat image = imread(ImgPath, IMREAD_COLOR);
	if (!image.data) {
		cout << "Can not load the image!" << std::endl;
		return -1;
	}
	namedWindow("Display Window", WINDOW_NORMAL);
	imshow("Display Window", image);
	waitKey(0);
	return 0;
}
