//
// Created by Chandler on 11/18/2018.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

#include "Flag.h"
#include "GameState.h"
#include "Menus.h"

using namespace std;
using namespace sf;

bool isClicked(const RectangleShape& object, const Vector2i& mousePosition) {
    return mousePosition.x > object.getGlobalBounds().left && mousePosition.x < object.getGlobalBounds().left+object.getGlobalBounds().width && mousePosition.y > object.getGlobalBounds().top && mousePosition.y < object.getGlobalBounds().top+object.getGlobalBounds().height;
}

bool isClicked(const Text& object, const Vector2i& mousePosition) {
    return mousePosition.x > object.getGlobalBounds().left && mousePosition.x < object.getGlobalBounds().left+object.getGlobalBounds().width && mousePosition.y > object.getGlobalBounds().top && mousePosition.y < object.getGlobalBounds().top+object.getGlobalBounds().height;
}

bool isClicked(const Sprite& object, const Vector2i& mousePosition) {
    return mousePosition.x > object.getGlobalBounds().left && mousePosition.x < object.getGlobalBounds().left+object.getGlobalBounds().width && mousePosition.y > object.getGlobalBounds().top && mousePosition.y < object.getGlobalBounds().top+object.getGlobalBounds().height;
}

int mainMenu() {
    //grass
    Texture grass;
    if (!grass.loadFromFile("grass.jpg")){
        cerr << "Error Loading Grass Texture" << endl;
        Image grassBackup;
        grassBackup.create(615, 615, Color::Green);
        grass.loadFromImage(grassBackup);
    }
    Sprite backgroundGrass;
    backgroundGrass.setTexture(grass);
    backgroundGrass.setScale(1.0f, 0.5f);
    backgroundGrass.setPosition(0, 615/2.0);

    //path
    Texture path;
    Image pathBackup;
    Color brown(225,153,83,255);
    pathBackup.create(72, 615/2.0+3.0, Color::Transparent);
    for (int x = 0; x < pathBackup.getSize().x; x++){
        for (int y = 0; y < pathBackup.getSize().y; y++) {
            if (x*25.0 >= y && x*-25.0+pathBackup.getSize().x*25 >= y) {
                pathBackup.setPixel(x,y, brown);
            }
        }
    }
    path.loadFromImage(pathBackup);
    Sprite pathMenu;
    pathMenu.setTexture(path);
    pathMenu.setPosition(615/2.0-73/2.0, (615/2.0));
    pathMenu.setOrigin(pathBackup.getSize().x, pathBackup.getSize().y);
    pathMenu.setRotation(180);

    //sky
    RectangleShape sky;
    Color skyBlue(21,44,171,255);
    sky.setSize(Vector2f(615,615));
    sky.setFillColor(skyBlue);

    //title
    Font font;
    if (!font.loadFromFile("cour.ttf")) {
        cerr << "Error Loading Font" << endl;
    }
    Text title;
    title.setString("NIM");
    title.setFont(font);
    title.setCharacterSize(150);
    title.setPosition(615/2.0-(title.getLocalBounds().width/2.0), 30);

    //flags
    Flag left(backgroundGrass.getPosition().y, 50);
    Flag right(backgroundGrass.getPosition().y, 615-150);
    right.setScale(.78);

    //Play
    RectangleShape playBox;
    Color transparentGrey(0,0,0,225);
    playBox.setFillColor(transparentGrey);
    playBox.setSize(Vector2f(200,50));
    playBox.setOutlineColor(Color::Black);
    playBox.setOutlineThickness(5);
    playBox.setPosition(615/2.0-(playBox.getSize().x/2.0), 615*7.0/12.0 - 15);
    Text play;
    play.setString("Play!");
    play.setFont(font);
    play.setFillColor(Color::White);
    play.setCharacterSize(40);
    play.setPosition(playBox.getPosition().x+playBox.getSize().x/2.0-play.getLocalBounds().width/2.0,playBox.getPosition().y+playBox.getSize().y/2.0-play.getLocalBounds().height*.75);


    //options
    RectangleShape optionBox = playBox;
    optionBox.setPosition(playBox.getPosition().x, playBox.getPosition().y + 100);
    Text option;
    option.setString("Options");
    option.setFillColor(Color::White);
    option.setFont(font);
    option.setCharacterSize(40);
    option.setPosition(optionBox.getPosition().x+optionBox.getSize().x/2.0-option.getLocalBounds().width/2.0, optionBox.getPosition().y+optionBox.getSize().y/2.0-play.getLocalBounds().height*.75);

    //rules
    RectangleShape rulesBox = optionBox;
    rulesBox.setPosition(optionBox.getPosition().x, optionBox.getPosition().y + 100);
    Text rules;
    rules.setString("Rules");
    rules.setFillColor(Color::White);
    rules.setFont(font);
    rules.setCharacterSize(40);
    rules.setPosition(rulesBox.getPosition().x+rulesBox.getSize().x/2.0-rules.getLocalBounds().width/2.0, rulesBox.getPosition().y+rulesBox.getSize().y/2.0-play.getLocalBounds().height*.75);


    //Render Main Menu
    RenderWindow window( VideoMode(615, 615), "Main Menu" );
    while( window.isOpen() ) {
        window.clear( Color::Black );

        //draw
        window.draw(sky);
        window.draw(backgroundGrass);
        window.draw(pathMenu);
        window.draw(title);
        window.draw(left.getBottom());
        window.draw(left.getUpright());
        window.draw(left.getFlag());
        window.draw(right.getBottom());
        window.draw(right.getUpright());
        window.draw(right.getFlag());
        window.draw(playBox);
        window.draw(play);
        window.draw(optionBox);
        window.draw(option);
        window.draw(rulesBox);
        window.draw(rules);

        //display
        window.display();

        //events
        Event event;
        while( window.pollEvent(event) ) {      // ask the window if any events occurred
            if( event.type == Event::Closed ) { // if event type is a closed event
                // i.e. they clicked the X on the window
                window.close();                 // then close our window
                return -1;
            }
            else if (Mouse::isButtonPressed(Mouse::Left)) {
                Vector2i mousePosition = Mouse::getPosition(window);
                if (isClicked(playBox, mousePosition)){
                    window.close();
                    return 1;
                }
                if (isClicked(optionBox, mousePosition)){
                    window.close();
                    return 2;
                }
                if (isClicked(rulesBox, mousePosition)) {
                    window.close();
                    return 3;
                }
            }
        }
    }
    return 1;
}

