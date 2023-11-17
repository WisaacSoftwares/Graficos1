# CC = gcc
CC = C:/MinGW/bin/gcc.exe
CFLAGS = -I"./resources/SDL2/include"
LDFLAGS = -L"./resources/SDL2/lib"
LIBS = -lSDL2 -lSDL2_ttf

TARGET = prueba2
SRC = prueba2.c resources/library.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TARGET)