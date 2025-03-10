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

all: compile

#compileは keycheck.cpp, ioset.hpp,ioset.hpp.gch に依存。
#ioset.hpp.gchがあればioset.hppの代わりにinclude（高速）。
#ioset.hpp.gchがない場合、下のルールが実行されて生成される。
compile:$(SRCS) ioset.hpp ioset.hpp.gch
	$(CC) -g $(SRCS) $(CFLAGS) -include ioset.hpp -o $(TARGET)
	@echo compiled

# $@ : 現在のターゲット
# $^ : すべての依存ファイルのリスト
# -c : オブジェクトファイルを生成


cleanup:
ifeq ($(OSENV), Linux) #cleanupでは事前コンパイルヘッダも掃除。
	@rm -f $(TARGET) *.d
	@rm -f *.gch
else ifeq ($(OSENV), Windows)
	@del $(TARGET) *.d
	@del *.gch
else
	@echo Unknown OS
endif
	@echo completed

ioset.hpp.gch: ioset.hpp 
# compileから必要に応じて呼び出される、事前コンパイルヘッダ作成ルール
	$(CC) -g -x c++-header $< -o $@
