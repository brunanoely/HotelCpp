CC = g++
CFLAGS = -std=c++17 -Wall -I. -Irepository
OUT = programa

SRCS = main.cpp usecase/cliente.cpp usecase/funcionario.cpp usecase/quarto.cpp usecase/estadia.cpp repository/repository.cpp
OBJS = $(SRCS:%.cpp=%.o)

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)
