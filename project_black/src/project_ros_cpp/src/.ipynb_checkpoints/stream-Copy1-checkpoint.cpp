#include <iostream>
#include <stdlib.h>

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	// 카메라 영상 읽기위한 정의, jetson 시리즈는 gstreamer 사용해야해서 pipeline 정의.
	Mat img;
	const char* gst = "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)608, height=(int)608, format=(string)NV12, framerate=(fraction)60/1 ! nvvidconv flip-method=4 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";

	VideoCapture cap(gst);
	if(!cap.isOpened()) {
		cerr << "VideoCapture error\n";
	}
	
	while( 1 )
	{
		cap.read(img);
		if(img.empty()){
			cerr << "image is empty\n";
			return -1;
		}
		
		namedWindow("img", WINDOW_AUTOSIZE);
		imshow("img", img);
		waitKey(1);
	
	}
	destroyWindow("img");
	return 0;
}