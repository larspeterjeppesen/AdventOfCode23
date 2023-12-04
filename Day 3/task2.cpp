#include <cassert>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

int main() {
  //Initial test to get dimension of input
  char buf[256];
  memset(buf, 0, 256);
  FILE* fp = fopen("input", "r");
  assert(fp != NULL);
  fgets(buf, 256, fp);

  int width = strlen(buf)+1;
  fseek(fp, 0, SEEK_END);
  int height = 1 + ftell(fp)/width;
  fseek(fp, 0, SEEK_SET); 

  //Load input into 2D array
  char input[height][width];
  memset(input, 0, height*width); 
  for (int i = 0; i < height; i++) {
    fgets(input[i], width, fp);
    input[i][width-2] = 0; //remove '\n'
  }
  //Search for all numbers in input
  int sum = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      char c = input[i][j];


      if (c == '*') {
        int g1 = 0;
        int g2 = 0;

        int col_end = i < height-1 ? i+1 : i;
        int row_end = j < width-2 ? j+1 : j;
        for (int col = i > 0 ? i-1 : i; col <= col_end; col++) {
          for (int row = j > 0 ? j-1 : j; row <= row_end; row++) {
            if (isdigit(input[col][row])) {
              int s = row;
              while (s > 0 && isdigit(input[col][s-1])) s--;
              while (row+1 < width-2 && isdigit(input[col][row+1])) row++;
              int v = 0;
              while (s <= row) {
                v = v * 10 + input[col][s++] - '0';
              } 
              if (g1 == 0) {
                g1 = v;
              } else {
                g2 = v;
              }
            }
          }
        }
        
        if (g1 > 0 && g2 > 0) {
          sum += g1*g2;
        }

      }
    } 
  }
  cout << sum << endl;;
  return 0;
}
