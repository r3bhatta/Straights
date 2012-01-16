#ifndef CONTROLLERGUI_H
#define CONTROLLERGUI_H

#include "Game.h"
#include "Hand.h"
class ControllerGUI{

public:
Game *BaseGame;
ControllerGUI(Game *NewGame );  // Create controller
void StartGame();
void SelectCard(Card c);
void PlayComputerCard();
void NewRound();
void SetSeedGUI(long seed);
void SetComputerPlayer(int PlayerIndex);

};


#endif
