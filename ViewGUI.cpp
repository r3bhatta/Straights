#include <stdlib.h>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "ViewGUI.h"

void ViewGUI::QuitGame(){
    ExitGameDialog();
}

void ViewGUI::DisableCardButtons(){
   for(int i = 0; i < 13; i++){
      Cardbutton[i].set_sensitive(false);
   }
}

void ViewGUI::StartGame(){
    for(int i = 0; i < 4; i++){
      PlayerDetails[i].RageButton.set_sensitive(true);
    }
    ResetTable();
    BaseController->SetSeedGUI(seed);
    BaseController->StartGame();
}

void ViewGUI::AttachCardsToTable(){
	int k  = 0 ;
	for(int i = 0 ; i < NumRows ; i++)
	{
	   for(int j = 0 ; j < NumCols; j++)
	   {
	   OnTable.attach(*Tablecards[k],j,j+1,i,i+1);
	   k++;
	   }
	}
}

void ViewGUI::InsertNullCards(){
    for(int i = 0; i < 52; i++){
      Tablecards[i] = new Gtk::Image( deck.getNullCardImage());
    }
}

void ViewGUI::InsertValidCard(Card c){
   const int CardsPerSuit = 13;
   int CardIndex = CardsPerSuit * (int)c.getSuit() + c.GetRankValue() -1;
   int suit = (int)c.getSuit();
   int rank = (int)c.getRank();
   Tablecards[CardIndex]->set(deck.getCardImage(c.getRank(), c.getSuit()));
}

void ViewGUI::ResetTable(){
   for(int i = 0; i < 52; i++){
      Tablecards[i]->set(deck.getNullCardImage());
   }
}

void ViewGUI::UpdateTable(){
   std::vector<Card> table = BaseGame->GetOnTable();
   for(int i = 0; i < table.size(); i++){
      InsertValidCard(table.at(i));
   }
}

bool ViewGUI::EndRound(){
   int numCards = 0;
   for(int i = 0; i < 4; i++){
      numCards += PlayerHands[i]->GetNumCards();
   }
   if(numCards == 0) //if every player has played all cards
      return true;
   else
      return false;
}

void ViewGUI::UpdateScores(){
   for(int i = 0; i < 4; i++){
      PlayerDetails[i].SetScore(BaseGame->GetPlayerScore(i));
   }
}

bool ViewGUI::EndGame(){
    const int MaxScore = 80 ;
    for(int i = 0; i < 4; i++){
        if(PlayerDetails[i].GetCurrentScore() >= MaxScore)   // need to do checks for multiple people having scores greater than 80
        {
            return true;
        }
    }
    return false;
}

void ViewGUI::UpdateDiscards(){
   for(int i = 0; i < 4; i++){
      PlayerDetails[i].SetDiscardCount(BaseGame->GetNumDiscards(i));
   }
}


void ViewGUI::EndGameDialog() {

    Gtk::Dialog EndDialog( "Game Over!", *this );
    Gtk::Label   EndLabel( "" );
    std::string Winners =  BaseGame->FindAndReturnGameWinner();
    EndLabel.set_text(Winners);
    Gtk::VBox* contentArea = EndDialog.get_vbox();
    contentArea->pack_start( EndLabel, true, false );
    contentArea->set_spacing(20);
    EndLabel.show();

    Gtk::Button * okButton = EndDialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);

    // Wait for a response from the dialog box.
	int result = EndDialog.run();

    switch (result) {
        case Gtk::RESPONSE_OK:
        case Gtk::RESPONSE_ACCEPT:
            break;
        case Gtk::RESPONSE_CANCEL:
        default:
            break;
    }
}

void ViewGUI::EndRoundDialog(){

    Gtk::Dialog EndRoundDialog("End of Round", *this);
    Gtk::Label   ScoreAndDiscardsLabel( "" );
    std::string ScoreAndDiscards = BaseGame->ReturnScoresAndDiscards(); //need to get score from game //  BaseGame->FindAndReturnGameWinner();
    ScoreAndDiscardsLabel.set_text(ScoreAndDiscards);
    Gtk::VBox* contentArea = EndRoundDialog.get_vbox();
    contentArea->pack_start( ScoreAndDiscardsLabel, true, false );
    contentArea->set_spacing(40);
    ScoreAndDiscardsLabel.show();
    UpdateScores();
    Gtk::Button * okButton = EndRoundDialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);

    // Wait for a response from the dialog box.
    int result = EndRoundDialog.run();

    switch (result) {
        case Gtk::RESPONSE_OK:
        case Gtk::RESPONSE_ACCEPT:
            if(!EndGame()){
                ResetTable();
                BaseController->NewRound();
                break;
            }else{
                DisableAllButtons();
                EndGameDialog();
            }
        case Gtk::RESPONSE_CANCEL:
        default:
            break;
    }

}


