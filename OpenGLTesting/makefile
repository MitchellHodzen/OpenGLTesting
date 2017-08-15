CC = g++
CLIBS = `sdl2-config --cflags --libs` -lSDL2_image -ldl -lGL -g 
INCLUDES = -Iinclude
OUTPUT = test
DEBUGOUTPUTDIR = bin/debug
RELEASEOUTPUTDIR = bin/release
OBJDIR = bin
SRCDIR = src

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
POBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=%.o) glad.o 
OBJECTS = $(addprefix $(OBJDIR)/, $(POBJECTS))

$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) $(CLIBS) -o $(DEBUGOUTPUTDIR)/$(OUTPUT) $(INCLUDES)
	@echo "\n"Debug build completed\; Enter $(DEBUGOUTPUTDIR)/$(OUTPUT) to run."\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(CLIBS) $(INCLUDES)

$(OBJDIR)/glad.o: $(SRCDIR)/glad.c
	$(CC) -c $< -o $@ $(CLIBS) $(INCLUDES)

clean:
	rm $(OBJDIR)/*.o $(DEBUGOUTPUTDIR)/$(OUTPUT) #$(RELEASEOUTPUTDIR)/$(OUTPUT)

#release: $(OBJECTS)
#	$(CC) $(OBJECTS) $(CLIBS) -O3 -o $(RELEASEOUTPUTDIR)/$(OUTPUT)
#	@echo "\n"Release build completed\; Enter $(RELEASEOUTPUTDIR)/$(OUTPUT) to run."\n"
