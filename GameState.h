#pragma once
//
// Created by Chandler on 11/17/2018.
//

#include <fstream>
#include <vector>

#include "Field.h"
#include "Player.h"

class GameState {
private:
    std::vector<Player> _players;               //holds all of the Players
    std::vector<Field> _fields;                 //holds all of the Fields
    std::vector<int> _flagsInFieldAtBeginning;  //holds ths starting value for the flags in each field
    int _initialFields;                         //initial number of fields
    int _currentPlayer;                          //tracks the active player
    int _looser;                                 //player num of the looser
    int _winner;                                 //player num of the winner
    bool _removeFlag(int, int);                  //removes int flage from the specified field
    void _addFlagToPlayer(int);                  //adds a flag to the specified player
    void _addFlagToPlayer(int, int);             //adds inf flags to the specified player
    int _status;                                //0 = select field, 1 = enter number of flags
public:
    int getActivePlayer() const;  //gets the active player
    int getNumPlayers() const;
    Player getPlayer(int) const;  //gets specified players
    int getNumFields() const;
    bool takeFlag(int, int);      //active player takes int flags from the specified field
    bool flagRemains();           //returns true if a field has a flag
    void assignLooser();          //sets looser to current player
    void assignWinner(int);          //sets winner to active player
    void intitializeGame();       //initialized the game
    GameState();
    GameState(int);
    GameState(int, int, int, std::vector<int>); //numH, numC, numF, <Flags>
    int getStatus() const;
    void setStatus(int);
    std::vector<int> getFlagArrangement() const;
    void setFields(const std::vector<Field>&);
    std::vector<Field> getFields() const;
    void incrementPlayer();
    void printWinner() const;
};
