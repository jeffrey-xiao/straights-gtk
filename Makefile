GTKFLAGS = `pkg-config gtkmm-3.0 --cflags`
GTKLIBS = `pkg-config gtkmm-3.0 --libs`
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = ${OBJECTS:.o=.d}
EXEC=straights

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CXXFLAGS = -std=c++14 -Wall -O -g -MMD -DDEBUG
else
	CXXFLAGS = -std=c++14 -Wall -O -g -MMD -DNDEBUG
endif

$(EXEC): $(OBJECTS)
	$(CXX) $(GTKFLAGS) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(GTKLIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(GTKFLAGS) $(CXXFLAGS) $(GTKLIBS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)

.PHONY: test
test: $(EXEC)
	./checkseed tests/tests-config straights sample_straights

.PHONY: check
check: $(EXEC)
	./checkmemory tests/tests-config straights
	cppcheck . --enable=all --quiet --inconclusive
