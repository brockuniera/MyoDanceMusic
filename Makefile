#RTMIDI_FLAGS = -D__MACOSX_CORE__ #D__MACOSX_CORE__ is needed for RtMidi

CC = g++ 
SRCDIR = src
BUILDDIR = build
TARGET = bin/myodance
 
SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS = -g -Wall
CLIBS = -framework myo -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
INC = -I include

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CC) $(CLIBS) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) $(CLIBS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR) $(TARGET)

