#include "testlib.h"
#include <vector>

using namespace std;

typedef vector<vector<string>> Matrix;

Matrix A;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1);
    int m = opt<int>(2);
    int k = opt<int>(3); // NaN
    int c = opt<int>(4); // mean = geomean
    int mn = opt<int>(5);
    int mx = opt<int>(6);
    int seed = opt<int>(5);
    A.resize(n);
    for (int i = 0; i < n; i++)
      A[i].resize(m);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        A[i][j] = to_string(rnd.next(mn, mx));
      }
    }

    for (int t = 0; t < k; t++) {
      int col = rnd.next(m);
      int row = rnd.next(n);
      int r = rnd.next(100);
      if (r % 3 == 0)
        A[row][col] = " ";
      if (r % 3 == 1)
        A[row][col] = rnd.next("[a-zA-Z0-9]{1,5}");
      if (r % 3 == 2)
        A[row][col] = to_string(rnd.next(100)) + "." + to_string(rnd.next(100));
    }

    for (int t = 0; t < c; t++) {
      int col = rnd.next(m);
      string s = to_string(rnd.next(10));
      for (int i = 0; i < n; i++)
        A[i][col] = s;
    }


    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m-1; j++) {
        cout << A[i][j] << ";";
      }
      cout << A[i][m-1] << endl;
    }

}
