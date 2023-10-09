# CMSC216 lab Makefile : dis06 corrected Makefile
AN = dis06
CLASS = 216

CFLAGS = -Wall -Werror -g 
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	coins_main \

all: $(PROGRAMS)

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make test-quiz                # run tests that verify quiz answers'
	@echo '  > make test-code                # run tests that verify code is correct'
	@echo '  > make test                     # run all automated tests'
	@echo '  > make clean-tests              # remove all test results'

############################################################
# 'make zip' to create complete.zip for submission
ZIPNAME = $(AN)-complete.zip
zip : clean clean-tests
	rm -f $(ZIPNAME)
	cd .. && zip "$(CWD)/$(ZIPNAME)" -r "$(CWD)"
	@echo Zip created in $(ZIPNAME)
	@if (( $$(stat -c '%s' $(ZIPNAME)) > 10*(2**20) )); then echo "WARNING: $(ZIPNAME) seems REALLY big, check there are no abnormally large test files"; du -h $(ZIPNAME); fi
	@if (( $$(unzip -t $(ZIPNAME) | wc -l) > 256 )); then echo "WARNING: $(ZIPNAME) has 256 or more files in it which may cause submission problems"; fi

coins_main : coins_main.c coins_funcs_asm.s
	$(CC) -o $@ $^

# hybrid executable, combines C and assembly functions, useful for
# testing but no used in evaluation
hybrid : coins_main.c coins_funcs_asm.s coins_funcs.c
	$(CC) -o coins_main $^


################################################################################
# testing targets
test-setup :
	@chmod u+rx testy test_quiz_filter

test : test-setup all
	./testy test_$(AN).org

test-quiz: test-setup QUESTIONS.txt
	./testy test_$(AN).org 1


test-code : test-setup coins_main
	./testy test_coins_main.org $(testnum)

clean:
	rm -f *.o $(PROGRAMS) 

clean-tests:
	rm -rf test-results/

