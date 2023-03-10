#define DEBUG

#include "camera/camera.h"

#include <thread>
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <memory>
#include <thread>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <zbar.h>


void Camera::decodeQRAndBarcode(cv::Mat &frame) {
 	
	//prepareForDecoding(frame);
 
	// configure zbar image scanner
	zbar::ImageScanner imageScanner;
 	imageScanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

 	// convert frame to gray image
 	cv::Mat grayImage;
 	cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);

	  // zbarImageWrapper
	  zbar::Image zbarImageWrapper(frame.cols, frame.rows, "Y800", (uchar *)grayImage.data, frame.cols * frame.rows);
	  // Scan the image for barcodes and QRCodes
	  int n = imageScanner.scan(zbarImageWrapper);
	 
	  for(zbar::Image::SymbolIterator symbol = zbarImageWrapper.symbol_begin(); symbol != zbarImageWrapper.symbol_end(); ++symbol)
	  {
		Code code;
	 
		code.type = symbol->get_type_name();
		code.data = symbol->get_data();
	 
		#ifdef DEBUG
			// Print code type and decoded value
			std::cout << std::endl << "Type : " << code.type << std::endl;
			std::cout << std::endl << "Data : " << code.data << std::endl;
		#endif
	 
		
		
		for(int i=0; i<symbol->get_location_size(); i++){
				code.location.push_back(cv::Point(symbol->get_location_x(i), symbol->get_location_y(i)));
		}
		decodedEntities.push_back(code);
	  }
}


Camera::Camera(int deviceId, int apiId) {
	deviceId = deviceId;
	apiId = apiId;

}

Camera::Camera() {
	deviceId = 0;
	apiId = cv::CAP_ANY;
	
	#ifdef DEBUG
		std::cout << "deviceId: " << deviceId << std::endl;
		std::cout << "apiId: " << apiId << std::endl;
	#endif	
}

void Camera::qrDecoderCallback(cv::Mat frame) {
	cv::QRCodeDetector qrDecoder = cv::QRCodeDetector();
	std::string data = qrDecoder.detectAndDecode(frame);
	if(data.length() > 0) {
		std::cout << "Decoded QR code = " << data;
	} 
}

void Camera::runCamera() {
	
	while(isRunning){
		
		cv::Mat frame;
		videoCapture.read(frame);
		if(frame.empty()) {

			#ifdef DEBUG
				std::cerr << std::endl << "empty frame!" << std::endl;
			#endif
		}

		imshow("Video Player", frame);
		if (cv::waitKey(5) >= 0){
			stop();
		}
        
		//qrDecoderCallback(frame);

		// Find and decode barcodes and QR codes
		decodeQRAndBarcode(frame);


	}
}


void Camera::start() {
	
	videoCapture.open(deviceId, apiId);
	

	if(videoCapture.isOpened()) {
		
		#ifdef DEBUG
			std::cout << std::endl << "Camera opened successfully!" << std::endl;
		#endif
		
		isRunning = 1;
	}
	else {
		
		#ifdef DEBUG
			std::cerr << std::endl << "Error occured...Unable to open camera..." << std::endl;
		#endif

		return;
	}
	
	// run camera in a separate thread
	cameraThread = std::thread(&Camera::runCamera, this);

}

void Camera::stop() {
	isRunning = 0;
}

 
Camera::~Camera() {
	
	#ifdef DEBUG
		std::cout << std::endl << "Inside Camera destructor" << std::endl;
		std::cout << std::endl << "isRunning: " << isRunning << std::endl;
	#endif
	
	cameraThread.join();
}
