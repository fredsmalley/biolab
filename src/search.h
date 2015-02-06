#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <regex>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class pgp_search {
public:
  vector<string> patterns; // patterns to search in one file
  vector<string> files; // search files to find patterns in each file
  vector<string> results;
  vector<string> ids;

  pgp_search() { set_patterns(); set_files(); }
  void set_patterns();
  void set_files();
  vector<string>& get_results();
  void write_results();
  void filter_results();
};

#ifdef TEST
void search_test();
#endif

#endif
