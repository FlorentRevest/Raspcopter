CXX=arm-linux-gnueabihf-g++

all: server

HDRS = Accelerometer.h Motors.h PID.h Logger.h Network.h
OBJS = main.o Accelerometer.o Motors.o PID.o Logger.o Network.o

CXXFLAGS = -Wall -Wextra -O2 -std=c++0x

$(OBJS) : $(HDRS)

server: $(OBJS)
		$(CXX) -o $@ $^ -lm -lpthread -lenet -lusb-1.0

clean:
		rm -f $(OBJS) server

send:
		scp -r server raspberry-pi:~/server

run:
		ssh raspberry-pi './server'

stop:
		ssh raspberry-pi 'killall -v server'
