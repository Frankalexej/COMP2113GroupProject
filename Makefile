SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)

.PHONY: all clean

all: main

-include $(DEPS)	

%.o:%.cpp
	g++ -pedantic-errors -std=c++11 -c $< -o $@ -MD -MF $*.d -MP 
main: $(OBJS)
	g++ $^ -o $@
clean: 
	rm -f  *.d *.o main