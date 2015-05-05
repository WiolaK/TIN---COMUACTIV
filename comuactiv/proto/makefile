#COMUACTIV::proto makefile
#Author: Jan Kumor

#Compiler
CC := g++
#Compiler flags
CFLAGS=-c -Wall -std=c++11 -O0
# Archiver
AR=ar

#Libraries
LIB := -pthread
#Include path
INC := -I include

#Project directories
SRCDIR := src
BUILDDIR := build
LIBTARGET := bin/libcomuactiv.a
TARGET := bin/main
#Src extension
SRCEXT := cpp
#Search for src and obj files
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	@echo " Archiving library..."
	@echo " $(AR) rcs $(LIBTARGET) $^"; $(AR) rcs $(LIBTARGET) $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
main: $(OBJECTS)
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: clean
