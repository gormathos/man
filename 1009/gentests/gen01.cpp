#include "testlib.h"
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


int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1);
    string d = opt<string>(2);
    string t = opt<string>(3);
    time_t posted_time = convertDateToTimestamp(d + " " + t);
    int solution_id = rnd.next(100000, 200000);
    double p;
    map<int,int> tests_amount;
    for (int i = 2001; i <= 2010; i++)
      tests_amount[i] = rnd.next(20, 50);

    cout << "solution_id;user_id;task_id;score;posted_time\n";
    for (int i = 0; i < n; i++) {
      solution_id += i;
      int user_id = rnd.next(1001, 1100);
      int task_id = rnd.next(2001, 2010);
      posted_time += rnd.next(0, 6000);
      int tests = rnd.next(0, tests_amount[task_id]);
      int rand = rnd.next(0, 3);
      p = 100.00 * tests / tests_amount[task_id];
      if (rand <= 1) 
         p = 100.00;
      cout << solution_id << ";" << user_id << ";" << task_id << ";";
      cout << fixed << setprecision(2) << p;
      cout << ";" << posted_time << endl;
   }
}
