all: server

HDRS = Accelerometer.h Motor.h
CMN_OBJS = Accelerometer.o Motor.o
DMP_OBJS = main.o

CXXFLAGS = -DDMP_FIFO_RATE=9 -Wall -g -O2

$(CMN_OBJS) $(DMP_OBJS) : $(HDRS)

server: $(CMN_OBJS) $(DMP_OBJS)
	$(CXX) -o $@ $^ -lm

clean:
	rm -f $(CMN_OBJS) $(DMP_OBJS) server

