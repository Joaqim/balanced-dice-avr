.PHONY : clean

CPPFLAGS= -fPIC -g -I../include
LDFLAGS= -shared

SOURCES = $(shell find ../src -wholename '../src/*.cpp' -not -wholename '../src/main.cpp')
HEADERS = $(shell echo ../include/*.h)
OBJECTS=$(SOURCES:.cpp=.o)
#OBJECTS=$(patsubst ../src/%.cpp,%.o,$(SOURCES))

BALANCED_DICE_INCDIR=../include

TARGET=./libbalanced-dice.so

all: $(TARGET) test

clean:
	rm -f $(OBJECTS) $(TARGET) test

$(TARGET) : $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

#$(OBJECTS) : $(SOURCES)
#	$(CC) $(CPPFLAGS) -c $< -o $@


test: main.cpp
	gcc -g -Wl,-rpath,./ -L./ -lbalanced-dice -I../include main.cpp -o test
clean-test: clean all run-test
run-test:
	./test
