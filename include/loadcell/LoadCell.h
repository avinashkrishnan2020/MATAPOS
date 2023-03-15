#ifndef LOAD_CELL
#define LOAD_CELL

#include<iostream>
#include<thread>
#include<vector>
#include <pigpio.h>

struct LoadCellCallback {
	public: virtual void hasData(unsigned long weight) = 0;
};

class LoadCell {

private:
	int fd = 0;
	bool running;
	std::thread t;
	int isReady(int);
	void ReadLoadCell();
	std::vector<LoadCellCallback*> loadcellcallback;

public:
	void registerCallback(LoadCellCallback* lc);
	void start();
	void stop();

};
#endif