#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::fstream;
using std::string;

int main () {
	string inFileName = "../in/DiseaseSurvey/PGPTrait&DiseaseSurvey2012_Cancers-20150206200050.csv";
	string outFileName = "../out/id_cancers.tsv";

	fstream inFile;
	fstream outFile;
	string line;
	string id;
	string cancers;
	string sline;
	inFile.open(inFileName, fstream::in);
	if (inFile.is_open()) {
		outFile.open(outFileName, fstream::out | fstream::trunc);
		if (outFile.is_open()) {
			outFile << "ID\tCancer Related" << endl;	// add titles
			getline(inFile, line);				// skip titles
			while (getline(inFile, line)) {
				id = line.substr(0, line.find(","));		// save id
				line = line.substr(line.find(",") + 1);
				line = line.substr(line.find(",") + 1);		// skip timestamp
				line = line.substr(line.find(",") + 1);		// skip extra
				sline = line[0];
				if (sline.compare("\"") == 0) {
					line = line.substr(1);
					cancers = line.substr(0, line.find("\""));
				} else
					cancers = line.substr(0, line.find(","));
				outFile << id << "\t" << cancers << endl;
			}
			outFile.close();
		}
		inFile.close();
	} else
		cout << "Unable to open " << inFileName << "!" << endl;
}
