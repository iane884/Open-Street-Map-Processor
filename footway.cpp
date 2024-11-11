/*footway.cpp*/

// A footway in the open street map
// Ian Evensen
// Northwestern University
// CS 211
// 

#include "footway.h"

using namespace std;

Footway::Footway(long long id)
    : ID(id) {}

void Footway::add(long long nodeid) {
    this->NodeIDs.push_back(nodeid);
}