//#include "boost/math/constants/constants.hpp"
//#include <iostream>
//#include <functional>
//#include <vector>
//#include <string>
//#include <time.h>
//#include "ImpliedVolExtractor.hpp"
//#include "ImpliedVolatility.hpp"
//
///*  This is the main program. 
//	To run unit tests comment this main.cpp file
//	and uncomment the testSuite file to run units
//	tests.
//*/
//int main() {
//
//	std::cout << "Main Application Started: Running through trades...and calculating implied vol..." << std::endl;
//	std::string projectDir = MYMACRO;
//	clock_t tStart = clock();
//	std::string inputDir = projectDir + "inputData\\input.csv";
//	std::string outputDir = projectDir + "outputData\\output.csv";
//	ImpliedVolExtractor volBox(inputDir, outputDir);
//	volBox.extractImpliedVols();
//	volBox.writeImpliedVolsToFile();
//
//	printf("Program finshed after: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
//	std::cout << "Main Application Finished, see: "<< std::endl << outputDir << std::endl;
//	std::cout << "for results." << std::endl;
//	
//	return 0;
//}
