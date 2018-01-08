CC      = g++
CFLAGS  = -Wall -lpthread -D_REENTRANT -lGLEW -lGLU -lGL -lglut
LDFLAGS = -lm

SOURCEDIR = .
BUILDDIR  = .
BINARY    = ShaderTest

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.cpp=%.o))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINARY) $(CFLAGS) $(LDFLAGS) 

$(BUILDDIR)/%.o: %.cpp
	$(CC) -I$(SOURCEDIR) -c $< -o $@ $(CFLAGS) $(LDFLAGS) 

clean:
	rm -rf Core/*.o ./*.o $(BINARY)
