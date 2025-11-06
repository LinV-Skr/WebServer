CXX ?= g++

Debug ?= 1
ifeq ($(Debug), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -O2
endif

server: main.cpp config.cpp webserver.cpp
	$(CXX) -o server $^ $(CXXFLAGS) -lpthread

clean:
	rm -rf server