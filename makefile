CXX ?= g++

Debug ?= 1
ifeq ($(Debug), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -O2
endif

server: main.cpp config.cpp webserver.cpp ./log/log.cpp
	$(CXX) -o server $^ $(CXXFLAGS) -lpthread -std=c++11

clean:
	rm -rf server