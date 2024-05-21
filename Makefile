CC = g++
CFLAGS = -std=c++11 -Wall -pthread -ggdb3
LIBS = -lSDL2_image -lSDL2_ttf -lSDL2 -lSDL2_mixer

# Les fichiers source
SRC = $(wildcard src/*.cpp)
SRC2 = $(filter-out src/main.cpp, $(wildcard src/*.cpp)) $(wildcard unittest/*.cpp)

# Les fichiers objets
OBJ = $(SRC:.cpp=.o)
OBJ2 = $(SRC2:.cpp=.o)

# Le nom de l'exécutable
EXEC = main
TEST_EXEC = test

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBS) -o $(EXEC)

test : $(TEST_EXEC)

$(TEST_EXEC): $(OBJ2)
	$(CC) $(OBJ2) $(CFLAGS) $(LIBS) -o $(TEST_EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(EXEC)
	rm -f src/*.o $(TEST_EXEC)
	rm -f unittest/*.o $(TEST_EXEC)

run_valgrind:
	valgrind --leak-check=full --show-reachable=yes ./$(EXEC)

run_valgrind2:
	valgrind --gen-suppressions=all --suppressions=linux_sdl_gl.sup --leak-check=full --show-leak-kinds=all ./$(EXEC)