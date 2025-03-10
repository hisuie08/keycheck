TARGET			:= $(firstword $(MAKECMDGOALS))
ARG1			:= $(word 2, $(MAKECMDGOALS))
ARG2			:= $(word 3, $(MAKECMDGOALS))

CFLAGS			:= -pthread
WINFLAGS		:= -lwsock32 -lgdi32 -lmingw32
NOCONSOLEFLAG	:= -mwindows
OSENV			:=

ifeq ($(OS),Windows_NT)
	OSENV := Windows
else
	UNAME_OS := $(shell uname -s)
	ifeq ($(UNAME_OS),Linux)
		OSENV := Linux
	else
		OSENV := Unknown
	endif
endif

<<<<<<< HEAD
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
=======
run:
ifeq ($(ARG1),)
	@python
else ifeq ($(findstring .py, $(ARG1)), .py)
	python $(ARG1)
else ifeq ($(findstring .cpp, $(ARG1)), .cpp)
    ifeq ($(OSENV), Windows)
		$(eval CFLAGS := $(CFLAGS) $(WINFLAGS))
    endif
    ifneq ($(ARG2), )
		$(eval CFLAGS := $(CFLAGS) $(NOCONSOLEFLAG))
    endif
	g++ -g $(ARG1) $(CFLAGS) -o $(ARG1:.cpp=.exe)
    
else ifeq ($(findstring .c, $(ARG1)), .c)
    ifeq ($(OSENV), Windows)
		$(eval CFLAGS := $(CFLAGS) $(WINFLAGS))
    endif
    ifneq ($(ARG2), )
		$(eval CFLAGS := $(CFLAGS) $(NOCONSOLEFLAG))
    endif
	gcc -g $(ARG1) $(CFLAGS) -o $(ARG1:.c=.exe)
endif
	@echo ERROR No.1 : Processing Complete
	@exit /b 1
>>>>>>> b05b0ab20481e35d804db7c14d752a0ec5f8c713
