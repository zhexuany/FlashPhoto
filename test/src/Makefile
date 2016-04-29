#
# Makefile for UN*X-like systems
#

# COMPILER for CPP
CXXC = g++
CPPFLAGS = -Wall -W -Werror -I. -I../cxxtest
LIBPHOTOFLAGS = -I../../libphoto
TESTGEN = ../cxxtest/bin/cxxtestgen

TARGETS = error_printer stdio_printer yes_no_runner file_printer aborter only
TESTS = *.h

all: $(TARGETS)

clean:
	rm -f *~ *.o *.obj $(TARGETS) $(GUI_TARGETS)
	rm -f tests.cpp error_printer.cpp stdio_printer.cpp file_printer.cpp aborter.cpp only.cpp

distclean: clean
	rm -f Makefile

run: error_printer
	./error_printer

error_printer.cpp: $(TESTS)
	$(TESTGEN) -o $@ --error-printer $(TESTS)

stdio_printer.cpp: $(TESTS)
	$(TESTGEN) -o $@ --runner=StdioPrinter $(TESTS)

file_printer.cpp: file_printer.tpl $(TESTS)
	$(TESTGEN) -o $@ --template=file_printer.tpl $(TESTS)

aborter.cpp: aborter.tpl $(TESTS)
	$(TESTGEN) -o $@ --template=aborter.tpl $(TESTS)

only.cpp: only.tpl $(TESTS)
	$(TESTGEN) -o $@ --template=only.tpl $(TESTS)

tests.cpp: $(TESTS)
	$(TESTGEN) -o $@ $(TESTS)

x11_runner.cpp: $(GUI_TESTS)
	$(TESTGEN) -o $@ --gui=X11Gui $(GUI_TESTS)

qt_runner.cpp: $(GUI_TESTS)
	$(TESTGEN) -o $@ --gui=QtGui $(GUI_TESTS)

%: %.cpp
	$(CXXC) $(CPPFLAGS) -o $@ $<

yes_no_runner: yes_no_runner.cpp tests.cpp
	$(CXXC) $(CPPFLAGS) -o $@ $^

x11_runner: x11_runner.cpp
	$(CXXC) -o $@ $^ $(X11_FLAGS)

qt_runner: qt_runner.cpp
	$(CXXC) -o $@ $^ $(QT_FLAGS)

#
# Local Variables:
# compile-command: "make -fMakefile.unix"
# End:
#
