#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

string html_to_string(string &filename);
vector<string> read_id(string &filename);
map<string, string> state_name_table();
#endif
