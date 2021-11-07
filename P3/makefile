
#Manejo de directorios
BASEDIR = .
INCLDIR = $(BASEDIR)/include
SRCDIR  = $(BASEDIR)/src
BINDIR  = $(BASEDIR)/bin

#Opciones del compilador
CC = g++
OUTFILE = cache_sim.out
CFLAGS  = -std=c++11 -g -I $(INCLDIR) -o $(BINDIR)/$(OUTFILE)
LFLAGS  =

build:
	mkdir -p bin
	$(CC) $(SRCDIR)/*.cpp $(CFLAGS) $(LFLAGS)

# Runs the benchmark with a cache block size sweep
barrido-tamano:
	gunzip -c mcf.trace.gz | $(BINDIR)/$(OUTFILE) 32 64 16
	gunzip -c mcf.trace.gz | $(BINDIR)/$(OUTFILE) 64 64 16
	gunzip -c mcf.trace.gz | $(BINDIR)/$(OUTFILE) 128 64 16

# Runs the benchmark with a cache size sweep
barrido-asociatividad:
	gunzip -c mcf.trace.gz | $(BINDIR)/$(OUTFILE) 32 64 4
	gunzip -c mcf.trace.gz | $(BINDIR)/$(OUTFILE) 32 64 8
	gunzip -c mcf.trace.gz | $(BINDIR)/$(OUTFILE) 32 64 16

# Runs the benchmark with a ways size sweep
barrido-linea:
	gunzip -c mcf.trace.gz | $(BINDIR)/$(OUTFILE) 32 32 8
	gunzip -c mcf.trace.gz | $(BINDIR)/$(OUTFILE) 32 64 8
	gunzip -c mcf.trace.gz | $(BINDIR)/$(OUTFILE) 32 128 8