all: server

HDRS = Accelerometer.h Motors.h PID.h Logger.h Network.h
OBJS = main.o Accelerometer.o Motors.o PID.o Logger.o Network.o

CXXFLAGS = -Wall -Wextra -O2 -std=c++0x

$(OBJS) : $(HDRS)

server: $(OBJS)
		$(CXX) -o $@ $^ -lm

clean:
		rm -f $(OBJS) server

sendToRpi:
		scp -r ~/Programmation/Raspcopter/raspberry-server/* raspberrypi:~/server

getFromRpi:
		scp -r raspberrypi:~/server/* ~/Programmation/Raspcopter/raspberry-server
