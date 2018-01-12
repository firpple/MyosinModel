// Precompiler directives /////////////////////////////////////////////////////
#ifndef MoleculePool_H
#define MoleculePool_H


#include "ActinFiliment.h"
class MoleculePool
{
	public:
	
		//MoleculePool();
		//MoleculePool(const MoleculePool&);
		//~MoleculePool();
	
		int addMolecule(std::string, float);
		int subMolecule(std::string, float);
		int setMolecule(std::string, float, bool = false);
		float getMolecule(std::string);
		int printMolecule(std::string);
		int printPool();
		int printPoolCSVHeader();
		int printPoolCSVBody();

		int resetConst();


		std::string toStringCSVHeader();
		std::string toStringCSVBody();

	private:
		std::map<std::string, float> MoleculeMap;
		std::map<std::string, float> ConstMap;
		std::map<std::string, float>::const_iterator iteratorMap;
};

#endif //MoleculePool_CPP
