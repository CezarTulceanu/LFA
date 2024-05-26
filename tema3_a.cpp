#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

ifstream in("in.txt");
ofstream out("out.txt");

const int NMAX = 5007;
struct Rule {
    char lhs;
    string rhs;
};

int n, q;
char S;
vector<Rule> rules;
unordered_map<string, unordered_set<char>> rtl;
unordered_set<char> mat[NMAX][NMAX];

int main() {
    // Reading number of rules
    in >> n;
    for (int i = 0; i < n; ++i) {
        Rule rule;
        in >> rule.lhs >> rule.rhs;
        rules.push_back(rule);
        rtl[rule.rhs].insert(rule.lhs);
    }
    // Reading start symbol
    in >> S;
    // Reading number of queries
    in >> q;

    for (int it = 0; it < q; ++it) {
        string word;
        in >> word;
        int l = word.size();

        // Reset the matrix for each query
        for (int i = 1; i <= l; ++i) {
            for (int j = 1; j <= l; ++j) {
                mat[i][j].clear();
            }
        }

        // Initialize the diagonal of the matrix
        for (int i = 1; i <= l; ++i) {
            string str(1, word[i - 1]);
            if (rtl.find(str) != rtl.end()) {
                mat[i][i] = rtl[str];
            }
        }

        // Fill the matrix using the CYK algorithm
        for (int len = 2; len <= l; ++len) {
            for (int i = 1; i <= l - len + 1; ++i) {
                int j = i + len - 1;
                for (int k = i; k < j; ++k) {
                    for (auto &w : mat[i][k]) {
                        for (auto &y : mat[k + 1][j]) {
                            string comp = string(1, w) + string(1, y);
                            if (rtl.find(comp) != rtl.end()) {
                                mat[i][j].insert(rtl[comp].begin(), rtl[comp].end());
                            }
                        }
                    }
                }
            }
        }

        if (mat[1][l].find(S) != mat[1][l].end()) {
            out << "The word was accepted\n";
        } else {
            out << "The word was rejected\n";
        }
    }

    return 0;
}
