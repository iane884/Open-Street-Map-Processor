/*buildings.cpp*/

//
// A collection of buildings in the Open Street Map
// implementation of functions defined in buildings.h

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include "buildings.h"
#include "building.h"
#include "tinyxml2.h"
#include "osm.h"
#include "footway.h"
#include "footways.h"
#include <curl/curl.h>
#include "curl_util.h"


using namespace std;
using namespace tinyxml2;



// add





// readMapBuildingsHelper
// helper function to push buildings into vector in readMapBuildings

void readMapBuildingsHelper(XMLElement* nd, Building& B) {
    while (nd != nullptr) {
        const XMLAttribute* ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);
        long long id = ndref->Int64Value();
        B.add(id);
        nd = nd->NextSiblingElement("nd");
    }
}

// readMapBuildings
// traverses XML document, starting from the first "way" element, 
// and pushes each building into the given vector

void Buildings::readMapBuildings(XMLDocument& xmldoc) {
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    // loop through each way element
    for (XMLElement* way = osm->FirstChildElement("way"); way != nullptr; way = way->NextSiblingElement("way")) {
        // check for a building obkect
        if (osmContainsKeyValue(way, "building", "university")) {
            string name = osmGetKeyValue(way, "name");
            string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " + osmGetKeyValue(way, "addr:street");

            // extract way's ID and convert to long long
            const char* wayIdAttr = way->Attribute("id");
            long long wayId = std::stoll(wayIdAttr);

            // create a building object
            Building B(wayId, name, streetAddr);

            XMLElement* nd = way->FirstChildElement("nd");
            readMapBuildingsHelper(nd, B);
            // add building to buildings vector
            MapBuildings.push_back(B);

        }
    }
}




// get NumMapBuildings
// returns the number of buildings in the map
int Buildings::getNumMapBuildings() const {
    return MapBuildings.size();
}

// print
// prints buildings 
void Buildings::print() const {
    for (const Building& b : MapBuildings) {
        cout << b.ID << ": " << b.Name << ", " << b.StreetAddress << endl;
    }
}

// footwaysintersect
// helper function to check if a footway intersects with a building
bool footwaysintersect(const Footway& footway, const Building& b) {
    // Check if any node ID in the footway is in the building's node IDs
    for (long long nodeID : footway.NodeIDs) {
        if (find(b.NodeIDs.begin(), b.NodeIDs.end(), nodeID) != b.NodeIDs.end()) {
            return true; // Intersection found
        }
    }
    return false; // No intersection
}


// footwayprinter
// helper function to print out all intersecting footways in findAndPrint
void footwayprinter(vector<long long> intersectingfootways) {
    for (long long id: intersectingfootways) {
            cout << " Footway " << id << endl;
        }
}
// findAndPrintHelper
// helper function to build vector of intersecting footways in findAndPrint
void findAndPrintHelper(vector<long long>& intersectingfootways, const Building& b, const Footways& footways) {
    for (const auto& footway: footways.MapFootways) {
        if (footwaysintersect(footway, b)) {
            intersectingfootways.push_back(footway.ID);
        }
    }
}
// findAndPrint
// finds buildings and prints them, along with their nearest bus stops
void Buildings::findAndPrint(const string& name, const Nodes& nodes, const Footways& footways, BusStops& busStops, CURL* curl, const string& apiKey) const {
    bool found = false;
    for (const Building& b : MapBuildings) {
        if (b.Name.find(name) != string::npos) {
            found = true;
            b.print(nodes); // print building
            pair<double, double> location = b.getLocation(nodes); // get location of building
            busStops.findClosestStops(location.first, location.second, curl, apiKey); // print nearest bus stops
        }
    }
    if (!found) { // if building doesn't exist
        cout << "No such building" << endl;
    }
}

// getLocation
// finds building by name and returns its location
pair<double, double> Buildings::getLocation(const string& name, const Nodes& nodes) const {
    for (const auto& building : MapBuildings) {
        if (building.Name.find(name) != string::npos) {
            return building.getLocation(nodes);
        }
    }
    return make_pair(-1.0, -1.0);
}




