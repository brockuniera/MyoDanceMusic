#CC = g++
#CFLAGS = -Wall
#RTMIDI_FLAGS = -D__MACOSX_CORE__ #D__MACOSX_CORE__ is needed for RtMidi
#CLIBS = -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
#objects = main.o RtMidi.o

#default: $(objects)
	#$(CC) $(objects) $(CFLAGS) $(CLIBS)

#midiout: RtMidi.o midiout.o
	#$(CC) RtMidi.o midiout.o $(CFLAGS) $(CLIBS)

#RtMidi.o: RtMidi.h
	#$(CC) -c $(CFLAGS) $(RTMIDI_FLAGS) $(CLIBS) RtMidi.cpp
#main.o: RtMidi.h

#midiout.o: RtMidi.h

#.PHONY : clean
#clean:
	#rm $(objects)




CC = g++ 
SRCDIR = src
BUILDDIR = build
TARGET = bin/myodance
 
SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS = -g -Wall
INC = -I include

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR) $(TARGET)

