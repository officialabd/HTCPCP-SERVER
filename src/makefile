OBJ_MAIN = main.cpp
OBJ_HANDLERS = handlers/ClientHandler.cpp handlers/ErrorHandler.cpp
OBJ_SERVER = server/Server.cpp
CC = gcc
OBJ_NAME_S = ../out/s
FLAGS = -lstdc++ -lnsl -lpthread

all : compile_server

compile_server: $(OBJ_MAIN) $(OBJ_HANDLERS) $(OBJ_SERVER)
	$(CC) $(OBJ_MAIN) $(OBJ_HANDLERS) $(OBJ_SERVER) $(FLAGS) -o $(OBJ_NAME_S)