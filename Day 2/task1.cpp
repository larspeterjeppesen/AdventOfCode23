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
  int red_max = 12, blue_max = 14, green_max = 13;
  int game_sum = 0;
  int game = 1;

  // Each iteration is a new game
  while (std::fgets(buf, 256, fp) != NULL) {
    int game_possible = 1;
    std::string line = buf;
    std::string::size_type n; 
 
    n = line.find(':');
    line = line.substr(n+2, line.size() - n+2); 
    n = line.size();

    // Each iteration parses a 'handful' in each game
    while (game_possible) { 
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
      if (cols[0] > red_max || cols[1] > blue_max || cols[2] > green_max) {
        game_possible = 0;
      }
       
      if (n == line.size()) {
        break;
      }

      line = line.substr(n+2, line.size() - n+2);
    } 
    if (game_possible) {
      game_sum += game;
    }
    game++;
    memset(buf, 0, 256);
  }

  std::cout << game_sum << std::endl;
  std::fclose(fp);

  return 0;
}
