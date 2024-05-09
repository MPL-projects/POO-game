CC = g++ # Le compilateur
CFLAGS = -std=c++11 -Wall -pthread -lSDL2_image -lSDL2_ttf -lSDL2 -lpthread -lSDL2_mixer

# Les fichiers source
SRC = $(wildcard *.cpp) ../game.cpp ../controller.cpp

# Les fichiers objets
OBJ = $(SRC:.cpp=.o)

# Le nom de l'exécutable
EXEC = joy

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)