#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <fstream> // Read in files 
#include <string.h> // String manipulation
#include <vector> 
#include <algorithm>
#include <bitset>

#define DEBUG 1
#define READIN 1

#ifndef CONTAINER_LENGTH
#define CONTAINER_LENGTH (sizeof(unsigned long long) * 8)
#endif

#include "dataStructs.h"
//#include "greedy.h"
//#include "backtrack.h"


using namespace std;

void printSubset(subsetContainer *subset){
    for(int i = 0; i < subset->arraySize; i++){
        cout << i << ": " << bitset<CONTAINER_LENGTH >(subset->elements[i]) << " " << endl;
        cout << (unsigned long long) subset->elements[i]  << endl;
    }
    cout << endl;
}



int main(int argc, char** argv){
    if(argc != 2){
        cout << "Usage: ./main sets.txt" << endl;
        return -1;
    }
    
    ifstream readFile;
    readFile.open(argv[1]);
    string line;
    // Size of universal set
    getline(readFile, line);
    int universeSize = atoi(line.c_str());
    // Number of subsets
    getline(readFile, line);
    int num_subsets = atoi(line.c_str());
    
    vector<subsetContainer> subsets;
 //   subsetContainer subsets[num_subsets];
    for(int i = 0; i < num_subsets; i++){
    	subsetContainer temp;
        cout << "Starting " << endl;
        initSubset(&temp, universeSize); // FDM
    	subsets.push_back(temp);
        subsets[i].subsetNumber = i;
    }
    char* line2;
    char* sptr;
    for(int i = 0; i < num_subsets; i++){
        getline(readFile, line);
        line2 = strdup(line.c_str());
        sptr = strtok(line2, " ");
       	int j = 0;
        while (sptr != NULL) {
        	int val = atoi(sptr);
            //addElement(subsets[i], val); // FDM
            //subsets[i].elements.push_back(val);
            sptr = strtok(NULL," ");
        }
        subsets[i].numUncoveredElements = subsets[i].size;
    }
    
    std::sort (subsets.begin(), subsets.end(), sortSubsetListGreatest );
   
    // FDM - I commented out the rest of the program 
    vector<int> base_solution;
    
    //greedy(subsets, base_solution, universeSize);
    //int base_size = base_solution.size();
    //cout << "Base solution size is " <<  base_solution.size() << endl;
    
/*    bool solved = checkSolution(subsets, base_solution, universeSize);
//    cout << (solved? "Solved" : "Not solved") << endl;
    if (solved){
    	process_solution(subsets, base_solution);
    }*/
    
    //vector<int> currentSolution;
    //vector<int> bestSolution = base_solution;
	//sort(subsets.begin(), subsets.end(), sortSubsetListGreatest);
    //backtrack(subsets, subsets, currentSolution, universeSize, base_size, bestSolution);
  //  cout << bestSolution.size() << endl;
    
   // process_solution(subsets, bestSolution);
    
  /*  solutions.push_back(4);
    solutions.push_back(3);
    solutions.push_back(2);
    bool solved = checkSolution(subsets, solutions, universeSize);
//    cout << (solved? "Solved" : "Not solved") << endl;
    if (solved){
    	process_solution(subsets, solutions);
    }*/

    // FDM deconstructs subsets 
    for(int i = 0; i < subsets.size(); i++){
        deleteSubset(subsets[i]);
    }
    
    return 0;

}
