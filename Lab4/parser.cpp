#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <cstring>

using namespace std;


// Define the productions
map<char, vector<string>> productions;
set<char> nonTerminals;
set<char> terminals;


// Function to calculate FIRST set
void calculateFirst(char symbol, set<char>& firstSet) {
    if (terminals.count(symbol) || symbol == 'e') {
        firstSet.insert(symbol);
        return;
    }
    for (string production : productions[symbol]) {
        bool hasEpsilon = true;
        for (char c : production) {
            calculateFirst(c, firstSet);
            if (!firstSet.count('e')) {
                hasEpsilon = false;
                break;
            }
        }
        if (hasEpsilon) firstSet.insert('e');
    }
}

// Function to calculate FOLLOW set
void calculateFollow(char symbol, set<char>& followSet) {
    if (symbol == 'S') followSet.insert('$');

    for (auto& entry : productions) {
        char nonTerminal = entry.first;
        for (string production : entry.second) {
            size_t found = production.find(symbol);
            if (found != string::npos) {
                if (found + 1 < production.size()) {
                    char nextSymbol = production[found + 1];
                    set<char> firstSet;
                    calculateFirst(nextSymbol, firstSet);
                    followSet.insert(firstSet.begin(), firstSet.end());

                    if (firstSet.count('e')) {
                        set<char> tempFollowSet;
                        calculateFollow(nonTerminal, tempFollowSet);
                        followSet.insert(tempFollowSet.begin(), tempFollowSet.end());
                    }
                } else if (found + 1 == production.size() && nonTerminal != symbol) {
                    calculateFollow(nonTerminal, followSet);
                }
            }
        }
    }
}

// LL(1) Parsing Table
map<pair<char, char>, string> parsingTable;

// Function to add entries to the LL(1) Parsing Table
void addToParsingTable(char nonTerminal, char terminal, string production) {
    parsingTable[make_pair(nonTerminal, terminal)] = production;
}

int main() {
    // Define the grammar rules
    productions['S'] = {"AA"};
    productions['A'] = {"aA", "b"};

    // Calculate terminals and non-terminals
    for (auto& entry : productions) {
        nonTerminals.insert(entry.first);
        for (string production : entry.second) {
            for (char c : production) {
                if (!isupper(c)) terminals.insert(c);
            }
        }
    }
    terminals.insert('$');

    // Calculate FIRST and FOLLOW sets
    map<char, set<char>> firstSets;
    map<char, set<char>> followSets;

    for (char nonTerminal : nonTerminals) {
        calculateFirst(nonTerminal, firstSets[nonTerminal]);
    }

    for (char nonTerminal : nonTerminals) {
        calculateFollow(nonTerminal, followSets[nonTerminal]);
    }

        // Display FIRST and FOLLOW sets
    cout << "FIRST sets:\n";
    for (char nonTerminal : nonTerminals) {
        cout << "FIRST(" << nonTerminal << ") = {";
        for (char symbol : firstSets[nonTerminal]) {
            cout << symbol << ", ";
        }
        cout << "}\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (char nonTerminal : nonTerminals) {
        cout << "FOLLOW(" << nonTerminal << ") = {";
        for (char symbol : followSets[nonTerminal]) {
            cout << symbol << ", ";
        }
        cout << "}\n";
    }
    // Add entries to the LL(1) Parsing Table
    addToParsingTable('S', 'a', "AA");
    addToParsingTable('S', 'b', "AA");
    addToParsingTable('A', 'a', "aA");
    addToParsingTable('A', 'b', "b");

    // Parse the input string
    string input = "ababa$"; // Append $ to the end to indicate the end of the input
    vector<char> stack;
    stack.push_back('$');
    stack.push_back('S'); // Push the start symbol onto the stack

    size_t inputIndex = 0;

    while (!stack.empty()) {
        char top = stack.back();
        char currentSymbol = input[inputIndex];

        if (top == currentSymbol) {
            // Matched, pop from stack and move to the next input symbol
            stack.pop_back();
            inputIndex++;
        } else if (nonTerminals.count(top)) {
            // Lookup in parsing table
            string production = parsingTable[make_pair(top, currentSymbol)];

            if (production != "") {
                // Replace top of stack with production
                stack.pop_back();
                for (int i = production.size() - 1; i >= 0; i--) {
                    if (production[i] != 'e') {
                        stack.push_back(production[i]);
                    }
                }
            } else {
                // Error: No production found in parsing table
                cout << "Error: Parsing table entry not found for (" << top << ", " << currentSymbol << ")\n";
                break;
            }
        } else {
            // Error: Mismatch between stack and input
            cout << "Error: Mismatch between stack and input\n";
            break;
        }
    }

    if (stack.empty() && inputIndex == input.size()) {
        cout << "Parsing successful! Input string is accepted.\n";
    } else {
        cout << "Parsing failed! Input string is not accepted.\n";
    }

    return 0;
}