int optionsMenu(Music& backgroundMusic, int& numHumans, int& numComputers, int& numFields, vector<int>& flagsInField) {

    //menu text positioning and constructing
    Font font;
    if (!font.loadFromFile("cour.ttf")) {
        cerr << "Error Loading Font" << endl;
    }
    Text title, players, computers, editFields, done, playersPlus, playersMinus, playersMinusLarge, playersCount, computersPlus, computersMinus, computersMinusLarge, computersCount, fields, fieldsPlus, fieldsMinus, fieldsMinusLarge, fieldsCount, toggleMusic;
    title.setString("Options");
    title.setFont(font);
    title.setCharacterSize(100);
    title.setPosition(640/2.0-(title.getLocalBounds().width/2.0), 15);

    players.setString("Number of Humans:");
    players.setFont(font);
    players.setCharacterSize(35);
    players.setPosition(25, 200);

    computers.setString("Number of Computers:");
    computers.setFont(font);
    computers.setCharacterSize(35);
    computers.setPosition(players.getPosition().x, players.getPosition().y+60);

    fields.setString("Number of Fields:");
    fields.setFont(font);
    fields.setCharacterSize(35);
    fields.setPosition(players.getPosition().x, computers.getPosition().y+60);

    editFields.setString("Edit Fields");
    editFields.setFont(font);
    editFields.setCharacterSize(35);
    editFields.setPosition(640/2.0-(editFields.getLocalBounds().width/2.0), fields.getPosition().y+60);

    toggleMusic.setString("Toggle Music Playback");
    toggleMusic.setFont(font);
    toggleMusic.setCharacterSize(35);
    toggleMusic.setPosition(640/2.0-(toggleMusic.getLocalBounds().width/2.0), editFields.getPosition().y+60);

    done.setString("Save");
    done.setFont(font);
    done.setCharacterSize(40);
    done.setPosition(640/2.0-(done.getLocalBounds().width/2.0), toggleMusic.getPosition().y+60);

    playersPlus.setString("+");
    playersPlus.setFont(font);
    playersPlus.setCharacterSize(35);
    playersPlus.setPosition(640-players.getPosition().x-playersPlus.getLocalBounds().width, players.getPosition().y);

    playersMinus = playersPlus;
    playersMinus.setString("-");
    playersMinus.setPosition(playersPlus.getPosition().x-playersMinus.getLocalBounds().width-75, playersPlus.getPosition().y);

    playersMinusLarge = playersMinus;
    playersMinusLarge.setString("+");

    playersCount = playersPlus;
    playersCount.setString(to_string(numHumans));
    playersCount.setPosition(((1.0/2.0)*(playersPlus.getPosition().x+playersPlus.getLocalBounds().width/2.0 + playersMinus.getPosition().x+playersMinus.getLocalBounds().width/2.0))-playersCount.getLocalBounds().width/2.0, players.getPosition().y);

    computersPlus = playersPlus;
    computersPlus.setPosition(playersPlus.getPosition().x, computers.getPosition().y);

    computersMinus = playersMinus;
    computersMinus.setPosition(playersMinus.getPosition().x, computers.getPosition().y);

    computersMinusLarge = computersMinus;
    computersMinusLarge.setString("+");

    computersCount = playersPlus;
    computersCount.setString(to_string(numComputers));
    computersCount.setPosition(((1.0/2.0)*(computersPlus.getPosition().x+computersPlus.getLocalBounds().width/2.0 + computersMinus.getPosition().x+computersMinus.getLocalBounds().width/2.0))-computersCount.getLocalBounds().width/2.0, computers.getPosition().y);

    fieldsPlus = playersPlus;
    fieldsPlus.setPosition(playersPlus.getPosition().x, fields.getPosition().y);

    fieldsMinus = playersMinus;
    fieldsMinus.setPosition(playersMinus.getPosition().x, fields.getPosition().y);

    fieldsMinusLarge = fieldsMinus;
    fieldsMinusLarge.setString("+");

    fieldsCount = playersPlus;
    fieldsCount.setString(to_string(numFields));
    fieldsCount.setPosition(((1.0/2.0)*(fieldsPlus.getPosition().x+fieldsPlus.getLocalBounds().width/2.0 + fieldsMinus.getPosition().x+fieldsMinus.getLocalBounds().width/2.0))-fieldsCount.getLocalBounds().width/2.0, fields.getPosition().y);

    RenderWindow window( VideoMode(640, 580), "Options" );
    while( window.isOpen() ) {
        window.clear( Color::Black );


        window.draw(title);
        window.draw(players);
        window.draw(computers);
        window.draw(fields);
        window.draw(editFields);
        window.draw(toggleMusic);
        window.draw(done);
        window.draw(playersPlus);
        window.draw(playersMinus);
        window.draw(playersCount);
        window.draw(computersPlus);
        window.draw(computersMinus);
        window.draw(computersCount);
        window.draw(fieldsPlus);
        window.draw(fieldsMinus);
        window.draw(fieldsCount);

        window.display();                       // display the window

        Event event;
        while( window.pollEvent(event) ) {      // ask the window if any events occurred
            if( event.type == Event::Closed ) { // if event type is a closed event
                window.close();
                return -1;
            }
            else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePosition = Mouse::getPosition(window);
                //do something based on what was clicked
                if (isClicked(done, mousePosition)) {
                    window.close();
                    if (numFields != flagsInField.size()) {
                        flagsInField.resize(numFields, 21);
                    }
                    return 0;
                }
                else if (isClicked(editFields, mousePosition)) {
                    if (fieldMenu(numFields, flagsInField, font) == -1){
                        window.close();
                        return -1;
                    }
                }
                else if (isClicked(playersPlus, mousePosition)) {
                    if (numHumans < 4) {
                        numHumans++;
                    }
                    else {
                        cerr << "Only Supports 4 Players" << endl;
                    }
                }
                else if (isClicked(playersMinusLarge, mousePosition)) {
                    if (numHumans > 1) {
                        numHumans--;
                    }
                    else {
                        cerr << "Must Have at least 1 Human" << endl;
                    }
                }
                else if (isClicked(computersPlus, mousePosition)) {
                    if (numComputers < 4) {
                        numComputers++;
                    }
                    else {
                        cerr << "Only Supports 4 Computers" << endl;
                    }
                }
                else if (isClicked(computersMinusLarge, mousePosition)) {
                    if (numComputers > 0) {
                        numComputers--;
                    }
                    else {
                        cerr << "Cannot have negative computers" << endl;
                    }
                }
                else if (isClicked(fieldsPlus, mousePosition)) {
                    if (numFields < 7) {
                        numFields++;
                    }
                    else {
                        cerr << "Cannot have more than 7 fields" << endl;
                    }
                }
                else if (isClicked(fieldsMinusLarge, mousePosition)) {
                    if (numFields > 1) {
                        numFields--;
                    }
                    else {
                        cerr << "Must have at lease one field" << endl;
                    }
                }
                else if (isClicked(toggleMusic, mousePosition)) {
                    switch (backgroundMusic.getStatus()) {
                        case Music::Status::Stopped:
                        case Music::Status::Paused:
                            backgroundMusic.play();
                            break;
                        case Music::Status::Playing:
                        default:
                            backgroundMusic.pause();
                    }
                }
            }
            if (numHumans == 1 && numComputers == 0) {
                cerr << "Must have Two Players" << endl;
                numComputers = 1;
            }
            if (numComputers + numHumans > 4) {
                cerr << "Cannot have more than 4 players" << endl;
                numComputers = 4 - numHumans;
            }
        }
        //update playerCount
        playersCount.setString(to_string(numHumans));
        playersCount.setPosition(((1.0/2.0)*(playersPlus.getPosition().x+playersPlus.getLocalBounds().width/2.0 + playersMinus.getPosition().x+playersMinus.getLocalBounds().width/2.0))-playersCount.getLocalBounds().width/2.0, players.getPosition().y);

        //update computerCount
        computersCount.setString(to_string(numComputers));
        computersCount.setPosition(((1.0/2.0)*(computersPlus.getPosition().x+computersPlus.getLocalBounds().width/2.0 + computersMinus.getPosition().x+computersMinus.getLocalBounds().width/2.0))-computersCount.getLocalBounds().width/2.0, computers.getPosition().y);

        //update fieldCount
        fieldsCount.setString(to_string(numFields));
        fieldsCount.setPosition(((1.0/2.0)*(fieldsPlus.getPosition().x+fieldsPlus.getLocalBounds().width/2.0 + fieldsMinus.getPosition().x+fieldsMinus.getLocalBounds().width/2.0))-fieldsCount.getLocalBounds().width/2.0, fields.getPosition().y);
    }
}

