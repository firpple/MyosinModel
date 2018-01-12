all: myoEqu myoEquDebug

myoEqu: myosinEqu_v1.cpp MoleculePool.o ActinFiliment.o
	g++ MoleculePool.o ActinFiliment.o myosinEqu_v1.cpp -o myoEqu
	g++ MoleculePool.o ActinFiliment.o myosinEqu_v1.cpp -g -o myoEquDebug

MoleculePool.o: MoleculePool.h MoleculePool.cpp 
	g++ -c MoleculePool.cpp 

ActinFiliment.o: ActinFiliment.h ActinFiliment.cpp
	g++ -c ActinFiliment.cpp



run: myoEqu
	./myoEqu

clean:
	rm myoEqu myoEquDebug



