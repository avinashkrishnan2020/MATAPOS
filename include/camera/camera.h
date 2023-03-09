#ifndef CAMERA_H
#define CAMERA_H

#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>


typedef struct{
  std::string type;
  std::string data;
  std::vector <cv::Point> location;
} Code;


class Camera {

public:

	// Constructor with default settings
	Camera();

	// Constructor
	Camera(int deviceId, int apiId);

	// destructor
	~Camera();

	// starts frame acquisition process
	void start();

	// stops frame acquisition
	void stop();

	// start running camera and acquiring frames
	void runCamera();

	// qrcode decode callback
	void qrDecoderCallback(cv::Mat frame);

	void decodeQRAndBarcode(cv::Mat &frame);

	void prepareForDecoding(cv::Mat &frame);

private:

	std::vector<Code> decodedEntities;
	
	// zbar image scanner
  	ImageScanner imageScanner;
	
	// gray image for decoding
	cv::Mat grayImage;

	// zbar image wrapper
	Image zbarImageWrapper;

	int isRunning = 0;
	int deviceId;
	int apiId;

	cv::VideoCapture videoCapture;
	std::thread cameraThread;
};

#endif