#pragma once
#include <iostream>
/*
* This class is the responsible of synchronizing frame rate and refresh rate
*/

#define NUM_SAMPLES 10	//The number of frames to average

class FPSLimiter { 
	float _fps;								//Current _fps based on the average of the last 10 rendered frames
	int _maxFPS;							//Maximum number of frames to render by second	
	int _currentFrame;						//The position of the frameTime array that has be to updated
	float _frameTimes[NUM_SAMPLES];			//Stores all the frametimes for each frame that we will average
	float _startTicks;						//Stores the initial value of the counter
	float _previousTickFrame;				//Ticks of the past frame
	bool _printFPS;							//Print (or not) the average of FPS
	bool _enable;							//Limits or not the FPS


	// Calculates the current FPS
	void updateAverageFPS();
public:
	//Initialize the max FPS
	FPSLimiter(bool enable, int maxFPS, bool printFPS);

	// Sets the desired max FPS. This method is useful if we decide to change the maxFPS during the execution
	void setMaxFPS(int maxFPS);

	//Start the counter
	void startSynchronization();

	//Force system to wait in order to sync with the refresh rate
	void forceSynchronization();

};