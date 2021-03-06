// dataStructs.h - helper functions and data structures for the set coverage algorithm

#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#ifndef CONTAINER_LENGTH
#define CONTAINER_LENGTH (sizeof(unsigned long long) * 8)
#endif

#define DATA_DEBUG 0
#if(DATA_DEBUG)
	using namespace std;
#endif

struct subsetContainer{
	int numUncoveredElements;
	int oldSubsetNumber; // Order read in
	int subsetNumber;
    int arraySize;
    // unsigned long long int = 64 bits
	std::vector< unsigned long long int> elements;
    int size;
};

#define uint64_t unsigned long long
const uint64_t m1  = 0x5555555555555555; //binary: 0101...
const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
const uint64_t m8  = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
const uint64_t hff = 0xffffffffffffffff; //binary: all ones
const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...

//This uses fewer arithmetic operations than any other known  
//implementation on machines with fast multiplication.
//It uses 12 arithmetic operations, one of which is a multiply.
// Code from Wikipedia
int popcount_3(std::vector<uint64_t> array, int universeSize, int numArrayElements) {
	unsigned int popcount = 0;
	for (int i = 0; i < numArrayElements; i++){
		uint64_t x = array[i];
		x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
		x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
		x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
		popcount += ( (x * h01 ) >> 56 ) ;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
	}
	return popcount;
}


/**
 * Initilizes subset
 *subsetContainer
 * Called on each subset before adding elements
 *
 * FDM
 * */
void initSubset(subsetContainer *subset, int universeSize){
    subset->arraySize = universeSize/CONTAINER_LENGTH;
    if (universeSize % CONTAINER_LENGTH != 0){
    	subset->arraySize += 1;
    }
 //   subset->elements = new unsigned long long [subset->arraySize];
    subset->size = 0;
    // Initialize elements to 0 for the universe
    for(int i = 0; i < subset->arraySize; i ++){
        subset->elements.push_back(0);
        // If it's the leftmost, init it to 1s.
        if ( i == subset->arraySize - 1 ){
	        subset->elements[i] = ~subset->elements[i];
	    }
    }
    
    // Rest of array are 1's (elements outside universe are 1)
    int shiftVal = universeSize % CONTAINER_LENGTH;
    subset->elements[subset->arraySize - 1] <<= shiftVal;
    
   /* for(int i = subset->arraySize * CONTAINER_LENGTH - universeSize; 
            i < subset->arraySize * CONTAINER_LENGTH; i++){
        std::cout << "It " << i << std::endl;
        subset->elements[subset->arraySize-1] = 
        	subset->elements[subset->arraySize-1] | (unsigned long long)(1 << i);
    }*/
}


/**
 * Adds an element *val* to *subset*
 *
 * FDM
 * */
void addElement(subsetContainer *subset, int val){
    int index = (int) val / CONTAINER_LENGTH;
    int shift = val - index * CONTAINER_LENGTH; 
    uint64_t x = subset->elements[index];
    uint64_t y = (unsigned long long int) (1 << shift);
    //std::cout << "X is " << x << " y: " << y << std::endl;
    subset->elements[index] =  x | y;
    subset->size += 1;
}

/** 
 * Deconstructs subset after we are done with the program
 *
 * FDM
 */
/*void deleteSubset(subsetContainer subset){
    delete subset.elements;
}*/

// Sort by number of uncovered elements remaining, least to greatest.
bool sortSubsetList(subsetContainer a, subsetContainer b){
	return (a.numUncoveredElements < b.numUncoveredElements);
}

bool sortSubsetMinSize(subsetContainer a, subsetContainer b){
	return (a.size < b.size);
}

// Sort by number of uncovered elements remaining, greatest to least.
bool sortSubsetListGreatest(subsetContainer a, subsetContainer b){
	return (a.numUncoveredElements > b.numUncoveredElements);
}

// Sort in the order the subset was in the input file.
bool sortSubsetListIndex(subsetContainer a, subsetContainer b){
	return (a.subsetNumber < b.subsetNumber);
}

/**
 * checkSolution
 * 
 * Needs to be modified to be binary check solution - FDM
 * */
bool checkSolution(std::vector<subsetContainer> &subsets, 
        std::vector<int> selections, int universeSize){
    return 0;
}
 /*
bool checkSolution(std::vector<subsetContainer> &subsets, std::vector<int> selections, int universeSize){
	char hitElements[universeSize];
	std::sort(subsets.begin(), subsets.end(), sortSubsetListIndex);
	for (int i = 0; i < universeSize; i++){
		hitElements[i] = 0;
	}
	
	for (int i = 0; i < selections.size(); i++){
		int subsetIndex = selections[i];
		#if(DEBUG && DATA_DEBUG)
			cout << "Selection subset is " << subsetIndex << endl;
		#endif
		for (int j = 0; j < subsets[subsetIndex].elements.size(); j++){
			int element = subsets[subsetIndex].elements[j];
			#if(DEBUG && DATA_DEBUG)
				cout << "Element is " << element << endl;
			#endif
			hitElements[element - 1 ] = 1; // Subtract 1 for [1..n] elements
		}
	}
	
	bool solved = true;
	for (int i = 0; i < universeSize; i++){
		if (hitElements[i] == 0){
			solved = false;
			break;
		}
	}
	
	return solved;
}*/

void process_solution(std::vector<std::vector<int> > subsets, std::vector<int> selections){
	std::sort(selections.begin(), selections.end());
	std::cout << selections.size() << std::endl;
	for (int i = 0; i < selections.size(); i++){
		std::cout << "(" << selections[i] + 1 << ") ";
		for (int j = 0; j < subsets[ selections[i] ].size(); j++){
			std::cout << subsets[ selections[i] ][j] << " ";
		}
		std::cout << std::endl;
	}
    std::cout << std::endl;
}

#endif
