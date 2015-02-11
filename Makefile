CXX = g++
CXXFLAGS = --std=c++11 -O2

OBJ = cameraocr.o cameraocr.cpp
HDR = cameraocr.h

BIN = cameraocr

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

	$(OBJ): $(HDR)

	clean:
		rm $(OBJ) $(BIN)
