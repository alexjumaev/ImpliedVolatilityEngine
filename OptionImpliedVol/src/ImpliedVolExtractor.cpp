#include "../boostLibrary/boost/algorithm/string/classification.hpp"
#include "../boostLibrary/boost/algorithm/string/split.hpp"
#include <fstream>
#include <iostream>
#include "ImpliedVolExtractor.hpp"

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
		if (trade.impliedVol!=0)
		{
			myfile <<"Trade ID," << trade.id << "," << trade.impliedVol << std::endl;
		}
		else {
			myfile << "Trade ID," << trade.id << ",nan" << std::endl;
		}
	}
	myfile.close();
}


