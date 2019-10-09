#pragma once
//
// Created by Chandler on 11/17/2018.
//

class Field {
private:
    int _flags; //num flags in the field
    bool _empty; //true if field is empty
public:
    void addFlags(int);     //adds flags to field
    void setFlags(int);     //sets the flags to the given value
    int getFlags() const;   //returns number of flags
    bool removeFlag(int);   //remove int flags, returns if sucessful, if not scucessful, does not modify num flags
    bool isEmpty() const;   //returns _empty
    Field();                //default to zero flags
    Field(int);             //set flags to int
};
