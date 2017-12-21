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
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(BINARY)

$(BUILDDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(SOURCEDIR) -c $< -o $@

clean:
	rm -rf Core/*.o ./*.o $(BINARY)
