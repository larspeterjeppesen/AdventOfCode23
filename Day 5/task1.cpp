#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;




int main() {
 vector<string> categories;
  categories.push_back("seed-to-soil map:");
  categories.push_back("soil-to-fertilizer map:");
  categories.push_back("fertilizer-to-water map:");
  categories.push_back("water-to-light map:");
  categories.push_back("light-to-temperature map:");
  categories.push_back("temperature-to-humidity map:");
  categories.push_back("humidity-to-location map:");


  //Step 1: Load input into vectors of tuples 
  //        (source_start, source_end, dest_start)
  //        sorted by source_start

  string line;
  fstream fs;
  fs.open("input", fstream::in);

  vector<__int64_t> seeds;
  string seeds_str;
  getline(fs, seeds_str);
  seeds_str = seeds_str.substr(7, seeds_str.size()-7);
  string seed;
  stringstream ss(seeds_str);
  while (ss >> seed) {
    seeds.push_back(stoull(seed)); 
  }

  vector<vector<tuple<__int64_t,__int64_t,__int64_t>>> maps;
  vector<tuple<__int64_t,__int64_t, __int64_t>> cat0;
  vector<tuple<__int64_t,__int64_t, __int64_t>> cat1;
  vector<tuple<__int64_t,__int64_t, __int64_t>> cat2;
  vector<tuple<__int64_t,__int64_t, __int64_t>> cat3;
  vector<tuple<__int64_t,__int64_t, __int64_t>> cat4;
  vector<tuple<__int64_t,__int64_t, __int64_t>> cat5;
  maps.push_back(cat0);
  maps.push_back(cat1);
  maps.push_back(cat2);
  maps.push_back(cat3);
  maps.push_back(cat4);
  maps.push_back(cat5);

  int map_cat = -1;
  while (getline(fs, line)) {
    if (line == "") continue;
    auto e = find(categories.begin(), categories.end(), line);
    // Either change category or insert element into maps
    if (e != categories.end()) {
      map_cat = e - categories.begin(); 
    } else {
      // Read ranges
      stringstream ss(line);
      string word;
      __int64_t vals[3];
      for (int i = 0; i < 3; i++) {
        ss >> word;
        vals[i] = stoull(word);
      } 
      //Insert into maps
      tuple<__int64_t, __int64_t, __int64_t> value = {vals[1], vals[1]+vals[2], vals[0]};
      maps[map_cat].push_back(value);
    }
  }

  //Sort by source_start
  for (int i = 0; i < 7; i++) {
    sort(begin(maps[i]), end(maps[i]),
        [](tuple<__int64_t, __int64_t, __int64_t> const &t1,
           tuple<__int64_t, __int64_t, __int64_t> const &t2) {
            return get<0>(t1) < get<0>(t2);
           }
    );
  }

  //Step 2: map seed to destination
  vector<__uint64_t> solutions;
  for (__uint64_t seed : seeds) {
    __uint64_t image = seed;
    for (auto map : maps) {
      for (auto tup : map) {
        if (image > get<0>(tup) && image < get<1>(tup)) {
          image = image - get<0>(tup) + get<2>(tup);
          break;
        }
      }
    }
    solutions.push_back(image);
  }
  sort(begin(solutions), end(solutions));
  cout << solutions[0] << endl;
  return 0;
}
