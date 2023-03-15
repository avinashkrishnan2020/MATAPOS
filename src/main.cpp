#include "camera/camera.h"
#include "barcodereader/barcodereader.h"

#include <opencv2/opencv.hpp>
#include "loadcell/LoadCell.h"
#include <iostream>
#include <unistd.h>
#include "loadcell/LoadCell.h"

using namespace cv;

using namespace std;


struct MyLoadCellCallback :LoadCellCallback {
public:
	void hasData(unsigned long weight) {

		if(weight > 33554433)
		{
			
		std::cout << "Weight " << weight << endl;
	    }
	    
	}


};


void LoadCellMain()
{
	MyLoadCellCallback callback;

	LoadCell loadcell;

	loadcell.registerCallback(&callback);

	loadcell.start();

	std::cout << "Load Cell reading started" << endl;

	sleep(5);

	loadcell.stop();

	std::cout << "Load Cell Main thread finished" << endl;

}






int main() {
	
	//std::unique_ptr<BarcodeReader> barcodeReaderPtr = std::make_unique<BarcodeReader>();
	LoadCellMain();
	
	return 0;
}
