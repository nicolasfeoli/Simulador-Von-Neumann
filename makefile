hellomake: Von.c 
	cc `pkg-config --cflags gtk+-3.0` Von.c -o Von `pkg-config --libs gtk+-3.0`
