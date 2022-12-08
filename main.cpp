#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

int L, S, C;
int tag, index, displacement;
int cacheclock;
int hits, misses, totalAccesses;
int memoryAccessClocks = 100;
vector<pair <bool, int> > cache;

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
    
    //calculating the number of bits for the tag, index, and displacement
    C = S / L;
    index = log2(C);
    displacement = log2(L);
    tag = 32 - index - displacement;

    //initializing cache size according to user input
    cache.resize(C);
    for (int i = 0; i < C; i++)
    {
        cache[i].first = false;
        cache[i].second = 0;
    }

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
    string bin = hex_to_binary(line);
    string tagbin = bin.substr(0, tag);
    string indexbin = bin.substr(tag, index);
    string displacementbin = bin.substr(tag + index, displacement);
    if(!cache[stoi(indexbin, nullptr, 2)].first || cache[stoi(indexbin, nullptr, 2)].second != stoi(tagbin, nullptr, 2))
    {
        misses++;
        cache[stoi(indexbin, nullptr, 2)].first = true;
        cache[stoi(indexbin, nullptr, 2)].second = stoi(tagbin, nullptr, 2);
    }
    else
    {
        hits++;
    }
    totalAccesses++;

    for(int i = 0; i < C; i++)
    {
        cout << i << " : " << cache[i].first << " " << cache[i].second << endl;
    }
    cout << "Total Accesses: " << totalAccesses << endl;
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
    cout << "Hit Ratio: " << (double)hits / (double)totalAccesses << endl;
    cout << "Miss Ratio: " << (double)misses / (double)totalAccesses << endl;

    cout << "Average Access Time: " << (double)(cacheclock) + (memoryAccessClocks * (double)misses / (double)totalAccesses) << endl;
}

string hex_to_binary(string hex)
{
    transform(hex.begin(), hex.end(), hex.begin(), ::toupper);
    string binary;
    for (int i = 0; i < hex.length(); i++)
    {
        switch (hex[i])
        {
        case '0':
            binary += "0000";
            break;
        case '1':
            binary += "0001";
            break;
        case '2':
            binary += "0010";
            break;
        case '3':
            binary += "0011";
            break;
        case '4':
            binary += "0100";
            break;
        case '5':
            binary += "0101";
            break;
        case '6':
            binary += "0110";
            break;
        case '7':
            binary += "0111";
            break;
        case '8':
            binary += "1000";
            break;
        case '9':
            binary += "1001";
            break;
        case 'A':
            binary += "1010";
            break;
        case 'B':
            binary += "1011";
            break;
        case 'C':
            binary += "1100";
            break;
        case 'D':
            binary += "1101";
            break;
        case 'E':
            binary += "1110";
            break;
        case 'F':
            binary += "1111";
            break;
        }
    }
    return binary;
}