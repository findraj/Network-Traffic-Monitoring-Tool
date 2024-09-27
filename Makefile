# ISA Project 2024

# file: Makefile
# brief: Makefile for ISA project 2024
# author: Jan Findra (xfindr01)


CXX = g++
CFLAGS = -std=c++20 -Wall -Wextra -pedantic -g
TARGET = isa-top
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

all : clean $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f xfindr01.zip

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS) -lpcap
	rm -f $(OBJS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

pack: clean
	zip -r xfindr01.zip .

run: $(TARGET)
	sudo ./isa-top -i en5