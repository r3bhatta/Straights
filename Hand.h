#ifndef _Hand_
#define _Hand_

#include "Card.h"
#include <vector>
class Hand
{
private:
int numCards;
std::vector<Card> Cards;

public:
Hand();
int GetNumCards();
void AddCard(Card card);      //add a card to the hand
void RemoveCard(Card card);   //remove a card from the hand
int FindCard(Card card);	  //returns the index of the card in the vector
Card GetCard(int index);      //gets a card from the hand given the index
std::vector<Card> GetCards();  //returns the vector of cards contained in the hand
};

#endif
