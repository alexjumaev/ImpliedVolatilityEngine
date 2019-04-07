#include "BrentSolver.hpp"
// Source: An Imporvemnt to the Brent's Method by Zhengqiu Zhang. International Journal of Experimental Algorithms, 2011

double BrentSolver::solve() const
{
	double a = lowerBound;
	double b = upperBound;
	double c{ 0.0 };
	double s{ 0.0 };
	double fa = f(lowerBound);
	double fb = f(upperBound);
	double fc = fb;
	double fs = fb;
	double r1, r2, r3, p, q;

	if (fa*fb >= 0.0) {
		return 0;
		std::cout << "Not solveable: f(a)*f(b) >= 0.0" << std::endl;
	}

	for (size_t i = 0; i < maxIterations; i++)
	{
		fa = f(a);
		fb = f(b);

		if (fb == 0 || abs(b-a) < tolerance) return b;
		if (fs == 0) return s;

		c = (b + a) / 2;
		fc = f(c);

		if ((fa != fb) && (fb != fc))
		{	// calculate s via inverse quadratic interpolation 
			r1 = fa / fc;
			r2 = fb / fc;
			r3 = fb / fa;  
			p = r3 * (((c - b) * r1 * (r1 - r2)) - ((b - a) * (r2 - 1)));
			q = (p > 0 ? -1.0 : 1.0 ) * (r1 - 1) * (r2 - 1) * (r3 - 1);
			if (q != 0) s = b + (p / q);
		}
		else 
		{	// calculate s via secant rule
			s = a - fa*((b-a)/(fb-fa));	
		}

		fs = f(s);
		if (c > s) std::swap(s, c);
		
		if (fs*fc < 0) {
			a = s;
			b = c;
		}
		else {
			fs*fb < 0 ? a = c : b = s;
		}
	}
	return 0;
}
