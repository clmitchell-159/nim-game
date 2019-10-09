#pragma once
//
// Created by Chandler on 11/18/2018.
//

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameState.h"

bool isClicked(const sf::RectangleShape&, const sf::Vector2i&);

bool isClicked(const sf::Text&, const sf::Vector2i&);

bool isClicked(const sf::Sprite&, const sf::Vector2i&);

int mainMenu(); //1=play, 2=options

int optionsMenu(sf::Music&, int&, int&, int&, std::vector<int>&);

int fieldMenu(const int&, std::vector<int>&, sf::Font&);

void printRules();

GameState runMenus(sf::Music&);