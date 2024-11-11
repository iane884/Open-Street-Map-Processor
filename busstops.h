/*busstops.h*/
//
// Bus Stops class to read all the bus stops from CSV file and store them
//



#pragma once

#include "busstop.h"
#include <vector>
#include <string>
#include <curl/curl.h>

using namespace std;

class BusStops {
public:
  vector<BusStop> stops;

  // constructor
  BusStops(const string& filename);

  // readFromFile
  // reads bus stops from csv file
  void readFromFile(const string& filename);

  // accessors/getters
  int getNumBusStops() const;

  // printAll()
  // prints all bus stops
  void printAll() const;

  // findAndPrint()
  // finds bus stop by name and prints it
  void findAndPrint(const string& name) const;

  
  // findClosestStops()
  // finds closest southbound/northbound stops to a given bus stop 
  // and also returns the bus stops' predictions
  void findClosestStops(double lat, double lon, CURL* curl, const string& apiKey) const;

};
