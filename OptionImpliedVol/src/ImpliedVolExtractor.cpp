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
	if (file.is_open())
	{
		while (getline(file,str)) rowCnt++;
		file.close();
	}
	else
	{
		throw "File " + inputFilename + " cannot be found!";
	}
};

void ImpliedVolExtractor::extractImpliedVols() {
	std::vector<std::string> tokens;
	std::string str;
	std::ifstream file(inputFilename);
	getline(file, str);	// Pass Headers
	if (file.is_open()) {
		while (getline(file, str))
		{
			boost::split(tokens, str, boost::is_any_of(","), boost::token_compress_on);
			ImpliedVolatility option(tokens);
			try {
				option.solveImpliedVol();
			}
			catch(...){
				std::cout << "Brent unable to solve for trade ID: " << tokens[0];
			}
			finalTradeOutput.push_back(OutputObj(tokens[0], option.getImpliedVol()));
		}
	}
	else
	{
		throw "File " + inputFilename + " cannot be found!";
	}
}

void ImpliedVolExtractor::writeImpliedVolsToFile() {
	std::ofstream outputfile;
	outputfile.open(outputFilename);
		for (OutputObj& trade : finalTradeOutput)
		{
			if (trade.impliedVol != 0)
			{
				outputfile << "Trade ID," << trade.id << "," << trade.impliedVol << std::endl;
			}
			else {
				outputfile << "Trade ID," << trade.id << ",nan" << std::endl;
			}
		}
	outputfile.close();
}


