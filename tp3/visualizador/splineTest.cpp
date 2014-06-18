
#include "spline.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <math.h>
#include <boost/algorithm/string.hpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <math.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

using namespace magnet::math;
using namespace std;

Spline spline;


void splinear(std::ofstream &outputFile){
	outputFile << "356 315 385 4" << endl;
	for (int i = 430; i > 110; i = i - 15)
  	{	
  		double y = spline(i);
  		if((i%5 == 0) && y > 0)
  		outputFile << i << " " << y << endl;	
  	}
}

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
	ifstream inputFile(inFile);
	string line1;
	getline (inputFile,line1);
	outputFile << line1 << endl;

	for (int i = 0; !(inputFile.eof()) ; ++i)
	{
		getline (inputFile,line1);
		if(!inputFile.eof()){

		
		vector<string> param1 = split(line1);


		float l1x = atof(param1[0].c_str());
		float l1y =  atof(param1[1].c_str());
		
		spline.addPoint(l1x, l1y);
	}

	}
	ifstream inputFile2(inFile);
	int lopuse = 0;
	for (int i = 0; !(inputFile2.eof()); ++i)
	{
		getline (inputFile2,line1);
		if(!inputFile2.eof()){
			vector<string> param1 = split(line1);

			float l1x = atof(param1[0].c_str());
			float l1y =  atof(param1[1].c_str());
			
			if(l1x < 125 && !lopuse){
				outputFile << 125 << " " << spline(125) << endl;
				lopuse = 1;
			}else{
				outputFile << l1x << " " << l1y << endl;
			}
		}
		

	}


	return 0;
}


/*void splinear(int x0, int y0, int x1, int y1, int xf, int yf, string  archivo ){
	ofstream outputFile;
	outputFile.open(archivo);
	Spline spline;

	spline.addPoint(x0, y0);
	spline.addPoint(x1,y1); 
	spline.addPoint(xf, yf);
	outputFile << "375 315 385 4" << endl;
	double dist = (x0 - (xf-50))/20; 
  	for (int i = x0; i > 50; i = i - dist)
  	{
  		double y = spline(i);
  		cout << i << " " << y << endl;	
  	}

}

*/


void splineate(){

	spline.addPoint(191.03, 360.10);
	spline.addPoint(174.03, 353.32);
	spline.addPoint(157.03,346.54 );
	spline.addPoint(140.03, 339.75 );
	spline.addPoint(123.03, 332.97);
	spline.addPoint(106.03, 326.19);
	double y = spline(125);
  	cout << y << endl;
}
int main(int argc, char *argv[])
{
	ofstream outputFile;

	char* inFile = argv[1];
	
	

	string archivo = "salida.tiro";
	
	
	//splineate();

  //ARCHIVOS DE ESTADISTICA:
	string nombre_final;
  std::vector<std::string> strs,strs2,strs3;
  boost::split(strs, inFile , boost::is_any_of("/"));
  string nombre_archivo = strs[strs.size()-1];
  boost::split(strs2, nombre_archivo , boost::is_any_of("."));
  string nuevo_nombre = strs2[0]+"_125.tiro";
  nombre_final = strs[0];
  for (int i = 1; i < strs.size()-1; ++i)
  {
  	nombre_final = nombre_final + "/"+strs[i];
  }
  nombre_final = nombre_final + "/"+nuevo_nombre;
  outputFile.open(nombre_final.c_str());
	resolver(inFile,outputFile);
}


