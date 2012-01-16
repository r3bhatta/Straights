#ifndef _GenericPlayer_
#define _GenericPlayer_

#include"Hand.h"
#include<vector>

class GenericPlayer
{
protected:
    int PlayerNumber;
    std::string PlayerType; //of type Human or Computer
    Hand* CurrentDeck;
    Hand* DiscardedDeck;
    Hand* LegalCards;
    int CurrentScore;

public:
    GenericPlayer();                                        //default constructor
    virtual ~GenericPlayer();                               //destructor
    GenericPlayer(int playerNum, std::string PlayerType);
    GenericPlayer(const GenericPlayer& h);
    int GetCurrentScore();                                  //get the score of the player
    std::string GetPlayerType();                            //returns 'c' or 'h' for player type
    int GetPlayerNumber();                                  //accessor for player number
    bool HasLegalPlay();                                    //checks if the player has any legal plays
    void CalculateLegalPlays(std::vector<Card> CardsOnTable, bool StarterPlayer);   //calculates all possible legal plays for player
    Hand* GetLegalCards();                                  //returns the hand containing all legal plays
    Hand* GetCurrentDeck();                                 //returns hand containing current deck
    Hand* GetDiscardedDeck();                               //returns hand containing discarded deck
    bool AddCardstoDeck(std::vector<Card> *Cards, int PlayerNumber);    //adds cards to current deck from the original deck
    void CalculateScore();                                  //calculates the players score
    void ResetDiscardedDeck();                              //resets discarded deck of player to an empty hand

    virtual Card PlayCard(Card c);                          //overrided in derived classes
    virtual Card DiscardCard(Card c);                       //overrided in derived classes
};


#endif
