/*main.cpp*/

//
// Main program to read and output map's buildings, bus stops, nearest bus stops, 
// and bus stop predictions, based on user commands.
// 
#include <iostream>
#include <string>
#include "building.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "buildings.h"
#include "footway.h"
#include "footways.h"
#include "busstop.h"
#include "busstops.h"
#include "curl_util.h"

using namespace std;
using namespace tinyxml2;

int main() {
    string filename;
    XMLDocument xmldoc;
    Buildings buildings;

    // initialize CURL library
    CURL* curl = curl_easy_init();
    if (curl == nullptr) {
        cout << "**ERROR:" << endl;
        cout << "**ERROR: unable to initialize curl library" << endl;
        cout << "**ERROR:" << endl;
        return 0;
    }

    cout << "** NU open street map **" << endl;
    cout << endl;
    cout << "Enter map filename> " << endl;
    getline(cin, filename);

    // read contents into XML doc and error if unsuccessful
    if (!osmLoadMapFile(filename, xmldoc)) {
        cerr << "Error loading OSM file: " << filename << endl;
        return 0;
    }

    // if successful, create nodes object 
    Nodes nodes;
    // and extract node elements from XML doc
    nodes.readMapNodes(xmldoc);

    // output number of nodes
    cout << "# of nodes: " << nodes.getNumMapNodes() << endl;

    // read buldings from XML doc
    buildings.readMapBuildings(xmldoc);

    // output number of buildings
    cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;

    Footways footways;
    footways.readMapFootways(xmldoc);

    // read bus stops from CSV files
    BusStops busStops("bus-stops.txt");

    // output number of bus stops
    cout << "# of bus stops: " << busStops.getNumBusStops() << endl;

    // API Key
    string apiKey = "Xu26rzkSMgRp6cvFjFCPSUfkE";

    string name;
    while (true) {
        cout << endl;
        cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl;
        getline(cin, name);

        if (name == "$") {
            cout << endl;
            break; // exit loop if user enters "$"
        }
        else if (name == "*") {
            buildings.print();
        }
        else if (name == "@") {
            busStops.printAll();
        }
        else {
            buildings.findAndPrint(name, nodes, footways, busStops, curl, apiKey);
        }   
    }

    // close CURL library
    curl_easy_cleanup(curl);

    cout << "** Done **" << endl;

    return 0;
}
