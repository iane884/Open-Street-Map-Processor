/*busstops.cpp*/
//
// Bus Stops class to read all the bus stops from CSV file and store them
//
// Ian Evensen
// Northwestern University 
// CS 211
//
#include "busstops.h"
#include "busstop.h"
#include "dist.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

// readFromFile
// reads bus stops from csv file
void BusStops::readFromFile(const string& filename) {
  ifstream file(filename);
  string line;
  
  while (getline(file, line)) {
    stringstream ss(line);
    int stopID;
    int route;

    string stopIDStr;
    string routeStr;
    string stopName;
    string direction;
    string location;
    string latStr;
    string lonStr;

    getline(ss, stopIDStr, ',');
    getline(ss, routeStr, ',');
    getline(ss, stopName, ',');
    getline(ss, direction, ',');
    getline(ss, location, ',');
    getline(ss, latStr, ',');
    getline(ss, lonStr);

    stopID = stoi(stopIDStr);
    route = stoi(routeStr);
    double lat = stod(latStr);
    double lon = stod(lonStr);

    BusStop stop(stopID, route, stopName, direction, location, lat, lon);
    stops.push_back(stop);
  }
}

// constructor
BusStops::BusStops(const string& filename) {
  readFromFile(filename);
}

// get number of bus stops
int BusStops::getNumBusStops() const {
  return stops.size();
}

// print all bus stops, sorted by stop ID
void BusStops::printAll() const {
  vector<BusStop> sortedStops = stops;

  // sort by stop ID
  sort(sortedStops.begin(), sortedStops.end(), 
  [](const BusStop& a, const BusStop& b) {
    return a.StopID < b.StopID;
  });

  // print stops in sorted order
  for (const auto& stop : sortedStops) {
    stop.print();
  }
}

// find and print bus stop by name
void BusStops::findAndPrint(const string& name) const {
  bool found = false;

  for (const auto& stop : stops) {
    if (stop.StopName.find(name) != string::npos) {
      found = true;
      stop.print();
    }
  }

  if (!found) {
    cout << "No such bus stop" << endl;
  }
}

// findClosestStops()
// finds closest southbound/northbound stops to a given bus stop 
// and also returns the bus stops' predictions
void BusStops::findClosestStops(double lat, double lon, CURL* curl, const string& apiKey) const {
  const BusStop* closestSouthbound = nullptr;
  const BusStop* closestNorthbound = nullptr;
  double minDistSouth = numeric_limits<double>::max();
  double minDistNorth = numeric_limits<double>::max();

  for (const auto& stop : stops) {
     double distance = distBetween2Points(lat, lon, stop.Lat, stop.Lon);

    if (stop.Direction == "Southbound" && distance < minDistSouth) {
      minDistSouth = distance;
      closestSouthbound = &stop; // identify closest southbound stop
    }
    else if (stop.Direction == "Northbound" && distance < minDistNorth) {
      minDistNorth = distance;
      closestNorthbound = &stop; // identify closest northbound stop
    }
  }

  if (closestSouthbound != nullptr) {
    cout << "Closest southbound bus stop:" << endl;
    cout << "  " << closestSouthbound->StopID << ": " << closestSouthbound->StopName
    << ", bus #" << closestSouthbound->Route << ", " << closestSouthbound->Location
    << ", " << minDistSouth << " miles" << endl;
    closestSouthbound->getPredictions(curl, apiKey); // get and print predicitons for bus stop
  }

  if (closestNorthbound != nullptr) {
    cout << "Closest northbound bus stop:" << endl;
    cout << "  " << closestNorthbound->StopID << ": " << closestNorthbound->StopName
    << ", bus #" << closestNorthbound->Route << ", " << closestNorthbound->Location
    <<  ", " << minDistNorth << " miles" << endl;
    closestNorthbound->getPredictions(curl, apiKey); // get and print predicitons for bus stop
  }

}
