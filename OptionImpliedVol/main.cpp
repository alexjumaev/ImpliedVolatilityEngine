#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/assertion.hpp>
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <time.h>
#include "ImpliedVolExtractor.h"
#include "ImpliedVolatility.h"
#include <boost/math/constants/constants.hpp>

using namespace boost::unit_test;

void test_NormalCDF()
{
	double half = 0.5;
	BOOST_CHECK_SMALL(ImpliedVolatility::CND(0) - half, 1e-8);
}

void test_NormalDiffCDF()
{
	double pi = boost::math::constants::pi<double>();
	double frontTerm = (1 / sqrt(2 * pi));
	BOOST_CHECK_SMALL(ImpliedVolatility::dN(0) - frontTerm, 1e-8);

}
void test_openFile() {
	clock_t tStart = clock();
	ImpliedVolExtractor VolBox("input.csv", "outPut.csv");
	VolBox.extractImpliedVols();
	VolBox.writeImpliedVolsToFile();
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}

void test_BrentSolver() {
	// Factors (x+1)(2x-11) so we should find root of +1/2 between interval [0.0001,2]
	std::function<double(double)> f_ = [](double x) {return (2*x*x + x - 1);};
	BrentSolver solver(f_, 0.0001 , 2, 1e-9, 100);
	double val = solver.solve();
	BOOST_CHECK_SMALL(solver.solve() - 0.5, 1e-8);  
}

void test_NumberThreads() {
	int n = std::thread::hardware_concurrency();
	std::cout << n << " concurrent threads are supported.\n";
}

void test_OptionPricing() {
	// OptionPricer : Given i price a option with a vol of 20% i should back out the same vol given the option price
	double targetVol = 0.2;
	ImpliedVolatility VanillaCallOption(UnderlyingType::Stock, ModelType::Black, CallPut::Call, 0, 100, 100, 0.05, 1.0);
	double optionPrice = VanillaCallOption.priceOption(targetVol);
	
	ImpliedVolatility OptionToSolve(UnderlyingType::Stock, ModelType::Black, CallPut::Call, optionPrice, 100, 100, 0.05, 1.0);
	OptionToSolve.solveImpliedVol();
	
	double impVol = OptionToSolve.getImpliedVol();
	BOOST_CHECK_SMALL(impVol - targetVol, 1e-8);
}

test_suite* init_unit_test_suite(int, char* [])
{
	unit_test_log.set_threshold_level(log_messages);
	test_suite* testStats = BOOST_TEST_SUITE("test_statistics");
	testStats->add(BOOST_TEST_CASE(&test_NormalCDF));
	testStats->add(BOOST_TEST_CASE(&test_NormalDiffCDF));

	test_suite* testFileOpen = BOOST_TEST_SUITE("test_openFile");
	testFileOpen->add(BOOST_TEST_CASE(&test_openFile));

	test_suite* testBrentSolver = BOOST_TEST_SUITE("test_BrentSolver");
	testBrentSolver->add(BOOST_TEST_CASE(&test_BrentSolver));

	test_suite* testOptionPricing = BOOST_TEST_SUITE("test_OptionPricing");
	testOptionPricing->add(BOOST_TEST_CASE(&test_OptionPricing));

	test_suite* testNumberThreads = BOOST_TEST_SUITE("test_NumberThreads");
	testNumberThreads->add(BOOST_TEST_CASE(&test_NumberThreads));

	//framework::master_test_suite().add(testStats);
	framework::master_test_suite().add(testFileOpen);
	//framework::master_test_suite().add(testBrentSolver);
	//framework::master_test_suite().add(testOptionPricing);
	//framework::master_test_suite().add(testNumberThreads);


	return 0;
}

