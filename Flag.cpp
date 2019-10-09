//
// Created by Chandler on 11/18/2018.
//

#include <SFML/Graphics.hpp>

#include "Flag.h"

using namespace sf;

Flag::Flag() {
    Flag temp(0,0);
    this->setPosition(temp.getPosition().first, temp.getPosition().second);
    this->_bottom = temp.getBottom();
    this->_upright = temp.getUpright();
    Image flagImage;
    flagImage.create(50,50, Color::Transparent);
    for (int x = 0; x < 50; x++) {
        for (int y = 0; y < 50; y++) {
            if (2*y >= x && y < 25) {
                flagImage.setPixel(x, y, Color::Red);
            }
            else if (50-y >= .5*x && y >= 25) {
                flagImage.setPixel(x, y, Color::Red);
            }
        }
    }
    _flagTexture.loadFromImage(flagImage);
    _flag.setTexture(_flagTexture);
    _flag.setPosition(_upright.getPosition().x+_upright.getSize().x, _upright.getPosition().y+5);
    _initialPosition = {0, 0};
    _scale = {1.0,1.0};
}

Flag::Flag(float baseDown, float baseRight) {
    _bottom.setSize(Vector2f(55,7));
    _upright.setSize((Vector2f(7,175)));
    _bottom.setPosition(baseRight,baseDown-_bottom.getSize().y);
    _bottom.setFillColor(Color::Yellow);
    _upright.setPosition(_bottom.getPosition().x-_upright.getSize().x/2.0+_bottom.getSize().x/2.0,_bottom.getPosition().y-_upright.getSize().y);
    _upright.setFillColor(Color::Yellow);
    Image flagImage;
    flagImage.create(50,50, Color::Transparent);
    for (int x = 0; x < 50; x++) {
        for (int y = 0; y < 50; y++) {
            if (2*y >= x && y < 25) {
                flagImage.setPixel(x, y, Color::Red);
            }
            else if (50-y >= .5*x && y >= 25) {
                flagImage.setPixel(x, y, Color::Red);
            }
        }
    }
    _flagTexture.loadFromImage(flagImage);
    _flag.setTexture(_flagTexture);
    _flag.setPosition(_upright.getPosition().x+_upright.getSize().x, _upright.getPosition().y+5);
    _initialPosition = {baseDown, baseRight};
    _scale = {1.0,1.0};
}

RectangleShape Flag::getBottom() const {
    return _bottom;
}

RectangleShape Flag::getUpright() const {
    return _upright;
}

Sprite Flag::getFlag() const {
    return _flag;
}

void Flag::setScale(double scale) {
    this->setScale(scale, scale);
}

void Flag::setScale(double scaleX, double scaleY) {
    _bottom.setScale(scaleX, scaleY);
    _upright.setScale(scaleX, scaleY);
    _flag.setScale(scaleX, scaleY);
    _scale = {scaleX, scaleY};
    this->setPosition(_initialPosition.first, _initialPosition.second);
}

void Flag::setPosition(double posDown, double posRight) {
    _initialPosition = {posDown, posRight};
    _bottom.setPosition(posRight,posDown-_bottom.getSize().y*_scale.second);
    _upright.setPosition(_bottom.getPosition().x-(_upright.getSize().x*_scale.first)/2.0+(_bottom.getSize().x*_scale.first)/2.0,_bottom.getPosition().y-(_upright.getSize().y*_scale.second));
    _flag.setPosition(_upright.getPosition().x+(_upright.getSize().x*_scale.first), _upright.getPosition().y+5*_scale.second);
}

std::pair<double, double> Flag::getPosition() const {
    return _initialPosition;
}

Vector2f Flag::getPosition(bool) const {
    return Vector2f(_initialPosition.first, _initialPosition.second);
}