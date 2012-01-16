
#include "Hand.h"
#include <iostream>

using namespace std;
Hand::Hand()
{
numCards = 0 ;
Cards = std::vector<Card>();
}

int Hand::GetNumCards()
{
	return numCards;
}

void Hand::AddCard(Card card){
	Cards.push_back(card);
	numCards++;
}

Card Hand::GetCard(int index)
{
   return Cards.at(index);
}

std::vector<Card> Hand::GetCards(){
    return Cards;
}

void Hand::RemoveCard(Card card){
	int CardIndex = FindCard(card);
	if (CardIndex == -1){
		cout<<"Selected Card not in Hand" << endl;
		return;
	}
	Cards.erase(Cards.begin() + CardIndex);
	numCards--;
}

int Hand::FindCard(Card card){
	for(int i = 0; i < Cards.size(); i++){
		if(Cards.at(i) == card)
			return i;
	}
	return -1;
}
