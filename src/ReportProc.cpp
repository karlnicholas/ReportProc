/*
 * ReportProcessor.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: karln
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <stdlib.h>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

#include "PoliceReport.h"

using namespace std;

// functions
vector<PoliceReport*> getPoliceReports();

bool sortComparePR(PoliceReport * l, PoliceReport * r) {
	return l->getIncidentNumber() < r->getIncidentNumber();
}

int main() {

    srand ( unsigned ( std::time(0) ) );

	vector<PoliceReport*> policeReports = getPoliceReports();

/*
	random_shuffle(policeReports.begin(), policeReports.end());
	long indicentNumbers[10];
	for (int i = 0; i < 10; i++) {
		indicentNumbers[i] = (*policeReports[i]).getIncidentNumber();
	}
*/
	long indicentNumbers[10];
	int length = policeReports.end() - policeReports.begin();
	for (int i = 0; i < 10; i++) {
		int offset = rand() % length;
		indicentNumbers[i] = (*policeReports[offset]).getIncidentNumber();
	}

	clock_t start = clock();
	sort( policeReports.begin(), policeReports.end(), sortComparePR);
	clock_t end = clock();
	double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;

	cout << "Time was " << time << endl;
	for (int i = 0; i < 10; i++) {
		long incidentNumber = indicentNumbers[i];

		clock_t start = clock();
		PoliceReport tRep(incidentNumber);

		vector<PoliceReport*>::iterator vit = lower_bound(policeReports.begin(), policeReports.end(), &tRep, sortComparePR);

		clock_t end = clock();
		double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
		cout << "Time for find was " << time << endl;
		cout << "Report = " << **vit << endl;

	}

}

vector<PoliceReport*> getPoliceReports() {
	string line;
	ifstream myfile("SFPD_Incidents_TheftLarceny.csv");
	int lineCount = 0;
	string temp[8];
	vector<PoliceReport*> policeReports;

	if (myfile.is_open()) {
		while (std::getline(myfile, line)) {
			int i = 0;
			istringstream iss(line);
			while (getline(iss, temp[i], ',')) {
				i++;
			}
			PoliceReport* report = new PoliceReport(atol(temp[0].c_str()), temp[1], temp[2],
					atoi(temp[3].c_str()), temp[4], temp[5], temp[6], temp[7]);
			policeReports.push_back(report);
			lineCount++;
		}
		myfile.close();
	}

	else
		cout << "Unable to open file";

	return policeReports;
}

