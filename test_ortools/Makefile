CC = g++
CFLAGS = -std=c++17
INCDIRS = /Users/usuario/Desktop/DITELLA/TD5/TP_1_TD5_Algoritmos/or-tools/include/
LIBDIRS = /Users/usuario/Desktop/DITELLA/TD5/TP_1_TD5_Algoritmos/or-tools/lib/
SRC = test_flow.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = test_flow

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -L$(LIBDIRS) -lortools -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCDIRS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
