//
//  sudoku_validator.c
//
//  Copyright © 2018 Bruce Lin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define GRID_SIZE 9

/* Initialize a 9x9 2D sudoku board. */
int GRID[GRID_SIZE][GRID_SIZE] = {
  { 6, 5, 3, 1, 2, 8, 7, 9, 4 },
  { 1, 7, 4, 3, 5, 9, 6, 8, 2 },
  { 9, 2, 8, 4, 6, 7, 5, 3, 1 },
  { 2, 8, 6, 5, 1, 4, 3, 7, 9 },
  { 3, 9, 1, 7, 8, 2, 4, 5, 6 },
  { 5, 4, 7, 6, 9, 3, 2, 1, 8 },
  { 8, 6, 5, 2, 3, 1, 9, 4, 7 },
  { 4, 1, 2, 9, 7, 5, 8, 6, 3 },
  { 7, 3, 9, 8, 4, 6, 1, 2, 5 }
};

/* Structure for passing data to threads. */
typedef struct {
  int row;
  int col;
} parameters;

/* Check if a subgrid has digits 1 - 9 wihtout duplication. */
void *checkSubgrid(void *subgrid) {
  parameters *grid = (parameters*)subgrid;
  int table[10] = {0}; // This is a mini hashtable
  
  for (int i = grid->row; i < grid->row + 3; i++) {
    for (int j = grid->col; j < grid->col + 3; j++) {
      if (table[GRID[i][j]] == 0)
         table[GRID[i][j]] = 1;
      else
        return (void*)0;
    }
  }
  
  return (void*)1;
};

/* Check if the grid has digits 1 - 9 wihtout duplication in each row. */
void *checkRow(void *theGrid) {
  parameters *grid = (parameters*)theGrid;
  
  for (int i = grid->row; i < 9; i++) {
    int table[10] = {0};
    for (int j = grid->col; j < 9; j++) {
      if (table[GRID[i][j]] == 0)
        table[GRID[i][j]] = 1;
      else
        return (void*)0;
    }
  }
  
  return (void*)1;
}

/* Check if the grid has digits 1 - 9 wihtout duplication in each column. */
void *checkCol(void *theGrid) {
  parameters *grid = (parameters*)theGrid;
  
  for (int i = grid->col; i < 9; i++) {
    int table[10] = {0};
    for (int j = grid->row; j < 9; j++) {
      if (table[GRID[i][j]] == 0)
        table[GRID[i][j]] = 1;
      else
        return (void*)0;
    }
  }
  
  return (void*)1;
}

