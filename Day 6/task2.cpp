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

  //Solution space is in a 2nd degree polynomial
  //so interval between roots describe valid solutions
  long det = sqrt(time*time - 4*dist);
  long x1 = (-time + det)/-2;
  long x2 = (-time - det)/-2;
  cout  << abs(x2-x1) + 1 << endl;;

  return 0;
}
