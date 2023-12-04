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
  cout << width << endl; 
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
      if (isdigit(c)) {
        int s = j;
        int n = c - '0';
        while (j+1 < width && isdigit(input[i][j+1])) {
          j++;
          n = n*10 + input[i][j] - '0';
        }

        // Look for symbols at rows i-1, i, i+1 in interval s-1 to j+1
        int col_end = i < height-1 ? i+1 : i;
        int row_end = j < width-1 ? j+1 : j;
        for (int col = i > 0 ? i-1 : i; col <= col_end; col++) {
          for (int row = s > 0 ? s-1 : s; row <= row_end; row++) {
            char c = input[col][row];
            if (c != '.' && !isdigit(c) && c != 0) {
              sum += n;
              col = col_end+1;
              break;
            }
          }

        }
      }
    } 
  }
  cout << sum << endl;;
  return 0;
}
