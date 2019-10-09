//
// Created by Chandler on 11/28/2018.
//

#include <bitset>
#include <iostream>
#include <utility>
#include <string>

#include "GameLogicFunctions.h"
#include "GameState.h"
#include "Flag.h"
#include "Field.h"
#include "Menus.h"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void playGame(GameState& currentGame) {
    //playerForce quit bool
    bool playerForceQuit = false;

    //setUpFields
    vector<Field> newFields;
    newFields.resize(currentGame.getNumFields());
    for (int i = 0; i < currentGame.getNumFields(); i++) {
        newFields.at(i).setFlags(currentGame.getFlagArrangement().at(i));
    }
    currentGame.setFields(newFields);

    //size the window
    unsigned windowHeight, windowWidth;
    windowHeight = 200;
    if (currentGame.getNumFields() == 1 || currentGame.getNumFields() == 2) {
        windowHeight += 150;
    }
    else {
        windowHeight += 380;
    }
    if (currentGame.getNumFields() <= 4) {
        windowWidth = 580;
    }
    else if (currentGame.getNumFields() <= 6) {
        windowWidth = 800;
    }
    else {
        windowWidth = 1020;
    }

    //load font
    Font font;
    if (!font.loadFromFile("cour.ttf")) {
        cerr << "Error Loading Font" << endl;
    }

    //load grass
    Texture grass;
    if (!grass.loadFromFile("grass.jpg")){
        cerr << "Error Loading Grass Texture" << endl;
        Image grassBackup;
        grassBackup.create(615, 615, Color::Green);
        grass.loadFromImage(grassBackup);
    }

    //make window
    RenderWindow window( VideoMode(windowWidth, windowHeight), "Board" );

    //make objects to display

    //current player
    Text currentPlayer;
    currentPlayer.setFont(font);
    currentPlayer.setFillColor(Color::White);
    currentPlayer.setCharacterSize(15);
    currentPlayer.setString("Current Player: " + currentGame.getPlayer(currentGame.getActivePlayer()).name);
    currentPlayer.setPosition(2,0);

    //what to do next
    Text currentAction;
    currentAction = currentPlayer;
    currentAction.setPosition(2,21);
    currentAction.setString("Select a Field, then Select How Many Flags to Remove");

    //dividing screen
    Vertex topLine[] = {Vertex(Vector2f(0, 21)), Vertex(Vector2f(window.getSize().x, 21))};
    Vertex secondLine[] = {Vertex(Vector2f(0, 42)), Vertex(Vector2f(window.getSize().x, 42))};
    Vertex bottomLine[] = {Vertex(Vector2f(0, window.getSize().y - 50)), Vertex(Vector2f(window.getSize().x, window.getSize().y - 50))};
    vector<array<Vertex, 2>> playerScoreDividers;
    if (currentGame.getNumPlayers() == 2) {
        array<Vertex, 2> divider = {Vertex(Vector2f(window.getSize().x/2.0, window.getSize().y - 50)), Vertex(Vector2f(window.getSize().x/2.0, window.getSize().y))};
        playerScoreDividers.push_back(divider);
    }
    else if (currentGame.getNumPlayers() == 3) {
        array<Vertex, 2> divider1 = {Vertex(Vector2f(window.getSize().x/3.0, window.getSize().y - 50)), Vertex(Vector2f(window.getSize().x/3.0, window.getSize().y))};
        array<Vertex, 2> divider2 = {Vertex(Vector2f(window.getSize().x/3.0*2, window.getSize().y - 50)), Vertex(Vector2f(window.getSize().x/3.0*2, window.getSize().y))};
        playerScoreDividers.push_back(divider1);
        playerScoreDividers.push_back(divider2);
    }
    else if (currentGame.getNumPlayers() == 4) {
        array<Vertex, 2> divider1 = {Vertex(Vector2f(window.getSize().x/2.0, window.getSize().y - 50)), Vertex(Vector2f(window.getSize().x/2.0, window.getSize().y))};
        array<Vertex, 2> divider2 = {Vertex(Vector2f(window.getSize().x/4.0, window.getSize().y - 50)), Vertex(Vector2f(window.getSize().x/4.0, window.getSize().y))};
        array<Vertex, 2> divider3 = {Vertex(Vector2f(window.getSize().x/4.0*3.0, window.getSize().y - 50)), Vertex(Vector2f(window.getSize().x/4.0*3.0, window.getSize().y))};
        playerScoreDividers.push_back(divider1);
        playerScoreDividers.push_back(divider2);
        playerScoreDividers.push_back(divider3);
    }

    //score
    vector<Text> playerScoreCount;
    Text tempPlayerScoreCount;
    tempPlayerScoreCount.setString("x" + to_string(currentGame.getPlayer(0).flagsCollected));
    tempPlayerScoreCount.setFont(font);
    tempPlayerScoreCount.setCharacterSize(15);
    tempPlayerScoreCount.setFillColor(Color::White);
    for (int i = 0; i < playerScoreDividers.size(); i++) {
        tempPlayerScoreCount.setPosition(playerScoreDividers.at(i).at(0).position.x - 25 - tempPlayerScoreCount.getLocalBounds().width, window.getSize().y - 25 - tempPlayerScoreCount.getLocalBounds().height);
        playerScoreCount.push_back(tempPlayerScoreCount);
    }
    tempPlayerScoreCount.setPosition(window.getSize().x - 25 - tempPlayerScoreCount.getLocalBounds().width, window.getSize().y - 25 - tempPlayerScoreCount.getLocalBounds().height);
    playerScoreCount.push_back(tempPlayerScoreCount);

    //flag icons
    vector<Flag> playerScoreFlags;
    Flag tempPlayerScoreFlag(0,0);
    tempPlayerScoreFlag.setScale(.2);
    for (int i = 0; i < playerScoreCount.size(); i++) {
        tempPlayerScoreFlag.setPosition(window.getSize().y - 6, playerScoreCount.at(i).getGlobalBounds().left - playerScoreCount.at(i).getGlobalBounds().width / 2.0 * playerScoreCount.at(i).getScale().x);
        playerScoreFlags.push_back(tempPlayerScoreFlag);
    }

    //player Names
    vector<Text> playerNameTags;
    Text tempName;
    tempName.setFillColor(Color::White);
    tempName.setFont(font);
    tempName.setCharacterSize(15);
    for (int i = 0; i < playerScoreFlags.size(); i++) {
        tempName.setString(currentGame.getPlayer(i).name.substr(0, 10));
        tempName.setPosition(static_cast<int>(playerScoreFlags.at(i).getBottom().getGlobalBounds().left - tempName.getGlobalBounds().width - 5), static_cast<int>(playerScoreCount.at(i).getGlobalBounds().top - tempName.getGlobalBounds().height/2));
        playerNameTags.push_back(tempName);
    }

    //fields
    vector<Sprite> fieldBackgrounds;
    Sprite tempFieldBackground;
    tempFieldBackground.setTexture(grass);
    tempFieldBackground.setTextureRect(IntRect(0,0,200,200));
    if (currentGame.getNumFields() == 1) {
        tempFieldBackground.setPosition(window.getSize().x/2.0 - tempFieldBackground.getLocalBounds().width/2.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
    }
    else if (currentGame.getNumFields() == 2) {
        tempFieldBackground.setPosition(window.getSize().x/3.0 - tempFieldBackground.getLocalBounds().width/3.0*2, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/3.0*2.0 - tempFieldBackground.getLocalBounds().width/3.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
    }
    else if (currentGame.getNumFields() == 3) {
        tempFieldBackground.setPosition(window.getSize().x/3.0 - tempFieldBackground.getLocalBounds().width/3.0*2, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/3.0*2.0 - tempFieldBackground.getLocalBounds().width/3.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/2.0 - tempFieldBackground.getLocalBounds().width/2.0, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
    }
    else if (currentGame.getNumFields() == 4) {
        tempFieldBackground.setPosition(window.getSize().x/3.0 - tempFieldBackground.getLocalBounds().width/3.0*2, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/3.0*2.0 - tempFieldBackground.getLocalBounds().width/3.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/3.0 - tempFieldBackground.getLocalBounds().width/3.0*2, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/3.0*2.0 - tempFieldBackground.getLocalBounds().width/3.0, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
    }
    else if (currentGame.getNumFields() == 5) {
        tempFieldBackground.setPosition(window.getSize().x/5.0 - tempFieldBackground.getLocalBounds().width/3.0*2, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/2.0 - tempFieldBackground.getLocalBounds().width/2.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/5.0*4.0 - tempFieldBackground.getLocalBounds().width/3.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/3.0 - tempFieldBackground.getLocalBounds().width/3.0*2, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/3.0*2.0 - tempFieldBackground.getLocalBounds().width/3.0, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
    }
    else if (currentGame.getNumFields() == 6) {
        tempFieldBackground.setPosition(window.getSize().x/5.0 - tempFieldBackground.getLocalBounds().width/3.0*2, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/2.0 - tempFieldBackground.getLocalBounds().width/2.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/5.0*4.0 - tempFieldBackground.getLocalBounds().width/3.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/5.0 - tempFieldBackground.getLocalBounds().width/3.0*2, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/2.0 - tempFieldBackground.getLocalBounds().width/2.0, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/5.0*4.0 - tempFieldBackground.getLocalBounds().width/3.0, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
    }
    else if (currentGame.getNumFields() == 7) {
        tempFieldBackground.setPosition(window.getSize().x/7.0 - tempFieldBackground.getLocalBounds().width/3.0*2, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/3.0 - tempFieldBackground.getLocalBounds().width/3.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/3.0*2.0 - tempFieldBackground.getLocalBounds().width/3.0*2, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/7.0*6.0 - tempFieldBackground.getLocalBounds().width/3.0, 70);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/5.0 - tempFieldBackground.getLocalBounds().width/3.0*2, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/2.0 - tempFieldBackground.getLocalBounds().width/2.0, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
        tempFieldBackground.setPosition(window.getSize().x/5.0*4.0 - tempFieldBackground.getLocalBounds().width/3.0, fieldBackgrounds.at(0).getGlobalBounds().top + fieldBackgrounds.at(0).getGlobalBounds().height + 30);
        fieldBackgrounds.push_back(tempFieldBackground);
    }

    currentGame.setStatus(1);

    //flags to put in fields
    vector<vector<pair<Flag, bool>>> fieldFlags;
    fieldFlags.resize(currentGame.getNumFields());
    for (int i = 0; i < currentGame.getNumFields(); i++) {
        fieldFlags.at(i).resize(36);
        for (auto& a : fieldFlags.at(i)) {
            a.second = true;
        }
        for (int j = 0; j < fieldFlags.at(i).size(); j++) {
            fieldFlags.at(i).at(j).first.setScale(.15,.13);
        }
        fieldFlags.at(i).at(0).first.setPosition(fieldBackgrounds.at(i).getGlobalBounds().top + 5 + static_cast<int>(fieldFlags.at(i).at(0).first.getUpright().getLocalBounds().height * fieldFlags.at(i).at(0).first.getUpright().getScale().y), fieldBackgrounds.at(i).getGlobalBounds().left + 5);
        for (int j = 6; j < fieldFlags.at(i).size(); j+=6) {
              fieldFlags.at(i).at(j).first.setPosition(fieldFlags.at(i).at(j - 6).first.getPosition(true).x + (fieldBackgrounds.at(0).getLocalBounds().height-10-(fieldFlags.at(0).at(0).first.getUpright().getLocalBounds().height * fieldFlags.at(0).at(0).first.getUpright().getScale().y))/5, fieldFlags.at(i).at(0).first.getPosition(true).y);
        }
        for (int j = 0; j < fieldFlags.at(i).size(); j++) {
            if (j%6 != 0) {
                fieldFlags.at(i).at(j).first.setPosition(fieldFlags.at(i).at( j-1 ).first.getPosition(true).x, fieldFlags.at(i).at( j-1 ).first.getPosition(true).y + (fieldBackgrounds.at(0).getLocalBounds().width-15-(fieldFlags.at(i).at(j).first.getBottom().getLocalBounds().width*fieldFlags.at(i).at(j).first.getBottom().getScale().y))/5);
            }
        }
    }
    //set which flags to display
    for (int i = 0; i < currentGame.getNumFields(); i++) {
        for (int j = 35; j > currentGame.getFlagArrangement().at(i) - 1; j--) {
            fieldFlags.at(i).at(j).second = false;
        }
    }



    while( window.isOpen() && !playerForceQuit ) {
        window.clear( Color::Black );           // clear the contents of the old frame

        //draw objects
        window.draw(currentPlayer);
        window.draw(currentAction);
        window.draw(topLine, 2, Lines);
        window.draw(secondLine, 2, Lines);
        window.draw(bottomLine, 2, Lines);
        for (const auto& a : playerScoreDividers) {
            Vertex temp[] = {a.at(0), a.at(1)};
            window.draw(temp, 2, Lines);
        }
        for (const Text& a : playerScoreCount) {
            window.draw(a);
        }
        for (const Flag a : playerScoreFlags) {
            window.draw(a.getBottom());
            window.draw(a.getUpright());
            window.draw(a.getFlag());
        }
        for (const Sprite& a : fieldBackgrounds) {
            window.draw(a);
        }
        for (const auto& a : fieldFlags) {
            for(const auto& b : a) {
                if (b.second) {
                    window.draw(b.first.getBottom());
                    window.draw(b.first.getUpright());
                    window.draw(b.first.getFlag());
                }
            }
        }
        for (const Text& a : playerNameTags) {
            window.draw(a);
        }


        window.display();                       // display the window


        //game logic
        Event event;
        while( window.pollEvent(event) ) {      // ask the window if any events occurred
            bool playedGame = false;
            if( event.type == Event::Closed ) { // if event type is a closed event
                // i.e. they clicked the X on the window
                playerForceQuit = true;
                window.close();                 // then close our window
            }
            //multifield
            else if (currentGame.getNumFields() != 1) {
                //human
                if (!currentGame.getPlayer(currentGame.getActivePlayer()).isComp) {
                    if (currentGame.getStatus() == 1) {
                        //figure out which field was clicked
                        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                            Vector2i mousePosition = Mouse::getPosition(window);
                            int fieldClicked = -1, flagsToRemove;
                            for (int i = 0; i < fieldBackgrounds.size(); i++) {
                                if (isClicked(fieldBackgrounds.at(i), mousePosition) &&
                                    !currentGame.getFields().at(i).isEmpty()) {
                                    fieldClicked = i;
                                    break;
                                }
                            }
                            if (fieldClicked != -1) {
                                //remove flags from field
                                flagsToRemove = askRemoveFlags(1, currentGame.getFields().at(fieldClicked).getFlags());
                                if (flagsToRemove == -1) {
                                    playerForceQuit = true;
                                    break;
                                }
                                //cout << "Flags in Filed: " << currentGame.getFields().at(fieldClicked).getFlags() << endl;
                                currentGame.takeFlag(fieldClicked, flagsToRemove);
                                playedGame = true;
                                //cout << "Flags in Filed: " << currentGame.getFields().at(fieldClicked).getFlags() << endl;

                            }
                        }
                    }
                }
                //computer
                else {
                    //"AI MAGIC"
                    cout << currentGame.getPlayer(currentGame.getActivePlayer()).name << " is Thinking ... " << endl;
                    int fieldsWithFlags = 0, totalFlags = 0;
                    vector<string> bits;
                    for (const auto& a : currentGame.getFields()) {
                        bits.push_back(bitset<6>(a.getFlags()).to_string());
                        if (a.getFlags() != 0) {
                            fieldsWithFlags++;
                            totalFlags += a.getFlags();
                        }
                    }
                    array<int, 6> numberOfMultiples;
                    numberOfMultiples.fill(0);
                    for (const string& a : bits) {
                        for (int i = 0; i < 6; i++) {
                            if (a.at(i) == '1') {
                                numberOfMultiples.at(i)++;
                            }
                        }
                    }
                    bool allPaired = true;
                    int notPaired = -1;
                    for (int i = 0; i < 5; i++) {
                        if (numberOfMultiples.at(i)%2 == 1) {
                            allPaired = false;
                            notPaired = i;
                        }
                    }
                    int toTake = 0;
                    int fieldWithMax = 0;

                    //take all from last field
                    if (fieldsWithFlags == 1 && totalFlags > 1) {
                        for (int i = 0; i < currentGame.getNumFields(); i++) {
                            if (currentGame.getFields().at(i).getFlags() != 0) {
                                fieldWithMax = i;
                                toTake = currentGame.getFields().at(i).getFlags() - 1;
                                break;
                            }
                        }
                    }
                    //else make all paired
                    else if (!allPaired) {
                        for (int i = 0; i < bits.size(); i++) {
                            if (bits.at(i).at(notPaired) == '1') {
                                toTake = 6 - notPaired;
                                fieldWithMax = i;
                                break;
                            }
                        }
                    }
                    //else take one and pray
                    else {
                        toTake = 1;
                        for (int i = 0; i < currentGame.getNumFields(); i++) {
                            if (currentGame.getFields().at(i).getFlags() > currentGame.getFields().at(fieldWithMax).getFlags()) {
                                fieldWithMax = i;
                            }
                        }
                    }
                    currentGame.takeFlag(fieldWithMax, toTake);
                    playedGame = true;
                    cout << currentGame.getPlayer(currentGame.getActivePlayer()).name << " took " << toTake << " From Field " << fieldWithMax << endl;
                }
            }
            //singlefield
            else {
                //human
                if (!currentGame.getPlayer(currentGame.getActivePlayer()).isComp) {
                    if (currentGame.getStatus() == 1) {
                        int flagsToTake, maxTake = 3;
                        if (currentGame.getFields().at(0).getFlags() < maxTake) {
                            maxTake = currentGame.getFields().at(0).getFlags();
                        }
                        flagsToTake = askRemoveFlags(1, maxTake);
                        if (flagsToTake == -1) {
                            playerForceQuit = true;
                            break;
                        }
                        currentGame.takeFlag(0, flagsToTake);
                        playedGame = true;
                    }
                }
                //AI
                else {
                    //"AI MAGIC"
                    cout << currentGame.getPlayer(currentGame.getActivePlayer()).name << " is Thinking ... " << endl;
                    int toTake = 0;
                    if (currentGame.getFields().at(0).getFlags() > 8){
                        if (currentGame.getFields().at(0).getFlags() - 1 % 4 == 0) {
                            toTake = 1;
                        }
                        else {
                            toTake = (currentGame.getFields().at(0).getFlags() - 1) % 4;
                        }
                    }
                    else if (currentGame.getFields().at(0).getFlags() == 1) {
                        toTake = 1;
                    }
                    else if (currentGame.getFields().at(0).getFlags() == 8 || currentGame.getFields().at(0).getFlags() == 7 || currentGame.getFields().at(0).getFlags() == 6) {
                        toTake = currentGame.getFields().at(0).getFlags() - 5;
                    }
                    else if (currentGame.getFields().at(0).getFlags() == 5) {
                        toTake = 1;
                    }
                    else {
                        toTake = currentGame.getFields().at(0).getFlags() - 1;
                    }
                    if (toTake == 0) {
                        toTake = 1;
                    }
                    currentGame.takeFlag(0, toTake);
                    playedGame = true;
                    cout << currentGame.getPlayer(currentGame.getActivePlayer()).name << " took " << toTake << " From Field " << 0 << endl;
                }
            }
            //update display
            if (playedGame) {
                cout << "Updating Display ... " << endl;

                //update all scores
                for (int i = 0; i < currentGame.getNumPlayers(); i++) {
                    playerScoreCount.at(i).setString("x" + to_string(currentGame.getPlayer(i).flagsCollected));
                }

                //update all field flags
                for (int i = 0; i < currentGame.getNumFields(); i++) {
                    for (int j = 35; j > currentGame.getFields().at(i).getFlags() - 1; j--) {
                        fieldFlags.at(i).at(j).second = false;
                    }
                }

                //if player lost
                if (!currentGame.flagRemains()) {
                    currentGame.assignLooser();
                    window.close();
                    bool atLeastTwoPlayersRemain = false;
                    for (int i = 0; i < currentGame.getNumPlayers(); i++) {
                        if (!currentGame.getPlayer(i).hasLost) {
                            for (int j = i + 1; j < currentGame.getNumPlayers(); j++) {
                                if (!currentGame.getPlayer(j).hasLost) {
                                    atLeastTwoPlayersRemain = true;
                                    break;
                                }
                            }
                            if (atLeastTwoPlayersRemain) {
                                break;
                            }
                        }
                    }
                    if (atLeastTwoPlayersRemain) {
                        currentGame.intitializeGame();
                        playGame(currentGame);
                    } else {
                        for (int i = 0; i < currentGame.getNumPlayers(); i++) {
                            if (!currentGame.getPlayer(i).hasLost) {
                                currentGame.assignWinner(i);
                                return;
                            }
                        }
                    }
                } else {
                    //increment player
                    //DEBUG: cout << "End Player " << currentGame.getActivePlayer() << "'s turn, ";
                    currentGame.incrementPlayer();
                    //DEBUG: cout << "begin Player " << currentGame.getActivePlayer() << "'s turn." << endl;
                    //update player name at top of screen
                    currentPlayer.setString(
                            "Current Player: " + currentGame.getPlayer(currentGame.getActivePlayer()).name);
                }
                break;
            }
        }
    }
    //player forced quit
    if (playerForceQuit) {
        currentGame.assignWinner(-1);
    }
}

int askRemoveFlags(int lower, int upper) {
    RenderWindow window( VideoMode(250, 200), "Select Flags" );

    int toRemove = lower;

    Font font;
    if (!font.loadFromFile("cour.ttf")) {
        cerr << "Error Loading Font" << endl;
    }

    Text selectTop, selectBot;
    selectTop.setCharacterSize(25);
    selectTop.setFont(font);
    selectTop.setString("How Many Flags");
    selectTop.setPosition(static_cast<int>(window.getSize().x/2 - selectTop.getLocalBounds().width/2), 0);

    selectBot = selectTop;
    selectBot.setString("To Remove?");
    selectBot.setPosition(static_cast<int>(window.getSize().x/2 - selectBot.getLocalBounds().width/2), static_cast<int>(selectTop.getGlobalBounds().top + selectTop.getGlobalBounds().height));


    Flag leftFlag(133,50);
    leftFlag.setScale(.3);

    Text x;
    x.setFont(font);
    x.setCharacterSize(35);
    x.setString("x");
    x.setPosition(static_cast<int>(leftFlag.getFlag().getGlobalBounds().left + leftFlag.getFlag().getGlobalBounds().width + 5),static_cast<int>( leftFlag.getUpright().getGlobalBounds().top + leftFlag.getUpright().getGlobalBounds().height/2 - x.getLocalBounds().height/2));

    Text count;
    count.setFont(font);
    count.setCharacterSize(35);
    count.setString(to_string(toRemove));
    count.setPosition(static_cast<int>((x.getGlobalBounds().left + x.getGlobalBounds().width + window.getSize().x)/2 - count.getGlobalBounds().width/2),static_cast<int>(x.getGlobalBounds().top - count.getGlobalBounds().height));

    Text save;
    save.setFont(font);
    save.setCharacterSize(35);
    save.setString("Accept");
    save.setPosition(static_cast<int>(window.getSize().x/2 - save.getGlobalBounds().width/2), window.getSize().y - 15 - save.getGlobalBounds().height);

    Text plus, minus, minusLarge;
    plus.setString("+");
    plus.setCharacterSize(35);
    plus.setFont(font);
    plus.setPosition(count.getGlobalBounds().left+count.getGlobalBounds().width + 20, x.getGlobalBounds().top - (plus.getGlobalBounds().height) - 2);

    minus = plus;
    minus.setPosition(count.getGlobalBounds().left - minus.getGlobalBounds().width - 22, plus.getGlobalBounds().top - minus.getGlobalBounds().height + 2);
    minus.setString("-");


    minusLarge = minus;
    minusLarge.setString("+");

    while( window.isOpen() ) {
        window.clear( Color::Black );           // clear the contents of the old frame
        // by setting the window to black

        window.draw(selectTop);
        window.draw(selectBot);
        window.draw(leftFlag.getUpright());
        window.draw(leftFlag.getBottom());
        window.draw(leftFlag.getFlag());
        window.draw(x);
        window.draw(count);
        window.draw(save);
        window.draw(plus);
        window.draw(minus);


        window.display();                       // display the window

        //****************************************
        // HANDLE EVENTS BELOW HERE
        //****************************************
        Event event;
        while( window.pollEvent(event) ) {      // ask the window if any events occurred
            if( event.type == Event::Closed ) { // if event type is a closed event
                // i.e. they clicked the X on the window
                window.close();                 // then close our window
                return -1;
            }
            else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePosition = Mouse::getPosition(window);
                if (isClicked(plus, mousePosition)) {
                    if (toRemove < upper) {
                        toRemove++;
                    }
                    else {
                       toRemove=upper;
                       cerr << "Cannot select more than " << upper << " flags" << endl;
                    }
                }
                else if (isClicked(minusLarge, mousePosition)) {
                    if (toRemove > lower) {
                        toRemove--;
                    }
                    else {
                        toRemove = lower;
                        cerr << "Cannot remove less than " << lower << " flags" << endl;
                    }
                }
                else if (isClicked(save, mousePosition)) {
                    return toRemove;
                }
            }
            //update count
            count.setString(to_string(toRemove));
            count.setPosition(static_cast<int>((x.getGlobalBounds().left + x.getGlobalBounds().width + window.getSize().x)/2 - count.getGlobalBounds().width/2),static_cast<int>(x.getGlobalBounds().top - count.getGlobalBounds().height));
        }
    }

}