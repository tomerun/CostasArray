OBJ = main.o
TARGET = solver
COMPILEOPT = -Wall -Wno-sign-compare -O2 -std=c++14
LINKOPT = 

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	g++ $(LINKOPT) -o $@ $(OBJ)

%.o: %.cpp
	g++ $(COMPILEOPT) -c $<

clean:
	rm -f $(TARGET)
	rm -f $(OBJ)
