#!make -f

all: demo
	./$<

test:  PhysicalNumber.o OurPhysicalNumberTest.o 
	clang++-5.0 -std=c++17 $^ -o test

%.o: %.cpp
	clang++-5.0 -std=c++17 -Wno-unused-comparison --compile $< -o $@

%PhysicalNumber%.o: PhysicalNumber.h Unit.h
%Test%.o: badkan.hpp

clean:
	rm -f *.o test
