#include "City.h"

City::City()
{
	
}

City::City(string cityName, int x, int y)
{
	this->cityName = cityName;
	xCoordinate = x;
	yCoordinate = y;
	visited = false;
	omitted = false;
	deadEnd = false;
	distanceTraveled = 0;
}

City::~City(void)
{
}

void City::addNeighbor(string cityName, int x, int y)
{
	Neighbor.insert(pair<string, int>(cityName, calculateDistance(x,y)));
}

void City::setVisit(bool visited)
{
	this->visited = visited;
}

void City::setOmission(bool omitted)
{
	this->omitted = omitted;
}

void City::setDeadEnd(bool deadEnd)
{
	this->deadEnd = deadEnd;
}

void City::setDistanceTraveled(int distance)
{
	distanceTraveled = distance;
}

void City::setPreviousCity(string city)
{
	previousCity = city;
}

bool  City::getVisit(void)
{
	return visited;
}

bool  City::getOmmission(void)
{
	return omitted;
}

bool  City::getDeadEnd(void)
{
	return deadEnd;
}

string City::getPreviousCity(void)
{
	return previousCity;
}

int City::getDistanceTraveled(void)
{
	return distanceTraveled;
}

int  City::calculateDistance(int x, int y)
{
	return (int)sqrt(pow(xCoordinate - x,2) + pow(yCoordinate - y,2));
}

void City::toString(void)
{
	cout << cityName << " " << xCoordinate << " " << yCoordinate << endl;
}

string City::getCityName(void)
{
	return cityName;
}

void City::printNeighbors(void)
{
	cout << cityName << " neighbors: ";

	for(map<string,int>::iterator it = Neighbor.begin(); it != Neighbor.end(); ++it)
	{
		cout << it->first << " " << it->second << " ";
	}
}

int City::getXCoordinate(void)
{
	return xCoordinate;
}

int City::getYCoordinate(void)
{
	return yCoordinate;
}

map<string, int> City::getNeighbors()
{
	return Neighbor;
}