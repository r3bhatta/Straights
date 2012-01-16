#ifndef _ComputerPlayer_
#define _ComputerPlayer_

#include"Hand.h"
#include<vector>
#include "GenericPlayer.h"


class ComputerPlayer : public GenericPlayer
{
public:
   ComputerPlayer();
   ComputerPlayer(int playerNum,std::string PlayerType);
   ComputerPlayer(const GenericPlayer& h) ; // copy constructor for ragequit feature
   ~ComputerPlayer();
   Card PlayCard(Card c);
   Card DiscardCard(Card c);
};

#endif
