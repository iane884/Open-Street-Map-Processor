# Northwestern University Bus Stop Finder: Real-Time Arrival Tracking and Location Mapping

## Project Overview
This project extends prior work with Northwestern University’s Evanston campus OpenStreetMap by integrating real-time data on nearby CTA bus stops. The program locates the closest northbound and southbound bus stops relative to a given building and queries the CTA bus tracker API to display upcoming arrival predictions.

## Steps Completed

### Setup and Project Structure
**Objective:** Organize the project files and make necessary configurations.  
**Implementation:**
- Created a directory for the project and set permissions.
- Configured the makefile to compile additional files for distance calculations and CURL library functions for API requests.

### Building Location Calculation
**Objective:** Compute the central location (latitude, longitude) of each building based on its perimeter nodes.  
**Implementation:**
- Added a `getLocation` method to the `Building` class, calculating the building’s center by averaging the coordinates of its nodes.  
**Outcome:** Successfully calculated and displayed building locations.

### Loading CTA Bus Stops Data
**Objective:** Import and model CTA bus stop data.  
**Implementation:**
- Created `BusStop` and `BusStops` classes to handle bus stop information from a CSV file, modeling each stop’s ID, route, name, direction, and coordinates.  
**Outcome:** Successfully loaded bus stop data and stored it in organized objects.

### Listing All Bus Stops
**Objective:** Provide a list of all bus stops when the user enters “@” as the building name.  
**Implementation:**
- Added a `print` method to the `BusStops` class, sorting stops by Stop ID and displaying them to the user.  
**Outcome:** Successfully displayed all bus stops when requested.

### Finding Closest Bus Stops
**Objective:** Determine the nearest northbound and southbound bus stops to a specified building.  
**Implementation:**
- Added functionality in the `BusStops` class to find and return the closest stops based on distance calculations between each building and bus stop.  
**Outcome:** Successfully identified and displayed the closest northbound and southbound stops.

### Bus Arrival Predictions
**Objective:** Query the CTA Bus Tracker API to get real-time arrival predictions for the nearest stops.  
**Implementation:**
- Used CURL for online requests and parsed the JSON response using a JSON library. Displayed the vehicle ID, route, direction, and arrival time.  
**Outcome:** Displayed bus arrival times, with appropriate messaging for unavailable predictions.

### Exception Handling for Data Parsing
**Objective:** Implement robust exception handling for JSON parsing to manage potential data errors.  
**Implementation:**
- Used a try-catch block to handle missing or malformed data, ensuring that the program gracefully outputs error messages without crashing.  
**Outcome:** The program handles unexpected data issues gracefully, displaying error messages when necessary.
