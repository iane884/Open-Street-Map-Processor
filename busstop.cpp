/*busstop.cpp*/
// A bus stop in the open street map

// Ian Evensen
// Northwestern University
// CS 211
//

#include "busstop.h"
#include <curl/curl.h>
#include "curl_util.h"
#include "json.hpp"
#include <iostream>

using namespace std;
using json = nlohmann::json;


// constructor

BusStop::BusStop(int stopID, int route, string stopName, 
  string direction, string location, double lat, double lon)
  : StopID(stopID), Route(route), StopName(stopName), 
  Direction(direction), Location(location), Lat(lat), Lon(lon) 
  {}

// print()
// prints bus stop
void BusStop::print() const {
  cout << this->StopID << ": " << "bus " << this->Route << ", " 
  << this->StopName << ", " << this->Direction << ", " << this->Location 
  << ", location (" << this->Lat << ", " << this->Lon << ")" << endl;
}

// makeURL
// helper function to build string-based URL with API key
string makeURL(const string& apiKey, int stopID, int route) {
  string url = "http://www.ctabustracker.com/bustime/api/v2/getpredictions";

  url += "?key=" + apiKey;
  url += "&stpid=" + to_string(stopID);
  url += "&rt=" + to_string(route);
  url += "&format=json";

  return url;
}

// getPredictions
// extracts and prints predictions for bus stop

void BusStop::getPredictions(CURL* curl, const string& apiKey) const {
  
  string url = makeURL(apiKey, this->StopID, this->Route); // build URL
  string response;

  if (callWebServer(curl, url, response)) { // call CTA API

    auto jsondata = json::parse(response); // parse data, build JSON object
    auto bus_response = jsondata["bustime-response"];

    auto predictions = bus_response["prd"];
    if (predictions.empty()) {
      cout << "  <<no predictions available>>" << endl;
      return;
    }
    for (auto& M : predictions) { // for each prediction in the list:
      try {
        cout << "  vehicle #" << stoi( M["vid"].get_ref<string&>())
        << " on route " << stoi( M["rt"].get_ref<string&>())
        << " travelling " << M["rtdir"].get_ref<string&>()
        << " to arrive in " << stoi( M["prdctdn"].get_ref<string&>())
        << " mins" << endl;
      }
      catch (const exception& e) { // exception handling
        cout << "  error" << endl;
        cout << "  malformed CTA response, prediction unavailable"
        << "  (error: " << e.what() << ")" << endl;
      }
    }
  }

  else { // if callWebServer fails
    cout << "  <<bus predictions unavailable, call failed>>" << endl;
  }
}