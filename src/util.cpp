#include "util.h"

string html_to_string(string &filename) {
  ostringstream ostr(ostringstream::ate) ; // *** binary
  ifstream in_file;
  in_file.exceptions(ifstream::failbit | ifstream::badbit);
  try {
    in_file.open(filename);

    string line;
    while(getline(in_file, line)) 
      ostr << line << "\n" ;

    in_file.close();
  }
  catch(ifstream::failure e) {
    //cerr << "Exception opening/reading/closing file: " << filename << " " << e.what() << endl;
  }
  return ostr.str();
}

vector<string> read_id(string &filename) {
  vector<string> ids;
  ostringstream ostr(ostringstream::ate) ; // *** binary
  ifstream in_file;
  in_file.exceptions(ifstream::failbit | ifstream::badbit);
  try {
    in_file.open(filename);

    string line;
    while(getline(in_file, line)) 
      ids.push_back(line);

    in_file.close();
  }
  catch(ifstream::failure e) {
    //cerr << "Exception opening/reading/closing file: " << filename << " " << e.what() << endl;
  }

  return ids;
}

map<string, string> state_name_table() {
  map<string, string> states;
  ostringstream ostr(ostringstream::ate) ; // *** binary
  ifstream in_file;
  in_file.exceptions(ifstream::failbit | ifstream::badbit);
  try {
    in_file.open("./tool/states");

    string line;
    while(getline(in_file, line, ':')) {
      string line2;
      getline(in_file, line2);
      states.insert(make_pair(line, line2));
    }

    in_file.close();
  }
  catch(ifstream::failure e) {
    //cerr << "Exception opening/reading/closing file: " << filename << " " << e.what() << endl;
  }

  return states;
}
