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
MIATARGET= ../../Mia/Mia
#this is thest file
BLUR = blur.png
CHANNEL = channel.png
EDGE = edge.png
N_S_BLUR = n_s_blur.png
E_W_BLUR = e_w_blur.png
NE_SW_BLUR = ne_sw_blur.png
NW_SE_BLUR = nw_se_blur.png
QUAN=quan.png
SATUR=satur.png
SHARPEN = sharpen.png
SPECIAL = spec.png
THRESHOLD = threshold.png
INPUT_PATH = ./input/water.png
OUTPUT_PATH = ./output/
VERIFY_PATH=./verify/
TESTGEN = ../cxxtest/bin/cxxtestgen

TARGETS = test_interactive_tool test_filter_tool
TEST_INTERACTIVE_TOOL = InteractiveToolTest.h
TEST_FILTER_TOOL = FilterToolTest.h

all: setup interactive_tool c++_filter_test MAKE_FILTER_TEST command_line_test

#command_line_test

setup:
	mkdir -p output

clean:
	rm -f *~ *.o *.obj $(TARGETS)
	rm -f *.cpp
	rm -f output/*

interactive_tool:
	./test_interactive_tool

c++_filter_test:

	@echo "\n"
	@echo Start to test filter tool using C++ and diff
	@echo "\n"
	./test_filter_tool

MAKE_FILTER_TEST:	MIA blur_test edge_test quan_test chann_test satur_test motion_blur_test spec_test thresh_test  shar_test

command_line_test:
	./test_mia_command_line.sh

# make sure MIA target exists
MIA:
		(cd ../../Mia; make)
thresh_test:
	@echo start to verify threshold filter
	$(MIATARGET) -i $(OUTPUT_PATH)$(THRESHOLD) -o $(VERIFY_PATH)$(THRESHOLD) -c

blur_test:
	@echo start to verify Blur filter
	$(MIATARGET) -i $(OUTPUT_PATH)$(BLUR) -o $(VERIFY_PATH)$(BLUR) -c

edge_test:
	@echo start to verify edge detection filter
	$(MIATARGET) -i $(OUTPUT_PATH)$(EDGE) -o $(VERIFY_PATH)$(EDGE) -c

quan_test:
	@echo start to verify quantize filter
	$(MIATARGET) -i $(OUTPUT_PATH)$(QUAN) -o $(VERIFY_PATH)$(QUAN) -c

chann_test:
	@echo start to verify channel filter
	$(MIATARGET) -i $(OUTPUT_PATH)$(CHANNEL) -o $(VERIFY_PATH)$(CHANNEL) -c

satur_test:
	@echo start to verify saturation filter
	$(MIATARGET) -i $(OUTPUT_PATH)$(SATUR) -o $(VERIFY_PATH)$(SATUR) -c

shar_test:
	@echo start to verify sharpen filter
	$(MIATARGET) -i $(OUTPUT_PATH)$(SHARPEN) -o $(VERIFY_PATH)$(SHARPEN) -c


motion_blur_test:
	@echo start to verify motion blur filter
	$(MIATARGET) -i $(OUTPUT_PATH)$(E_W_BLUR) -o $(VERIFY_PATH)$(E_W_BLUR) -c
	$(MIATARGET) -i $(OUTPUT_PATH)$(N_S_BLUR) -o $(VERIFY_PATH)$(N_S_BLUR) -c
	$(MIATARGET) -i $(OUTPUT_PATH)$(NE_SW_BLUR) -o $(VERIFY_PATH)$(NE_SW_BLUR) -c
	$(MIATARGET) -i $(OUTPUT_PATH)$(NW_SE_BLUR) -o $(VERIFY_PATH)$(NW_SE_BLUR) -c

spec_test:
	@echo start to verify special filter
	$(MIATARGET) -i $(OUTPUT_PATH)$(SPECIAL) -o $(VERIFY_PATH)$(SPECIAL) -c

test_interactive_tool.cpp: $(TEST_INTERACTIVE_TOOL)
	$(TESTGEN) -o $@ --error-printer $(TEST_INTERACTIVE_TOOL)

test_filter_tool.cpp: $(TEST_FILTER_TOOL)
	$(TESTGEN) -o $@ --error-printer $(TEST_FILTER_TOOL)

%: %.cpp
	$(CXXC) $(CPPFLAGS) $(INCLUDE) -o $@ $< $(LINK_LIBS) $(LDFLAGS)
