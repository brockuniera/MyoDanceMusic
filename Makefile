CC = g++ 
SRCDIR = src
BUILDDIR = build
TARGET = bin/myodance
 
SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CLIBS = -framework myo -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
CFLAGS = -g -Wall -std=c++11 -D__MACOSX_CORE__
INC = -I include

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CC) $(CLIBS) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CLIBS) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR) $(TARGET)

