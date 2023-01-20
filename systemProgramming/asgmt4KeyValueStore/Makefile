SRCS = static_main.c
SRCSD = dynamic_main.c
LIBSRCS = open.c close.c put.c get.c 
TARG = kvs_static
TARGD = kvs_dynamic

CC = gcc
OPTS = -Wall -O
LIBS = -L. -lkvs

OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LARSD = libkvs.so


all: 

static: $(TARG)

$(TARG) : $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) 

$(LARS) : $(LOBJS)
	ar rs $(LARS) $(LOBJS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

dynamic: $(TARGD)

$(TARGD) : $(LARSD)
	$(CC) -o $(TARGD) $(SRCSD) -ldl

$(LARSD) : $(LIBSRCS)
	$(CC) -fPIC -shared -o $@ $(LIBSRCS)

clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(TARG) $(LARSD) $(TARGD)
