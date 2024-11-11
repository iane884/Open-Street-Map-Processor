/*footway.h*/

// A footway in the open street map
// Ian Evensen
// Northwestern University
// CS 211
// 

#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// footway

// Defines a footway, consiting of an ID and a vector of NodeIDs

class Footway {
public:
    long long ID;
    vector<long long> NodeIDs;

    // constructor
    Footway(long long id);
        
    // add
    // adds the given nodeid to the end of the vector.
    //
    void add(long long nodeid);
};
