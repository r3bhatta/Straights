#include "PlayerDetailsGUI.h"
#include <gtkmm.h>
#include <sstream>


PlayerDetailsGUI::PlayerDetailsGUI() : RageButton("Rage!") , Points("0 points")  , Discards( "0 discards")  { }

std::string IntToString(int value){
    std::string retString = "";
    std::stringstream ss;
    ss << value;
    ss >> retString;
    return retString;
}

void PlayerDetailsGUI::SetScore(int newScore){
   score = newScore;
   Points.set_label(IntToString(newScore) + " points");
}

void PlayerDetailsGUI::SetDiscardCount(int newDiscardCount){
   discards = newDiscardCount;
   Discards.set_label(IntToString(newDiscardCount) + " discards");
}


int PlayerDetailsGUI::GetCurrentScore(){
    return score;
}

