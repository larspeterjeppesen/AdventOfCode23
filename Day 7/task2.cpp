#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

#define FIVE_OF_A_KIND 7
#define FOUR_OF_A_KIND 6
#define FULL_HOUSE 5
#define THREE_OF_A_KIND 4
#define TWO_PAIR 3
#define ONE_PAIR 2
#define HIGH_CARD 1


int card_type_to_rank(char type) {
  switch (type) {
    case 'A': return 14;
    case 'K': return 13;
    case 'Q': return 12;
    case 'J': return 1;
    case 'T': return 10;
    default: return type - '0';
  }
  //never reached
  return -1;
}

// Always need to count how many are of the same value
// Pass string by value to avoid modification
int hand_type(string hand) {
  //Count duplicates
  unordered_map<char,int> cards;
  int jokers = 0;
  for (int i = 0; i < hand.size(); i++) {
    if (hand[i] == 'J') {
      jokers++;
    } else {
      cards[hand[i]]++;
    }
  }
  //Sort in vector so categorization is easy
  vector<int> cards_v;
  for (auto card_type : cards) {
    cards_v.push_back(card_type.second);
  } 
  sort(cards_v.begin(), cards_v.end(), greater<int>());

  if (jokers == 5) {
    cards_v.push_back(0);
  }

  //Card duplicates cases:
  //(5)
  //(4,1)
  //(3,2) (3,1,1)
  //(2,2,1) (2,1,1,1,1)
  //(1,1,1,1,1)

  switch(cards_v[0]+jokers) {
    case 5: return FIVE_OF_A_KIND;
    case 4: return FOUR_OF_A_KIND;
    case 3: if (cards_v[1] == 2) return FULL_HOUSE;
            return THREE_OF_A_KIND;
    case 2: if (cards_v[1] == 2) return TWO_PAIR;
            return ONE_PAIR;
    case 1: return HIGH_CARD;
    default: cout << "Failed to match cards\n";
             exit(0);
  } 

  //Not reached
  return 0;
}

int main() {
  //Step 0: Parse input, categorize each hand


  fstream fs;
  fs.open("input", fstream::in);

  vector<tuple<string, long, int>> hands;
  string hand;
  string bid;
  while (fs >> hand) {
    int t = hand_type(hand);
    fs >> bid;
    long b = stol(bid);
    tuple<string,long,int> entry = {hand, b, t};
    hands.push_back(entry);
  }

  //Step 2: Sort by type, then by second order rule
  sort(hands.begin(), hands.end(), 
      [](tuple<string, long, int> const &t1,
         tuple<string, long, int> const &t2) {
          if (get<2>(t1) != get<2>(t2)) {
            //Sort after type
            return get<2>(t1) < get<2>(t2); 
          } else {
            //Sort after second rule
            for (int i = 0; i < get<0>(t1).size(); i++) {
              int a = card_type_to_rank(get<0>(t1)[i]);
              int b = card_type_to_rank(get<0>(t2)[i]);
              if (a < b) {
                return true;
              } else if (a > b) {
                return false;
              }
            }
            return true; // Arbitrary tie
         }
       }
  );

  //Step 3: Run through sorted list to calc answer

  int rank = 0;
  int sum = 0;
  for (auto hand : hands) {
    rank++;
    sum = sum + rank * get<1>(hand);
  }
  cout << sum << endl;
  return 0;
}
