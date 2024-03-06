#include "Library.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Write number of electoral divisions in the nation (n) and number of campaigning days before the election (m) after the program name." << endl;
        cerr << "Usage: .\\AEP n m" << endl;
        return 1;
    }

    int n = stoi(argv[1]);
    int m = stoi(argv[2]);

    if (n < 1 || n > 10 || m < 1 || m > 30) {
        cerr << "Invalid input. n should be in the range 1 to 10 inclusive. m should be in the range 1 to 30 inclusive." << endl;
        cerr << "Usage: .\\AEP n m" << endl;
        return 1;
    }

    simulateElection(n, m);
}