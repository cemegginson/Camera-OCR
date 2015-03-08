CXX = clang++
CXXFLAGS = -I/usr/local/include -std=c++11 -O2
CXXLINKFLAGS = `pkg-config --cflags --libs opencv tesseract`

SRC = src/cameraocr.cpp
OBJ = $(SRC:.cpp=.o)
HDR = src/cameraocr.h

BIN = cameraocr

all: $(BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(CXXLINKFLAGS) -o $@ $^

$(OBJ): $(HDR)

clean:
	$(RM) $(OBJ) $(BIN)
