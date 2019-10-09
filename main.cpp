//CSCI 261: Final Project
//Chandler Mitchell
//The Unbeatable Game of Nim

//standard libraries
#include <iostream> //cin, cout, cerr
using namespace std;

//SFML
#include <SFML/Graphics.hpp> //drawing things
#include <SFML/Audio.hpp>    //music
using namespace sf;

//custom files
#include "GameState.h"
#include "Menus.h"
#include "GameLogicFunctions.h"



int main() {
    //Variables

    //music
    //All music by audionautix.com and released under the Creative Commons License 3.0
    Music backgroundMusic;
    if (!backgroundMusic.openFromFile("RubixCube.wav")) {
        cerr << "Failed to Load Music" << endl;
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(100.0);
        backgroundMusic.play();
    }

    GameState game = runMenus(backgroundMusic);

    if (game.getActivePlayer() != -1) {
        playGame(game);
    }

    game.printWinner();

    return EXIT_SUCCESS;                        // report our program exited successfully
}