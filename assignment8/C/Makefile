CC = g++-4.9

CFLAGS = -c -std=c++11 -Wall -L/usr/local/include
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
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	rm -f $(ODIR)/*.o $(EXECUTABLE)
