#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

#include "Map.h" 
 
Map::Map(){}

Map::~Map(void){}

int Map::setLocations(string fileName)
{
	string line;
	ifstream file;

	file.open(fileName);

	if(!file) //verify file could be opened
	{ 
		cerr << "Error: file could not be opened" << endl;
		return -1;
	}
	else
	{
		while (!file.eof())
		{
			getline (file, line);
			locations.push_back(line);
			//cout << line << endl;			
		}
		file.close();
		
		/*cout << "locations contains:" << endl;
		for (vector<string>::iterator it = locations.begin() ; it != locations.end(); ++it)
		{
			cout << ' ' << *it;
			cout << '\n';
		}*/
	}

	return 0;
}

int Map::setConnections(string fileName)
{
	string line;
	ifstream file;

	file.open(fileName);

	if(!file) //verify file could be opened
	{ 
		cerr << "Error: file could not be opened" << endl;
		return -1;
	}
	else
	{
		while (!file.eof())
		{
			getline (file, line);
			connections.push_back(line);
			//cout << line << endl;
		}
		file.close();

		/*cout << "connections contains:" << endl;
		for (vector<string>::iterator it = connections.begin() ; it != connections.end(); ++it)
			{
				cout << ' ' << *it;
				cout << '\n';
			}*/
	}

	return 0;
}

void Map::mapCities()
{
	string cityName, temp, neighbor, neighborCity, tempNeighbor;
	int locX, locY, numNeighbors, tempLoc; 
	vector<string>::iterator itLoc, itConn;
	vector<City>::iterator itCity;
	stringstream ssLoc, ssConn, ssTemp;

	//cout << "locations Building:" << endl;
	//Building vector of cities
	//initializing the cities using the conections file first
	for (itLoc = locations.begin() ; itLoc != locations.end(); ++itLoc)
	{
		temp = *itLoc;
		//cout << temp << " " ;
		
		if(temp.compare("END") == 0)
			break;
		
		ssLoc << (*itLoc);
		ssLoc >> cityName;
		ssLoc >> locX;
		ssLoc >> locY;
		ssLoc.clear();


		City city(cityName, locX, locY);
		cities.push_back(city);
		
		//cout << cityName << " " << locX << " " << locY << endl;
	}

	/*cout << "verify vector of cities created properly:" << endl;
	for (itCity = cities.begin() ; itCity != cities.end(); ++itCity)
	{
		(*itCity).toString();
	}*/

	//add adjacent cities to each city
	//iterate through the connections list to add each adjacent(neighbor) city
	for(itConn = connections.begin(); itConn != connections.end(); ++itConn)
	{
		temp = *itConn;
		//cout << temp << " " ;
		
		if(temp.compare("END") == 0)
			break;

		ssConn << (*itConn);
		ssConn >> cityName;
		ssConn >> numNeighbors;

		//find the city to add its neighbors
		for (itCity = cities.begin() ; itCity != cities.end(); ++itCity)
		{

			temp = (*itCity).getCityName();

			//if this is the city i am on, add its neighbors
			if(temp.compare(cityName) == 0) 
			{

				//add the neighbors the city has
				for (int i = 0; i < numNeighbors; ++i)
				{
					ssConn >> neighbor;
				
					//find the location of the neighbor
					for (itLoc = locations.begin() ; itLoc != locations.end(); ++itLoc)
					{
						temp = *itLoc;
						ssTemp << (*itLoc);
						ssTemp >> tempNeighbor;
						ssTemp >> tempLoc; //only used to clear buffer
						ssTemp >> tempLoc; //only way that I could make it work
						ssTemp.clear(); //clear stream of any input that is left

						//if this is the neighbor, add it to the city
						if(tempNeighbor.compare(neighbor) == 0)
						{			
							ssLoc << (*itLoc);
							ssLoc >> neighborCity;
							ssLoc >> locX;
							ssLoc >> locY;
							ssLoc.clear(); 

							(*itCity).addNeighbor(neighborCity, locX, locY); 
						}
					}
				}
			}
		}

		ssConn.clear(); //clear stream to capture next input string
	}	
}

