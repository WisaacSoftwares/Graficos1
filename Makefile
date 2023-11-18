CC = C:/MinGW/bin/gcc.exe # windows
CFLAGS = -I"./resources/SDL2-windows/include" # windows
LDFLAGS = -L"./resources/SDL2-windows/lib" # windows

# CC = gcc # linux
# CFLAGS = -I"./resources/SDL2-linux/include" # linux
# LDFLAGS = -L"./resources/SDL2-linux/lib" # linux

LIBS = -lSDL2 -lSDL2_ttf

TARGET = prueba2
SRC = prueba2.c resources/library.c resources/functions.c resources/vectores.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TARGET)