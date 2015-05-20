# set compiler and compile options
EXEC = tnb
MPICC = g++
OPTS = -O0 -Wall -g
CFLAGS = $(OPTS) -I/usr/include/freetype2
LDFLAGS = $(OPTS) -lSOIL `pkg-config --libs glfw3 ftgl --static`

# set a list of directories
INCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
SRCDIR = ./src

# set the include folder where the .h files reside
CFLAGS += -I$(INCDIR) -I$(SRCDIR)

# add here the source files for the compilation
SOURCES = tnb.cxx window.cxx sprite.cxx character.cxx player.cxx \
			static_object.cxx floor.cxx physics_engine.cxx

# create the obj variable by substituting the extension of the sources
# and adding a path
_OBJ = $(SOURCES:.cxx=.o)
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: $(BINDIR)/$(EXEC)

run: $(BINDIR)/$(EXEC)
	mpirun -np 4 $(BINDIR)/$(EXEC) 4

$(BINDIR)/$(EXEC): $(OBJ)
	$(MPICC) -o $(BINDIR)/$(EXEC) $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cxx
	$(MPICC) -c -o $@ $< $(CFLAGS) $(DIRECTIVES)

clean:
	rm -vf $(BINDIR)/$(EXEC) $(OBJ)
