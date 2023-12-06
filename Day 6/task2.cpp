#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
  string line;
  fstream fs;
  fs.open("input", fstream::in);

  getline(fs, line);
  string time_str = line.substr(12, line.size()-12);
  getline(fs, line);
  string dist_str = line.substr(12, line.size()-12);

  long time = 0;
  long dist = 0;
  string input;
  stringstream s_time(time_str);
  stringstream s_dist(dist_str);
  while (s_time >> input) {
    long t = stol(input);
    s_dist >> input;
    long d = stol(input);  
    time = time * 100 + t;
    dist = dist * pow(10, input.size()) + d;
  }
  long start = -1;
  long end = -1;
  for (long i = 0; i < time; i++) {
    long d = i * (time - i);
    if (d > dist) {
      start = i;
      break;
    }
  }
  for (long i = time-1; i > 0; i--) {
    long d = i * (time - i);
    if (d > dist) {
      end = i;
      break;
    }
  }

  long res = end - start + 1;
  

  cout << res << endl;
  return 0;
}
