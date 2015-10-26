#include "MemCDIndex.hh"
#include <stdlib.h>
#include <iostream>


// Get command line arguments for array size (100M) and number of trials (1M)
void arrayArgs(int argc, char* argv[], unsigned long long& asize, int& reps) {
  asize = (argc>1) ? strtoull(argv[1], 0, 0) : 100000000;
  reps  = (argc>2) ? strtol(argv[2], 0, 0)   : 1000000;
}


// Main program goes here

int main(int argc, char* argv[]) {
  unsigned long long arraySize;
  int queryTrials;
  arrayArgs(argc, argv, arraySize, queryTrials);

  std::cout << "Memcached Table " << arraySize << " elements, " << queryTrials
	    << " trials" << std::endl;

  MemCDIndex memcd(2);		// Verbosity
  memcd.CreateTable(arraySize);
  memcd.ExerciseTable(queryTrials);
}