#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
#include <map>
#include <random>
#include <list>

using namespace std;

/***********
*   MAIN   *
***********/

int main([[maybe_unused]] int argc, char *argv[]) {
    ///   Variable Defaults   ///
    vector<string> tokens;
    set<string> unique;

    string next_line;  // Each data line
    string fileName = argv[1];

    std::random_device rd;
    std::mt19937 mt(rd());

    ///   Add to Vectors and Sets   ///

    ifstream in(argv[1]);
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct;
            for (auto & c : token) { // Remove Punctuation
                if (isalpha(c)) {
                    nopunct += c;
                }
            }
            tokens.push_back(nopunct);
            unique.insert(nopunct);
        }
    }


    ///   Print to Screen and Set File   ///

    cout << "Number of words " << tokens.size() << endl;
    cout << "Number of unique words " << unique.size() << endl;

    ofstream setFile(fileName + "_set.txt");
    for (const auto & it : unique) {
        setFile << ' ' << it;
    }
    cout << endl;


    ///   Print the Vector to a File   ///

    cout << "Number of words " << tokens.size() << endl;
    cout << "Number of unique words " << unique.size() << endl;

    ofstream vectorFile(fileName + "_vector.txt");
    for (const auto & it : tokens) {
        vectorFile << ' ' << it;
    }
    cout << endl;


    ///   Map Vector   ///

    std::uniform_real_distribution<> dist(0, 5);

    const int M = static_cast<int>(dist(mt));
    map<list <string>, vector<string> > wordmap;

    // Set up a list with empty strings
    list <string> state;
    for (int i = 0; i < M; i++) {
        state.emplace_back("");
    }

    for (auto & token : tokens) {
        wordmap[state].push_back(token);
        state.push_back(token);
        state.pop_front();
    }

/**************
*   COMMENT   *
**************/

    state.clear();
    for (int i = 0; i < M; i++) {
        state.emplace_back("");
    }
    for (int i = 0; i < 100; i++) {
        ///   Use random library to effectively randomize the dice rolls   ///
        std::uniform_real_distribution<> newDist(0, static_cast<double>(wordmap[state].size()));

        auto ind = static_cast<int>(newDist(mt));
        cout << wordmap[state][ind]<<" ";
        state.push_back(wordmap[state][ind]);
        state.pop_front();
    }

    return 0;
}
