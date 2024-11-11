/*footways.cpp*/

// A collection of footways in the open street map
// Ian Evensen
// Northwestern University
// CS 211
// 
#include "footways.h"
#include "osm.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace tinyxml2;


//// readMapFootwaysHelper
// helper function to push buildings into vector in readMapBuildings

void readMapFootwaysHelper(XMLElement* nd, Footway& footway) {
    while (nd != nullptr) {
        const char* ref = nd->Attribute("ref");
        long long nodeid = std::stoll(ref);
        footway.add(nodeid);
        nd = nd->NextSiblingElement("nd");
    }
}

void Footways::readMapFootways(XMLDocument& xmldoc) {
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    // loops through each way element:
    for (XMLElement* way = osm->FirstChildElement("way"); way != nullptr; way = way->NextSiblingElement("way")) {
        // check for footway object
        if (osmContainsKeyValue(way, "highway", "footway") || osmContainsKeyValue(way, "area:highway", "footway")) {
            const char* wayIdAttr = way->Attribute("id");
            long long wayId = std::stoll(wayIdAttr);

            Footway footway(wayId);

            XMLElement* nd = way->FirstChildElement("nd");
            readMapFootwaysHelper(nd, footway); // call helper function

            MapFootways.push_back(footway); // adds footway to footway vector
        }
    }
}

int Footways::getNumMapFootways() const {
    return MapFootways.size();
}