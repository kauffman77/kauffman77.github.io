// hashmap_demo_init.c: demostrateds how one can allocate a
// stack-based hashmap then initialize its fields via the
// hashmap_init() function. Also shows how to iterate through the
// elements of the table[] field of the hash map.

#include <stdio.h>
#include <string.h>
#include "hashmap.h"

int main(int argc, char *argv[]){
  hashmap_t hashmap = {                                   // hashmap to initialize, filled with
    .item_count = -1,                                     // values that should be overwritten
    .table_size = -1,
    .table = NULL,
  };

  hashmap_init(&hashmap, HASHMAP_DEFAULT_TABLE_SIZE);     // call function being tested

  if(hashmap.item_count != 0){                            // check item_count field after init
    printf("item_count wrong\n");
    printf("Expect: %d\n",0);
    printf("Actual: %d\n",hashmap.item_count);
    return 1;
  }

  if(hashmap.table_size != HASHMAP_DEFAULT_TABLE_SIZE){   // check table_size field
    printf("table_size wrong\n");
    printf("Expect: %d\n",HASHMAP_DEFAULT_TABLE_SIZE);
    printf("Actual: %d\n",hashmap.table_size);
    return 1;
  }

  for(int i=0; i<hashmap.table_size; i++){                // check all table entries have been NULL'ed
    if( hashmap.table[i] != NULL ){
      printf("table[%d] wrong\n",i);
      printf("Expect: %p\n",NULL);
      printf("Actual: %p\n",hashmap.table[i]);
      return 1;
    }
  }

  printf("OK\n");                                         // all tests passed
  return 0;
}
    
