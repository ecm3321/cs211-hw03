# For building CS 211 Homework 3
# You don’t need to edit this file, and you probably shouldn’t.

# Programs we can build:
EXES        = count test_vc

# C compiler to use:
CC         ?= cc
# Extra options for catching bad stuff:
SANFLAGS   += -fsanitize=address,undefined
# Flags for compiling individual files:
CFLAGS     += -g -std=c11 -pedantic-errors @.Wflags $(SANFLAGS)
# Flags for linking the final program:
LDFLAGS    += -l211 $(SANFLAGS)

all: $(EXES)

test: test_vc
	./$<

test_vc: test/test_vc.o src/libvc.o
	$(CC) -o $@ $^ $(LDFLAGS)

count: src/count.o src/libvc.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(EXES) */*.o

# Header dependencies:
src/count.o src/libvc.o test/test_vc.o: src/libvc.h

# Targets that are not actually files we can build:
.PHONY: all test clean

# Ensure we have the correct C compiler version:
CSHOST = .northwestern.edu
ifeq ($(DEV211)$(CSHOST),$(findstring $(CSHOST),$(shell hostname)))
  $(error You need to run ‘dev’ first)
endif
