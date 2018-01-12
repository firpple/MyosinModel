// Precompiler directives /////////////////////////////////////////////////////
#ifndef ActinFiliment_H
#define ActinFiliment_H


class ActinFiliment
{
	public:
		ActinFiliment();
		ActinFiliment(float stepSizeInput);
		void TakeStep();
		void UndoStep();
		void TakeSteps(int numSteps);
		float getDistance();		
		float getStepSize();
		int getSteps();
	private:
		int steps;
		float stepSize;
};

#endif //ActinFiliment_H