int fieldMenu(const int& numFields, vector<int>& flagsInFields, Font& font) {
    //resize the vector to the numFields
    flagsInFields.resize(numFields, 21);

    //for storing the text to display on screen
    vector<Text> fieldText, fieldTextPlus, fieldTextMinus, fieldTextMinusLarge, fieldTextCount;

    Text templateText, title, done;

    //title
    title.setString("Edit Fields");
    title.setFont(font);
    title.setCharacterSize(100);
    title.setPosition(740/2.0-(title.getLocalBounds().width/2.0), 15);

    //field text
    templateText.setFont(font);
    templateText.setCharacterSize(35);
    templateText.setPosition(25, 200);
    templateText.setString("Number of Flags in Field ");
    for (int i = 0; i < numFields; i++) {
        fieldText.push_back(templateText);
        fieldText.at(i).setString(fieldText.at(i).getString() + to_string(i+1) + ":");
        if (i != 0) {
            fieldText.at(i).setPosition(fieldText.at(0).getPosition().x, fieldText.at(i-1).getPosition().y+60);
        }
    }

    done.setString("Save");
    done.setFont(font);
    done.setCharacterSize(40);
    done.setPosition(740/2.0-(done.getLocalBounds().width/2.0), fieldText.at(fieldText.size()-1).getPosition().y+60);

    //field text plus
    templateText.setString("+");
    fieldTextPlus.resize(fieldText.size(), templateText);
    for (int i = 0; i < fieldTextPlus.size(); i++) {
        fieldTextPlus.at(i).setPosition(740-25-fieldTextPlus.at(i).getLocalBounds().width, fieldText.at(i).getPosition().y);
    }

    //field text minus
    templateText.setString("-");
    fieldTextMinus.resize(fieldText.size(), templateText);
    for (int i = 0; i < fieldTextMinus.size(); i++) {
        fieldTextMinus.at(i).setPosition(fieldTextPlus.at(i).getPosition().x-fieldTextPlus.at(i).getLocalBounds().width-75, fieldTextPlus.at(i).getPosition().y);
    }

    //field text minus large
    fieldTextMinusLarge.resize(fieldText.size());
    for (int i = 0; i < fieldTextMinusLarge.size(); i++) {
        fieldTextMinusLarge.at(i) = fieldTextMinus.at(i);
        fieldTextMinusLarge.at(i).setString("+");
    }

    //field text count
    templateText.setString("");
    fieldTextCount.resize(fieldText.size(), templateText);
    for (int i = 0; i < fieldTextCount.size(); i++) {
        fieldTextCount.at(i).setString(to_string(flagsInFields.at(i)));
        fieldTextCount.at(i).setPosition(((1.0/2.0)*(fieldTextPlus.at(0).getPosition().x+fieldTextPlus.at(0).getLocalBounds().width/2.0 + fieldTextMinus.at(0).getPosition().x+fieldTextMinus.at(0).getLocalBounds().width/2.0))-fieldTextCount.at(i).getLocalBounds().width/2.0, fieldText.at(i).getPosition().y);
    }


    RenderWindow window( VideoMode(740, 280+60*numFields), "Edit Fields" );
    while( window.isOpen() ) {
        window.clear( Color::Black );


        window.draw(title);
        for (const Text& a : fieldText) {
            window.draw(a);
        }
        for (const Text& a : fieldTextPlus) {
            window.draw(a);
        }
        for (const Text& a : fieldTextMinus) {
            window.draw(a);
        }
        for (const Text& a : fieldTextCount) {
            window.draw(a);
        }
        window.draw(done);

        window.display();


        Event event;
        while( window.pollEvent(event) ) {      // ask the window if any events occurred
            if( event.type == Event::Closed ) { // if event type is a closed event
                // i.e. they clicked the X on the window
                window.close();                 // then close our window
                return -1;
            }
            else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePosition = Mouse::getPosition(window);
                //increment or decrement the correct count based on what was clicked
                for (int i = 0; i < fieldTextPlus.size(); i++) {
                    if (isClicked(fieldTextPlus.at(i), mousePosition)) {
                        if (flagsInFields.at(i) < 35) {
                            flagsInFields.at(i)++;
                        }
                        else {
                            cerr << "Cannot have more than 35 flags in a field" << endl;
                        }
                        break;
                    }
                }
                for (int i = 0; i < fieldTextMinusLarge.size(); i++) {
                    if (isClicked(fieldTextMinusLarge.at(i), mousePosition)) {
                        if (flagsInFields.at(i) > 1) {
                            flagsInFields.at(i)--;
                        }
                        else {
                            cerr << "Each field must have at least one flag" << endl;
                        }
                        break;
                    }
                }
                if (isClicked(done, mousePosition)) {
                    return 0;
                }
            }
        }
        //update flags in field count
        for (int i = 0; i < fieldTextCount.size(); i++) {
            fieldTextCount.at(i).setString(to_string(flagsInFields.at(i)));
            fieldTextCount.at(i).setPosition(((1.0/2.0)*(fieldTextPlus.at(0).getPosition().x+fieldTextPlus.at(0).getLocalBounds().width/2.0 + fieldTextMinus.at(0).getPosition().x+fieldTextMinus.at(0).getLocalBounds().width/2.0))-fieldTextCount.at(i).getLocalBounds().width/2.0, fieldText.at(i).getPosition().y);
        }
    }
}


