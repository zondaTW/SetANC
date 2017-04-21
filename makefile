CC = g++
CFLAGS = -g -Wall -m32 -static-libgcc -static-libstdc++
objs := src\message.o src\reg.o src\vmware.o src\vbox.o src\antivm.o src\main.o
bin := main.exe

all: $(bin)

$(bin): $(objs)
	$(CC) $(CFLAGS) $(objs) -o $@

$(objs): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	del /Q $(objs)
	del /Q $(bin)

