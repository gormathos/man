#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <locale>
#include <vector>
#include <map>
#include <set>

using namespace std;

time_t convertDateToTimestamp(const string& date) {
    tm tm = {};
    istringstream ss(date);
    ss >> get_time(&tm, "%d.%m.%Y %H:%M:%S");
    return timegm(&tm); // - 3 * 3600;
}

string convertTimestampToDateTime(time_t timestamp) {
//    timestamp += 3 * 3600;
    tm* tm = gmtime(&timestamp); // Конвертуємо мітку часу в UTC-час
    ostringstream oss;
    oss << setfill('0')
        << setw(2) << tm->tm_mday << "."
        << setw(2) << (tm->tm_mon + 1) << "." // tm_mon починається з 0
        << setw(4) << (tm->tm_year + 1900) << " "
        << setw(2) << tm->tm_hour << ":"
        << setw(2) << tm->tm_min << ":"
        << setw(2) << tm->tm_sec;
    return oss.str();
}

vector<string> v;

int main() {
   map<int, string> lang;
   lang[1] = "Pascal";
   lang[2] = "Python";
   lang[3] = "C++";
   lang[4] = "Java";
   lang[5] = "C#";
   map<int, pair<int,pair<int,int>>> lang_stat;
   map<int, set<int>> user_stat;
   v.clear();
   stringstream ss;
   string s;
   cin >> s;
   int solution_id, user_id, task_id, lang_id;
   double score;
   char c;
   while (cin >> s) {
     ss.clear();
     ss << s;
     ss >> solution_id >> c >> user_id >> c >> task_id >> c >> lang_id >> c >> score;
     lang_stat[lang_id].first += 1;
     user_stat[lang_id].insert(user_id);
     if (score == 100.00)
       lang_stat[lang_id].second.first += 1;
     if (score == 0.00)
       lang_stat[lang_id].second.second += 1;
   }
   
   for (auto s : lang_stat) {
     cout << lang[s.first] << ": ";
     cout << user_stat[s.first].size() << " ";
     cout << s.second.first << " " << s.second.second.first << " " << s.second.second.second; 
     cout << '\n';

   }
  

}
