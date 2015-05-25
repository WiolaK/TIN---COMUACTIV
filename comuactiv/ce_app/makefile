#COMUACTIV::ce_app makefile
#Author: Jan Kumor

#Compiler
CC := g++
#Compiler flags
CFLAGS=-c -g -Wall -std=c++11 -O0 -fpermissive
#Libraries
LIB := -lcomuactiv -pthread
#Include
INC_PATH := -I include
LIB_PATH := -L ../proto/bin/


#Project directories
SRCDIR := src
BUILDDIR := build
TARGET := bin/ce_app
#Src extension
SRCEXT := cpp
#Search for src and obj files
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ $(LIB_PATH) $(LIB) -o $(TARGET) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) 
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC_PATH) $(LIB) -o bin/tester

.PHONY: clean
