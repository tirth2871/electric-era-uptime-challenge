CXX = g++
CXXFLAGS = -Wall -Wextra -O2

TARGET = uptime
SRCS = main.cpp state_machine.cpp parser.cpp uptime.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@rm -f $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

test: all
	cd tests && ./run_tests.sh
