CC = g++-4.9

CFLAGS = -c -Wall
LIBS = -lgmpxx -lgmp
LDFLAGS = $(LIBS)
SOURCES=EEA.cc CRT.cc Main.cc
DEPS = EEA.hxx CRT.hxx
_OBJECTS=$(SOURCES:.cc=.o)
OBJECTS=$(patsubst %,$(ODIR)/%,$(_OBJECTS))
EXECUTABLE=Main
ODIR=obj

run: all
	@./$(EXECUTABLE)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(ODIR)/%.o: %.cc $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	rm -rf $(ODIR) $(EXECUTABLE)
