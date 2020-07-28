TAR=main
OBJ=main.o
CC=g++

all: $(TAR)
$(TAR): $(OBJ) 
	$(CC)  $(OBJ)  -o $(TAR)

$@: $^
	$(CC) -c $^ -o $@

.PHONY:clean
clean:
	@rm *.o $(TAR)
