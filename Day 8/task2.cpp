#include <iostream>
#include <fstream>
#include <unordered_map>
#include <numeric>
#include <vector>

using namespace std;

int main() {

  fstream fs;
  fs.open("input", fstream::in);

  string directions;
  fs >> directions;

  unordered_map<string, tuple<string,string>> road_map;

  vector<string> A_paths;

  string entry;
  string left_side;
  string right_side;
  while (fs >> entry) {
    if (entry[2] == 'A') {
      A_paths.push_back(entry);
    }
    fs.ignore(5, '(');
    fs >> left_side;
    left_side = left_side.substr(0,3);
    fs >> right_side;
    right_side = right_side.substr(0,3);
    tuple<string,string> entries = {left_side, right_side};
    road_map[entry] = entries;
  }

  vector<long> all_steps;
  for (auto A_path : A_paths) {
    cout << A_path << endl;
    long steps = 0;
    int i = 0;
    string position = A_path;
    char c;
    do {
      if (i == directions.size()) i = 0;
      c = directions[i++];
      position = c == 'L' ? get<0>(road_map[position]) : get<1>(road_map[position]);
      steps++;
    } while (position[2] != 'Z');
    all_steps.push_back(steps);
  } 
  long max_lcm = all_steps[0];
  for (int i = 1; i < all_steps.size(); i++) {
    max_lcm = lcm(max_lcm, all_steps[i]);
  }
  


  //while (position != "ZZZ") {
  //  steps++;
  //  if (i == directions.size()) {
  //    i = 0;
  //  }
  //  char c = directions[i++];
  //  if (c == 'L') {
  //    position = get<0>(road_map[position]);
  //  } else if (c == 'R') {
  //    position = get<1>(road_map[position]);
  //  } else {
  //    cout << "directions misread\n";
  //    exit(0);
  //  }
  //}

  cout << max_lcm << endl;
  return 0;
}
