# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
OBJDIR = obj
BINDIR = bin
LIBDIR = lib
MANDIR = man/man3

SRC = src/mystrfunctions.c src/myfilefunctions.c src/main.c
OBJS = $(OBJDIR)/mystrfunctions.o $(OBJDIR)/myfilefunctions.o $(OBJDIR)/main.o
PIC_OBJS = $(OBJDIR)/mystrfunctions.pic.o $(OBJDIR)/myfilefunctions.pic.o

.PHONY: all multifile static dynamic clean install test

all: multifile static dynamic

# -- Direct multifile compilation (v0.1.1-multifile)
multifile: $(BINDIR)/client

$(BINDIR)/client: $(SRC) | $(BINDIR)
	$(CC) $(CFLAGS) $(SRC) -o $@

# -- Static library build (v0.2.1-static)
static: $(LIBDIR)/libmyutils.a $(BINDIR)/client_static

$(LIBDIR)/libmyutils.a: $(OBJDIR)/mystrfunctions.o $(OBJDIR)/myfilefunctions.o | $(LIBDIR)
	ar rcs $@ $^

$(BINDIR)/client_static: $(OBJDIR)/main.o $(LIBDIR)/libmyutils.a | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJDIR)/main.o -L$(LIBDIR) -lmyutils -o $@

# -- Dynamic library build (v0.3.1-dynamic)
dynamic: $(LIBDIR)/libmyutils.so $(BINDIR)/client_dynamic

$(LIBDIR)/libmyutils.so: $(PIC_OBJS) | $(LIBDIR)
	$(CC) -shared -o $@ $^

$(BINDIR)/client_dynamic: $(OBJDIR)/main.o $(LIBDIR)/libmyutils.so | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJDIR)/main.o -L$(LIBDIR) -lmyutils -o $@

# Object compilation rules
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.pic.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# directories
$(OBJDIR) $(LIBDIR) $(BINDIR):
	mkdir -p $@

# Install man pages and binary (requires sudo)
install: all
	sudo cp $(BINDIR)/client /usr/local/bin/
	sudo mkdir -p /usr/local/share/man/man3
	sudo cp $(MANDIR)/*.1 /usr/local/share/man/man3/
	# Update man database (may ask for sudo)
	- sudo mandb || true

# Small test helper: run dynamic client (set LD_LIBRARY_PATH)
test_dynamic:
	LD_LIBRARY_PATH=$(PWD)/lib $(BINDIR)/client_dynamic

clean:
	rm -rf $(OBJDIR)/* $(LIBDIR)/* $(BINDIR)/*

#export LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH
#./bin/client_dynamic

