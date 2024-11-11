/*building.h*/

//
// A building in the Open Street Map.
// 
// Ian Evensen
// Northwestern University
// CS 211
// 

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <utility>

#include "node.h"
#include "nodes.h"

using namespace std;


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  // print
  // helper function to print id, name, address, nodes of a building

  void print(const Nodes& nodes) const;

  // getLocation
  // gets the center (lat, lon) of the building based
  // on the nodes that form the perimeter
  pair<double, double> getLocation(const Nodes& nodes) const;

  
};
