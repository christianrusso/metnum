
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


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%i
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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%i
int resolver(std::ifstream &inputFile, std::ofstream &outputFile){
  //El return es para salvar el caso que termine el archivo en un newline
	string line1;
	getline (inputFile,line1);
	outputFile << line1 << endl;

  while(inputFile.eof())
	{
		getline (inputFile,line1);
		vector<string> param1 = split(line1);

		if(inputFile.eof()){
			return 1;
		}

		float l1x = atof(param1[0].c_str());
		float l1y =  atof(param1[1].c_str());
		spline.addPoint(l1x, l1y);
		if(l1x <= 125){
			outputFile << 125 << " " << spline(125) << endl;
			return 1;
		}else{
			outputFile << l1x << " " << l1y << endl;
		}
	}
	return 0;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%i


int main(int argc, char *argv[])
{
	ofstream outputFile;

	char* inFile = argv[1];
	ifstream inputFile(inFile);
	string archivo = "salida.tiro";

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
	resolver(inputFile,outputFile);

  return 0;
}


