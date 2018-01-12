 // Precompiler directives /////////////////////////////////////////////////////
 
#ifndef ActinFiliment_CPP
#define ActinFiliment_CPP
#define NEGATIVESTATUS 1
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "ActinFiliment.h"


ActinFiliment::ActinFiliment()
{
	steps = 0;
	stepSize = 1;
}

ActinFiliment::ActinFiliment(float stepSizeInput)
{
	steps = 0;
	stepSize = stepSizeInput;
}

void ActinFiliment::TakeStep()
{
	steps++;
}

void ActinFiliment::UndoStep()
{
	steps--;
}

void ActinFiliment::TakeSteps( int numSteps)
{
	steps += numSteps;
}

float ActinFiliment::getDistance()
{
	return steps * stepSize;
}

float ActinFiliment::getStepSize()
{
	return stepSize;
}

int ActinFiliment::getSteps()
{
	return steps;
}


#endif //ActinFiliment_CPP
