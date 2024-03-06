#include "testlib.h"
#include <vector>

using namespace std;

long determinant(const vector<vector<long>>& matrix) {
    int n = matrix.size();
    if (n == 1) {
        return matrix[0][0]; // Для матриці 1x1 детермінант = елементу матриці
    }

    long det = 0LL;
    for (int i = 0; i < n; ++i) {
        vector<vector<long>> submatrix(n - 1, vector<long>(n - 1, 0));
        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (k < i) {
                    submatrix[j - 1][k] = matrix[j][k];
                } else if (k > i) {
                    submatrix[j - 1][k - 1] = matrix[j][k];
                }
            }
        }
        det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(submatrix);
    }

    return det;
}


int main(int argc, char *argv[]) {
    setName("Numpy: linalg");

    registerTestlibCmd(argc, argv);

    int n = 0;
    string firstElems;
    vector<int> vans, vouf;
    vans.clear();
    vouf.clear();

    while (!ans.seekEof() && !ouf.seekEof()) {
        n++;
        long long j = ans.readLong();
        long long p = ouf.readLong();
        vans.push_back(j);
        vouf.push_back(p);
    }

    int extraInAnsCount = 0;

    while (!ans.seekEof()) {
        ans.readLong();
        extraInAnsCount++;
    }

    int extraInOufCount = 0;

    while (!ouf.seekEof()) {
        ouf.readLong();
        extraInOufCount++;
    }

    if (extraInAnsCount > 0)
        quitf(_wa, "Answer contains longer sequence [length = %d], but output contains %d elements",
              n + extraInAnsCount, n);

    if (extraInOufCount > 0)
        quitf(_wa, "Output contains longer sequence [length = %d], but answer contains %d elements",
              n + extraInOufCount, n);


    
    int n1 = vans[0];
    int n2 = vouf[0];
    if (n1 != n2)
      quitf(_wa, "Wrong size");

    int d1 = vans.back();
    int d2 = vouf.back();
    if (d1 != d2)
      quitf(_wa, "Wrong det");
    vector<vector<long>> A, B;

    A.resize(n1);
    B.resize(n1);
    for (int i = 0; i < n1; i++) {
      A[i].resize(n1);
      B[i].resize(n1);
    }   

    int k = 1;
    for (int i = 0; i < n1; i++) {
      for (int j = 0; j < n1; j++) {
        A[i][j] = vans[k];
        B[i][j] = vouf[k];
        k += 1;
      }
    }

    long detA = determinant(A);
    long detB = determinant(B);
    if (detA != detB)
      quitf(_wa, "Wrong det");



    if (n <= 5)
        quitf(_ok, "%d number(s): \"%s\"", n, compress(firstElems).c_str());
    else
        quitf(_ok, "%d numbers", n);
}
