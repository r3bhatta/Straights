#include"Game.h"
#include"Card.h"
#include <iostream>
#include<cstdlib>
#include <sstream>


using namespace std;

std::string Game::convertInt(int number)
{
    stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

Game::Game()    //default constructor
{
    Deck = new std::vector<Card>() ;
    OnTable =  std::vector<Card>() ;
    Players = new std::vector<GenericPlayer *>();
}

void Game::ResetGame(){
    delete Deck;
    delete Players;
    Deck = new std::vector<Card>() ;
    OnTable =  std::vector<Card>() ;
    Players = new std::vector<GenericPlayer *>();
}

void Game::CreateDeck()
{
    int  NumberofSuits = 4;
    int  NumberofRanks = 13 ;
    for(int i = 0 ; i<NumberofSuits ; i++)
    {
        for(int j = 0 ; j<NumberofRanks ; j++)
        {
            Deck->push_back(Card((Suit)i,(Rank)j)) ;
        }
    }
}

int Game::GetPlayerScore(int PlayerNumber){
    return Players->at(PlayerNumber)->GetCurrentScore();
}

int Game::GetCurrentPlayer(){
    return CurrentPlayer;
}

Hand* Game::GetHand(int PlayerIndex){
    return Players->at(PlayerIndex)->GetCurrentDeck();
}

void Game::StartGameGUI(){
    for(int i = 1 ; i <=4 ; i++)
    {
        AddHumanPlayer( new HumanPlayer(i,"h"));
    }

    CreateDeck();
    ShuffleCards();
    FirstPlayer = DealCards();
    CurrentPlayer = FirstPlayer;
    Players->at(CurrentPlayer-1)->CalculateLegalPlays(OnTable, true);
    notify();
}

void Game::ShuffleCards(){
    int n = 52;
    while ( n > 1 ) {
        int k = (int) (lrand48() % n);
        --n;
        Card c = Deck->at(n);
        Deck->at(n) = Deck->at(k);
        Deck->at(k) = c;
    }
}

void Game::SetSeed(long seed)
{
    srand48(seed);
}


void Game::AddComputerPlayer( ComputerPlayer *player)
{
    Players->push_back(player);
}

void Game::AddHumanPlayer(HumanPlayer * player){
    Players->push_back(player);
}

bool Game::IsComputerPlayer(int PlayerIndex){
   if(Players->at(PlayerIndex)->GetPlayerType() == "c")
      return true;
   else
      return false;
}

int Game::DealCards(){
   int StarterPlayer = 0 ;

   for(int i = 1 ; i<= NumberOfPlayers ; i++)
   {
      if(Players->at(i-1)->AddCardstoDeck(Deck,i))
      StarterPlayer = i;
   }
   return StarterPlayer;
}

void Game::SelectCard(Card c){
    if( Players->at(CurrentPlayer-1)->GetLegalCards()->FindCard(c) != -1)
    {
        FirstPlayer = -1;
        PlayCurrentPlayerCard(c);
    }else if(!(Players->at(CurrentPlayer-1)->HasLegalPlay())){
        DiscardCurrentPlayerCard(c);
    }
}

void Game::PlayComputerCard(){
   if(Players->at(CurrentPlayer-1)->HasLegalPlay() == true )
   {
      FirstPlayer = -1;
      PlayComputerPlayerCard();
   }else{
      DiscardCurrentPlayerCard(Card());
   }
}

int Game::CalculateNumCardsPlayed(){
    int NumberOfCards = OnTable.size();
    for(int i = 0; i < Players->size(); i++){
        NumberOfCards += Players->at(i)->GetDiscardedDeck()->GetNumCards();
    }
    return NumberOfCards;
}

void Game::NewRoundGUI(){
    OnTable =  std::vector<Card>() ; //resetting onTable
    for(int i = 0 ; i < 4 ; i++){
        Players->at(i)->CalculateScore();
        Players->at(i)->ResetDiscardedDeck();
    }
    ShuffleCards();
    FirstPlayer = DealCards();
    CurrentPlayer = FirstPlayer;
    Players->at(CurrentPlayer-1)->CalculateLegalPlays(OnTable, true);
    notify();
}

void Game::NextPlayerTurn(){
   if(CurrentPlayer == 4)
      CurrentPlayer = 1;
   else
      CurrentPlayer++;
}

void Game::PlayCurrentPlayerCard(Card c){
      Players->at(CurrentPlayer -1)->PlayCard(c);
      OnTable.push_back(c);
      NextPlayerTurn();
      Players->at(CurrentPlayer-1)->CalculateLegalPlays(OnTable, false);
      notify();
}

void Game::PlayComputerPlayerCard(){
      Card playedCard = Players->at(CurrentPlayer-1)->PlayCard(Card());
      OnTable.push_back(playedCard);
      NextPlayerTurn();
      Players->at(CurrentPlayer-1)->CalculateLegalPlays(OnTable, false);
      notify();
}

void Game::DiscardCurrentPlayerCard(Card c){
      Players->at(CurrentPlayer -1)->DiscardCard(c);
      NextPlayerTurn();
      Players->at(CurrentPlayer-1)->CalculateLegalPlays(OnTable, false);
      notify();
}

int Game::GetNumDiscards(int PlayerNumber){
   return Players->at(PlayerNumber)->GetDiscardedDeck()->GetNumCards();
}

std::vector<Card> Game::GetOnTable(){
   return OnTable;
}

std::string Game::FindAndReturnGameWinner(){
    string ReturnString;
    int min = -1 ;
    vector<int> WinnerIndex ;
    for(int i =1  ; i <=4 ; i++)
    {
        if(min==-1)
        {
            min = Players->at(i-1)->GetCurrentScore();
            WinnerIndex.push_back(i) ;
        }
        else if(min >  Players->at(i-1)->GetCurrentScore())
        {
            WinnerIndex.pop_back();
            WinnerIndex.push_back(i);
            min = Players->at(i-1)->GetCurrentScore();
        }
    }
    // for multiple winners
    for(int i =1  ; i <=4 ; i++)
    {
        if(i!= WinnerIndex[0] && min== Players->at(i-1)->GetCurrentScore() )
        {
            WinnerIndex.push_back(i) ;
        }
    }
    // printing out of multiple winner if neccessary
    for(int i = 0 ; i<WinnerIndex.size() ; i++)
    {
        ReturnString+= "Player " + convertInt(WinnerIndex.at(i)) + " wins!";
        ReturnString+= "\n";
        cout<<"Player "<<WinnerIndex.at(i)<<" wins!";
        cout<<endl;
    }
    return ReturnString;
}

std::string Game::ReturnScoresAndDiscards(){
    std::string retString = "";
    for(int i =1  ; i <=4 ; i++)
    {
        int playerScore = Players->at(i-1)->GetCurrentScore();
        Hand *Discards =  Players->at(i-1)->GetDiscardedDeck();
        Players->at(i-1)->CalculateScore();


        cout<<"Player "<<i<<"'s discards: ";
        retString += "Player " + convertInt(i) + "'s discards: ";
        for(int j = 0 ; j < Discards->GetNumCards() ; j++){
            retString += Discards->GetCard(j).ToString() + " ";
            cout<<Discards->GetCard(j)<<" ";
        }
        retString += "\n";
        cout<<endl;

        retString += "Player " + convertInt(i) + "'s score: ";
        retString += convertInt(playerScore) + " + " + convertInt(Players->at(i-1)->GetCurrentScore()-playerScore) + " = " + convertInt(Players->at(i-1)->GetCurrentScore());
        retString += "\n";
        cout<<"Player "<<i<<"'s score: ";
        cout<<playerScore<<" + "<< Players->at(i-1)->GetCurrentScore()-playerScore<<" = "<<  Players->at(i-1)->GetCurrentScore();
        cout<<endl;
        Players->at(i-1)->ResetDiscardedDeck();
    }
    return retString;
}

Hand* Game::GetLegalCards(int PlayerIndex){
    return Players->at(PlayerIndex)->GetLegalCards();
}

void Game::SetComputerPlayer(int PlayerIndex){
    Players->at(PlayerIndex) = new ComputerPlayer( *Players->at(PlayerIndex) );
    std::cout << "Player " << PlayerIndex+1 << " ragequits!" << std::endl;
    notify();
}
