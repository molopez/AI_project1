#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Map.h"
using namespace std;

int main ( )
{
	string fileName, line;
	Map map;

	cout << "Please Enter a LOCATIONS file name" << endl;
	getline(cin, fileName);
	map.setLocations(fileName);

	cout << "Please Enter a CONNECTIONS file name" << endl;
	getline(cin, fileName);
	map.setConnections(fileName);

	map.mapCities();

	//map.printMap();

	string start, finish, omit;
	
	cout << "Enter starting city: " ;
	cin >> start;
	transform(start.begin(), start.end(),start.begin(), ::toupper);

	cout << "Enter ending city: ";
	cin >> finish;
	transform(finish.begin(), finish.end(),finish.begin(), ::toupper);

	cout << "Enter city to omit or type none if you do not wish to ommit a city: ";
	cin >> omit;
	if(omit.compare("none") == 0)
		omit = "";			
	else
		transform(omit.begin(), omit.end(),omit.begin(), ::toupper);


	//cout << start << " " << finish << " " << omit << endl;

	map.findPath(start, finish, omit);

	map.showPath();
	

	getchar();
	getchar();
	return 0;
}