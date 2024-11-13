# ISA Project 2024

# file: Makefile
# brief: Makefile for ISA project 2024
# author: Jan Findra (xfindr01)


CXX = g++
CFLAGS = -std=c++20 -Wall -Wextra -pedantic -g
TARGET = isa-top
SRCS = main.cpp messages.cpp args.cpp screen.cpp packetHandler.cpp
OBJS = $(SRCS:.cpp=.o)

all : clean $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f xfindr01.tar

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS) -lpcap -lncurses
	rm -f $(OBJS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

pack: clean
	tar --exclude='.vscode' --exclude='.git' --exclude='.gitignore' -cf xfindr01.tar *

test:
	sudo ./test/test.sh