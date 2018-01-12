#include <iostream>
#include <sstream>
#include <string>
#include <map>
//main stuffs
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>

#include "MoleculePool.h"
//main stuffs
#define NEGATIVESTATUS 1

////////////////////////////////////////////////////////////////////////////
//User Defined Names Begin//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//This is used for convience and readablity
//Please look at the marked sections of 
//User Initial Setup Code and User K value code


//filenames
#define FILE "output/out8.csv"
#define FILEP "output/outP8.csv"

//Sim Parameters
#define TIME_START 0
#define TIME_END 20
#define TIME_STEP 0.05

//molecules
#define AM "AM"
#define MT "MT"
#define A "A"
#define MDP "MPD"
#define P "P"
#define AMD "AMD"
#define ATP "ATP"
#define ADP "ADP"

//Populations
#define AM_POP 1000
#define MT_POP 0
#define A_POP 0
#define MDP_POP 0
#define P_POP 0
#define AMD_POP 0
#define ATP_POP 100
#define ADP_POP 0

//isConstant (False by default)
#define ATP_CONS true
#define P_CONS true
#define ADP_CONS true

//reaction names and k values
#define AM_ATP__MT_A "AM_ATP__MT_A"
#define MT_A__AM_ATP "MT_A__AM_ATP"
#define MT__MDP "MT__MDP"
#define MDP__MT "MDP__MT"
#define A_MDP__AMD_P "A_MDP__AMD_P"
#define AMD_P__A_MDP "AMD_P__A_MDP"
#define AMD__AM_ADP "AMD__AM_ADP"
#define AM_ADP__AMD "AM_ADP__AMD"

#define AM_ATP__MT_A__K 7
#define MT_A__AM_ATP__K .01
#define MT__MDP__K 10
#define MDP__MT__K 10
#define A_MDP__AMD_P__K 1
#define AMD_P__A_MDP__K .01
#define AMD__AM_ADP__K 100
#define AM_ADP__AMD__K .01

//step size
#define STEPSIZE 2


////////////////////////////////////////////////////////////////////////////
//User Defined Names End////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

//Start of Reactions///////////////////////////////////////////////////////////

class Reaction
{
	public:
		float KValue;
		std::map<std::string, float> ReactionMap;
		float KTotal(class MoleculePool &);
};



