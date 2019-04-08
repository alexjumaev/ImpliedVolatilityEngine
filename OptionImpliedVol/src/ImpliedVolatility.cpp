#include <cmath>
#include <random>
#include "ImpliedVolatility.hpp"
#include "boost/math/constants/constants.hpp"


double ImpliedVolatility::priceOption(double vol)
{
	double df = exp(-riskFreeRate * timeMat);
	double r = (underType == UnderlyingType::Future ? 0 : riskFreeRate);
	if(modType== ModelType::Black)
	{
		double d1 = (log(currentPrice / strike) + (r + 0.5*vol*vol)*timeMat) / (vol * sqrt(timeMat));
		double d2 = d1 - vol * sqrt(timeMat);
		double forward = (underType == UnderlyingType::Future ? currentPrice : currentPrice * exp(riskFreeRate*timeMat));
		return df *callPut* (forward*CND(callPut*d1) - strike * CND(callPut*d2));
	}
	else if(modType == ModelType::Bachelier)
	{
		double d = (currentPrice - strike) / (vol*sqrt(timeMat));
		return df *(callPut*(currentPrice - strike)*CND(callPut*d) + vol*sqrt(timeMat)*dN(d));
	}
	else
	{
		throw "Model could not be recognised!";
		//return 0;
	}
}

double ImpliedVolatility::calculate(double x)
{
	return optPrice - priceOption(x);
}

double ImpliedVolatility::CND(double d)
{
	const double       A1 = 0.31938153;
	const double       A2 = -0.356563782;
	const double       A3 = 1.781477937;
	const double       A4 = -1.821255978;
	const double       A5 = 1.330274429;
	const double RSQRT2PI = 0.39894228040143267793994605993438;

	double K = 1.0 / (1.0 + 0.2316419 * fabs(d));

	double	cnd = RSQRT2PI * exp(-0.5 * d * d) *
		(K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

	if (d > 0)
		cnd = 1.0 - cnd;

	return cnd;
};

double ImpliedVolatility::dN(double x) {
	double pi = boost::math::double_constants::pi;
	return (1 / sqrt(2 * pi)) * exp(-0.5 * x * x);
};


