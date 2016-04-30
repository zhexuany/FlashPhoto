#
# Makefile for UN*X-like systems
#

# COMPILER for CPP
CXXC = g++
CPPFLAGS = -Wall -W -Werror -I. -I../cxxtest -Wunused-parameter -std=c++11
PHOTO_PATH = ../../libphoto
PNG_PATH = ../../libpng
JPEG_PATH = ../../libjpeg
INCLUDE += -I$(PHOTO_PATH)/include
# -I$(PNG_PATH)/include -I$(JPEG_PATH)/include
LINK_LIBS += -L$(PHOTO_PATH)/lib/  -L$(PNG_PATH)/lib/  -L$(JPEG_PATH)/lib/
LDFLAGS += -lpng -lz -ljpeg -lphoto
PHOTO_LIB = $(PHOTO_PATH)/lib/libphoto.a
TESTGEN = ../cxxtest/bin/cxxtestgen

TARGETS = error_printer
TESTS = *.h

all: $(TARGETS) run

clean:
	rm -f *~ *.o *.obj $(TARGETS) $(GUI_TARGETS)
	rm -f tests.cpp error_printer.cpp stdio_printer.cpp file_printer.cpp aborter.cpp only.cpp

run:
	./error_printer

error_printer.cpp: $(TESTS)
	$(TESTGEN) -o $@ --error-printer $(TESTS)

tests.cpp: $(TESTS)
	$(TESTGEN) -o $@ $(TESTS)

%: %.cpp
	$(CXXC) $(CPPFLAGS) $(INCLUDE) $(LINK_LIBS) -o $@ $< $(LDFLAGS)