void Map::printMap()
{
	cout << "verify neighbors of cities created properly:" << endl;
	for (vector<City>::iterator itCity = cities.begin() ; itCity != cities.end(); ++itCity)
	{
		(*itCity).printNeighbors();
		cout << endl;
	}
}

int Map::findPath(string start, string finish, string omit)
{
	startCity = start; endCity = finish; omitCity = omit;

	bool startExists = false, finishExists = false, omitExists = false;

	for(vector<City>::iterator it = cities.begin(); it != cities.end(); ++it)
	{
		if(it->getCityName() == start) //We got the initial city
		{
			it->setVisit(true);
			startExists = true;	
		}

		if(it->getCityName() == finish) //We got the ending city
		{
			finishExists = true;			
		}

		if(it->getCityName() == omit) // We got the omited city
		{
			it->setOmission(true);
			omitExists = true;
		}
		if(startExists && finishExists && omitExists)
			break;
	}

	{// Response if one of the cities is not in the vector
		if(!startExists)
		{
			cout << start << " is not found. Unable to proceed." << endl;
			exit(-1);
		}

		if(!finishExists)
		{
			cout << finish << " is not found. Unable to proceed." << endl;
			exit(-1);
		}

		if(!omitExists)
		{
			cout << omit << " is not found. We'll proceed without omissions" << endl;
		}

	}


	string currentCity = start;
	map<string, int> currentNeighbors;

	//A* Algorithm functionality
	while(currentCity != endCity)
	{
		City currCity = getCity(currentCity);	
		currCity.setVisit(true);
		updateVisited(currCity);

		//get the adjacent cities to the current city that we are on
		currentNeighbors = getNeighborCities(currentCity);

		//iterate through the adjacent cities and set up the heuristics map structure
		for(map<string, int>::iterator it = currentNeighbors.begin(); it != currentNeighbors.end(); ++it)
		{
			//adds neighbors to the heuristics map structure
			setupHeuristic(it->first, it->second, currentCity, endCity);
		}

		//if the heuristics map structure is empty
		//then we did not find a path
		if(heuristics.empty())
		{
			pathFound = false;
			return -1;
		}
		
		currentCity = getNextCity();
	}

	buildPath();
	pathFound = true;
	return 0;
}

void Map::showPath()
{
	list<string>::iterator it2;

	if(pathFound)
	{
		for(list<string>::iterator it = path.begin(); it != path.end(); it++)
		{
			it2 = it;
			it2++;
			if(it2 != path.end())
			{
				cout << *it << " -> " << *it2 << endl;
			}
		}
	}
	else
	{
		cout << "No path was found from: " << startCity << " to: " << endCity << endl; 
	}
}

int Map::heuristicDistance(City a, City b)
{
	return (int)sqrt(pow((a.getXCoordinate() - b.getXCoordinate()),2) + pow((a.getYCoordinate() - b.getYCoordinate()),2));
}

map<string, int> Map::getNeighborCities(string cityName)
{
	City city = getCity(cityName);

	if(city.getNeighbors().empty())
	{
		city.setDeadEnd(true);
		updateDeadEnd(city);
	}

	return city.getNeighbors();
}

