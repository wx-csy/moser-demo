#include <cstdio>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;

constexpr int NR_VARIABLE = 112500;
constexpr int VAR_PER_CL = 9;
constexpr int NR_CLAUSE = 100000;
static_assert(NR_CLAUSE * VAR_PER_CL % NR_VARIABLE == 0,
        "the number of variables is not uniform");

int clauses[NR_CLAUSE][VAR_PER_CL];
bool used[NR_VARIABLE];

inline int index(int x, int y) {
    return x * VAR_PER_CL + y;
}

int main() {
    vector<int> vars;
    mt19937 gen(time(NULL));
    for (int i = 1; i <= NR_VARIABLE; i++) 
        for (int j = 0; j < VAR_PER_CL; j++) 
            vars.push_back(i);
reshuffle:
    shuffle(vars.begin(), vars.end(), gen);
    fill(begin(used), end(used), false);
    for (int i = 0; i < NR_CLAUSE; i++) {
        for (int j = 0; j < VAR_PER_CL; j++) {
            if (used[vars[index(i, j)]]) {
                for (int ii = i + 1; ii < NR_CLAUSE; ii++) {
                    for (int jj = 0; jj < VAR_PER_CL; jj++) {
                        if (!used[vars[index(ii, jj)]]) {
                            swap(vars[index(ii, jj)], vars[index(i, j)]);
                            goto done;
                        }
                    }
                }
                fprintf(stderr, "Reshuffle at (%d, %d)\n", i, j);
                goto reshuffle;
            }
done:
            clauses[i][j] = vars[index(i, j)];
            used[clauses[i][j]] = true;
        }
        for (int j = 0; j < VAR_PER_CL; j++) 
            used[clauses[i][j]] = false;
    }
     
    for (int i = 0; i < NR_CLAUSE; i++) 
        for (int j = 0; j < VAR_PER_CL; j++) 
            if (gen() & 1) clauses[i][j] = -clauses[i][j];

    printf("p cnf %d %d\n", NR_VARIABLE, NR_CLAUSE);
    for (int i = 0; i < NR_CLAUSE; i++) {
        for (int j = 0; j < VAR_PER_CL; j++)
            printf("%d ", clauses[i][j]);
        printf("0\n");
    }
    return 0;
}
