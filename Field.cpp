//
// Created by Chandler on 11/17/2018.
//

#include "Field.h"

void Field::addFlags(int toAdd) {
    _empty = false;
    _flags += toAdd;
}

void Field::setFlags(int toSet) {
    _empty = false;
    _flags = toSet;
}

int Field::getFlags() const {
    return _flags;
}


bool Field::removeFlag(int toRemove) {
    if (_flags >= toRemove) {
        _flags -= toRemove;
        if (_flags == 0) {
            _empty = true;
        }
        return true;
    }
    return false;
}

bool Field::isEmpty() const {
    return _empty;
}

Field::Field() {
    _flags = 0;
    _empty = true;
}

Field::Field(int flags) {
    if (flags == 0) {
        _flags = 0;
        _empty = true;
    }
    else {
        _flags = flags;
        _empty = false;
    }
}