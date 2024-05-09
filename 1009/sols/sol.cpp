#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <locale>
#include <vector>
#include <map>

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
   v.clear();
   stringstream ss;
   string s;
   cin >> s;
   int solution_id, user_id, task_id, posted_time;
   double score;
   char c;
   while (cin >> s) {
     ss.clear();
     ss << s;
     ss >> solution_id >> c >> user_id >> c >> task_id >> c >> score >> c >> posted_time;
     if (score == 100.00)
       v.push_back(convertTimestampToDateTime(posted_time));
   }
   cout << v.size() << endl;
   for (auto s : v)
     cout << s << '\n';


}
