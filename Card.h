#ifndef _CARD_
#define _CARD_

#include <ostream>
#include <istream>

enum Suit { CLUB , DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE , TWO , THREE , FOUR , FIVE , SIX , SEVEN ,
			EIGHT, NINE, TEN, JACK , QUEEN, KING , RANK_COUNT };
int static const RankValues[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
std::string static const SuitString[4] = {"C", "D", "H", "S"};

class Card{
	friend std::istream &operator>>(std::istream &, Card &);

public:

  Card();
	Card(Suit, Rank);
	Suit getSuit() const;
	Rank getRank() const;
	int GetRankValue();
  std::string ToString();


private:
	Suit suit_;
	Rank rank_;
	int rankValue_;
};

bool operator==(const Card &, const Card &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif
