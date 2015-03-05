CC = gcc

C_FLAGS = -g -lnvidia-ml

INCLUDE = -I../include -I/usr/local/cuda/include

OBJS =  main.o      \
	load.o      \
	assign.o    \
	functions.o \
	message.o   \
	kernels.o   \

DAEMON = crcuda_run_daemon

all: $(DAEMON)

$(DAEMON): $(OBJS)
	$(CC) $(C_FLAGS) $(INCLUDE) -o $@ $(OBJS)
	cp -f $(DAEMON) ../bin/.

%.o: %.c
	$(CC) -c $*.c $(INCLUDE)

clean: 
	rm $(OBJS) $(DAEMON)