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

  vector<tuple<__uint64_t,__uint64_t>> seeds;
  string seeds_str;
  getline(fs, seeds_str);
  seeds_str = seeds_str.substr(7, seeds_str.size()-7);
  string v;
  stringstream ss(seeds_str);
  while (ss >> v) {
    __uint64_t start = stoull(v);
    ss >> v;
    __uint64_t end = stoull(v) + start-1;
    tuple<__uint64_t, __uint64_t> tup = {start, end};
    seeds.push_back(tup); 
  }

  vector<vector<tuple<__uint64_t,__uint64_t,__uint64_t>>> maps;
  vector<tuple<__uint64_t,__uint64_t, __uint64_t>> cat0;
  vector<tuple<__uint64_t,__uint64_t, __uint64_t>> cat1;
  vector<tuple<__uint64_t,__uint64_t, __uint64_t>> cat2;
  vector<tuple<__uint64_t,__uint64_t, __uint64_t>> cat3;
  vector<tuple<__uint64_t,__uint64_t, __uint64_t>> cat4;
  vector<tuple<__uint64_t,__uint64_t, __uint64_t>> cat5;
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
      __uint64_t vals[3];
      for (int i = 0; i < 3; i++) {
        ss >> word;
        vals[i] = stoull(word);
      } 
      //Insert into maps
      tuple<__uint64_t, __uint64_t, __uint64_t> value = {vals[1], vals[1]+vals[2]-1, vals[0]};
      maps[map_cat].push_back(value);
    }
  }

  //Sort by source_start
  for (int i = 0; i < 7; i++) {
    sort(begin(maps[i]), end(maps[i]),
        [](tuple<__uint64_t, __uint64_t, __uint64_t> const &t1,
           tuple<__uint64_t, __uint64_t, __uint64_t> const &t2) {
            return get<0>(t1) < get<0>(t2);
           }
    );
  }

  //Step 2: map seed to destination
  vector<tuple<__uint64_t,__uint64_t>> solutions;
  for (auto seed_tup : seeds) {
    vector<tuple<__uint64_t,__uint64_t>> seed_intervals;
    seed_intervals.push_back(seed_tup);
    vector<tuple<__uint64_t,__uint64_t>> image;
    for (auto map : maps) {
      auto size = seed_intervals.size();
      for (auto i = 0; i < size; i++) {
        int match = 0;
        auto seed_interval = seed_intervals[i];
        for (auto map_range : map) {
          __uint64_t im_min = get<0>(seed_interval);
          __uint64_t im_max = get<1>(seed_interval);
          __uint64_t m_min = get<0>(map_range);
          __uint64_t m_max = get<1>(map_range);
          __uint64_t m_offset = get<2>(map_range);
          if ((im_min >= m_min && im_min <= m_max) ||
                (im_max >= m_min && im_max <= m_max)) {
            __uint64_t min_val = im_min < m_min ? m_offset :
                                  im_min - m_min + m_offset;
            __uint64_t max_val = im_max > m_max ? m_max - m_min + m_offset : 
                              im_max - m_min + m_offset;
            tuple<__uint64_t,__uint64_t> im_interval = {min_val, max_val};
            image.push_back(im_interval); 

            if (im_min < m_min) {
              tuple<__uint64_t,__uint64_t> remaining = {im_min, m_min-1};
              seed_intervals.push_back(remaining);
              size++;
            }
            if (im_max > m_max) {
              tuple<__uint64_t, __uint64_t> remaining = {m_max+1, im_max};
              seed_intervals.push_back(remaining);
              size++;
            } 
            match = 1;
            break;
          }
        } 
        if (match == 0) {
          image.push_back(seed_interval);
        }
      }
      seed_intervals.clear();
      for (auto interval : image) {
        seed_intervals.push_back(interval);
      }
      image.clear();
    }
    for (auto tup : seed_intervals) {
      solutions.push_back(tup);
    }
  }
  sort(begin(solutions), end(solutions),
      [](tuple<__uint64_t, __uint64_t> const &t1,
         tuple<__uint64_t, __uint64_t> const &t2) {
          return get<0>(t1) < get<0>(t2);
         }
  );
  cout << get<0>(solutions[0]) << endl;
  return 0;
}
