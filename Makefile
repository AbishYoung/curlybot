CC = gcc
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
CFLAGS = -Wall -g -I$(INCDIR)

all: setup curlybot

setup:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

run:
	$(BINDIR)/curlybot

curlybot: curlybot.o astring.o querystring.o 
	$(CC) $(CFLAGS) -o $(BINDIR)/curlybot $(OBJDIR)/curlybot.o $(OBJDIR)/astring.o $(OBJDIR)/querystring.o

curlybot.o:
	$(CC) $(CFLAGS) -c $(SRCDIR)/curlybot.c -o $(OBJDIR)/curlybot.o

astring.o:
	$(CC) $(CFLAGS) -c $(SRCDIR)/astring.c -o $(OBJDIR)/astring.o

querystring.o:
	$(CC) $(CFLAGS) -c $(SRCDIR)/querystring.c -o $(OBJDIR)/querystring.o

$PHONY: all setup clean run