#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

double L, S, C;
int cacheclock;
int hits, misses, totalaccesses;
vector<vector<string>> cache;

void readAccessSequence(string);
void cacheAccess(string);

int main()
{
    string accessfile;

    // taking all necessary input from user
    cout << "Enter your total cache size: ";
    cin >> S;

    cout << "Enter your cache line size: ";
    cin >> L;

    cout << "Enter the number of clock cycles needed to access the cache: ";
    cin >> cacheclock;

    cout << "Enter the complete path for the .txt file with the access sequences for your program: ";
    cin >> accessfile;
    
    //initializing cache size according to user input
    C = S / L;
    cache.resize(C);
    for (int i = 0; i < C; i++)
    {
        cache[i].resize(L);
    }

    //cout << cache[0][0];

    //reading in the access sequence from the file
    readAccessSequence(accessfile);

}

void readAccessSequence(string filename)
{
    ifstream infile;
    infile.open(filename);

    if (infile.fail())
    {
        cout << "Error opening your entered file path, terminating program..." << endl;
        exit(1);
    }

    string line;
    while (getline(infile, line))
    {
        cacheAccess(line);
        cout << line << endl;
    }
}

void cacheAccess(string line)
{
    
}