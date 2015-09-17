UNAME_O := $(shell uname -o)



ifeq ($(UNAME_O), Cygwin)
	# cygwin
	GTEST_DIR = googletest
	GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
			$(GTEST_DIR)/include/gtest/internal/*.h


	CPPFLAGS += -isystem $(GTEST_DIR)/include
	CPPFLAGS += -L$(GTEST_DIR)/make

	CXX        := g++
	CXXFLAGS   := -pedantic -std=gnu++11 -Wall

else
	# Not cygwin
	CXX        := g++-4.8
	CXXFLAGS   := -pedantic -std=c++11 -Wall

endif



LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind


clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f TestKitayuta
	rm -f RunCollatz
	rm -f RunCollatz.tmp
	rm -f CollatzSpoj
	rm -f TestCollatz
	rm -f TestCollatz.tmp
	rm -f TestCollatzSpeed

config:
	git config -l

scrub:
	make  clean
	rm -f  Collatz.log
	rm -rf collatz-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunCollatz.tmp TestCollatz.tmp


#------------------------- TestKitayuta
TestKitayuta: Kitayuta.h Kitayuta.c++ TestKitayuta.c++
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) Kitayuta.c++ TestKitayuta.c++ -o TestKitayuta $(LDFLAGS)



#------------------------- RunCollatz
#RunCollatz: Collatz.h Collatz.c++ RunCollatz.c++
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) Collatz.c++ RunCollatz.c++ -o RunCollatz

RunCollatz: Collatz.h Collatz.c++ RunCollatz.c++ CollatzLazyAggressive.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) Collatz.c++ RunCollatz.c++ CollatzLazyAggressive.o -o RunCollatz

RunCollatz.tmp: RunCollatz
	./RunCollatz < RunCollatz.in > RunCollatz.tmp
	diff RunCollatz.tmp RunCollatz.out


#------------------------- TestCollatz
CollatzLazy.o: CollatzLazy.h CollatzLazy.c++
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) -c CollatzLazy.c++

CollatzLazyAggressive.o: CollatzLazyAggressive.h CollatzLazyAggressive.c++
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) -c CollatzLazyAggressive.c++

CollatzLazyAggressiveArray.o: CollatzLazyAggressiveArray.h CollatzLazyAggressiveArray.c++
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) -c CollatzLazyAggressiveArray.c++

#TestCollatz: Collatz.h Collatz.c++ TestCollatz.c++ CollatzLazy.o
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) Collatz.c++ TestCollatz.c++ CollatzLazy.o -o TestCollatz $(LDFLAGS)

#TestCollatz: Collatz.h Collatz.c++ TestCollatz.c++ CollatzLazyAggressiveArray.o
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) Collatz.c++ TestCollatz.c++ CollatzLazyAggressiveArray.o -o TestCollatz $(LDFLAGS)

TestCollatz: Collatz.h Collatz.c++ TestCollatz.c++ CollatzLazyAggressive.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) Collatz.c++ TestCollatz.c++ CollatzLazyAggressive.o -o TestCollatz $(LDFLAGS)

TestCollatz.tmp: TestCollatz
	$(VALGRIND) ./TestCollatz                                       >  TestCollatz.tmp 2>&1
	$(GCOV) -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.tmp
	$(GCOV) -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.tmp
	cat TestCollatz.tmp


#------------------------- TestCollatzSpeed
CollatzGetBounds.o: CollatzGetBounds.h CollatzGetBounds.c++
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) -c CollatzGetBounds.c++

TestCollatzSpeed: Collatz.h Collatz.c++ TestCollatzSpeed.c++ CollatzGetBounds.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GCOVFLAGS) Collatz.c++ TestCollatzSpeed.c++ CollatzGetBounds.o -o TestCollatzSpeed $(LDFLAGS)


#------------------------- CollatzSpoj
CollatzSpoj: CollatzSpoj.c++
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) CollatzSpoj.c++ -o CollatzSpoj -pthread
