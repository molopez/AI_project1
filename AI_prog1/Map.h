#pragma once
#include <string>
#include <vector>
#include <list>
using namespace std;

#include "City.h"

class Map
{
private:
	vector<string> connections;
	vector<string> locations;
	vector<City> cities;
	list<string> path;
	map<string, int> heuristics;
	string startCity, endCity, omitCity;
	bool pathFound;
	
public: 
	Map();
	~Map();

	//Retrieve the locations file
	//takes the path to where the file is located
	//returns 0 if file is found
	//returns -1 if file is not found
	int setLocations( string );

	//Retrieves the connections file
	//takes the path to the file as an argument
	//returns 0 if file is found
	// return -1 if file is not found
	int setConnections( string );

	//Creates the map of the cities
	void mapCities();

	//Finds the shortest path from one city to another
	//takes as arguments:
	//starting city, ending city, city to omit
	int findPath(string, string, string);
	
	//Display the shortest path from one city to another
	//if one is found
	void showPath();	

	void printMap();

private:
	//computes the straight line distance from
	//a city to the ending city
	int heuristicDistance(City, City);

	//pass in the name of the city
	//and returns its neighbors
	map<string, int> getNeighborCities(string);

	//for each adjacent(neighbor) city
	//pass the city, distance from current city, the current city and the ending city
	//Method will calculate the SLD + DT and add the 
	//city and the heuristic distance to the 
	//heuristics map structure
	void setupHeuristic(string, int, string, string);

	//finds the next city that would give us the
	//next shortest distance to travel through
	string getNextCity();

	//returns the City object you are looking for
	City getCity(string);
	
	//builds the list with the cities in the path
	//that we are looking for
	void buildPath();

	void updateVisited(City);

	void updatePreviousCity(City);

	void updateDistanceTraveled(City);

	void updateDeadEnd(City);
};