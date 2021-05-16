OBJ_MAIN = main.cpp
OBJ_HANDLERS = handlers/ClientHandler.cpp handlers/ErrorHandler.cpp
OBJ_SERVER = server/Server.cpp
OBJ_PARSER = parser/Parser.cpp parser/ErrorResponse.cpp

CC = gcc
OBJ_NAME_S = ../out/s
FLAGS = -lstdc++ -lnsl -lpthread

all : compile_server

compile_server: $(OBJ_MAIN) $(OBJ_HANDLERS) $(OBJ_SERVER) $(OBJ_PARSER)
	$(CC) $(OBJ_MAIN) $(OBJ_HANDLERS) $(OBJ_SERVER) $(OBJ_PARSER) $(FLAGS) -o $(OBJ_NAME_S)