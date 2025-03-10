CC     = g++
CFLAGS = -g -pthread -lwsock32 -mwindows -lgdi32 -lmingw32
TARGET = keycheck.exe
SRCS   = keycheck.cpp

OBJS   = $(SRCS:.cpp=.o)
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

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

# $@ : 現在のターゲット
# $^ : すべての依存ファイルのリスト

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

# -c : オブジェクトファイルを生成

all: $(OBJS) $(TARGET) 

clean:
ifeq ($(OSENV), Linux)
	@rm -f $(OBJS) *.d
else ifeq ($(OSENV), Windows)
	@del $(OBJS) *.d
else
	@echo Unknown OS
endif
	@echo complete