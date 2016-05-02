#
# Makefile for UN*X-like systems
#

# COMPILER for CPP
CXXC = g++
CPPFLAGS = -Wall -W -I. -I../cxxtest -std=c++11
PHOTO_PATH = ../../libphoto
PNG_PATH = ../../libpng
JPEG_PATH = ../../libjpeg
INCLUDE += -I$(PHOTO_PATH)/include -I$(PNG_PATH)/include -I$(JPEG_PATH)/include
LINK_LIBS += -L$(PHOTO_PATH)/lib/  -lphoto -L$(PNG_PATH)/lib/ -lpng -L$(JPEG_PATH)/lib/ -ljpeg
LDFLAGS += -lz

TESTGEN = ../cxxtest/bin/cxxtestgen

#TODO need add mia_command_tool
TARGETS = test_interactive_tool test_filter_tool
TEST_INTERACTIVE_TOOL = InteractiveToolTest.h
TEST_FILTER_TOOL = FilterToolTest.h
TEST_MIA_COMMAND_LINE = MIACommandLineTest.h

all: $(TARGETS) run

clean:
	rm -f *~ *.o *.obj $(TARGETS)
	rm -f *.cpp
	rm -f output/*

run:
	./test_interactive_tool
	./test_filter_tool

test_interactive_tool.cpp: $(TEST_INTERACTIVE_TOOL)
	$(TESTGEN) -o $@ --error-printer $(TEST_INTERACTIVE_TOOL)

test_filter_tool.cpp: $(TEST_FILTER_TOOL)
	$(TESTGEN) -o $@ --error-printer $(TEST_FILTER_TOOL)

test_mia_command_line.cpp: $(TEST_MIA_COMMAND_TOOL)
	$(TESTGEN) -o $@ --error-printer $(TEST_MIA_COMMAND_TOOL)


%: %.cpp
	$(CXXC) $(CPPFLAGS) $(INCLUDE) -o $@ $< $(LINK_LIBS) $(LDFLAGS)
