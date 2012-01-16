#ifndef __PlayerDetailsGUI_H
#define __PlayerDetailsGUI_H

#include <gtkmm.h>

class PlayerDetailsGUI
{
    public:
        Gtk::Button  RageButton;
        Gtk::Label   Points;
        Gtk::Label   Discards;

        PlayerDetailsGUI();
        int GetCurrentScore();
        void SetScore(int newScore);
        void SetDiscardCount(int newDiscardCount);

    private :
        int score;  //current score
        int discards;  //number of discards
};

#endif

