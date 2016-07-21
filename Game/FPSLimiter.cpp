#include "FPSLimiter.h"

#include <SDL/SDL.h>


/*
* Initialize the FPS limiter
* @param maxFPS is the max FPS
*/
FPSLimiter::FPSLimiter(bool enable,int maxFPS, bool printFPS) : _enable(enable),_maxFPS(maxFPS), _printFPS(printFPS), _currentFrame(-1){
		//Initialize the array that will manage the last 10 rendered frames
	for (int i = 0; i < NUM_SAMPLES; i++) {
		_frameTimes[i] = (1000.0f / _maxFPS);
	}
	_previousTickFrame = (float)SDL_GetTicks();
}
	
/*
* Sets the desired max FPS. This method is useful if we decide to change the maxFPS during the execution
* @param maxFPS is the max FPS
*/
void FPSLimiter::setMaxFPS(int maxFPS) {
	_maxFPS = maxFPS;
}

/**
* Start the counter
*/
void FPSLimiter::startSynchronization() {
	_startTicks = (float)SDL_GetTicks();
}

/**
* Force system to wait in order to sync with the refresh rate
*/
void FPSLimiter::forceSynchronization() {			
	
	//Update the average of the FPS
	updateAverageFPS();

	//Print the current average of FPS
	if (_printFPS) {
		if (_currentFrame == NUM_SAMPLES - 1) {
			std::cout << "FPS:" << _fps << std::endl;
		}
	}
	if (_enable) {
		//Force system to sync
		//Ex: 1000msec / 60 frames per second -> Each frame must be rendered each 16msec
		//Count how much time we have used to render the current frame
		//Wait the difference between 16msec and the current time
		float frameTicks = SDL_GetTicks() - _startTicks;
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay((Uint32)((1000.0f / _maxFPS) - frameTicks));
		}
		
	}
}

/**
* Compute the average of the fps based on the last 10 rendered frames 
*/
void FPSLimiter::updateAverageFPS() {	
	
		//Ticks for the current frame
	float currentTicks = (float)SDL_GetTicks();

		//Calculate the number of ticks (ms) for this frame
	_currentFrame = (_currentFrame + 1) % NUM_SAMPLES;
	_frameTimes[_currentFrame] = currentTicks - _previousTickFrame;
	_previousTickFrame = currentTicks;
	
		//Average all the frame times
	float frameTimeAverage = 0;
	for (int i = 0; i < NUM_SAMPLES; i++) {
		frameTimeAverage += _frameTimes[i];
	}
	frameTimeAverage /= NUM_SAMPLES;

		//Calculate FPS
	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	} else {
		_fps = 1000.0f / _maxFPS;
	}
}
