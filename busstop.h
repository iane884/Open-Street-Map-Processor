/*busstop.h*/
// A bus stop in the open street map


#pragma once

#include <string>
#include <curl/curl.h>

using namespace std;

class BusStop{
public:
  int StopID;
  int Route;
  string StopName;
  string Direction;
  string Location;
  double Lat;
  double Lon;

  // constructor
  BusStop(int stopID, int route, string stopName, 
  string direction, string location, double lat, double lon);

  // print bus stop
  void print() const;

  // getPredictions
  // get predictions for a bus stop
  void getPredictions(CURL* curl, const string& apiKey) const;

};
