/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_FilterToolTest_init = false;
#include "FilterToolTest.h"

static FilterToolTest suite_FilterToolTest;

static CxxTest::List Tests_FilterToolTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FilterToolTest( "FilterToolTest.h", 15, "FilterToolTest", suite_FilterToolTest, Tests_FilterToolTest );

static class TestDescription_suite_FilterToolTest_testEdgeDetection : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testEdgeDetection() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 54, "testEdgeDetection" ) {}
 void runTest() { suite_FilterToolTest.testEdgeDetection(); }
} testDescription_suite_FilterToolTest_testEdgeDetection;

static class TestDescription_suite_FilterToolTest_testThreshold : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testThreshold() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 83, "testThreshold" ) {}
 void runTest() { suite_FilterToolTest.testThreshold(); }
} testDescription_suite_FilterToolTest_testThreshold;

static class TestDescription_suite_FilterToolTest_testChannel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testChannel() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 100, "testChannel" ) {}
 void runTest() { suite_FilterToolTest.testChannel(); }
} testDescription_suite_FilterToolTest_testChannel;

static class TestDescription_suite_FilterToolTest_testSharpen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testSharpen() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 117, "testSharpen" ) {}
 void runTest() { suite_FilterToolTest.testSharpen(); }
} testDescription_suite_FilterToolTest_testSharpen;

static class TestDescription_suite_FilterToolTest_testSaturate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testSaturate() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 134, "testSaturate" ) {}
 void runTest() { suite_FilterToolTest.testSaturate(); }
} testDescription_suite_FilterToolTest_testSaturate;

static class TestDescription_suite_FilterToolTest_testQuantize : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testQuantize() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 151, "testQuantize" ) {}
 void runTest() { suite_FilterToolTest.testQuantize(); }
} testDescription_suite_FilterToolTest_testQuantize;

static class TestDescription_suite_FilterToolTest_testSpecial : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testSpecial() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 168, "testSpecial" ) {}
 void runTest() { suite_FilterToolTest.testSpecial(); }
} testDescription_suite_FilterToolTest_testSpecial;

static class TestDescription_suite_FilterToolTest_testBlur : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testBlur() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 184, "testBlur" ) {}
 void runTest() { suite_FilterToolTest.testBlur(); }
} testDescription_suite_FilterToolTest_testBlur;

static class TestDescription_suite_FilterToolTest_testMBlurNorthSouth : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testMBlurNorthSouth() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 201, "testMBlurNorthSouth" ) {}
 void runTest() { suite_FilterToolTest.testMBlurNorthSouth(); }
} testDescription_suite_FilterToolTest_testMBlurNorthSouth;

static class TestDescription_suite_FilterToolTest_testMBlurWestEast : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testMBlurWestEast() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 219, "testMBlurWestEast" ) {}
 void runTest() { suite_FilterToolTest.testMBlurWestEast(); }
} testDescription_suite_FilterToolTest_testMBlurWestEast;

static class TestDescription_suite_FilterToolTest_testMBlurNE_SW : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testMBlurNE_SW() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 237, "testMBlurNE_SW" ) {}
 void runTest() { suite_FilterToolTest.testMBlurNE_SW(); }
} testDescription_suite_FilterToolTest_testMBlurNE_SW;

static class TestDescription_suite_FilterToolTest_testMBlurNW_SE : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterToolTest_testMBlurNW_SE() : CxxTest::RealTestDescription( Tests_FilterToolTest, suiteDescription_FilterToolTest, 255, "testMBlurNW_SE" ) {}
 void runTest() { suite_FilterToolTest.testMBlurNW_SE(); }
} testDescription_suite_FilterToolTest_testMBlurNW_SE;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
