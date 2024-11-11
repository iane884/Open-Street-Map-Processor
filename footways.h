/*footways.h*/

// A collection of footways in the open street map
// Ian Evensen
// Northwestern University
// CS 211
// 
#pragma once

#include <vector>
#include <string>
#include "footway.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Footways {
public:
    vector<Footway> MapFootways;

    // reads footways and stores them in given vector
    void readMapFootways(XMLDocument& xmldoc);

    // returns number of footways in map
    int getNumMapFootways() const;
};