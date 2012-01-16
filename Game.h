#ifndef _GAME_
#define _GAME_

#include <iostream>
#include <vector>
#include "Card.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "SubjectGUI.h"

class Game : public SubjectGUI{
	friend std::istream &operator>>(std::istream & instream, Card & card);

public:
	int static const NumberOfPlayers = 4 ;

    Game();
    void CreateDeck();  //creates the original deck
    void AddComputerPlayer(ComputerPlayer * player);    //adds a computer player to the list of Players in game
    void AddHumanPlayer(HumanPlayer  * player);         //adds a human player to the list of Players in game
    int DealCards();                                    //eals 13 cards to each player
    void ShuffleCards();
    int CalculateNumCardsPlayed();                       //a round ends when 52 cards have been played
    Hand* GetHand(int PlayerNumber);
    void StartGameGUI();
    int GetCurrentPlayer();
    void NextPlayerTurn();
    void PlayCurrentPlayerCard( Card c);
    void DiscardCurrentPlayerCard(Card c);
    std::vector<Card> GetOnTable();
    void SelectCard(Card c);
    void NewRoundGUI();
    int GetPlayerScore(int PlayerNumber);
    void SetSeed(long seed);
    void ResetGame();
    int GetNumDiscards(int PlayerNumber);
    void SetComputerPlayer(int PlayerIndex);
    bool IsComputerPlayer(int PlayerIndex);
    void PlayComputerCard();
    void PlayComputerPlayerCard();
    std::string FindAndReturnGameWinner();
    std::string ReturnScoresAndDiscards();
    Hand* GetLegalCards(int PlayerIndex);
    std::string convertInt(int number);

private:
   int FirstPlayer; //holds the first player  //1 based
   int CurrentPlayer; //holds the current player //1 based
   std::vector<Card> *Deck;
   std::vector<Card> OnTable;
   std::vector<GenericPlayer*> *Players;

};

#endif
