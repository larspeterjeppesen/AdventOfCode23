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

  vector<tuple<long,long>> games;
  string input;
  stringstream s_time(time_str);
  stringstream s_dist(dist_str);
  while (s_time >> input) {
    long t = stol(input);
    s_dist >> input;
    long d = stol(input);  
    tuple<long,long> game = {t, d};
    games.push_back(game);
  }

  int res = 1;
  for (auto game : games) {
    long sum = 0;
    long time = get<0>(game);
    long dist = get<1>(game);
    for (long i = 0; i < time; i++) {
      long d = i * (time - i);
      if (d > dist) {
        sum++; 
      }
    }
    if (sum > 0) {
      res = res * sum;
    }
  }

  cout << res << endl;
  return 0;
}
