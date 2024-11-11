# CMSC216 Makefile
AN = lab10
CLASS = 216

CFLAGS = -Wall -Werror -g 
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

########################################
# Programs / Object files to build

PROGRAMS = \
	switch_stdout redirect_child \
	stat_demo newer_file \

all: $(PROGRAMS)

switch_stdout : switch_stdout.c
	$(CC) -o $@ $^

redirect_child : redirect_child.c
	$(CC) -o $@ $^

stat_demo : stat_demo.c 
	$(CC) -o $@ $^

newer_file : newer_file.c
	$(CC) -o $@ $^

clean:
	rm -f *.o $(PROGRAMS)

########################################
help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make test                     # run all tests'
	@echo '  > make test-quiz                # run tests that verify quiz answers'
	@echo '  > make test-code                # run tests that verify code is correct'
	@echo '  > make test-prob1               # run Code tests for problem 1'
	@echo '  > make test-prob2               # run Code tests for problem 2'

############################################################
# 'make zip' to create complete.zip for submission
ZIPNAME = $(AN)-complete.zip
zip : clean clean-tests
	rm -f $(ZIPNAME)
	cd .. && zip "$(CWD)/$(ZIPNAME)" -r "$(CWD)"
	@echo Zip created in $(ZIPNAME)
	@if (( $$(stat -c '%s' $(ZIPNAME)) > 10*(2**20) )); then echo "WARNING: $(ZIPNAME) seems REALLY big, check there are no abnormally large test files"; du -h $(ZIPNAME); fi
	@if (( $$(unzip -t $(ZIPNAME) | wc -l) > 256 )); then echo "WARNING: $(ZIPNAME) has 256 or more files in it which may cause submission problems"; fi

########################################
# Testing Targets

test : test-setup all
	./testy test_$(AN).org

test-quiz: test-setup QUESTIONS.txt
	./testy test_$(AN).org 1

test-code : test-setup all
	./testy test_$(AN).org 2

test-prob1 : test-setup redirect_child
	./testy test_redirect_child.org

test-prob2 : test-setup newer_file
	./testy test_newer_file.org

test-setup:
	@chmod u+x ./testy ./test_quiz_filter


clean-tests:
	@echo Removing temporary test files
	rm -rf *.o test-results

