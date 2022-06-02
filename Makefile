OBJ_DIR = obj
INC_DIR = include

INCS = $(wildcard $(INC_DIR)/*.hpp)
OBJS = $(patsubst $(INC_DIR)/%.hpp, $(OBJ_DIR)/%.o, $(INCS))
CFLAGS = -Wall -O3 -std=c++14 -I$(INC_DIR)

all: test

test: $(OBJS) test.cpp
	g++ $(CFLAGS) $(OBJS) test.cpp -o $@

$(OBJ_DIR)/%.o: $(INC_DIR)/%.hpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(OBJ_DIR)/*.o test 
