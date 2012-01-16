CXX= g++
CXXFLAGS = -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJS = SubjectGUI.o ControllerGUI.o DeckGUI.o ViewGUI.o Gui.o PlayerDetailsGUI.o Game.o Card.o HumanPlayer.o ComputerPlayer.o GenericPlayer.o Hand.o 
EXEC = Straights

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJS) -o $(EXEC)

clean:
	rm $(EXEC) $(OBJS)

PlayerDetailsGUI.o: PlayerDetailsGUI.h PlayerDetailsGUI.cpp
DeckGUI.o: DeckGUI.h Card.h DeckGUI.cpp
SubjectGUI.o: SubjectGUI.h SubjectGUI.cpp
ControllerGUI.o: ControllerGUI.h Game.h Hand.h ControllerGUI.cpp
ViewGUI.o: PlayerDetailsGUI.h ViewGUI.h ObserverGUI.h ControllerGUI.h Game.h SubjectGUI.h DeckGUI.h Hand.h Card.h ViewGUI.cpp
Gui.o: ViewGUI.h ControllerGUI.h Game.h Gui.cpp
Game.o: Game.h Card.h HumanPlayer.h ComputerPlayer.h SubjectGUI.h Game.cpp
Card.o : Card.cpp Card.h
HumanPlayer.o : HumanPlayer.cpp HumanPlayer.h GenericPlayer.h
ComputerPlayer.o : ComputerPlayer.cpp ComputerPlayer.h GenericPlayer.h
GenericPlayer.o : GenericPlayer.cpp GenericPlayer.h Hand.h
Hand.o : Hand.cpp Hand.h Card.h
