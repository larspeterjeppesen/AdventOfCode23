#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main() {

  fstream fs;
  fs.open("input", fstream::in);

  string directions;
  fs >> directions;

  unordered_map<string, tuple<string,string>> road_map;
 
  string entry;
  string left_side;
  string right_side;
  while (fs >> entry) {
    fs.ignore(5, '(');
    fs >> left_side;
    left_side = left_side.substr(0,3);
    fs >> right_side;
    right_side = right_side.substr(0,3);
    tuple<string,string> entries = {left_side, right_side};
    road_map[entry] = entries;
  }

  int steps = 0;
  string position = "AAA";
  int i = 0;
  while (position != "ZZZ") {
    steps++;
    if (i == directions.size()) {
      i = 0;
    }
    char c = directions[i++];
    if (c == 'L') {
      position = get<0>(road_map[position]);
    } else if (c == 'R') {
      position = get<1>(road_map[position]);
    } else {
      cout << "directions misread\n";
      exit(0);
    }
  }

  cout << steps << endl;
  return 0;
}
