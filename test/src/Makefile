#
# Makefile for UN*X-like systems
#

# COMPILER for CPP
CXXC = g++
CPPFLAGS = -Wall -W -Werror -I. -I../cxxtest -Wunused-parameter
PHOTO_PATH = ../../libphoto
GLUI_PATH = ../../glui
PNG_PATH = ../../libpng
JPEG_PATH = ../../libjpeg
INCLUDE += -I$(PHOTO_PATH)
# -I$(PNG_PATH)/include -I$(JPEG_PATH)/include
LINK_LIBS +=  -L$(GLUI_PATH)/lib/ -lglui -lpthread -L$(PHOTO_PATH)/lib/ -lphoto -L$(PNG_PATH)/lib/ -lpng -L$(JPEG_PATH)/lib/ -ljpeg -lz
PHOTO_LIB = $(PHOTO_PATH)/lib/libphoto.a
TESTGEN = ../cxxtest/bin/cxxtestgen

TARGETS = error_printer
TESTS = *.h

all: $(TARGETS)

clean:
	rm -f *~ *.o *.obj $(TARGETS) $(GUI_TARGETS)
	rm -f tests.cpp error_printer.cpp stdio_printer.cpp file_printer.cpp aborter.cpp only.cpp

distclean: clean
	rm -f Makefile

all: error_printer
	./error_printer

error_printer.cpp: $(TESTS)
	$(TESTGEN) -o $@ --error-printer $(TESTS)

tests.cpp: $(TESTS)
	$(TESTGEN) -o $@ $(TESTS)

%: %.cpp
	$(CXXC) $(CPPFLAGS) $(INCLUDE) $(LINK_LIBS) -o $@ $<

yes_no_runner: yes_no_runner.cpp tests.cpp
	$(CXXC) $(CPPFLAGS) $(INCLUDE) $(LINK_LIBS) -o $@ $^