void Map::setupHeuristic(string neighbor, int distFromPrevCity, string prevCity, string endCity)
{
	int sld, dt, heuristicDist;
	bool added = false;

	City thisNeighbor = getCity(neighbor);									 //get the neighbor city

	if(!thisNeighbor.getOmmission() && !thisNeighbor.getDeadEnd() && !thisNeighbor.getVisit())			 //verify that the city is not omitted or a deadend
	{
		City previousCity = getCity(prevCity);								 //get the previous city from neighbor

		City endingCity = getCity(endCity);									 //get the ending city

		sld = heuristicDistance(thisNeighbor, endingCity);					 //find the straigh line distance form the neighbor city to the ending city
		dt = previousCity.getDistanceTraveled() + distFromPrevCity;			 //find the distance that would be traveled if this path is shosen paths
		heuristicDist = sld + dt; //this is the distance used for our huristic
		
		for(map<string, int>::iterator it = heuristics.begin(); it != heuristics.end(); ++it)
		{
			if(it->first.compare(neighbor) == 0)
			{
				if(it->second > heuristicDist)
				{
					thisNeighbor.setPreviousCity(prevCity);								//let this neighbor know from which city we arrived to it
					updatePreviousCity(thisNeighbor);
		
					thisNeighbor.setDistanceTraveled(dt);								 //this is the total distances traveled through this path so far
					updateDistanceTraveled(thisNeighbor);

					added = true;
					heuristics.erase(neighbor);
					heuristics.insert(pair<string, int>(neighbor, heuristicDist));		 //add the city and the heuristic distance to the map structure
																						 //that is holding our cities to choose a from to form the path
					break;
				}				
			}
		}

		if(!added)
		{

			thisNeighbor.setPreviousCity(prevCity);								//let this neighbor know from which city we arrived to it
			updatePreviousCity(thisNeighbor);
			
			thisNeighbor.setDistanceTraveled(dt);								 //this is the total distances traveled through this path so far
			updateDistanceTraveled(thisNeighbor);

			
			heuristics.insert(pair<string, int>(neighbor, heuristicDist));		 //add the city and the heuristic distance to the map structure
																				 //that is holding our cities to choose a from to form the path

		/*cout<< "city: " << neighbor << " prev: " <<prevCity << "\tdt: " << previousCity.getDistanceTraveled()
			<< "\tcity dt: " << dt << "\tsld: " <<sld << "\theurDist: " << heuristicDist << "\n" << endl; */
		}	
	}
}

string Map::getNextCity()
{
	int min = heuristics.begin() -> second;
	string nextCity = heuristics.begin() -> first;

	for(map<string, int>::iterator it = heuristics.begin(); it != heuristics.end(); ++it)
	{
		if(it->second < min)
		{
			min = it->second;
			nextCity = it->first;
		}
	}
	
	if(!heuristics.empty())
	{
		heuristics.erase(nextCity);
		return nextCity;
	}
	else
		return "NOCITY";
}

City Map::getCity(string cityName)
{
	City city;

	for (vector<City>::iterator it = cities.begin(); it != cities.end(); ++it)
	{
		if(cityName.compare(it->getCityName()) == 0)
		{
			city = (*it);
			break;
		}
	}

	return city;
}

void Map::updateVisited(City updateCity)
{
	for (vector<City>::iterator it = cities.begin(); it != cities.end(); ++it)
	{
		if(updateCity.getCityName().compare(it->getCityName()) == 0)
		{
			it->setVisit(updateCity.getVisit());
			break;
		}
	}
}

void Map::updatePreviousCity(City updateCity)
{
	for (vector<City>::iterator it = cities.begin(); it != cities.end(); ++it)
	{
		if(updateCity.getCityName().compare(it->getCityName()) == 0)
		{
			it->setPreviousCity(updateCity.getPreviousCity());
			break;
		}
	}
}

void Map::updateDistanceTraveled(City updateCity)
{
	for (vector<City>::iterator it = cities.begin(); it != cities.end(); ++it)
	{
		if(updateCity.getCityName().compare(it->getCityName()) == 0)
		{
			it->setDistanceTraveled(updateCity.getDistanceTraveled());
			break;
		}
	}
}

void Map::updateDeadEnd(City updateCity)
{
	for (vector<City>::iterator it = cities.begin(); it != cities.end(); ++it)
	{
		if(updateCity.getCityName().compare(it->getCityName()) == 0)
		{
			it->setVisit(updateCity.getDeadEnd());
			break;
		}
	}
}

void Map::buildPath()
{
	City start, end, nextCity;
	
	end = getCity(endCity);
	start = getCity(startCity);
	nextCity = end;

	while(nextCity.getCityName() != start.getCityName())
	{
		path.push_front(nextCity.getCityName());
		nextCity = getCity(nextCity.getPreviousCity());
	}
	path.push_front(nextCity.getCityName());	
}