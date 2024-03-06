/*
 * Outputs random number between 1 and 10^6, inclusive.
 * To generate different values, call "igen.exe" with different parameters.
 * For example, "igen.exe 1" returns 504077, but "igen.exe 3" returns 808747.
 * 
 * It is typical behaviour of testlib generator to setup randseed by command line.
 */

#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1);
    int k = opt<int>(2);
    int seed = opt<int>(3);
    cout << n << endl;
    for (int i = 0; i < n - 1; i++)
      cout << rnd.next(-10.0, 10.0) << " ";
    cout << rnd.next(-10.0, 10.0) << endl;
    cout << k << endl;
    for (int i = 0; i < k-1; i++)
      cout << rnd.next(-10.0, 10.0) << " ";
    cout << rnd.next(-10.0, 10.0) << endl;
}
