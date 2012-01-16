#include "GenericPlayer.h"
#include<string>

GenericPlayer::GenericPlayer()
{
   CurrentDeck = new Hand();
   DiscardedDeck = new Hand();
   LegalCards = new Hand();
   CurrentScore = 0;
}

GenericPlayer::~GenericPlayer()
{
}

void GenericPlayer::ResetDiscardedDeck()
{
   delete DiscardedDeck;
   DiscardedDeck = new Hand();
}

GenericPlayer::GenericPlayer(int playerNum, std::string playerType)
{
   PlayerNumber = playerNum;
   PlayerType = playerType;
   CurrentDeck = new Hand();
   DiscardedDeck = new Hand();
   LegalCards = new Hand();
   CurrentScore = 0;
}

GenericPlayer::GenericPlayer(const GenericPlayer& h)
{
//set points, current deck, type, and discards
    PlayerNumber = h.PlayerNumber;
    PlayerType = "c";
    CurrentDeck = h.CurrentDeck;
    DiscardedDeck = h.DiscardedDeck;
    LegalCards = h.LegalCards;
    CurrentScore = h.CurrentScore;
}

void GenericPlayer::CalculateScore()
{
   for(int i=0 ; i< DiscardedDeck->GetNumCards() ; i++)
   {
    int rank = (Rank)DiscardedDeck->GetCard(i).getRank() + 1;
     CurrentScore+= rank;
   }
}

Hand* GenericPlayer::GetCurrentDeck()
{
   return CurrentDeck;
}

Hand* GenericPlayer::GetDiscardedDeck()
{
   return DiscardedDeck;
}

Hand* GenericPlayer::GetLegalCards()
{
   return LegalCards;
}
bool GenericPlayer::HasLegalPlay()
{
    if(LegalCards->GetNumCards() == 0)
        return false;
    else
        return true;
}

int GenericPlayer::GetCurrentScore()
{
   return CurrentScore;
}

int GenericPlayer::GetPlayerNumber()
{
   return PlayerNumber;
}

std::string GenericPlayer::GetPlayerType()
{
   return PlayerType;
}

Card GenericPlayer::PlayCard(Card c) {

    return Card();
}
Card GenericPlayer::DiscardCard(Card c) {

    return  Card();
}


void GenericPlayer::CalculateLegalPlays(std::vector<Card> CardsOnTable,  bool StarterPlayer){
    int MinValues[4] =  {-1,-1,-1,-1};  //need to be -1 by default so that when onTable is empty ACE is not added to Legal Plays
    int MaxValues[4] = {-1,-1,-1,-1};
    int Ranks[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    Hand* LegalPlays = new Hand();
    for(int i = 0; i < CardsOnTable.size(); i++){
        for(int j = 0; j < 4; j++){


            if(CardsOnTable.at(i).getSuit() == (Suit)j){
            int rank = (Rank)CardsOnTable.at(i).getRank() + 1;
                //cout<<"Rank value"<<CardsOnTable.at(i).GetRankValue()<<endl; // this returns something really insane
                if(MinValues[j] == -1){
                    MinValues[j] =rank;
                }else if(rank< MinValues[j])
                    MinValues[j] =rank;
                 if(MaxValues[j] == -1)
                    MaxValues[j] = rank;
                else if(rank> MaxValues[j])
                    MaxValues[j] = rank;
            }
        }
    }

    std::vector<Card> PlayerCards =  GetCurrentDeck()->GetCards();
    for(int i = 0 ; i <  GetCurrentDeck()->GetNumCards();i++)
    {
       if(PlayerCards.at(i).getRank()==SEVEN)
       {
            if(StarterPlayer) // if he is the starter player, his ONLY play available should be 7S
            {
            if(PlayerCards.at(i).getSuit()==SPADE)
             LegalPlays->AddCard(PlayerCards.at(i));
            }
            else
            {
            LegalPlays->AddCard(PlayerCards.at(i));
            }
       }
       else
       {
          for(int j = 0; j < 4; j++) {
              if(PlayerCards.at(i).getSuit() == (Suit)j){
                 int value = PlayerCards.at(i).GetRankValue();
                 if(value ==   MinValues[j] -1 || value ==   MaxValues[j] + 1)
                 {
                    LegalPlays->AddCard(PlayerCards.at(i));
                 }
              }
          }
       }
    }
    LegalCards = LegalPlays;
}

/*
   will return a value of false or true, depending on whether the given assigned cards contains a 7 of spades or not
*/
bool GenericPlayer::AddCardstoDeck(std::vector<Card> *Cards, int PlayerNumber)
{
    int StartingNumberofDeck = 13*(PlayerNumber-1);
    int j = StartingNumberofDeck ;
    bool DeckContainsSevenSpades = false ;
    while(j - StartingNumberofDeck < 13) // use a const of number of cards dealed to each player
    {
       if(Cards->at(j).getSuit()==SPADE && Cards->at(j).getRank()== SEVEN)
       DeckContainsSevenSpades = true ;

       CurrentDeck->AddCard(Cards->at(j));
       j++;
    }
    return DeckContainsSevenSpades;
}
