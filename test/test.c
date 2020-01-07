#include <stdio.h>
#include <stdlib.h>

enum {ROW = 5, COL = 2};

int main(void)
{
  int i, j;
  
  int tab1[5][2] =
    { {1, 1},
      {1, 2},
      {1, 3},
      {1, 4},
      {1, 5}
    };
  int tab2[2] = {1, 4};
  /* int tab2[5][2] = */
  /*   { */
  /*    {0, 0}, */
  /*    {0, 0}, */
  /*    {1, 4}, */
  /*    {0, 0}, */
  /*    {0, 0}, */
    /* }; */

  for (i = 0; i < ROW; i++)
    for (j = 0; j < COL; j++)
      if (tab2[0] == tab1[i][j] && tab2[1] == tab1[i][j + 1])
	printf("Row %d, Match !\n", i);
  
  return 0;
}
