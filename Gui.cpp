#include"ViewGUI.h"
#include <gtkmm.h>
#include"Game.h"
#include"ControllerGUI.h"


int main(int argc, char *argv[]){
    Gtk::Main kit(argc, argv);
    Game NewGame;
    ControllerGUI Controller( &NewGame );  // Create controller -- is passed reference to model
    ViewGUI View( &Controller, &NewGame );     // Create the view -- is passed reference to controller and model

    Gtk::Main::run(View);
    return EXIT_SUCCESS;
}

