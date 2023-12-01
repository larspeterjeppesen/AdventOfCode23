#include <iostream>
#include <cstring>
//#include <string>

int main() {

  FILE* fp = std::fopen("input", "r");

  char *buf = new char[128]();

  int sum = 0;
  
  while (std::feof(fp) == 0) {
    std::fgets(buf, 128, fp);  
    
    int d1 = 0;
    int d2 = 0;
    int i = 0;
    for (; i < 128 && buf[i] != 0; i++) {
      if (isdigit(buf[i])) {
        d1 = buf[i] - '0';
        break;
      }
    }

    while (buf[i] != 0) {i++;}
    for (; i >= 0; i--) {
      if (isdigit(buf[i])) {
        d2 = buf[i] - '0';
        break;
      }
    }
    std::cout << std::to_string(d1*10 + d2) << "\n";
    sum += d1*10 + d2;

    memset(buf, 0, 128);
  }
  std::cout << sum << "\n";
  return 0;
}
