install:
	g++ -I /usr/local/include `pkg-config --cflags --libs tesseract` src/main.cpp -o bin/main.o
