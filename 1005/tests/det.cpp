#include <iostream>
#include <vector>

using namespace std;

// Функція для обчислення детермінанту матриці
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

vector<vector<long>> A;

int main() {
    int n;
    cin >> n;
    A.resize(n);
    for (int i = 0; i < n; i++)
      A[i].resize(n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        cin >> A[i][j];

    long det = determinant(A);
    cout << det << endl;

    return 0;
}

