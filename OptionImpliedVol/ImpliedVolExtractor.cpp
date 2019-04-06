#include "ImpliedVolExtractor.h"
#include <fstream>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <iostream>
#include <future>
#include <thread>

ImpliedVolExtractor::ImpliedVolExtractor(const std::string inputFilename_, const std::string outputFilename_)
{
	inputFilename = inputFilename_;
	outputFilename = outputFilename_;

	std::string str;
	std::ifstream file(inputFilename);
	while (getline(file,str))
		rowCnt++;
};

void ImpliedVolExtractor::extractImpliedVols() {
	std::vector<std::string> result;
	std::string str;
	std::ifstream file(inputFilename);
	getline(file, str);

	while (getline(file, str))
	{
		boost::split(result, str, boost::is_any_of(","), boost::token_compress_on);
		ImpliedVolatility option(result);
		option.solveImpliedVol();
		finalTradeOutput.push_back(OutputObj(result[0], option.getImpliedVol()));
		//std::cout << "ID," << result[0] << ",impVol, " << option.getImpliedVol() << std::endl;
	}
}

void ImpliedVolExtractor::writeImpliedVolsToFile() {
	std::ofstream myfile;
	myfile.open(outputFilename);
	for (OutputObj& trade : finalTradeOutput)
	{
		myfile << trade.id << "," << trade.impliedVol << std::endl;
	}
	myfile.close();
}


