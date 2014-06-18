
#include "spline.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <math.h>
#include <boost/algorithm/string.hpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace magnet::math;
using namespace std;

Spline spline;


vector<string> split(string &line) {
	vector<string> res;
	char* strToken;

	strToken = strtok ((char*) line.c_str()," ");
  	while (strToken != NULL)
	{
		if (strToken != NULL) {
			string s(strToken);
			res.push_back(s);
		}
		strToken = strtok (NULL, " ");
	}
	return res;
}


int resolver(char* inFile, std::ofstream &outputFile){
  //El return es para salvar el caso que termine el archivo en un newline
	string line1;
	ifstream inputFile(inFile);
	getline (inputFile,line1);
	outputFile << line1 << endl;

	while(!(inputFile.eof()))
	{
		getline (inputFile,line1);
		if(!inputFile.eof()){
      vector<string> param1 = split(line1);
      float l1x = atof(param1[0].c_str());
      float l1y =  atof(param1[1].c_str());
      cout << "l1x: " << l1x << endl;
      cout << "l1y: " << l1y << endl;
      spline.addPoint(l1x, l1y);
	  }
	}
  spline.setLowBC(Spline::FIXED_2ND_DERIV_BC, 0);
  spline.setHighBC(Spline::FIXED_2ND_DERIV_BC, 0);
  for (int i = 122; i <= 143; i++) {
    cout << "spline de " << i <<": " << spline(i) << endl;
  }
	ifstream inputFile2(inFile);
	bool lopuse = false;
	while(!(inputFile2.eof()))
	{
		getline (inputFile2,line1);
		if(!inputFile2.eof()){
			vector<string> param1 = split(line1);

			float l1x = atof(param1[0].c_str());
			float l1y = atof(param1[1].c_str());

			if(l1x <= 125 && !lopuse){
				cout << 125 << " " << spline(125) << endl;
				outputFile << 125 << " " << spline(125) << endl;
				lopuse = true;
			}else{
				outputFile << l1x << " " << l1y << endl;
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char* inFile = argv[1];
	char* outFile = argv[2];
	ofstream outputFile(outFile);
	ifstream inputFile(inFile);

	return resolver(inFile,outputFile);
}


