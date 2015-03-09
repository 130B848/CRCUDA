CC = gcc

C_FLAGS = -g -shared -fPIC -lpthread -ldl -lstdc++ -lcuda

INCLUDE = -I../include -I/usr/local/cuda/include

OBJS = message.o   \
       libcudart.o \
       connect.o   \
       event.o     \
       stream.o    \
       device.o    \

SHARED = libcudart.so
LINK1  = libcudart.so.5.5
LINK2  = libcudart.so.5.5.22

all: $(SHARED)

$(SHARED): $(OBJS) ../include/iden.h
	$(CC) $(C_FLAGS) $(INCLUDE) -o $@ $(OBJS)
	cp -f $(SHARED) ../lib64

%.o: %.c
	$(CC) -fPIC -c $*.c $(INCLUDE)

link:
	ln -s ../lib64/$(SHARED) ../lib64/$(LINK1)
	ln -s ../lib64/$(SHARED) ../lib64/$(LINK2)

clean: 
	rm $(OBJS) $(SHARED)