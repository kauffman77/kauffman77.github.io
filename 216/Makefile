# CMSC216 Project 4 Makefile
AN = p4
CLASS = 216

# -Wno-comment: disable warnings for multi-line comments, present in some tests

## REMOVE LATER
# -Wno-format-security: disable warning for printf(str); used in default help printing
CFLAGS = -Wall -Wno-comment -Werror -g -Wno-format-security
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = bake
TEST_PROGRAMS = test_bake_funcs12 test_bake_funcs34

############################################################
# Default target and cleaning target to remove compiled programs/objects
all : $(PROGRAMS) $(TEST_PROGRAMS)

clean :
	rm -f $(PROGRAMS) $(TEST_PROGRAMS) *.o

############################################################
# help message to show build targets
help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make prob1                    # built targets associated with problem 1'
	@echo '  > make test                     # run all tests'
	@echo '  > make test-prob2               # run test for problem 2'
	@echo '  > make test-prob2 testnum=5     # run problem 2 test #5 only'

############################################################
# 'make zip' to create complete.zip for submission
ZIPNAME = $(AN)-complete.zip
zip : clean clean-tests
	rm -f $(ZIPNAME)
	cd .. && zip "$(CWD)/$(ZIPNAME)" -r "$(CWD)"
	@echo Zip created in $(ZIPNAME)
	@if (( $$(stat -c '%s' $(ZIPNAME)) > 10*(2**20) )); then echo "WARNING: $(ZIPNAME) seems REALLY big, check there are no abnormally large test files"; du -h $(ZIPNAME); fi
	@if (( $$(unzip -t $(ZIPNAME) | wc -l) > 256 )); then echo "WARNING: $(ZIPNAME) has 256 or more files in it which may cause submission problems"; fi

############################################################
# bake targets
%.o : %.c
	$(CC) -c $<

bake : bake_funcs.o bake_main.o bake_util.o
	$(CC) -o $@ $^

test_bake_funcs12 : test_bake_funcs12.o bake_funcs.o bake_util.o
	$(CC) -o $@ $^

test_bake_funcs34 : test_bake_funcs34.o bake_funcs.o bake_util.o
	$(CC) -o $@ $^

test_bake_funcs34.c :
	@ echo "=== NOTICE ==="
	@ echo "test_bake_funcs34.c is not yet available"
	@ echo "Watch for an announcement to download it"
	@ echo "=== NOTICE ==="

############################################################
# Testing Targets
test : test-prob1 test-prob2 test-prob3 test-prob4

test-setup:
	@chmod u+x testy

test-prob1 : test_bake_funcs12 test-setup test_prob1.org
	./testy test_prob1.org $(testnum)

test-prob2 : test_bake_funcs12 test-setup test_prob2.org
	./testy test_prob2.org $(testnum)

test-prob3 : test_bake_funcs34 test-setup test_prob3.org
	./testy test_prob3.org $(testnum)

test-prob4 : test_bake_funcs34 test-setup test_prob4.org bake
	./testy test_prob4.org $(testnum)

clean-tests :
	rm -rf test-results 