GameState runMenus(sf::Music& backgroundMusic) {
    //variables for gameState Construction
    int numHumans, numComputers, numFields;
    vector<int> flagsInField;
    //defaults
    numHumans = numComputers = numFields = 1;
    flagsInField.push_back(21);

    int selectedInMain;
    bool notDefault = false;
    do {
        selectedInMain = mainMenu();
        if (selectedInMain == 2) {
            if (optionsMenu(backgroundMusic, numHumans, numComputers, numFields, flagsInField) != -1) {
                notDefault = true;
            }
            else {
                return GameState(-1);
            }
        }
        else if (selectedInMain == 3) {
            printRules();
        }
        else if (selectedInMain == -1) {
            return GameState(-1);
        }
    } while (selectedInMain != 1);
    if (notDefault) {
        return GameState(numHumans, numComputers, numFields, flagsInField);
    }
    else {
        return GameState();
    }
}

void printRules() {
    //read rules from text file
    fstream rules;
    rules.open("rules.txt", fstream::in );
    if (!rules.is_open()) {
        cerr << "Cannont Read Rules.txt" << endl;
        cerr << "Ensure that it exists and is not open in another program then try again.";
    }
    else {
        string currLine = "";
        while (!rules.eof()) {
            getline(rules, currLine);
            cout << currLine << endl;
        }
    }
    rules.close();
}