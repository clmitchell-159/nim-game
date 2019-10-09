#pragma once
//
// Created by Chandler on 11/18/2018.
//

#include <SFML/Graphics.hpp>


//Automatically creates the flag elements so that I do not have to do math each time
class Flag{
private:
    sf::RectangleShape _bottom;
    sf::RectangleShape _upright;
    sf::Sprite _flag;
    sf::Texture _flagTexture;
    std::pair<double, double> _initialPosition; //down, right
    std::pair<double, double> _scale;           //x,y
public:
    Flag(); //default
    Flag(float baseDown, float baseRight); //constructor
    sf::RectangleShape getBottom() const;
    sf::RectangleShape getUpright() const;
    sf::Sprite getFlag() const;
    void setScale(double);                  //sets scale and adjusts position by a square amount
    void setScale(double, double);          //sets scale and adjusts position by an axial amount
    void setPosition(double, double);       //changes position
    std::pair<double, double> getPosition() const;
    sf::Vector2f getPosition(bool) const;
};