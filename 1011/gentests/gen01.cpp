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

struct Data {
  int solution_id;
  int task_id;
  int user_id;
  int score;
};

vector<Data> v;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int rand = opt<int>(1);
    int first_user_id = 1001;
    int last_user_id = 1002;
    int first_task_id = 2001;
    int last_task_id = 2003;
    int first_solution_id = rnd.next(100000, 200000);
    int last_solution_id = first_solution_id + 100;
    int attempts = rnd.next(3, 3); 

    int solution_id = rnd.next(100000, 200000);
    double p;
    map<int,int> tests_amount;
    for (int i = first_task_id; i <= last_task_id; i++)
      tests_amount[i] = rnd.next(20, 50);

    map<int, vector<pair<int, int>>> users_sols; // user_id -> {task_id, score}
    for (int i = first_user_id; i <= last_user_id; i++) {
      for (int j = first_task_id; j <= last_task_id; j++) {
        for (int a = 0; a < attempts; a++) {
          int tests = rnd.next(0, tests_amount[j]);
          int rand = rnd.next(0, 3);
          if (rand <= 1)
            tests = tests_amount[j];
          users_sols[i].push_back({j, rnd.next(0, tests)});
        }
      }
    }

    for (auto x : users_sols) {
      for (auto r : x.second) {
        Data d;
        d.user_id = x.first;
        d.task_id = r.first;
        d.score = r.second;
        v.push_back(d);
      }
    }

    int shuffle = 100;
    for (int s = 0; s < shuffle; s++) {
      int i = rnd.next(0, int(v.size() - 1));
      int j = rnd.next(0, int(v.size() - 1));
      if (v[i].user_id != v[j].user_id)
        swap(v[i], v[j]);
    }
    for (int s = 0; s < shuffle; s++) {
      int i = rnd.next(0, int(v.size() - 1));
      int j = rnd.next(0, int(v.size() - 1));
      if (v[i].user_id == v[j].user_id && v[i].task_id == v[j].task_id) {
        if (i < j && v[i].score == tests_amount[v[i].task_id])
          swap(v[i], v[j]);
        if (i > j && v[j].score == tests_amount[v[j].task_id])
          swap(v[i], v[j]);
      }
    }
    
    for (int i = 0; i < v.size(); i++) {
      solution_id += rnd.next(0, 10);
      v[i].solution_id = solution_id;
    }

    cout << "sol_id;user_id;task_id;score\n";
    for (int i = 0; i < v.size(); i++) {
      cout << v[i].solution_id << ";" << v[i].user_id << ";" << v[i].task_id << ";";
      cout << fixed << setprecision(2) << 100.00 * v[i].score / tests_amount[v[i].task_id]  << endl;
   }
}