void ViewGUI::update()
{
    UpdateHandsDisplay();
    UpdateScores();
    UpdateDiscards();
    if(EndRound()){
        EndRoundDialog();
    }else{
        UpdateTable();
    }
    if(!EndGame()){
        if(BaseGame->IsComputerPlayer(BaseGame->GetCurrentPlayer()-1)){
            BaseController->PlayComputerCard();
        }
    }
}

void ViewGUI::UpdateHandsDisplay(){
    DisableCardButtons();
    GetLatestHands();

    Hand* currentHand = PlayerHands[BaseGame->GetCurrentPlayer() - 1];
    Hand* legalCards = BaseGame->GetLegalCards(BaseGame->GetCurrentPlayer()-1);
    std::vector<Card> CurrentPlayerCards = currentHand->GetCards();

    for(int i = 0 ; i < currentHand->GetNumCards(); i++)
    {
        delete card[i];
        card[i] = new Gtk::Image(deck.getCardImage(CurrentPlayerCards.at(i).getRank(), CurrentPlayerCards.at(i).getSuit()));
        Cardbutton[i].set_image( *card[i] );
    }

    if(currentHand->GetNumCards() <13){
        delete card[currentHand->GetNumCards()];
        card[currentHand->GetNumCards()] = new Gtk::Image(deck.getNullCardImage());
        Cardbutton[currentHand->GetNumCards()].set_image(*card[currentHand->GetNumCards()]);
    }

    PlayerHandFrame.set_label( "Player " + BaseGame->convertInt(BaseGame->GetCurrentPlayer()) + "'s hand" );
    for(int i = 0; i < currentHand->GetNumCards(); i++){
        if(legalCards->GetNumCards() != 0){
            if(legalCards->FindCard(CurrentPlayerCards.at(i)) == -1)
                Cardbutton[i].set_sensitive(false);
            else
                Cardbutton[i].set_sensitive(true);
        }else{
            Cardbutton[i].set_sensitive(true);
        }
    }
}

void ViewGUI::GetLatestHands(){
    for(int i = 0; i < 4; i++){
        PlayerHands[i] = BaseGame->GetHand(i);
    }
}


void ViewGUI::DisableAllButtons(){
    for (int i = 0; i < 13; i++ ) {
        card[i]->set(deck.getNullCardImage());
        Cardbutton[i].set_image( *card[i] );
    }
}


void ViewGUI::CardButtonClicked(int ButtonIndex){
    if(ButtonIndex < PlayerHands[BaseGame->GetCurrentPlayer()-1]->GetNumCards()){
      Card playedCard = PlayerHands[BaseGame->GetCurrentPlayer()-1]->GetCard(ButtonIndex);
      BaseController->SelectCard(playedCard);
    }
}

void ViewGUI::RageButtonClicked(int PlayerIndex){
   PlayerDetails[PlayerIndex].RageButton.set_sensitive(false);
   BaseController->SetComputerPlayer(PlayerIndex);
}

void ViewGUI::ExitGameDialog(){
    Gtk::Dialog ExitDialog( "Exit Game", *this);

    Gtk::Label  ExitWarning("Are you sure you want to quit ?");
    Gtk::VBox* contentArea = ExitDialog.get_vbox();
    contentArea->pack_start( ExitWarning, true, false );
    contentArea->set_spacing(20);
    ExitWarning.show();

    Gtk::Button * okButton = ExitDialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    Gtk::Button * cancelButton = ExitDialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

  	int result = ExitDialog.run();

    switch (result) {
        case Gtk::RESPONSE_OK:
        case Gtk::RESPONSE_ACCEPT:
             exit(0);
             break;
        case Gtk::RESPONSE_CANCEL:
        default:
            break;
    }
}
void ViewGUI::SeedButtonClicked() {

    Gtk::Dialog SeedDialog( "Seed Entry", *this );

    Gtk::Entry   SeedField;
    Gtk::Label   SeedLabel( "Please enter a seed:" );
    Gtk::VBox* contentArea = SeedDialog.get_vbox();
    contentArea->pack_start( SeedLabel, true, false );
    contentArea->pack_start( SeedField, true, false );

    SeedField.set_text( "0" );
    SeedLabel.show();
    SeedField.show();

    Gtk::Button * okButton = SeedDialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    Gtk::Button * cancelButton = SeedDialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

    // Wait for a response from the dialog box.
	int result = SeedDialog.run();

    switch (result) {
        case Gtk::RESPONSE_OK:
        case Gtk::RESPONSE_ACCEPT:
            seed = atol( SeedField.get_text().c_str());
            break;
        case Gtk::RESPONSE_CANCEL:
        default:
            break;
    }
}

