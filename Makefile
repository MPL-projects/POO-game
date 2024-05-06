CC = g++
CFLAGS = -std=c++11 -Wall -pthread
LIBS = -lSDL2_image -lSDL2_ttf -lSDL2 -lpthread -lSDL2_mixer

# Les fichiers source
SRC = $(wildcard src/*.cpp)

# Les fichiers objets
OBJ = $(SRC:.cpp=.o)

# Le nom de l'exécutable
EXEC = main_menu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)