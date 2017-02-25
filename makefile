CC = gcc

IDIR = include
SDIR = src
BDIR = bin

CFLAGS = -I $(IDIR)

# make 

all: server client

clean:
	rm $(BDIR) -r -f
	

server: $(IDIR)/libserver.c $(SDIR)/server.c
	@mkdir -p $(BDIR)
	@echo Compile server
	$(CC) $(CFLAGS) $^ -o $(BDIR)/$@

client: $(IDIR)/libclient.c $(SDIR)/client.c 
	@mkdir -p $(BDIR)
	@echo Compile client
	$(CC) $(CFLAGS) $^ -o $(BDIR)/$@