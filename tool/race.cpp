#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::pair;
using std::vector;

int main () {
	string inFileName;
	string listFileName = "../in/participantList.txt";
	string outFileName = "../out/id_race.tsv";
	string participantDirectory = "../in/PGP-participants/";

	fstream inFile;
	fstream listFile;
	string line;
	vector<pair<string, string> > vec;
	listFile.open(listFileName, fstream::in);
	if (listFile.is_open()) {
		while (getline(listFile, inFileName)) {
			inFile.open(participantDirectory+inFileName, fstream::in);
			if (inFile.is_open()) {
				while (getline(inFile, line)) {
					if (line.find(">Race<") != string::npos) {
						line = line.substr(line.find("<td>") + 4);
						line = line.substr(0, line.find("<"));
						//cout << line << endl;
						vec.push_back(pair<string, string>(inFileName.substr(0, 8), line));

						break;
					}
				}

				inFile.close();
			} else
				cout << "Unable to open " << participantDirectory << inFileName << endl;
		}

		listFile.close();
	} else
		cout << "Unable to open " << listFileName << "!" << endl;

	fstream outFile;
	outFile.open(outFileName, fstream::out | fstream::trunc);
	if (outFile.is_open()) {
		outFile << "ID\tRace" << endl;
		for (vector<pair<string, string> >::const_iterator itr = vec.begin();
				itr != vec.end(); itr++)
			outFile << itr->first << "\t" << itr->second << endl;
	} else
		cout << "Unable to open " << outFileName << endl;
}
