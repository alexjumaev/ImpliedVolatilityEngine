#ifndef IMPLIEDVOLEXTRACTOR_HPP
#define IMPLIEDVOLEXTRACTOR_HPP
#include "ImpliedVolatility.hpp"

struct OutputObj {
	std::string id;
	double impliedVol;
	OutputObj(const std::string& id_, const double& impliedVol_) :id(id_), impliedVol(impliedVol_) {}
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