int main(int argc, const char * argv[]) {
  printf("CS149 Sudoku from Bruce Lin\n\n");
  
  /*
   * There are 9 subgrids in total, each of it is 3x3,
   * 1 to 9, from top left to top right,
   * from bottom left to bottom right.
   */
  printf("Sudoku solution:\n");
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      printf("%d ", GRID[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  /**
   * First row
   **/
  
  pthread_t thread_1;
  void *returnPtr_1 = malloc(sizeof(int));
  parameters *subgrid_1 = (parameters*)malloc(sizeof(parameters));
  
  /* Assign the row and column number into struct parameters. */
  subgrid_1->row = 0;
  subgrid_1->col = 0;
  
  /* Create thread 1. */
  if (pthread_create(&thread_1, NULL, checkSubgrid, subgrid_1)) {
    printf("Failed creating thread 1.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 1 is created successfully.\n");
  
  pthread_t thread_2;
  void *returnPtr_2 = malloc(sizeof(int));
  parameters *subgrid_2 = (parameters*)malloc(sizeof(parameters)); // for thread 2
  subgrid_2->row = 0;
  subgrid_2->col = 3;
  
  /* Create thread 2. */
  if (pthread_create(&thread_2, NULL, checkSubgrid, subgrid_2)) {
    printf("Failed creating thread 2.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 2 is created successfully.\n");
  
  pthread_t thread_3;
  void *returnPtr_3 = malloc(sizeof(int));
  parameters *subgrid_3 = (parameters*)malloc(sizeof(parameters)); // for thread 3
  subgrid_3->row = 0;
  subgrid_3->col = 6;
  
  /* Create thread 3. */
  if (pthread_create(&thread_3, NULL, checkSubgrid, subgrid_3)) {
    printf("Failed creating thread 3.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 3 is created successfully.\n");
  
  /**
   * Second row
   **/
  
  pthread_t thread_4;
  void *returnPtr_4 = malloc(sizeof(int));
  parameters *subgrid_4 = (parameters*)malloc(sizeof(parameters)); // for thread 4
  subgrid_4->row = 3;
  subgrid_4->col = 0;
  
  /* Create thread 4. */
  if (pthread_create(&thread_4, NULL, checkSubgrid, subgrid_4)) {
    printf("Failed creating thread 4.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 4 is created successfully.\n");
  
  pthread_t thread_5;
  void *returnPtr_5 = malloc(sizeof(int));
  parameters *subgrid_5 = (parameters*)malloc(sizeof(parameters)); // for thread 5
  subgrid_5->row = 3;
  subgrid_5->col = 3;
  
  /* Create thread 5. */
  if (pthread_create(&thread_5, NULL, checkSubgrid, subgrid_5)) {
    printf("Failed creating thread 5.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 5 is created successfully.\n");
  
  pthread_t thread_6;
  void *returnPtr_6 = malloc(sizeof(int));
  parameters *subgrid_6 = (parameters*)malloc(sizeof(parameters)); // for thread 6
  subgrid_6->row = 3;
  subgrid_6->col = 6;
  
  /* Create thread 6. */
  if (pthread_create(&thread_6, NULL, checkSubgrid, subgrid_6)) {
    printf("Failed creating thread 6.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 6 is created successfully.\n");
  
  
  /**
   * Third row
   **/
  
  pthread_t thread_7;
  void *returnPtr_7 = malloc(sizeof(int));
  parameters *subgrid_7 = (parameters*)malloc(sizeof(parameters)); // for thread 7
  subgrid_7->row = 6;
  subgrid_7->col = 0;
  
  /* Create thread 7. */
  if (pthread_create(&thread_7, NULL, checkSubgrid, subgrid_7)) {
    printf("Failed creating thread 7.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 7 is created successfully.\n");
  
  pthread_t thread_8;
  void *returnPtr_8 = malloc(sizeof(int));
  parameters *subgrid_8 = (parameters*)malloc(sizeof(parameters)); // for thread 8
  subgrid_8->row = 6;
  subgrid_8->col = 3;
  
  /* Create thread 8. */
  if (pthread_create(&thread_8, NULL, checkSubgrid, subgrid_8)) {
    printf("Failed creating thread 8.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 8 is created successfully.\n");
  
  pthread_t thread_9;
  void *returnPtr_9 = malloc(sizeof(int));
  parameters *subgrid_9 = (parameters*)malloc(sizeof(parameters)); // for thread 9
  subgrid_9->row = 6;
  subgrid_9->col = 6;
  
  /* Create thread 9. */
  if (pthread_create(&thread_9, NULL, checkSubgrid, subgrid_9)) {
    printf("Failed creating thread 9.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 9 is created successfully.\n");
  
  /* Create the thread to check each row contains the digits 1 through 9 without duplication */
  pthread_t thread_10;
  void *returnPtr_10 = malloc(sizeof(int));
  parameters *theGrid = (parameters*)malloc(sizeof(parameters));
  theGrid->row = 0;
  theGrid->col = 0;
  
  /* Create thread 10. */
  if (pthread_create(&thread_10, NULL, checkRow, theGrid)) {
    printf("Failed creating thread 10.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 10 is created successfully.\n");
  
  /* Create the thread to check each column contains the digits 1 through 9 without duplication */
  /* Create thread 11. */
  pthread_t thread_11;
  void *returnPtr_11 = malloc(sizeof(int));
  if (pthread_create(&thread_11, NULL, checkCol, theGrid)) {
    printf("Failed creating thread 11.\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Thread 11 is created successfully.\n");
  
  /* Thread Join */
  pthread_join(thread_1, returnPtr_1);
  pthread_join(thread_2, returnPtr_2);
  pthread_join(thread_3, returnPtr_3);
  pthread_join(thread_4, returnPtr_4);
  pthread_join(thread_5, returnPtr_5);
  pthread_join(thread_6, returnPtr_6);
  pthread_join(thread_7, returnPtr_7);
  pthread_join(thread_8, returnPtr_8);
  pthread_join(thread_9, returnPtr_9);
  pthread_join(thread_10, returnPtr_10);
  pthread_join(thread_11, returnPtr_11);
  
  /* Cast void* to int* and then dereference the int* to access the integer value */
  int valid = *((int*)returnPtr_1) & *((int*)returnPtr_2) & *((int*)returnPtr_3) & *((int*)returnPtr_4) & *((int*)returnPtr_5) & *((int*)returnPtr_6) & *((int*)returnPtr_7) & *((int*)returnPtr_8) & *((int*)returnPtr_9) & *((int*)returnPtr_10) & *((int*)returnPtr_11);

  /* Free memory */
  free(returnPtr_1);
  free(returnPtr_2);
  free(returnPtr_3);
  free(returnPtr_4);
  free(returnPtr_5);
  free(returnPtr_6);
  free(returnPtr_7);
  free(returnPtr_8);
  free(returnPtr_9);
  free(returnPtr_10);
  free(returnPtr_11);
  
  if (valid == 1)
    printf("\nThis sudoku solution is valid.\n");
  else
    printf("\nThis sudoku solution is not valid.\n");
  
  return 0;
}
