
#include"HumanPlayer.h"
#include<iostream>

using namespace std;

HumanPlayer::HumanPlayer() : GenericPlayer()
{
}

HumanPlayer::~HumanPlayer()
{
}

HumanPlayer::HumanPlayer(int playerNum,std::string PlayerType) : GenericPlayer(playerNum,PlayerType)
{
}

Card HumanPlayer::PlayCard(Card c)
{

      LegalCards->RemoveCard(c);
      CurrentDeck->RemoveCard(c);
      cout << "Player " << PlayerNumber << " plays " << c <<"."<<endl;
      return c;
}

Card HumanPlayer::DiscardCard(Card c)
{
    DiscardedDeck->AddCard(c);
    CurrentDeck->RemoveCard(c);
    cout << "Player " << PlayerNumber << " discards " << c <<"."<< endl;
    return c;

}