float Reaction::KTotal(class MoleculePool &mPool)
{
	float float_Temp;
	float_Temp = 0;
	std::map<std::string, float>::iterator it_Reactant;
	for(it_Reactant = ReactionMap.begin(); it_Reactant != ReactionMap.end(); it_Reactant++)
	{
		if((it_Reactant -> second) < 0)
		{
			float_Temp *= mPool.getMolecule(it_Reactant->first);
		}
	}
};
//Start of Main////////////////////////////////////////////////////////////////
//delete below when done
int main()
{
	MoleculePool mPool;
	MoleculePool constPool;
	std::map<std::string, class Reaction> AllReactions;
	std::map<std::string, class Reaction>::iterator it_Reactions;
	std::map<std::string, float>::iterator it_Accu;
	std::map<std::string, float>::iterator it_Reactant;
	std::map<std::string, float> AccuReactMap;
	class Reaction * reaction_ptr;
	float timeCurrent;
	float timeStep;
	float timePrintDelta;
	float timePrintCulm;
	float timeEnd;
	float KTotal;
	float float_Temp;
	float RNGChoice;


	std::ostringstream stream;

	std::ofstream csvFile;
	std::ofstream paraFile;


	////////////////////////////////////////////////////////////////////////////
	//User Initial Setup Code Begin/////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	//setting up experiement parameters///////////
	timeCurrent = TIME_START; //start time
	timeEnd = TIME_END; //end time
	timePrintDelta = TIME_STEP; //print out Intervals
	srand (time(NULL)); //seeds randomness

	//setting initial conditions//////////////////
	//Format:
	//mPool.setMolecule(<Name>, <amount>, <is constant (optional, defaults to false)>)
	//Name should be defined at the top
	mPool.setMolecule(AM, AM_POP);
	mPool.setMolecule(MT, MT_POP);
	mPool.setMolecule(A, A_POP);
	mPool.setMolecule(MDP, MDP_POP);
	mPool.setMolecule(P, P_POP,P_CONS);
	mPool.setMolecule(AMD, AMD_POP);
	mPool.setMolecule(ATP, ATP_POP, ATP_CONS);
	mPool.setMolecule(ADP, ADP_POP, ADP_CONS);

	//creates a actin "filiment"
	class ActinFiliment Afiliment(36 * pow(10, -9));

	//reactions///////////////////////////////////
	//////////////////////////////////////////////
	//reaction AM+ATP -> MT+A
	//creates reaction
	reaction_ptr = new class Reaction;
	//sets KValue
	reaction_ptr -> KValue = AM_ATP__MT_A__K;
	//loss or reactants (must be negative number)
	reaction_ptr -> ReactionMap[AM] = -1;
	reaction_ptr -> ReactionMap[ATP] = -1;
	//gains or products (must be positive number)
	reaction_ptr -> ReactionMap[A] = 1;
	reaction_ptr -> ReactionMap[MT] = 1;
	//add to reactions
	AllReactions[AM_ATP__MT_A] = *reaction_ptr;
	delete reaction_ptr;
	reaction_ptr = NULL;


	//reaction MT_A__AM_ATP
	//creates reaction
	reaction_ptr = new class Reaction;
	//sets KValue
	reaction_ptr -> KValue = MT_A__AM_ATP__K;
	//loss or reactants (must be negative number)
	reaction_ptr -> ReactionMap[A] = -1;
	reaction_ptr -> ReactionMap[MT] = -1;
	//gains or products (must be positive number)
	reaction_ptr -> ReactionMap[AM] = 1;
	reaction_ptr -> ReactionMap[ATP] = 1;
	//add to reactions
	AllReactions[MT_A__AM_ATP] = *reaction_ptr;
	delete reaction_ptr;
	reaction_ptr = NULL;

	//////////////////////////////////////////////
	//////////////////////////////////////////////

	//reaction MT__MDP
	//creates reaction
	reaction_ptr = new class Reaction;
	//sets KValue
	reaction_ptr -> KValue = MT__MDP__K;
	//loss
	reaction_ptr -> ReactionMap[MT] = -1;
	//gains
	reaction_ptr -> ReactionMap[MDP] = 1;
	//add to reactions
	AllReactions[MT__MDP] = *reaction_ptr;
	delete reaction_ptr;
	reaction_ptr = NULL;


	//reaction MDP__MT
	//creates reaction
	reaction_ptr = new class Reaction;
	//sets KValue
	reaction_ptr -> KValue = MDP__MT__K;
	//loss
	reaction_ptr -> ReactionMap[MDP] = -1;
	//gains
	reaction_ptr -> ReactionMap[MT] = 1;
	//add to reactions
	AllReactions[MDP__MT] = *reaction_ptr;
	delete reaction_ptr;
	reaction_ptr = NULL;

	//////////////////////////////////////////////
	//////////////////////////////////////////////

	//reaction A_MDP__AMD_P
	//creates reaction
	reaction_ptr = new class Reaction;
	//sets KValue
	reaction_ptr -> KValue = A_MDP__AMD_P__K;
	//loss
	reaction_ptr -> ReactionMap[A] = -1;
	reaction_ptr -> ReactionMap[MDP] = -1;
	//gains
	reaction_ptr -> ReactionMap[P] = 1;
	reaction_ptr -> ReactionMap[AMD] = 1;
	//add to reactions
	AllReactions[A_MDP__AMD_P] = *reaction_ptr;
	delete reaction_ptr;
	reaction_ptr = NULL;

	//reaction AMD_P__A_MDP
	//creates reaction
	reaction_ptr = new class Reaction;
	//sets KValue
	reaction_ptr -> KValue = AMD_P__A_MDP__K;
	//loss
	reaction_ptr -> ReactionMap[P] = -1;
	reaction_ptr -> ReactionMap[AMD] = -1;
	//gains
	reaction_ptr -> ReactionMap[A] = 1;
	reaction_ptr -> ReactionMap[MDP] = 1;
	//add to reactions
	AllReactions[AMD_P__A_MDP] = *reaction_ptr;
	delete reaction_ptr;
	reaction_ptr = NULL;

	//////////////////////////////////////////////
	//////////////////////////////////////////////

	//reaction AMD__AM_ADP
	//creates reaction
	reaction_ptr = new class Reaction;
	//sets KValue
	reaction_ptr -> KValue = AMD__AM_ADP__K;
	//loss
	reaction_ptr -> ReactionMap[AMD] = -1;
	//gains
	reaction_ptr -> ReactionMap[ADP] = 1;
	reaction_ptr -> ReactionMap[AM] = 1;
	//add to reactions
	AllReactions[AMD__AM_ADP] = *reaction_ptr;
	delete reaction_ptr;
	reaction_ptr = NULL;

	//reaction AM_ADP__AMD
	//creates reaction
	reaction_ptr = new class Reaction;
	//sets KValue
	reaction_ptr -> KValue = AM_ADP__AMD__K;
	//loss
	reaction_ptr -> ReactionMap[ADP] = -1;
	reaction_ptr -> ReactionMap[AM] = -1;
	//gains
	reaction_ptr -> ReactionMap[AMD] = 1;
	//add to reactions
	AllReactions[AM_ADP__AMD] = *reaction_ptr;
	delete reaction_ptr;
	reaction_ptr = NULL;
	////////////////////////////////////////////////////////////////////////////
	//User Initial Setup Code End///////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	

	//opens file
	csvFile.open(FILE);
	paraFile.open(FILEP);
	//sets up periodic print times
	timePrintCulm = timeCurrent + timePrintDelta;
	//print header
	stream << "Time," << mPool.toStringCSVHeader();
	stream << "Distance" << ',' << std::endl;
	std::cout << stream.str();
	csvFile << stream.str();
	stream.str(std::string());
	//print initial conditions
	stream << timeCurrent << "," << mPool.toStringCSVBody();
	stream << Afiliment.getDistance() << ',' << std::endl;
	std::cout << stream.str();
	csvFile << stream.str();
	stream.str(std::string());


	//Start Gillespie model
	while(timeCurrent < timeEnd)
	{
		//calc Ktotal/////////////////////////////
		KTotal = 0;
			
		//cycles through reactions
		for( it_Reactions = AllReactions.begin(); it_Reactions != AllReactions.end(); it_Reactions++)
		{
			//grabs a reaction
			float_Temp = it_Reactions -> second.KValue;
			reaction_ptr = &(it_Reactions -> second);

			//runs default K calculations
			for(it_Reactant = (*reaction_ptr).ReactionMap.begin(); it_Reactant != (*reaction_ptr).ReactionMap.end(); it_Reactant++)
			{
				if((it_Reactant -> second) < 0)
				{
					float_Temp *= mPool.getMolecule(it_Reactant->first)* (it_Reactant -> second);
				}
				float_Temp = abs(float_Temp);
			}
			
			
			////////////////////////////////////////////////////////////////////
			//User K value code begin///////////////////////////////////////////
			////////////////////////////////////////////////////////////////////

			//custom formula
			//put custom reactions here in the form of:
			//float_temp on the left hand side is 
			//it_Reactions -> second.KValue is the current reaction's KValue
			//if(it_Reactions -> first = "REACTIONNAME")
			//{
			//   float_temp = it_Reactions -> second.KValue * mPool.getMolecule("myosin") * mPool.getMolecule("ATP"))
			//}
			if(it_Reactions -> first == A_MDP__AMD_P)
			{
				float kSpring = 2;
				float force = kSpring * Afiliment.getDistance() * Afiliment.getStepSize();
				float work = force * Afiliment.getStepSize();
				float kRate = it_Reactions -> second.KValue * mPool.getMolecule(A) * mPool.getMolecule(MDP);
				float tempature = 293; //room temp
				float boltzmann = 1.38064852 * pow(10, -23);
				//work =0;
				float_Temp = kRate * exp(-1* work / (boltzmann*tempature));
				//printf("<><> %f <><>\n", -1* work / (boltzmann*tempature));
				//<><><><><><><<><><><
			}
			
			
			
			
			////////////////////////////////////////////////////////////////////
			//User K value code end/////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////

			//adds the K calculation 
			KTotal += float_Temp;
			AccuReactMap[it_Reactions -> first] = KTotal;
		}

		//checks for any possible reactions///////
		if(KTotal <= 0)
		{
			//if no more reactions, stop algorithm
			break;
		}

		//Roll for time///////////////////////////
		//calcs time till next reaction
		timeStep = -1 * log(rand()/((double) RAND_MAX)) / KTotal;

		//roll for action/////////////////////////
		RNGChoice = rand()/((double) RAND_MAX) * KTotal;

		//calcs which reaction happens////////////
		for( it_Accu = AccuReactMap.begin(); it_Accu != AccuReactMap.end(); it_Accu++)
		{
			if(RNGChoice < it_Accu -> second)
			{
				break;
			}
		}

		//checks for valid reactions//////////////
		if(it_Accu == AccuReactMap.end())
		{
			//something went wrong
			break;
		}



		//carry out reaction//////////////////////
		for(it_Reactant = AllReactions[it_Accu -> first].ReactionMap.begin(); it_Reactant != AllReactions[it_Accu -> first].ReactionMap.end(); it_Reactant++)
		{
			mPool.addMolecule(it_Reactant -> first, it_Reactant -> second);
		}

		//ActinMovement///////////////////////////
		if (it_Accu -> first == A_MDP__AMD_P)
		{
			Afiliment.TakeStep();
		}
		else if(it_Accu -> first == AMD_P__A_MDP)
		{
			Afiliment.UndoStep();
		}
		//increase time///////////////////////////
		timeCurrent += timeStep;

		//reset const/////////////////////////////
		mPool.resetConst();



		//stamp
		if(timeCurrent > timePrintCulm)
		{
			stream << timeCurrent << "," << mPool.toStringCSVBody();
			stream << Afiliment.getDistance() << ',' << std::endl;
			std::cout << stream.str();
			csvFile << stream.str();
			stream.str(std::string());
			timePrintCulm = timeCurrent + timePrintDelta;
		}



	}

	//stamps reactions
	stream << "Name,k value,units" << std::endl;
	stream << "molecule name,reactant/product,value" << std::endl;
	stream  << std::endl << std::endl;
	paraFile << stream.str();
	stream.str(std::string());
	for( it_Reactions = AllReactions.begin(); it_Reactions != AllReactions.end(); it_Reactions++)
	{
		//grabs a reaction

		stream << it_Reactions -> first << ",";
		stream << it_Reactions -> second.KValue << ",";
		stream << "1/s,";
		stream << std::endl;
		paraFile << stream.str();
		stream.str(std::string());


		reaction_ptr = &(it_Reactions -> second);
		//reactants first
		for(it_Reactant = (*reaction_ptr).ReactionMap.begin(); it_Reactant != (*reaction_ptr).ReactionMap.end(); it_Reactant++)
		{
			if((it_Reactant -> second) < 0)
			{
				stream << it_Reactant->first << ",";
				stream << "reactant,";
				stream << it_Reactant->second << std::endl;
				paraFile << stream.str();
				stream.str(std::string());
			}
		}
		//products last
		for(it_Reactant = (*reaction_ptr).ReactionMap.begin(); it_Reactant != (*reaction_ptr).ReactionMap.end(); it_Reactant++)
		{
			if((it_Reactant -> second) > 0)
			{
				stream << it_Reactant->first << ",";
				stream << "product,";
				stream << it_Reactant->second << std::endl;
				paraFile << stream.str();
				stream.str(std::string());
			}
		}

		stream  << std::endl << std::endl;
		paraFile << stream.str();
		stream.str(std::string());
	}


	//close file
	csvFile.close();
	paraFile.close();
	return 0;
}
