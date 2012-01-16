#ifndef __ViewGUI_H
#define __ViewGUI_H
#include <gtkmm.h>
#include "Card.h"
#include"PlayerDetailsGUI.h"
#include "DeckGUI.h"
#include "ObserverGUI.h"
#include "ControllerGUI.h"
#include "Game.h"
#include "SubjectGUI.h"

class ViewGUI : public Gtk::Window, public ObserverGUI {
public:
	ViewGUI(ControllerGUI *Controller,Game *NewGame );     // Create the view -- is passed handle to controller and model
	virtual ~ViewGUI();
	Gtk::VBox AddPlayerDetailsGUI(PlayerDetailsGUI details);
    void QuitGame();
	void InsertNullCards();
	void InsertValidCard(Card c);
	void StartGame();

	void AttachCardsToTable();

    virtual void update();	// Observer Pattern: concrete update() method
    void UpdateHandsDisplay();
    void UpdateTable();
    void GetLatestHands();
    void CardButtonClicked(int ButtonIndex);
    void ResetTable();
    bool EndRound();
    void UpdateScores();
    bool EndGame();
    void DisableAllButtons();
    void SeedButtonClicked();
    void UpdateDiscards();
    void RageButtonClicked(int PlayerIndex);
    void EndGameDialog() ;
    void EndRoundDialog();
    void ExitGameDialog();
    void UpdateRecordOfPlays();
    void DisableCardButtons();

private:
    static const int NumRows = 4;
    static const int NumCols = 13 ;
    long seed  ;

    Game *BaseGame;
    ControllerGUI *BaseController;

    DeckGUI                         deck;             // Knows all of the card pixel buffers.

    Hand                         * PlayerHands[4]; //contains the hands of the players
    // Member widgets:
    Gtk::Image                    * card[13];          // Images to display.
    Gtk::Image                    * Tablecards[52];          // Images to display.


    Gtk::Button                     Cardbutton[13];           // Button that will hold an image.
    PlayerDetailsGUI                PlayerDetails[4];

    Gtk::Button                     StartButton,EndButton;

    Gtk::HBox                       CardHbox;             // Horizontal box for aligning widgets in the window.
    Gtk::HBox                       PlayerControllerBox;
    Gtk::HBox                       PlayerBox;

    Gtk::VBox                       VerticalBoxHolder;
    Gtk::VBox                       PlayersVBox[4];
    Gtk::VBox                       MenuBox;

    Gtk::Frame                      Mainframe;
    Gtk::Frame                      PlayerHandFrame;
    Gtk::Frame                      OnTableFrame;
    Gtk::Frame                      PlayersBoxFrame[4];

    Gtk::Table                      OnTable;

    Glib::RefPtr<Gtk::UIManager> m_refUIManager;
    Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;


};
#endif
