CPPFLAGS = -I include/ -Wall  -pthread -Wno-address-of-packed-member

SRCS := $(wildcard src/**/*.c)
OBJS := $(patsubst %.c, build/%.o,$(notdir $(SRCS)))
HEADERS = $(wildcard include/**/*.h)
TARGET:= net

all:  $(TARGET) 

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/main.c -o build/test.o
	$(CC) $(OBJS) build/test.o -o $(TARGET) 
	@echo

# 构建目标
$(OBJS): $(SRCS) $(HEADERS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

run:
	./net

cmake:
	cmake -S . -B build

.PHONY: clean run net cmake

clean:
	rm -rf build/*.o  net
	rm -rf build/CMakeFiles
	rm -rf build/cmake_install.cmake
	rm -rf build/CMakeCache.txt
	rm -rf compile_commands.json
	rm -rf build/Makefile
