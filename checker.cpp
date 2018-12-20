#include <bits/stdc++.h>
using namespace std;

mt19937 gen(time(NULL));

int nvar, ncl;
vector<vector<int>> clauses;
vector<vector<int>> varc;
vector<bool> asgn;

bool sat(int cl) {
    for (int x : clauses[cl]) {
        if (x > 0 and asgn[x]) return true;
        if (x < 0 and !asgn[-x]) return true;
    }
    return false;
}

int main() {
    scanf("%*s %*s %d %d", &nvar, &ncl);
    asgn.resize(nvar + 1);
    varc.resize(nvar + 1);
    for (int i = 0; i < ncl; i++) {
        vector<int> clause;
        int var;
        while (scanf("%d", &var), var) {
            clause.push_back(var);
            varc[abs(var)].push_back(i);
        }
        clauses.push_back(clause);
    }
    scanf("%*s");
    int var;
    while (scanf("%d", &var), var)
        if (var > 0) asgn[var] = true;
    for (int i = 0; i < ncl; i++) {
        if (!sat(i)) {
            printf("Clause %d not satisfied!\n", i);
            return EXIT_FAILURE;
        }
    }
    puts("Correct!");
    return 0;
}
