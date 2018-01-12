 // Precompiler directives /////////////////////////////////////////////////////
 
#ifndef MoleculePool_CPP
#define MoleculePool_CPP
#define NEGATIVESTATUS 1
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "MoleculePool.h"

int MoleculePool::addMolecule (std::string name, float amount)
{
	if(MoleculeMap.find(name) != MoleculeMap.end())
	{
		//molecule with name is found
		MoleculeMap[name] += amount;
	}
	else
	{
		//molecule with name is not found
		MoleculeMap[name] = amount;
	}
	
	if(MoleculeMap[name] < 0)
	{
		MoleculeMap[name] = 0;
		return NEGATIVESTATUS;
	}
	
	return 0;
	
	
}

int MoleculePool::subMolecule (std::string name, float amount)
{
	return addMolecule (name,  (-1 * amount));
}

int MoleculePool::setMolecule (std::string name, float amount, bool isConst)
{
	MoleculeMap[name] = amount;
	if(isConst)
	{
		ConstMap[name] = amount;
	}
	if(MoleculeMap[name] < 0)
	{
		MoleculeMap[name] = 0;
		if(isConst)
		{
			ConstMap[name] = 0;
		}
		return NEGATIVESTATUS;
	}
	
	return 0;
}

float MoleculePool::getMolecule(std::string name)
{
	if(MoleculeMap.find(name) == MoleculeMap.end())
	{
		return 0;
	}
	return MoleculeMap[name];
}

int MoleculePool::printMolecule (std::string name)
{
	if(MoleculeMap.find(name) == MoleculeMap.end())
	{
		std::cout << "Molecule ["<< name <<"] not found" << std::endl;
	}
	else
	{
		std::cout << "Molecule [" << name << "]: " << MoleculeMap[name] << std::endl; 
	}
}

int MoleculePool::printPool()
{
	std::cout << "printing all molecules in pool" << std::endl << std::endl;
	for(iteratorMap = MoleculeMap.begin(); iteratorMap != MoleculeMap.end(); iteratorMap++)
	{
		std::cout << "Molecule [" << iteratorMap -> first << "]: "; 
		std::cout << iteratorMap -> second << std::endl; 
	}
}

int MoleculePool::printPoolCSVHeader()
{
	for(iteratorMap = MoleculeMap.begin(); iteratorMap != MoleculeMap.end(); iteratorMap++)
	{
		std::cout << iteratorMap -> first << ","; 
	}
	std::cout << std::endl; 
}
int MoleculePool::printPoolCSVBody()
{
	for(iteratorMap = MoleculeMap.begin(); iteratorMap != MoleculeMap.end(); iteratorMap++)
	{
		std::cout << iteratorMap -> second << ","; 
	}
	std::cout << std::endl; 
}

int MoleculePool::resetConst()
{
	for(iteratorMap = ConstMap.begin(); iteratorMap != ConstMap.end(); iteratorMap++)
	{
		MoleculeMap[ iteratorMap ->first ] = iteratorMap -> second;
	}
}


std::string MoleculePool::toStringCSVHeader()
{
	std::string str;
	std::ostringstream stream;
	for(iteratorMap = MoleculeMap.begin(); iteratorMap != MoleculeMap.end(); iteratorMap++)
	{
		stream << iteratorMap -> first << ","; 
	}
	str = stream.str();
	return str;
}
std::string MoleculePool::toStringCSVBody()
{
	std::string str;
	std::ostringstream stream;
	for(iteratorMap = MoleculeMap.begin(); iteratorMap != MoleculeMap.end(); iteratorMap++)
	{
		stream << iteratorMap -> second << ","; 
	}
	str = stream.str();

	return str;
}



#endif //MoleculePool_CPP