ViewGUI::ViewGUI(ControllerGUI *Controller,Game *NewGame) : StartButton("Start New Game") ,EndButton("End Current Game"), OnTable(4,13) {

    BaseController = Controller;
    seed = 0 ;

    BaseGame = NewGame;
	 const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	 const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf     = deck.getCardImage( TEN, SPADE );

    //BUTTON SIGNAL COLLECTIONS
    EndButton.signal_clicked().connect(sigc::mem_fun( *this, &ViewGUI::QuitGame ));
    StartButton.signal_clicked().connect(sigc::mem_fun( *this, &ViewGUI::StartGame ));

    m_refActionGroup = Gtk::ActionGroup::create();
    m_refActionGroup->add( Gtk::Action::create("MenuFile", "Menu") );
    m_refActionGroup->add( Gtk::Action::create("New", Gtk::Stock::NEW),
          sigc::mem_fun(*this, &ViewGUI::StartGame ) );
    m_refActionGroup->add( Gtk::Action::create("Quit", Gtk::Stock::QUIT),
          sigc::mem_fun(*this, &ViewGUI::QuitGame ) );
    m_refActionGroup->add( Gtk::Action::create("Seed","Set Game Seed"),
          sigc::mem_fun(*this, &ViewGUI::SeedButtonClicked ) );

    //Define how the actions are presented in the menus and toolbars:
    Glib::RefPtr<Gtk::UIManager> m_refUIManager = Gtk::UIManager::create();
    m_refUIManager->insert_action_group(m_refActionGroup);
    add_accel_group(m_refUIManager->get_accel_group());

    //Layout the actions in a menubar and toolbar:
    Glib::ustring ui_info =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='MenuFile'>"
    "      <menuitem action='New'/>"
    "      <menuitem action='Quit'/>"
    "      <menuitem action='Seed'/>"
    "    </menu>"
    "  </menubar>"
    "</ui>";

    try {
    m_refUIManager->add_ui_from_string(ui_info);
    } catch(const Glib::Error& ex) {
    std::cerr << "building menus and toolbars failed: " <<  ex.what();
    } // catch

    Gtk::Widget* pMenuBar = m_refUIManager->get_widget("/MenuBar") ;
    MenuBox.pack_start(*pMenuBar, Gtk::PACK_SHRINK);

    //Max 13 Cards that can possibly be played
    for(int i = 0; i < 13; i++){
        Cardbutton[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ViewGUI::CardButtonClicked), i));
    }

    //4 possible rage buttons can be clicked
    for(int i = 0; i < 4; i++){
        PlayerDetails[i].RageButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ViewGUI::RageButtonClicked), i));
    }

	 Mainframe.set_label_align( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP );
	 Mainframe.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );

	// Add the Mainframe to the window. Windows can only hold one widget, same for frames.
	add( Mainframe );
	// Add the horizontal box for laying out the images to the Mainframe.

	Mainframe.add(VerticalBoxHolder);

	VerticalBoxHolder.add(PlayerControllerBox);
	VerticalBoxHolder.add(OnTableFrame);

	OnTableFrame.add(OnTable);
    OnTable.set_row_spacings(2);

    ViewGUI::InsertNullCards();
    ViewGUI::AttachCardsToTable();

	VerticalBoxHolder.add(PlayerBox);

    for(int i = 0 ; i <4 ; i++)
    {
        PlayerBox.add(PlayersBoxFrame[i]);
        PlayersVBox[i].add(PlayerDetails[i].RageButton);
        PlayerDetails[i].RageButton.set_sensitive(false);
        PlayersVBox[i].add(PlayerDetails[i].Points);
        PlayersVBox[i].add(PlayerDetails[i].Discards);
        PlayersBoxFrame[i].add(PlayersVBox[i]);
        PlayersBoxFrame[i].set_label("Player " + BaseGame->convertInt(i+1));
    }


    VerticalBoxHolder.add(PlayerHandFrame);
    PlayerHandFrame.add(CardHbox);
    PlayerControllerBox.add(MenuBox) ;
    OnTableFrame.set_label("Cards on the table");
    PlayerHandFrame.set_label( "Your hand" );

	// Initialize 13 empty cards and place them in the box.
	for (int i = 0; i < 13; i++ ) {
		card[i] = new Gtk::Image( nullCardPixbuf );
		Cardbutton[i].set_image( *card[i] );
		CardHbox.add( Cardbutton[i] );
	}

    DisableAllButtons();

    BaseGame->subscribe(this);
    show_all();
}

ViewGUI::~ViewGUI() {
    BaseGame->unsubscribe(this);
	for (int i = 0; i < 13; i++ ) delete card[i];
    for (int i = 0; i < 52; i++ ) delete Tablecards[i];
}
