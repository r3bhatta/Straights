#include "ComputerPlayer.h"
#include<iostream>

using namespace std;

ComputerPlayer::ComputerPlayer() : GenericPlayer()
{
}

ComputerPlayer::ComputerPlayer(int playerNum,std::string PlayerType) : GenericPlayer(playerNum,PlayerType)
{
}

ComputerPlayer::ComputerPlayer(const GenericPlayer& h): GenericPlayer(h)
{
}

ComputerPlayer::~ComputerPlayer()
{
}

 Card ComputerPlayer::PlayCard(Card c)
{
    Card retCard = LegalCards->GetCard(0);
    LegalCards->RemoveCard(retCard);
    CurrentDeck->RemoveCard(retCard);
    cout << "Player " << PlayerNumber << " plays " << retCard<<"."<<endl;
    return retCard;
}

Card ComputerPlayer::DiscardCard(Card c)
{
    Card retCard = CurrentDeck->GetCard(0);
    CurrentDeck->RemoveCard(retCard);
    DiscardedDeck->AddCard(retCard);
    cout << "Player " << PlayerNumber << " discards " << retCard<<"."<<endl;
    return retCard;
}
