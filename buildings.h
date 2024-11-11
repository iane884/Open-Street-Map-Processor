/*buildings.h*/

//
// A collection of buildings in the Open Street Map
//

#pragma once
#include <vector>
#include "building.h"
#include "tinyxml2.h"
#include "nodes.h"
#include "footways.h"
#include "busstops.h"

using namespace std;
using namespace tinyxml2;

//
// Keeps track of all the buildings in the map
//
class Buildings {
    public:
        vector<Building> MapBuildings;
        // 
        // readMapBuildings
        //
        // Given an XML document, reads through the document and
        // stores all the buildings into the given vector
        //
        void readMapBuildings(XMLDocument& xmldoc);
        //
        // accessors / getters
        //
        int getNumMapBuildings() const;

        // print
        // helper function to print buildings in main
        void print() const;

        //
        // findAndPrint
        // finds buildings and prints them, along with their nearest bus stops
        void findAndPrint(const string& name, const Nodes& nodes, const Footways& footways, BusStops& busStops, CURL* curl, const string& apiKey) const;

        // getLocation
        // find building by name and return its location
        pair<double, double> getLocation(const string& name, const Nodes& nodes) const;

};
