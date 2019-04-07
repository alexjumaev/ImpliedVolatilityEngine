#ifndef IMPLIEDVOLEXTRACTOR_HPP
#define IMPLIEDVOLEXTRACTOR_HPP
#include "ImpliedVolatility.hpp"

struct OutputObj {
	int id;
	double Spot;
	double Strike;
	double rate;
	double timMat;
	double MarketPrice;
	double impliedVol;
	std::string OptionType;
	std::string ModelType;

	OutputObj(const int& id_, const double& Spot_, const double& Strike_, const double& rate_, const double& timMat_,
		const std::string& OptionType_, const std::string& ModelType_, const double& MarketPrice_, const double& impliedVol_)
		:
		id(id_), Spot(Spot_) , Strike(Strike_) , rate(rate_),timMat(timMat_), OptionType(OptionType_) , ModelType(ModelType_), 
		MarketPrice(MarketPrice_),  impliedVol(impliedVol_) {}
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
	ImpliedVolExtractor(const ImpliedVolExtractor& Other) = delete;


	void extractImpliedVols();
	void writeImpliedVolsToFile();
	inline int getRowCount() const { return rowCnt;};
};

#endif IMPLIEDVOLEXTRACTOR_HPP