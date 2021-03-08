CFLAGS += -Iinclude -Irosbridge_functions/include

ifdef OS
	LDFLAGS += -lws2_32
endif

all:
	gcc -std=c90 $(CFLAGS) -o counter counter.c rosbridge_functions/rosbridge_functions.c $(LDFLAGS)
