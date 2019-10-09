//
// Created by Chandler on 11/17/2018.
//

#include "GameState.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "Field.h"
#include "Player.h"


using namespace std;

bool GameState::_removeFlag(int field, int toReomve) {
    return _fields.at(field).removeFlag(toReomve);
}

void GameState::_addFlagToPlayer(int player) {
    _players.at(player).flagsCollected++;
}

void GameState::_addFlagToPlayer(int player, int toAdd) {
    _players.at(player).flagsCollected += toAdd;
}

int GameState::getActivePlayer() const {
    return _currentPlayer;
}

int GameState::getNumPlayers() const {
    return _players.size();
}

Player GameState::getPlayer(int location) const {
    return _players.at(location);
}

int GameState::getNumFields() const {
    return _initialFields;
}

bool GameState::takeFlag(int field, int toTake) {
    if (_removeFlag(field, toTake)) {
        _addFlagToPlayer(getActivePlayer(), toTake);
        return true;
    }
    return false;
}

bool GameState::flagRemains() {
    for (Field a : _fields) {
        if (!a.isEmpty()) {
            return true;
        }
    }
    return false;
}

void GameState::assignLooser() {
    _looser = getActivePlayer();
    _players.at(_currentPlayer).hasLost = true;
    cout << _players.at(_looser).name << " has lost." << endl;
}

void GameState::assignWinner(int number) {
    _winner = number;
}

void GameState::intitializeGame() {
    for (auto& a : _players) {
        a.flagsCollected = 0;
    }
    vector<Field> newFields;
    newFields.resize(_initialFields);
    for (int i = 0; i < _initialFields; i++) {
        newFields.at(i).setFlags(_flagsInFieldAtBeginning.at(i));
    }
    _fields = newFields;
    for (int i = 0; i < _players.size(); i++) {
        if (!_players.at(i).hasLost){
            _currentPlayer = i;
            break;
        }
    }
    _looser = _winner = -1;
    _status = 0;
    return;
}

GameState::GameState() {
    //Play default game vs. computer
    _initialFields = 1;
    _flagsInFieldAtBeginning.push_back(21);

    //set up human players
    Player human;
    human.isComp = false;
    human.hasLost = false;
    human.flagsCollected = 0;
    cout << "Enter Your Name: ";
    getline(cin, human.name);

    //set up computers
    Player computer;
    computer.isComp = true;
    computer.hasLost = false;
    computer.flagsCollected = 0;
    computer.name = "Computer";

    //add players to vector
    _players.push_back(human);
    _players.push_back(computer);

    //housekeeping
    _currentPlayer = 0;
    _winner = _looser = -1;
}

GameState::GameState(int numHumans, int numComputers, int numFields, vector<int> flagsInField) {
    //set up fields
    _initialFields = numFields;
    _flagsInFieldAtBeginning.resize(_initialFields, 0);
    for (int i = 0; i < _flagsInFieldAtBeginning.size(); i++) {
        _flagsInFieldAtBeginning.at(i) = flagsInField.at(i);
    }

    //set up and add players
    _players.clear();
    Player human;
    human.isComp = false;
    human.hasLost = false;
    human.flagsCollected = 0;
    for (int i = 0; i < numHumans; i++) {
        cout << "Player " << i+1 << " Enter Your Name: ";
        getline(cin, human.name);
        _players.push_back(human);
    }

    //set up and add computers
    Player computer;
    computer.isComp = true;
    computer.hasLost = false;
    computer.flagsCollected = 0;
    for (int i = 0; i < numComputers; i++) {
        computer.name = "Comp " + to_string(i);
        _players.push_back(computer);
    }

    //housekeeping
    _currentPlayer = 0;
    _winner = _looser = -1;
}

void GameState::setStatus(int state) {
    _status = state;
}

int GameState::getStatus() const {
    return _status;
}

vector<int> GameState::getFlagArrangement() const {
    return _flagsInFieldAtBeginning;
}

void GameState::setFields(const std::vector<Field>& newFields) {
    _fields = newFields;
}

vector<Field> GameState::getFields() const {
    return _fields;
}

void GameState::incrementPlayer() {
    do {
        _currentPlayer++;
        if (_currentPlayer > _players.size() - 1) {
            _currentPlayer = 0;
        }
    } while(_players.at(_currentPlayer).hasLost);
}

void GameState::printWinner() const {
    if (_winner == -1) {
        cout << "Exiting Game." << endl;
    }
    else {
        cout << "Congratuations " << _players.at(_winner).name << " you are the winner!" << endl;
    }
}

GameState::GameState(int quit) {
    _currentPlayer = _winner = -1;
}