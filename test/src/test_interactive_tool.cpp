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
bool suite_InteractiveToolTest_init = false;
#include "InteractiveToolTest.h"

static InteractiveToolTest suite_InteractiveToolTest;

static CxxTest::List Tests_InteractiveToolTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_InteractiveToolTest( "InteractiveToolTest.h", 13, "InteractiveToolTest", suite_InteractiveToolTest, Tests_InteractiveToolTest );

static class TestDescription_suite_InteractiveToolTest_testBlur : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testBlur() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 32, "testBlur" ) {}
 void runTest() { suite_InteractiveToolTest.testBlur(); }
} testDescription_suite_InteractiveToolTest_testBlur;

static class TestDescription_suite_InteractiveToolTest_testStamp : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testStamp() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 38, "testStamp" ) {}
 void runTest() { suite_InteractiveToolTest.testStamp(); }
} testDescription_suite_InteractiveToolTest_testStamp;

static class TestDescription_suite_InteractiveToolTest_testCrayon : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testCrayon() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 43, "testCrayon" ) {}
 void runTest() { suite_InteractiveToolTest.testCrayon(); }
} testDescription_suite_InteractiveToolTest_testCrayon;

static class TestDescription_suite_InteractiveToolTest_testFillTool : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testFillTool() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 53, "testFillTool" ) {}
 void runTest() { suite_InteractiveToolTest.testFillTool(); }
} testDescription_suite_InteractiveToolTest_testFillTool;

static class TestDescription_suite_InteractiveToolTest_testPen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testPen() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 67, "testPen" ) {}
 void runTest() { suite_InteractiveToolTest.testPen(); }
} testDescription_suite_InteractiveToolTest_testPen;

static class TestDescription_suite_InteractiveToolTest_testSparyCan : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testSparyCan() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 80, "testSparyCan" ) {}
 void runTest() { suite_InteractiveToolTest.testSparyCan(); }
} testDescription_suite_InteractiveToolTest_testSparyCan;

static class TestDescription_suite_InteractiveToolTest_testEraser : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testEraser() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 91, "testEraser" ) {}
 void runTest() { suite_InteractiveToolTest.testEraser(); }
} testDescription_suite_InteractiveToolTest_testEraser;

static class TestDescription_suite_InteractiveToolTest_testCalligraphyPen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testCalligraphyPen() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 113, "testCalligraphyPen" ) {}
 void runTest() { suite_InteractiveToolTest.testCalligraphyPen(); }
} testDescription_suite_InteractiveToolTest_testCalligraphyPen;

static class TestDescription_suite_InteractiveToolTest_testHightlighter : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testHightlighter() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 124, "testHightlighter" ) {}
 void runTest() { suite_InteractiveToolTest.testHightlighter(); }
} testDescription_suite_InteractiveToolTest_testHightlighter;

static class TestDescription_suite_InteractiveToolTest_testWaterColor : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testWaterColor() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 135, "testWaterColor" ) {}
 void runTest() { suite_InteractiveToolTest.testWaterColor(); }
} testDescription_suite_InteractiveToolTest_testWaterColor;

static class TestDescription_suite_InteractiveToolTest_testColorData : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_InteractiveToolTest_testColorData() : CxxTest::RealTestDescription( Tests_InteractiveToolTest, suiteDescription_InteractiveToolTest, 169, "testColorData" ) {}
 void runTest() { suite_InteractiveToolTest.testColorData(); }
} testDescription_suite_InteractiveToolTest_testColorData;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
