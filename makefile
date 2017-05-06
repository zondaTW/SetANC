CC = g++
CFLAGS = -g -Wall -m32 -static-libgcc -static-libstdc++
NONE_WINDOWS_CFLAGS = -g -Wall -m32 -static-libgcc -static-libstdc++ -mwindows
objs_c := src\message.o src\reg.o src\vmware.o src\vbox.o src\antivm.o src\process.o src\file.o
exe_forever_obj_c := src\execute_forever.o
objs_cpp := src\SetAnc_main.o
boot_objs_cpp := src\SetANC_boot.o
objs := $(objs_c) $(objs_cpp)
boot_objs := $(objs_c) $(boot_objs_cpp) 
exe_forever_objs := $(exe_forever_obj_c)
bin := SetANC.exe
boot_bin := SetANC_boot.exe
exe_forever_bin := exe_forever.exe

all: $(bin) $(boot_bin) $(exe_forever_bin)

$(bin): $(objs)
	$(CC) $(CFLAGS) $(objs) -o $@

$(boot_bin): $(boot_objs)
	$(CC) $(CFLAGS) $(boot_objs) -o $@

$(exe_forever_bin): $(exe_forever_objs)
	$(CC) $(NONE_WINDOWS_CFLAGS) $(exe_forever_objs) -o $@ 

$(objs_c): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(boot_objs_cpp): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(exe_forever_obj_c): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(objs_cpp): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	del /Q $(objs)
	del /Q $(bin)
	del /Q $(boot_objs)
	del /Q $(boot_bin)
	del /Q $(exe_forever_objs)
	del /Q $(exe_forever_bin)

