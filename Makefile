CXX = clang++
CXXFLAGS = -I/usr/local/include `pkg-config --cflags --libs tesseract`
#CXXFLAGS = -std=c++11 -O2

SRC = src/cameraocr.cpp
OBJ = $(SRC:.cpp=.o)
HDR = src/cameraocr.h

BIN = cameraocr

all: $(BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ): $(HDR)

clean:
	$(RM) $(OBJ) $(BIN)
