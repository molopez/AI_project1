#pragma once
#include <iostream>
#include <map>
#include <string>
#include <cmath>

using namespace std;

class City
{
/* This class possesses the properties of a city */

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
	void setDistanceTraveled(double);
	void setPreviousCity(string);
	bool getVisit(void);
	bool getOmmission(void);
	bool getDeadEnd(void);
	string getPreviousCity(void);
	double getDistanceTraveled(void);
	void toString(void);
	string getCityName(void);
	void printNeighbors(void);
	int getXCoordinate(void);
	int getYCoordinate(void);

	//this functions will return the 
	//map structure that contains the
	//adjacent(neighbor) cities
	map<string, double> getNeighbors();
	

private:
	//Properties
	string cityName, previousCity;
	int xCoordinate, yCoordinate;
	double distanceTraveled;
	bool visited, omitted, deadEnd;
	map<string, double> Neighbor;

	//Methods
	double calculateDistance(int,int);
};
