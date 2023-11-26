#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Cell {
    int length;
    int fromRow, fromCol;  // Pointers to trace back the substring
};

string longest_common_substring(const string &str1, const string &str2, vector<vector<Cell>> &dp) {
    int n = str1.length(), m = str2.length();
    dp.assign(n + 1, vector<Cell>(m + 1, {0, 0, 0}));
    int length = 0;
    int endRow, endCol;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j].length = dp[i - 1][j - 1].length + 1;
                dp[i][j].fromRow = i - 1;
                dp[i][j].fromCol = j - 1;
                if (dp[i][j].length > length) {
                    length = dp[i][j].length;
                    endRow = i;
                    endCol = j;
                }
            }
        }
    }

    // Reconstruct the longest common substring
    string lcs;
    while (length--) {
        lcs = str1[endRow - 1] + lcs;
        int prevRow = dp[endRow][endCol].fromRow;
        int prevCol = dp[endRow][endCol].fromCol;
        endRow = prevRow;
        endCol = prevCol;
    }

    return lcs;
}

void print_table(const vector<vector<Cell>>& dp) {
    for (const auto &row : dp) {
        for (const auto &cell : row) {
            cout << "{" << cell.length << ", (" << cell.fromRow << ", " << cell.fromCol << ")} ";
        }
        cout << "\n";
    }
}

int main() {
    string str1 = "ABAB";
    string str2 = "BABA";
    vector<vector<Cell>> dp;

    string lcs = longest_common_substring(str1, str2, dp);
    cout << "Longest Common Substring: " << lcs << endl;
    cout << "\nLookup Table with Pointers:\n";
    print_table(dp);

    return 0;
}
