CXX = g++
CXXFLAGS = -O2

SRC = src/cameraocr.cpp
OBJ = $(SRC:.cpp=.o)
HDR = src/cameraocr.h

BIN = cameraocr

all: $(BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

$(OBJ): $(HDR)

clean:
	$(RM) $(OBJ) $(BIN)
