// UPDATED: Tue Sep 16 01:23:15 PM EDT 2025

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define QUOTE_COUNT 10
char *all_quotes[QUOTE_COUNT] = {
  "Edsger Dijkstra: If debugging is the process of removing software bugs, then programming must be the process of putting them in.",
  "Brian Kernighan: Debugging is twice as hard as writing the code in the first place. Therefore, if you write the code as cleverly as possible, you are, by definition, not smart enough to debug it.",
  "Nicholas Negroponte: Programming allows you to think about thinking, and while debugging you learn learning.",
  "Richard E. Pattis: When debugging, novices insert corrective code; experts remove defective code.",
  "Brian Kernighan: The most effective debugging tool is still careful thought, coupled with judiciously placed print statements.",
  "Boris Beizer: Testing proves a programmer's failure. Debugging is the programmer's vindication.",
  "Maurice Wilkes: As soon as we started programming, we found to our surprise that it wasn't as easy to get programs right as we had thought. Debugging had to be discovered. I can remember the exact instant when I realized that a large part of my life from then on was going to be spent in finding mistakes in my own programs.",
  "Steven Levy: There has never been an unexpectedly short debugging period in the history of computers.",
  "Brian Kernighan: One university computer center kept a teddy bear near the help desk. Students with mysterious bugs were required to explain them to the bear before they could speak to a human counselor.",
  "Christopher Thompson: Sometimes it pays to stay in bed on Monday, rather than spending the rest of the week debugging Monday's code.",
};

// pseudo-random number generation; defined after main
unsigned int pb_rand();
void pb_srand(unsigned long seed);

// checks the for an expected userID: the directory ID which is the
// first part of an @terpmail.umd.edu email address; prints a warning
// if non-matching
void check_userid(char *userid);

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <infile>\n",argv[0]);
    return 1;
  }
  char *infile = argv[1];
  FILE *fin = fopen(infile,"r");
  if(fin == NULL){
    fprintf(stderr,"Couldn't open file '%s'\n",infile);
    exit(1);
  }
  char email[64];
  printf("Reading an @terpmail.umd.edu address from input\n");
  int ret = fscanf(fin, "%s", email);
  if(ret != 1){
    fprintf(stderr,"Failed to read email\n");
    exit(1);
  }
  char userid[10] = "________";
  int i;
  for(i=0; i<8 && email[i]!='@'; i++){
    userid[i] = toupper(email[i]);
  }
  if(email[i] != '@'){
    fprintf(stderr,"Something wrong with email address: char %d not '@' in %s\n",
            i,email);
    exit(1);
  }

  check_userid(userid);
  printf("UserID Accepted\n");
  int magic1 = *((int *) userid);
  int magic2 = *(1 + ((int *) userid));
  printf("Checking for matching magic\n");
  int inmagic1, inmagic2;
  ret = fscanf(fin,"%d %d",&inmagic1,&inmagic2);
  if(ret != 2){
    fprintf(stderr,"Could not read 2 magic numbers from file\n");
    exit(1);
  }
  if(inmagic1!=magic1 || inmagic2!=magic2){
    fprintf(stderr,"The magic did not match!\n");
    exit(1);
  }
  printf("That's your kind of magic!\n");
  int hash = magic1 ^ magic2;
  pb_srand(hash);
  int quote_index = pb_rand() % QUOTE_COUNT;
  char *quote_expect = all_quotes[quote_index];
  char quote_actual[256];
  strcpy(quote_actual, quote_expect);
  int quote_len = strlen(quote_expect);
  printf("Mangling a quote\n");
  int mod1 = pb_rand() % quote_len;
  quote_actual[mod1] = '_';
  int mod2 = pb_rand() % quote_len;
  quote_actual[mod2] = 95;
  int mod3 = pb_rand() % (quote_len / sizeof(int));
  int *quote_as_int = (int *) quote_actual;
  quote_as_int[mod3] = 1600085855;

  printf("De-mangling a quote\n");
  int idx;
  char inchar;
  int inint;
  ret = fscanf(fin,"%d %c", &idx, &inchar);
  if(ret != 2){
    fprintf(stderr,"First de-mangling step has missing/wrong input\n");
    exit(1);
  }
  inchar = (inchar=='_') ? ' ' : inchar;
  quote_actual[idx] = inchar;
  ret = fscanf(fin,"%d %c", &idx, &inchar);
  if(ret != 2){
    fprintf(stderr,"Second de-mangling step has missing/wrong input\n");
    exit(1);
  }
  inchar = (inchar=='_') ? ' ' : inchar;
  quote_actual[idx] = inchar;
  ret = fscanf(fin,"%d %d", &idx, &inint);
  if(ret != 2){
    fprintf(stderr,"Third de-mangling step has missing/wrong input\n");
    exit(1);
  }
  quote_as_int[idx] = inint;
  printf("Checking de-mangling\n");
  if(strncmp(quote_actual, quote_expect, quote_len)!=0){
    fprintf(stderr,"Failed de-mangling:\nExpect: %s\nActual: %s\n",
            quote_expect, quote_actual);
    exit(1);
  }
  printf("De-mangling successful!\n");
  printf("+================================+\n"
         "|  ,dGDb.dGDb,                   |\n"
         "|  GDBGDBGDBGD   GDB...          |\n"
         "|  `YGDBGDBGY'   will always be  |\n"
         "|    `YGDBY'     there for ME!   |\n"
         "|      `Y'                       |\n"
         "+================================+\n");
  return 0;
}
// state of the random number generator 
unsigned long state = 1;
// generate a random integer
unsigned int pb_rand() {
  state = state * 1103515245 + 12345;
  return (unsigned int)(state/65536) % 32768;
}
// set seed for pb_rand()
void pb_srand(unsigned long seed){
  state = seed;
}

// checks the for an expected userID: the directory ID which is the
// first part of an @terpmail.umd.edu email address; prints a warning
// if non-matching
void check_userid(char *userid){
  char *eid = getenv("EXPECT_USERID");
  if(eid!=NULL && strlen(eid)>0){
    char *eid = getenv("EXPECT_USERID");
    char expect_userid[10] = "________";
    for(int i=0; eid[i]!='\0'; i++){
      expect_userid[i] = toupper(eid[i]);
    }
    if(strcmp(userid, expect_userid)!=0){
      printf("==============================================================\n");
      printf("WARNING: actual userid '%s' does not match expected '%s'\n",
             userid, expect_userid);
      printf("         Ensure your @terpmail.umd.edu address is correct\n");
      printf("         before proceeding or submitting to Gradescope.\n");
      printf("==============================================================\n");
    }
  }
}
