#ifndef ImpliedVolatility_H
#define ImpliedVolatility_H
#include "../boostLibrary/boost/lexical_cast.hpp"
#include "../boostLibrary/boost/bind.hpp"
#include "../boostLibrary/boost/functional.hpp"
#include <functional>
#include "BrentSolver.hpp"
using boost::lexical_cast;

const double lowBound = 0.0001;
const double upperBound = 5;
const double tol = 1e-8;
const int maxIter = 50;

enum UnderlyingType{
	Stock,
	Future
};

enum ModelType {
	Black,
	Bachelier
};

enum CallPut {
	Call=1,
	Put=-1
};

struct ImpliedVolatility {
	int TradeID{0};
	UnderlyingType underType;
	ModelType modType;
	CallPut callPut;
	double optPrice;
	double currentPrice;
	double strike;
	double riskFreeRate;
	double timeMat;
	double impliedVol;
	std::unique_ptr<BrentSolver> solver_{nullptr};

	explicit ImpliedVolatility(const UnderlyingType& under_type, const ModelType& mod_type, const CallPut& call_put,
		const double& opt_price, const double& current_price, const double&  strike, const double&  risk_free_rate, const double&  time_mat)
		: underType(under_type),  modType(mod_type),  callPut(call_put),  optPrice(opt_price),  currentPrice(current_price),  strike(strike),
		  riskFreeRate(risk_free_rate), timeMat(time_mat)
	{
		std::function<double(double)> priceFunctor = bind(&ImpliedVolatility::calculate, this, _1);
		solver_ = std::make_unique<BrentSolver>(priceFunctor, lowBound, upperBound, tol, maxIter);
	}

	explicit ImpliedVolatility(std::vector<std::string>& tradeDetails)
	{
		TradeID = lexical_cast<int>(tradeDetails[0]);
		underType = (tradeDetails[1] == "Future" ? UnderlyingType::Future : UnderlyingType::Stock);
		currentPrice = lexical_cast<double>(tradeDetails[2]);
		riskFreeRate = lexical_cast<double>(tradeDetails[3]);
		timeMat = lexical_cast<double>(tradeDetails[4]) / 365.0;
		strike = lexical_cast<double>(tradeDetails[5]);
		callPut = (tradeDetails[6] == "Call" ? CallPut::Call : CallPut::Put);
		modType = (tradeDetails[7] == "Bachelier" ? ModelType::Bachelier: ModelType::Black);
		optPrice = lexical_cast<double>(tradeDetails[8]);
		std::function<double(double)> priceFunctor = bind(&ImpliedVolatility::calculate, this, _1);
		solver_ = std::make_unique<BrentSolver>(priceFunctor, lowBound, upperBound, tol, maxIter);
	}
	
	ImpliedVolatility& operator=(ImpliedVolatility& other) = default;
	~ImpliedVolatility() = default;

	double priceOption(double vol);
	double calculate(double x);
	
	void solveImpliedVol() {impliedVol = solver_->solve();}

	inline int getTradeID() const { return TradeID; }
	inline double getImpliedVol() const { return impliedVol;}
	inline double getOptionPrice() const { return optPrice; }
	inline double getTimToMat()const { return timeMat; }
	inline double getStrike()const { return strike; }
	inline double getSpot()const { return currentPrice; }
	inline double getriskFreeRate()const { return riskFreeRate; }
	inline std::string getOptionType() const { return (callPut == 1 ? "Call" : "Put"); }
	inline std::string getModelType() const { return (modType==0 ? "BlackScholes" : "Bachelier"); }

	static double dN(double x);
	static double CND(double d);
};

#endif ImpliedVolatility_H