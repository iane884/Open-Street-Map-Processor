/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Ian Evensen
// Northwestern University
// CS 211
// 

#include "building.h"
#include "node.h"
#include "nodes.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}


// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
pair<double, double> Building::getLocation(const Nodes& nodes) const {
  
  double totalLat = 0.0;
  double totalLon = 0.0;
  double lat;
  double lon;
  bool isEntrance;

  for (long long nodeID : NodeIDs) {
    if (nodes.find(nodeID, lat, lon, isEntrance)) {
      totalLat += lat;
      totalLon += lon;
    }
  }
  double avgLat = totalLat / this->NodeIDs.size();
  double avgLon = totalLon / this->NodeIDs.size();

  return make_pair(avgLat, avgLon);
}

//
// prints name id, address, nodes of a buildings
void Building::print(const Nodes& nodes) const {
  auto location = this->getLocation(nodes);
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  cout << "# perimeter nodes: " << this->NodeIDs.size() << endl;
  cout << "Location: (" << location.first << ", " << location.second << ")" << endl;
}