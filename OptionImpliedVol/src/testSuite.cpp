//#include "../boostLibrary/boost/math/constants/constants.hpp"
//#include "../boostLibrary/boost/test/tools/assertion.hpp"
//#include "../boostLibrary/boost/test/included/unit_test.hpp"
//#include <iostream>
//#include <functional>
//#include <vector>
//#include <string>
//#include <time.h>
//#include "ImpliedVolExtractor.hpp"
//#include "ImpliedVolatility.hpp"
//
//using namespace boost::unit_test;
//
//void test_dN()
//{
//	double pi = boost::math::double_constants::pi;
//	BOOST_CHECK_SMALL(ImpliedVolatility::dN(0) - (1 / sqrt(2 * pi)), 1e-8);
//}
//
//void test_NormalCDF()
//{
//	BOOST_TEST_MESSAGE("Statistical tests...");
//	double half = 0.5;
//	BOOST_CHECK_SMALL(ImpliedVolatility::CND(0) - half, 1e-8);
//}
//
//void test_openFile() {
//	BOOST_TEST_MESSAGE("Open File test...");
//	//Check to see if the file reader returns the correct row count inc Header
//	ImpliedVolExtractor VolBox("inputData/input.csv", "");
//	BOOST_CHECK_SMALL(VolBox.getRowCount() - 65537 , 0);
//}
//
//void test_BrentSolver() {
//	BOOST_TEST_MESSAGE("Brent solver test...");
//	// Factors (x+1)(2x-1) so we should find root of +1/2 between interval [0.0001,2]
//	std::function<double(double)> f_ = [](double x) {return (2 * x*x + x - 1);};
//	BrentSolver solver(f_, 0.0001, 2, 1e-9, 100);
//	double val = solver.solve();
//	BOOST_CHECK_SMALL(solver.solve() - 0.5, 1e-8);
//}
//
//void test_OptionPricing() {
//	BOOST_TEST_MESSAGE("Option Pricing tests...");
//	// OptionPricer : Given i price a option with a vol of 20% i should back out the same vol given the option price
//	double targetVol = 0.2;
//	ImpliedVolatility VanillaCallOption(UnderlyingType::Stock, ModelType::Black, CallPut::Call, 0, 100, 100, 0.05, 1.0);
//	double optionPrice = VanillaCallOption.priceOption(targetVol);
//
//	ImpliedVolatility OptionToSolve(UnderlyingType::Stock, ModelType::Black, CallPut::Call, optionPrice, 100, 100, 0.05, 1.0);
//	OptionToSolve.solveImpliedVol();
//
//	double impVol = OptionToSolve.getImpliedVol();
//	BOOST_CHECK_SMALL(impVol - targetVol, 1e-8);
//}
//
//void test_WhyNANOptionImpliedVols() {
//	// OptionPricer : TRADE ID 39
//	std::vector<double> optionPrices;
//	double S = 0.273; double K = 0.3066; double timMat = 340.1189 / 365.0; double r = -0.0009; double mktPrice = 0.30025505;
//	for (double p = mktPrice / 4; p < mktPrice * 4; p += 0.003) optionPrices.push_back(p);
//	for (double& p : optionPrices) {
//		ImpliedVolatility VanillaCallOption(UnderlyingType::Stock, ModelType::Black, CallPut::Call, p, S, K, r, timMat);
//		VanillaCallOption.solveImpliedVol();
//		double impVol = VanillaCallOption.getImpliedVol();
//		//std::cout << "Option Price," << p << ",ImpVol," << impVol << std::endl;
//	}
//}
//
//test_suite* init_unit_test_suite(int, char*[])
//{
//	BOOST_TEST_MESSAGE("Main Test Suite has started...");
//	unit_test_log.set_threshold_level(log_messages);
//
//	test_suite* testStats = BOOST_TEST_SUITE("test_statistics");
//	testStats->add(BOOST_TEST_CASE(&test_NormalCDF));
//	testStats->add(BOOST_TEST_CASE(&test_dN));
//
//	test_suite* testFileOpen = BOOST_TEST_SUITE("test_openFile");
//	testFileOpen->add(BOOST_TEST_CASE(&test_openFile));
//
//	test_suite* testBrentSolver = BOOST_TEST_SUITE("test_BrentSolver");
//	testBrentSolver->add(BOOST_TEST_CASE(&test_BrentSolver));
//
//	test_suite* testOptionPricing = BOOST_TEST_SUITE("test_OptionPricing");
//	testOptionPricing->add(BOOST_TEST_CASE(&test_OptionPricing));
//	testOptionPricing->add(BOOST_TEST_CASE(&test_WhyNANOptionImpliedVols));
//
//	framework::master_test_suite().add(testStats);
//	framework::master_test_suite().add(testBrentSolver);
//	framework::master_test_suite().add(testFileOpen);
//	framework::master_test_suite().add(testOptionPricing);
//
//	BOOST_TEST_MESSAGE("Main Test Suite Finished!");
//
//	return 0;
//}
//
