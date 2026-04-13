# CMSC216 Makefile : UPDATED Mon Apr 13 10:54:02 AM EDT 2026
AN = lab09
CLASS = 216
GS_COURSE_ID = 1239298
GS_ASSIGN_ID = 7975928

CFLAGS = -Wall -Werror -g 
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

export PARALLEL?=True		#enable parallel testing if not overridden

PROGRAMS = \
	switch_stdout childout_query \


all : $(PROGRAMS)

########################################
help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make test                     # run all tests'
	@echo '  > make test-quiz                # run tests that verify quiz answers'
	@echo '  > make test-code testnum=2      # run tests that verify code is correct'
	@echo '  > make test-prob1               # run Code tests for problem 1'
	@echo '  > make test-prob2               # run Code tests for problem 2'
	@echo '  > make clean-tests              # remove all test results'
	@echo '  > make submit                   # upload submission to Gradescope'

############################################################
# 'make zip' to create complete.zip for submission
ZIPNAME = $(AN)-complete.zip
zip : clean clean-tests
	rm -f $(ZIPNAME)
	cd .. && zip "$(CWD)/$(ZIPNAME)" -r "$(CWD)"
	@echo Zip created in $(ZIPNAME)
	@if (( $$(stat -c '%s' $(ZIPNAME)) > 10*(2**20) )); then echo "WARNING: $(ZIPNAME) seems REALLY big, check there are no abnormally large test files"; du -h $(ZIPNAME); fi
	@if (( $$(unzip -t $(ZIPNAME) | wc -l) > 256 )); then echo "WARNING: $(ZIPNAME) has 256 or more files in it which may cause submission problems"; fi

################################################################################
# `make submit` to upload to gradescope
submit : zip
	@chmod u+x gradescope-submit
	@echo '=== SUBMITTING TO GRADESCOPE ==='
	./gradescope-submit $(GS_COURSE_ID) $(GS_ASSIGN_ID) $(ZIPNAME)


########################################
# Programs / Object files to build

## PROBLEM 2: I/O redirection
switch_stdout : switch_stdout.c
	$(CC) -o $@ $^

childout_query : childout_query.c
	$(CC) -o $@ $^

clean:
	rm -f *.o $(PROGRAMS) vgcore.*

clean-tests:
	rm -rf *.o test-results

########################################
# Testing Targets

test : test-setup all
	./testy -o md test_$(AN).org

test-quiz: test-setup QUESTIONS.txt
	./testy -o md test_$(AN).org 1

test-code : test-setup all
	./testy -o md test_$(AN).org 2

test-prob1: test-setup
	./testy -o md test_makefile.org

test-prob2 : test-setup childout_query
	./testy -o md test_childout_query.org $(testnum)

test-setup:
	@chmod u+x ./testy ./test_quiz_filter

