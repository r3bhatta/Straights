#include "ControllerGUI.h"
#include<iostream>
#include<vector>


ControllerGUI::ControllerGUI(Game *NewGame )  // Create controller
{
   BaseGame = NewGame;
}
void ControllerGUI::StartGame()
{
   BaseGame->ResetGame();
   BaseGame->StartGameGUI();
}

void ControllerGUI::SelectCard(Card c){
   BaseGame->SelectCard(c);
}

void ControllerGUI::NewRound(){
   BaseGame->NewRoundGUI();
}

void ControllerGUI::SetSeedGUI(long seed)
{
   BaseGame->SetSeed(seed);
}

void ControllerGUI::SetComputerPlayer(int PlayerIndex){

   BaseGame->SetComputerPlayer(PlayerIndex);
}

void ControllerGUI::PlayComputerCard(){
   BaseGame->PlayComputerCard();
}
