#
# 
#	tested only on Linux

include ../Makefile.config

## Main application file
DEMOS = \
	main\

all: $(DEMOS)

# COMPILE
main: main.cpp $(CSNAP)/Snap.o
	$(CC) $(CXXFLAGS) -o $@ $@.cpp $(CSNAP)/Snap.o -I$(CSNAP) -I$(CGLIB) $(LDFLAGS) $(LIBS)

$(CSNAP)/Snap.o:
	$(MAKE) -C $(CSNAP)

clean:
	rm -f *.o $(DEMOS) *.exe
	rm -rf Debug Release
	rm -rf *.Err demo*.dat

