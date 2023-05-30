CPPFLAGS = -I include/ -I include/device -Wall  -pthread -Wno-address-of-packed-member

SRCS := $(wildcard src/**/*.c)
OBJS := $(patsubst %.c, build/%.o,$(notdir $(SRCS)))
HEADERS = $(wildcard include/**/*.h)

all: $(OBJS) 

$(OBJS): $(SRCS) $(HEADERS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

cmake:
	cmake -S . -B build

.PHONY: clean run cmake

clean:
	rm -rf build/*.o  net
	rm -rf build/CMakeFiles
	rm -rf build/cmake_install.cmake
	rm -rf build/CMakeCache.txt
	rm -rf build/Makefile
