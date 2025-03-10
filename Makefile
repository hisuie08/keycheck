CC     = g++
CFLAGS = -pthread -lwsock32 -mwindows -lgdi32 -lmingw32
TARGET = keycheck.exe
SRCS   = keycheck.cpp

#OBJS   = $(SRCS:.cpp=.o)
INCDIR = 
LIBDIR = 
LIBS   = 

OSENV =

ifeq ($(OS),Windows_NT)
	OSENV = Windows
else
	UNAME_OS := $(shell uname -s)
	ifeq ($(UNAME_OS),Linux)
		OSENV = Linux
	else
		OSENV = Unknown
	endif
endif

compile:
	$(CC) -g $(SRCS) $(CFLAGS) -o $(TARGET)
	@echo compiled


# $@ : 現在のターゲット
# $^ : すべての依存ファイルのリスト
# -c : オブジェクトファイルを生成

all: compile

cleanup:
ifeq ($(OSENV), Linux)
	@rm -f $(TARGET) *.d
else ifeq ($(OSENV), Windows)
	@del $(TARGET) *.d
else
	@echo Unknown OS
endif
	@echo completed