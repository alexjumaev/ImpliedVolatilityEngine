#ifndef BRENTSOLVER_H
#define BRENTSOLVER_H
#include <functional>
#include <iostream>
#include <cmath>

class BrentSolver
{
	std::function<double(double)> f;
	int maxIterations = 200;
	double tolerance = 1e-10;
	double lowerBound = 1e-4;
	double upperBound = 5;
public:

	explicit BrentSolver(const std::function<double(double)>& f_, const double& lowerBound_, const double& upperBound_,
		const double& tolerance_, const int& maxIterations_)
		: f(f_), lowerBound(lowerBound_), upperBound(upperBound_), tolerance(tolerance_), maxIterations(maxIterations_){}
	
	double solve() const;
};

#endif  BRENTSOLVER_H
