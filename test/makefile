.PHONY : clean

CPPFLAGS= -fPIC -g -I../include
LDFLAGS= -shared

SOURCES = $(shell find ../src -wholename '../src/*.cpp' -not -wholename '../src/main.cpp')
HEADERS = $(shell echo ../include/*.h)
OBJECTS=$(SOURCES:.cpp=.o)

BALANCED_DICE_INCDIR=../include

TARGET=./libbalanced-dice.so

all: $(TARGET) test

clean:
	rm -f $(OBJECTS) $(TARGET) test

$(TARGET) : $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

test: main.cpp
	gcc -Wl,-rpath,../lib -L./ -lbalanced-dice -I../include main.cpp -o test
