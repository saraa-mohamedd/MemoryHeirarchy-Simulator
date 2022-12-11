#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

int L, S, C;
int tag, indexBits, displacement;
int cacheclock;
int hits, misses, totalAccesses;
int memoryAccessClocks = 100;
vector<pair <bool, string> > cache;

void readAccessSequence(string);
void cacheAccess(string);
string hex_to_binary(string);

int main()
{
    string accessfile;

    // taking all necessary input from user
    cout << "Enter your total cache size: ";
    cin >> S;

    cout << "Enter your cache line size: ";
    cin >> L;

    // validate clock cycles to be between 1 and 10
    do
    {
        cout << "Enter the number of clock cycles needed to access the cache: ";
        cin >> cacheclock;
        if(cacheclock < 1 || cacheclock > 10)
            cout << "Please enter a number between 1 and 10" << endl;
    } while (cacheclock < 1 || cacheclock > 10);

    cout << "Enter the complete path for the .txt file with the access sequences for your program: ";
    cin >> accessfile;
    
    //calculating the number of bits for the tag, indexBits, and displacement
    C = S / L;
    indexBits = log2(C);
    displacement = log2(L);
    tag = 32 - indexBits - displacement;

    //initializing cache size according to user input
    cache.resize(C);
    for (int i = 0; i < C; i++)
    {
        cache[i].first = false;
        cache[i].second = "";
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
        cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
        cout <<  "Memory Access: " << line << endl << endl;
        cacheAccess(line);
    }
}

void cacheAccess(string line)
{
    string bin = hex_to_binary(line);
    string tagbin = bin.substr(0, tag);
    string indexbin = bin.substr(tag, indexBits);
    string displacementbin = bin.substr(tag + indexBits, displacement);
    if(!cache[stoi(indexbin, nullptr, 2)].first || cache[stoi(indexbin, nullptr, 2)].second != tagbin)
    {
        misses++;
        cache[stoi(indexbin, nullptr, 2)].first = true;
        cache[stoi(indexbin, nullptr, 2)].second = tagbin;
    }
    else
    {
        hits++;
    }
    totalAccesses++;

    for(int i = 0; i < C; i++)
    {
        cout << i << " : valid = " << cache[i].first << " tag = " << cache[i].second << endl;
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