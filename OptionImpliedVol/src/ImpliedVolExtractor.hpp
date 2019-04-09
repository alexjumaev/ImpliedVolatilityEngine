#ifndef IMPLIEDVOLEXTRACTOR_HPP
#define IMPLIEDVOLEXTRACTOR_HPP
#include "ImpliedVolatility.hpp"

struct OutputObj {
	int id;
	double spot;
	double strike;
	double rate;
	double timMat;
	double marketPrice;
	double impliedVol;
	std::string optionType;
	std::string modelType;

	OutputObj(const int& id_, const double& spot_, const double& strike_, const double& rate_, const double& timMat_,
		const std::string& optionType_, const std::string& modelType_, const double& marketPrice_, const double& impliedVol_)
		:
		id(id_), spot(spot_) , strike(strike_) , rate(rate_),timMat(timMat_), optionType(optionType_) , modelType(modelType_), 
		marketPrice(marketPrice_),  impliedVol(impliedVol_) {}
};

class ImpliedVolExtractor
{
	std::string inputFilename;
	std::string outputFilename;
	std::vector<OutputObj> finalTradeOutput;
	int rowCnt{0};
public:
	ImpliedVolExtractor(const std::string inputFilename_, const std::string outputFilename_);
	~ImpliedVolExtractor() = default;
	ImpliedVolExtractor(const ImpliedVolExtractor& other) = delete;


	void extractImpliedVols();
	void writeImpliedVolsToFile();
	inline int getRowCount() const { return rowCnt;};
};

#endif IMPLIEDVOLEXTRACTOR_HPP