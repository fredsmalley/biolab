#include "search.h"
#include "util.h"

#include <iostream>
void pgp_search::set_patterns() {
  string pattern = "State:</t[d|h]><td>";
  patterns.push_back(pattern + "([[:alpha:] ]+)" + "</td>");
  //string pattern = "State:";
  //patterns.push_back(pattern);
}

void pgp_search::set_files() {
  string id_file_name = "./test/participants.tsv";
  ids = read_id(id_file_name);
  cout << "ids.size() = " << ids.size() << endl;
#if 1
  for(int i = 0; i < ids.size(); ++i)
    files.push_back("./test/PGP-participants/"+ids[i]+".html");
#endif
}

vector<string>& pgp_search::get_results() {
  for(int i = 0; i  < files.size(); ++i) {
    for(int j = 0; j  < patterns.size(); ++j) {
      smatch r;
      regex reg(patterns[j]);
      if(regex_search(html_to_string(files[i]), r, reg)) {
        //cout << "found pattern: " << patterns[j] << endl;
        results.push_back(r.str());
      }
      else {
        cout << files[i] << " does not have state" << endl;
        results.push_back("");
      }
    }
  }

  cout << "results size() = " << results.size() << endl;
  return results;
}


void pgp_search::write_results() {
  ofstream ofs;
  ofs.open ("id_state.txt", ofstream::out | ofstream::app);
  for(int i = 0; i < ids.size(); i++)
    ofs << ids[i] << "\t" << results[i] << endl;
  ofs.close();
}

void pgp_search::filter_results() {
  // remove tags
  for(int i = 0; i < results.size(); i++) {
    if(results[i].length() > 0) {
    results[i].erase(results[i].begin(), results[i].begin()+15);
    results[i].erase(results[i].end()-5, results[i].end());
    }
  }

  // abbreviations
  map<string, string> state_table = state_name_table();
#ifdef DEBUG
  for(map<string, string>::iterator it = state_table.begin(); it != state_table.end(); ++it) {
    cout << it->first << " " << it->second << endl;
  }
#endif
  for(int i = 0; i < results.size(); i++) {
    results[i] = state_table[results[i]];
  }
}

#ifdef TEST
void search_test() {
  pgp_search se;
  vector<string> &output = se.get_results();
  cout << "output size: " << output.size() << endl;

  se.filter_results();

  for(vector<string>::iterator it = output.begin();
      it != output.end(); ++it) {
    cout << *it << endl;
  }

  se.write_results();
}
#endif
