CC = C:/MinGW/bin/gcc.exe # windows
CFLAGS = -I"./resources/SDL2-windows/include" # windows
LDFLAGS = -L"./resources/SDL2-windows/lib" # windows

# CC = gcc # linux
# CFLAGS = -I"./resources/SDL2-linux/include" # linux
# LDFLAGS = -L"./resources/SDL2-linux/lib" # linux

LIBS = -lSDL2 -lSDL2_ttf

TARGET = main
SRC = main.c resources/library.c resources/vectores.c resources/controlador.c resources/render.c resources/ui.c
# resources/functions.c 

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TARGET)