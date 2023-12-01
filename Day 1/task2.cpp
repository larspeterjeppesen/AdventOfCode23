#include <iostream>
#include <cstring>
#include <vector>

std::vector<std::string> nums = {
  "zero",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine"
};

int checkdigit(char* buf) {

  if (isdigit(*buf)) {
    return *buf - '0';
  }

  int bufsize = 0;
  for (; buf[bufsize] != 0; bufsize++){}
  bufsize--; 

  //Parse string
  for (int i = 0; i < nums.size(); i++) {
    std::string number = nums[i];
    if (number.size() > bufsize) {
      continue;
    }

    int j = 0;
    for (; j < number.size(); j++) {
      if (buf[j] != number[j]) {
        break;
      }
    }
    if (j == number.size()) {
      return i;
    }
  } 

  return -1;
}


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
      int t = checkdigit(&buf[i]);
      if (t >= 0) {
        d1 = t;
        break;
      }
    }

    while (buf[i] != 0) {i++;}
    for (; i >= 0; i--) {
      int t = checkdigit(&buf[i]);
      if (t >= 0) {
        d2 = t;
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
