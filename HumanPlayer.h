#ifndef _HumanPlayer_
#define _HumanPlayer_

#include "GenericPlayer.h"

class HumanPlayer : public GenericPlayer
{
public:
    HumanPlayer();                                      //default constructor
    ~HumanPlayer();                                     //destructor
    HumanPlayer(int playerNum, std::string PlayerType); //constructor taking a playerNum and playerType
    Card PlayCard(Card c);                              //plays a card for a human player
    Card DiscardCard(Card c);                           //discards a card for a human player
};

#endif
