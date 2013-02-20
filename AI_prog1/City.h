#pragma once
#include <iostream>
#include <map>
#include <string>
#include <cmath>

using namespace std;

class City
{
public:
	//Constructors
	City();
	City(string, int, int);
	~City(void);

	//Methods
	void addNeighbor(string, int, int);
	void setVisit(bool);
	void setOmission(bool);
	void setDeadEnd(bool deadEnd);
	void setDistanceTraveled(int);
	void setPreviousCity(string);
	bool getVisit(void);
	bool getOmmission(void);
	bool getDeadEnd(void);
	string getPreviousCity(void);
	int getDistanceTraveled(void);
	void toString(void);
	string getCityName(void);
	void printNeighbors(void);
	int getXCoordinate(void);
	int getYCoordinate(void);

	//this functions will return the 
	//map structure that contains the
	//adjacent(neighbor) cities
	map<string, int> getNeighbors();
	

private:
	//Properties
	string cityName, previousCity;
	int xCoordinate, yCoordinate, distanceTraveled;
	bool visited, omitted, deadEnd;
	map<string,int> Neighbor;

	//Methods
	int calculateDistance(int,int);
};
