// test_bake_funcs34.c: unit tests for bake functions and data for
// problems 3 and 4
#include "bake.h"

// macro to set up a test with given name, print the source of the
// test; very hacky, fragile, but useful
#define IF_TEST(TNAME) \
  if( RUNALL ) { printf("\n"); } \
  if( RUNALL || strcmp( TNAME, test_name)==0 ) { \
    sprintf(sysbuf,"awk 'NR==(%d){P=1;gsub(\"^ *\",\"\");} P==1 && /ENDTEST/{P=0; print \"}\\n---OUTPUT---\"} P==1{print}' %s", __LINE__, __FILE__); \
    system(sysbuf); nrun++;  \
  } \
  if( RUNALL || strcmp( TNAME, test_name)==0 )

void print_sys(char *cmd){
  printf("%s\n",cmd);
  system(cmd);
}

char sysbuf[1024];
int RUNALL = 0;
int nrun = 0;

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <test_name>\n", argv[0]);
    printf("       %s ALL\n", argv[0]);
    return 1;
  }
  char *test_name = argv[1];
  char sysbuf[1024];

  RUNALL = strcmp(test_name,"ALL")==0; // possibly run all tests

  system("mkdir -p test-results"); // ensure a subdirectory for data is present
    
  IF_TEST("bake_set_updates1") { 
    // Checks the simplest case of a single rule with target dependent
    // on a source single file. The target file does not exist so an
    // update is required: the RULE_UPDATE_BIT / UP should be set on
    // calling bake_set_update() for the single explicit rule.
    system("rm -rf test-results/bake_set_updates1");
    system("cp -r data34/bake_set_updates1 test-results/");
    chdir("test-results/bake_set_updates1");
    printf("CONTENTS OF BAKEFILE\n");
    system("cat Bakefile");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    printf("---CALL TO bake_set_updates()---\n");
    int ret = bake_set_updates(bake,"program");
    printf("ret: %d\n",ret);
    printf("BAKE STRUCT AFTER bake_set_updates()\n");
    bake_show_bake(bake,0);    
    bake_free(bake);
    chdir("../..");
  } // ENDTEST

  IF_TEST("bake_set_updates2") { 
    // program target is dependent on a .o file which is dependent on
    // a .c file. Both the .o and program should be deteceted as in
    // need of update.
    system("rm -rf test-results/bake_set_updates2");
    system("cp -r data34/bake_set_updates2 test-results/");
    chdir("test-results/bake_set_updates2");
    printf("CONTENTS OF BAKEFILE\n");
    system("cat Bakefile");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    printf("---CALL TO bake_set_updates()---\n");
    int ret = bake_set_updates(bake,"program");
    printf("ret: %d\n",ret);
    printf("BAKE STRUCT AFTER bake_set_updates()\n");
    bake_show_bake(bake,0);    
    bake_free(bake);
    chdir("../..");
  } // ENDTEST

  IF_TEST("bake_set_updates3") { 
    // program dependent on two .o files which each have an associated
    // .c file. All need updates.
    system("rm -rf test-results/bake_set_updates3");
    system("cp -r data34/bake_set_updates3 test-results/");
    chdir("test-results/bake_set_updates3");
    printf("CONTENTS OF BAKEFILE\n");
    system("cat Bakefile");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    printf("---CALL TO bake_set_updates()---\n");
    int ret = bake_set_updates(bake,"program");
    printf("ret: %d\n",ret);
    printf("BAKE STRUCT AFTER bake_set_updates()\n");
    bake_show_bake(bake,0);    
    bake_free(bake);
    chdir("../..");
  } // ENDTEST

  IF_TEST("bake_set_updates4") { 
    // program dependent on two .o files which each have an associated
    // .c file. Before calling bake_set_updates(), one C file is
    // compiled to a .o file which means it does not need an
    // update. Verifies that target files are checked and if they are
    // present and newer than the associated source file, no update is
    // needed.
    system("rm -rf test-results/bake_set_updates4");
    system("cp -r data34/bake_set_updates4 test-results/");
    chdir("test-results/bake_set_updates4");
    printf("CONTENTS OF BAKEFILE\n");
    system("cat Bakefile");
    printf("---COMPILING A C FILE---\n");
    print_sys("gcc -c hello.c");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    printf("---CALL TO bake_set_updates()---\n");
    int ret = bake_set_updates(bake,"program");
    printf("bake_set_updates() ret: %d\n",ret);
    printf("BAKE STRUCT\n");
    bake_show_bake(bake,0);    
    bake_free(bake);
    chdir("../..");
  } // ENDTEST


  IF_TEST("bake_set_updates5") { 
    // Larger Bakefile used with 3 source files, .o dependencies for
    // each and a main_prog. Calls bake_set_updates() several times:
    // CALL 1: updates needed for all rules as nothing has been compiled
    // CALL 2: make is run first so no updates are needed
    // CALL 3: one .o file is removed so updates are needed for it and
    //         targets dependent on it
    system("rm -rf test-results/bake_set_updates5");
    system("cp -r data34/bake_set_updates5 test-results/");
    chdir("test-results/bake_set_updates5");
    printf("CONTENTS OF BAKEFILE\n");
    system("cat Bakefile");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    int ret;

    printf("\n----CALL 1 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    bake_show_bake(bake,0);    

    printf("\n---BUILDING USING MAKE---\n");
    print_sys("make -f Bakefile --no-print-directory");

    printf("\n----CALL 2 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    bake_show_bake(bake,0);    

    printf("\n---REMOVING FILE(S)---\n");
    print_sys("rm -f func1.o");

    printf("\n----CALL 3 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    bake_show_bake(bake,0);    

    bake_free(bake);
    chdir("../..");
  } // ENDTEST

  IF_TEST("bake_set_updates6") { 
    // Starts by using make to build all files, then modifies time
    // stamps to determine if dependency checks based on time
    // differences are done correctly.
    // CALL 1: a single c source file is modified requiring a .o to be
    // updated and the main_prog to be updatd.
    // CALL 2: all .o files are up to date but the main_prog is older
    // so requires an update.
    system("rm -rf test-results/bake_set_updates6");
    system("cp -r data34/bake_set_updates6 test-results/");
    chdir("test-results/bake_set_updates6");
    printf("CONTENTS OF BAKEFILE\n");
    system("cat Bakefile");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    int ret;

    printf("\n---BUILDING USING MAKE---\n");
    print_sys("make -f Bakefile --no-print-directory");

    printf("\n---ALTERING TIMESTAMPS---\n");
    print_sys("touch -d -1min *");       // make files older
    print_sys("touch -d -1sec func2.c"); // make 1 c file newer

    printf("\n----CALL 1 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    bake_show_bake(bake,0);    

    printf("\n---ALTERING TIMESTAMPS---\n");
    print_sys("touch -d -2min *.c");     // make c files older
    print_sys("touch -d -1sec *.o");     // make .o files newer
    print_sys("touch -d -1min main_prog"); // program older

    printf("\n----CALL 2 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    bake_show_bake(bake,0);    
    bake_free(bake);
    chdir("../..");
  } // ENDTEST

  IF_TEST("bake_set_updates7") { 
    // Checks 2 error cases for bake_set_updates()
    // CALL 1: a non-existent target is passed which should return an
    // error and print an error message.
    // CALL 2: a .o file is required but there is no rule for it and
    // there is no existing file for it. An error should be returned
    // and a message about a missing file for an implicit rule should
    // be printed.
    system("rm -rf test-results/bake_set_updates7");
    system("cp -r data34/bake_set_updates7 test-results/");
    chdir("test-results/bake_set_updates7");
    printf("CONTENTS OF BAKEFILE\n");
    system("cat Bakefile");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    int ret;

    printf("\n----CALL 1 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"no_targ");
    printf("ret: %d\n",ret);

    printf("\n----CALL 2 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    printf("ret: %d\n",ret);

    bake_free(bake);
    chdir("../..");
  } // ENDTEST

  IF_TEST("bake_do_updates1") { 
    // Small case of needing to compile a .c to a .o then to a
    // program; checks the basic behavior of bake_do_updates()
    system("rm -rf test-results/bake_do_updates1");
    system("cp -r data34/bake_do_updates1 test-results/");
    chdir("test-results/bake_do_updates1");
    printf("\n----DIRECTORY CONTENTS---\n");
    print_sys("ls -1");
    printf("\n---CONTENTS OF BAKEFILE---\n");
    system("cat Bakefile");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    int ret;
    printf("\n----CALL TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"program");
    printf("ret: %d\n",ret);
    printf("\n----CALL TO bake_do_updates()----\n");
    ret = bake_do_updates(bake,"program");
    printf("ret: %d\n",ret);
    printf("\n----DIRECTORY CONTENTS---\n");
    print_sys("ls -1");
    bake_free(bake);
    chdir("../..");
  } // ENDTEST


  IF_TEST("bake_do_updates2") { 
    // Modest case of needing to compile sevearal .c to a .o files and
    // link them to become a program. Uses repeated calls to examine
    // whether bake_set_updates() and bake_do_updtes() correctly
    // refrain from rebuilding parts of the program that do not need
    // to be rebuilt, once after the first build (no updates) and
    // again after altering timestamps to emulate a change in source
    // files.
    system("rm -rf test-results/bake_do_updates2");
    system("cp -r data34/bake_do_updates2 test-results/");
    chdir("test-results/bake_do_updates2");
    printf("\n----DIRECTORY CONTENTS---\n");
    print_sys("ls -1");
    printf("\n---CONTENTS OF BAKEFILE---\n");
    system("cat Bakefile");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    int ret;
    printf("\n----CALL 1 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    printf("\n----CALL 1 TO bake_do_updates()----\n");
    ret = bake_do_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    printf("\n----DIRECTORY CONTENTS---\n");
    print_sys("ls -1");
    printf("\n----CALL 2 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    printf("\n----CALL 2 TO bake_do_updates()----\n");
    ret = bake_do_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    printf("\n----DIRECTORY CONTENTS---\n");
    print_sys("ls -1");
    printf("\n---ALTERING TIMESTAMPS---\n");
    print_sys("touch -d -1min *");       // make files older
    print_sys("touch -d -1sec func2.c"); // make 1 c file newer
    printf("\n----CALL 3 TO bake_set_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    printf("\n----CALL 3 TO bake_do_updates()----\n");
    ret = bake_do_updates(bake,"main_prog");
    printf("ret: %d\n",ret);
    bake_free(bake);
    chdir("../..");
  } // ENDTEST


  IF_TEST("bake_do_updates3") { 
    // Checks error cases for bake_do_updates()
    // CALL 1: while building a single target, the first command will
    // return a non-zero exit status which should terminate the build
    // with an error message and -1 return value.
    // CALL 2: while building a a program, a .o fails to build due to
    // the command to be run not being found. This should terminate
    // the build with an error message and -1 return value.
    system("rm -rf test-results/bake_do_updates3");
    system("cp -r data34/bake_do_updates3 test-results/");
    chdir("test-results/bake_do_updates3");
    printf("\n---CONTENTS OF BAKEFILE---\n");
    system("cat Bakefile");
    bake_t *bake = bake_create_from_file("Bakefile");
    bake_add_implicit_rules(bake);
    int ret;

    printf("\n----CALL 1 TO bake_do_updates()----\n");
    ret = bake_set_updates(bake,"failfiles");
    ret = bake_do_updates(bake,"failfiles");
    printf("ret: %d\n",ret);

    printf("\n----CALL 2 TO bake_do_updates()----\n");
    ret = bake_set_updates(bake,"main_prog");
    ret = bake_do_updates(bake,"main_prog");
    printf("ret: %d\n",ret);

    bake_free(bake);
    chdir("../..");
  } // ENDTEST

  IF_TEST("bake_cmd_postprocess1") { 
    // Checks that post processing properly handles output redirection
    cmd_t cmd = {
      .tokens = {"echo","The","spice","must","flow",">","mantra.txt"},
      .line_number = 17,
    };
    printf("---CMD BEFORE POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
    bake_cmd_postprocess(NULL, &cmd);
    printf("\n---CMD AFTER POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
  } // ENDTEST

  IF_TEST("bake_cmd_postprocess1") { 
    // Checks that post processing properly handles input redirection
    cmd_t cmd = {
      .tokens = {"wc","-l","<","notes_on_sandworms.txt"},
      .line_number = 45,
    };
    printf("---CMD BEFORE POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
    bake_cmd_postprocess(NULL, &cmd);
    printf("\n---CMD AFTER POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
  } // ENDTEST

  IF_TEST("bake_cmd_postprocess2") { 
    // Checks that post processing properly handles input + output redirection
    cmd_t cmd = {
      .tokens = {"sed","s/fear/FEAR/g","<","i-must-not-fear.txt",">","caps.txt"},
      .line_number = 97,
    };
    printf("---CMD BEFORE POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
    bake_cmd_postprocess(NULL, &cmd);
    printf("\n---CMD AFTER POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
  } // ENDTEST

  IF_TEST("bake_cmd_postprocess3") { 
    // Checks that post processing properly handles the @ silence sigil
    cmd_t cmd = {
      .tokens = {"@","echo","I","must","not","fear"},
      .line_number = 88,
    };
    printf("---CMD BEFORE POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
    bake_cmd_postprocess(NULL, &cmd);
    printf("\n---CMD AFTER POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
  } // ENDTEST

  IF_TEST("bake_cmd_postprocess4") { 
    // Checks that post processing properly handles combinations of
    // input/output redirection and silencing. The order of
    // input/output redirect is opposite from a previous combination
    // test.
    cmd_t cmd = {
      .tokens = {"@","sed","s/fear/FEAR/g",">","caps.txt","<","i-must-not-fear.txt"},
      .line_number = 88,
    };
    printf("---CMD BEFORE POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
    bake_cmd_postprocess(NULL, &cmd);
    printf("\n---CMD AFTER POSTPROCESSING---\n");
    bake_show_cmd(&cmd, 0);
  } // ENDTEST

  IF_TEST("bake_post_process1") { 
    // Load a Bakefile and post-process it via bake_post_process() to
    // adjust commands with I/O redirection and silencing. Print out
    // the resulting bake and iterate over the commamnds displaying
    // them with bake_print_cmd().
    bake_t *bake =
      bake_create_from_file("data34/bake_postprocess1/Dunefile");
    printf("---BAKE BEFORE POSTPROCESSING---\n");
    bake_show_bake(bake, 0);
    bake_post_process(bake);
    printf("---BAKE AFTER POSTPROCESSING---\n");
    bake_show_bake(bake, 0);
    printf("---CALLING bake_print_cmd() ON EACH COMMAND---\n");
    printf("Note: silenced commands won't print\n");
    for(int i=0; i<bake->rule_count; i++){
      for(int j=0; j<bake->rules[i].cmd_count; j++){
        printf("rules[%d].cmds[%d]:\n",i,j);
        bake_print_cmd(&bake->rules[i].cmds[j]);
      }
    }
    bake_free(bake);
  } // ENDTEST

  ////////////////////////////////////////////////////////////////////////////////
  // END OF ALL TESTS

  if(nrun == 0){                // check that at least one test was run
    printf("No test named '%s' found\n",test_name);
    return 1;
  }
  return 0;
}

