#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <cstring>

using namespace std;

long f(long dp[22][22], int i, int d) {
  if (dp[d][i] != LONG_MIN) {
    return dp[d][i];
  } 
  if (d != 0) {
    long left_parent = dp[d-1][i] != LONG_MIN ? dp[d-1][i] : f(dp, i, d-1); 
    long right_parent = dp[d-1][i+1];
    if (left_parent != LONG_MIN && right_parent != LONG_MIN) {
      dp[d][i] = right_parent - left_parent;
      return dp[d][i];
    } else if (i == 0) {
      return right_parent;
    }
  }  
  dp[d][i] = f(dp,i-1,d) + f(dp,i-1,d+1);
  return dp[d][i];
}

int count_words(string line) {
  int count = 1;
  for (char c : line) {
    if (c == ' ') {
      count++;
    } 
  }
  return count;
}

int main() {
  fstream fs;
  fs.open("input", fstream::in);
  string line;
  long sum = 0;
  while (getline(fs, line)) {
    int size = count_words(line);
    long dp[22][22];
    for (int i = 0; i < size+1; i++) {
      for (int j = 0; j < size+1; j++) {
        dp[i][j] = LONG_MIN;
      }
    } 
    string number;
    stringstream sline(line);
    int i = 0;
    while (sline >> number) {
      dp[0][i++] = stoi(number); 
    }
    long res = f(dp, 21, 0);
    sum = sum + dp[0][21];
  }
  cout << sum << endl;


  return 0;
}
