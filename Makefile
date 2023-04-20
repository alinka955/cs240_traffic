CC = g++
LD = $(CC)
INCDIR = -I../
CCFLAGS = -Wall -std=c++17 $(INCDIR) -g -c
LDFLAGS = -Wall -std=c++17 -g
OBJS = Simulation.o readinput.o VehicleBase.o Animator.o RandomClass.o
EXEC = simulation

simulation: $(OBJS)
        $(LD) $(LDFLAGS) $(OBJS) -o $@

Simulation.o: Simulation.cpp Animator.h VehicleBase.h RandomClass.h readinput.h
        $(CC) $(CCFLAGS) Simulation.cpp

readinput.o: readinput.cpp readinput.h
        $(CC) $(CCFLAGS) readinput.cpp

VehicleBase.o: VehicleBase.cpp VehicleBase.h
        $(CC) $(CCFLAGS) VehicleBase.cpp

Animator.o: Animator.cpp Animator.h
        $(CC) $(CCFLAGS) Animator.cpp

RandomClass.o: RandomClass.cpp RandomClass.h
        $(CC) $(CCFLAGS) RandomClass.cpp

all: simulation

.PHONY: clean
clean:
        rm -f $(OBJS) $(EXEC)

