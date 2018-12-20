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

void perfcnt(int cl) {
    static int cnt = 0;
    cnt++;
    fprintf(stderr, "[%4d] fixing clause %d\n", cnt, cl);
}

void fix(int cl) {
    perfcnt(cl);
    for (int x : clauses[cl])
        asgn[abs(x)] = gen() & 1;
    for (int x : clauses[cl])
        for (int c : varc[abs(x)]) 
            if (!sat(c)) fix(c);
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
    for (int i = 1; i <= nvar; i++) 
        asgn[i] = gen() & 1;
    for (int i = 0; i < ncl; i++)
        if (!sat(i)) fix(i);
    printf("SAT\n");
    for (int i = 1; i <= nvar; i++) 
        printf("%d ", asgn[i] ? i : -i);        
    printf("0\n");
    return 0;
}
