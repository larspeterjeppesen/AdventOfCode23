#include <cassert>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
using namespace std;


int main() {
  string line;
  fstream fs;
  fs.open ("input", fstream::in); 

  vector<int> copies;

  int round = 0;
  while (getline(fs, line))  {
    vector<int> w_numbers;
    vector<int> my_numbers;
    
    stringstream ss(line);
    ss.seekg(10, ios::cur);
    string word;
    int flag = 0;
    while (ss >> word) {
      switch(flag) {
        case 0:
          if (word == "|") {
            flag = 1;
            break;
          }
          w_numbers.push_back(stoi(word));
          break;
        case 1:
          my_numbers.push_back(stoi(word)); 
          break;
        default:
          cout << "Switch case fail\n";
          exit(0);
      } 
    }

    sort(w_numbers.begin(), w_numbers.end());
    sort(my_numbers.begin(), my_numbers.end());

    int w = 0;
    int m = 0;
    int score = 0;
    while (w < w_numbers.size() && m < my_numbers.size()) {
      if (w_numbers[w] < my_numbers[m]) {
        w++;
      } else if (w_numbers[w] > my_numbers[m]) {
        m++; 
      } else {
        score++; 
        w++; m++;
      }
    }

    while (copies.size() < round + score + 1) {
      copies.push_back(1);
    }
    auto e = copies.begin(); 
    advance(e, round+1);
    for (int i = 0; i < score; i++) {  
      *e = *e + copies[round];
      e = next(e,1);
    }
    round++;
  }
  auto sum = reduce(copies.begin(), copies.end());
  cout << sum << endl;
  fs.close();
  return 0;
}
