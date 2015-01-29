#include <stdio.h>
#include <stdlib.h>

float p[4];
int w[4];

void init() {
  p[0] = 0.01;
  p[1] = 0.2;
  p[2] = 0.22;
  p[3] = 0.1;

  w[0] = 1;
  w[1] = 1;
  w[2] = 1;
  w[3] = 1;
}

void print(int loopCount) {
  printf("loop#%d\n", loopCount);
  for (int i = 0; i < 4; i++) {
    printf("w[%d]=%d\n", i, w[i]);
  }
}

int main() {
  init();

  int action = rand() % 4;
  w[action]++;
  for (int i = 0; i < 4000; i++) {
    
    print(i);
  }
}
