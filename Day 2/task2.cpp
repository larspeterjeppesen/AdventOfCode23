#include <iostream>
#include <tuple>
#include <cstring>
#include <vector>
//using namespace std; //Tomorrow I'm using this line

std::vector<std::string> colors = {
 "red",
 "blue",
 "green"
};

int main() {
  FILE* fp = std::fopen("input", "r");
  char* buf = new char[256]; 

  int power_sum = 0;

  // Each iteration is a new game
  while (std::fgets(buf, 256, fp) != NULL) {
    int game_possible = 1;
    std::string line = buf;
    std::string::size_type n; 
 
    n = line.find(':');
    line = line.substr(n+2, line.size() - n+2); 
    n = line.size();

    int red_max = 0, blue_max = 0, green_max = 0;
    // Each iteration parses a 'handful' in each game
    while (1) { 
      n = line.find(';');
      n = n == std::string::npos ? line.size() : n;
      auto handful = line.substr(0, n);
      std::vector<int> cols = {0,0,0};
     
      // Iterate over handful to identify numbers
      for (int i = 0; handful[i] != 0; i++) {
        if (isdigit(line[i])) { 
          int number = line[i] - '0';
          if (isdigit(line[i+1])) {
            number = number*10 + line[i+1] - '0';
            i++;
          } 
          // Check which color current number is associated with
          for (int col = 0; col < 3; col++) {
            auto c = colors[col];
            if (c.size() > line.size() - i) {
              continue;
            }
            if (line.compare(i+2, c.size(), c, 0, c.size()) == 0) { 
              cols[col] = number;
              break;
            } 
          }
        }
      }
      
      red_max = std::max(red_max, cols[0]);
      blue_max = std::max(blue_max, cols[1]);
      green_max = std::max(green_max, cols[2]);
       
      if (n == line.size()) {
        break;
      }

      line = line.substr(n+2, line.size() - n+2);
    } 
    power_sum += red_max * blue_max * green_max; 
    memset(buf, 0, 256);
  }

  std::cout << power_sum << std::endl;
  std::fclose(fp);

  return 0;
}
