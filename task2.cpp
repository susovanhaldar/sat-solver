#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

#include "togasat.hpp"
using namespace std;
vector<vector<int>> vec; //global vector to store all the clauses.
int unsat = 0;
int iteration = 0;
int guess[4]; //global array to store current guess by the code-breaker
std::vector<int> clause; // it stores one clauses temporarily.
int i, j, k, l, m;
void findSAT() {
    togasat::Solver solver;
    for (int i = 0; i < vec.size(); i++) {
        solver.addClause(vec[i]);
    }
    togasat::lbool status = solver.solve(); //solving the cnf logical equation here
    if (status == 1) {
        unsat = 1;
    }
    solver.guess_solution(guess); // this function is in "togasat.hpp"
}
void code_breaker(int black, int white) {
    if (iteration++ == 0) {
        // second initialize the condition that if any color present in any
        // position, then other colors cannot present in that position.
        for (i = 0; i < 4; i++) {
            for (j = i; j < 32; j += 4) {
                for (k = j + 4; k < 32; k += 4) {
                    clause.clear();
                    clause.push_back(-j - 1);
                    clause.push_back(-k - 1);
                    vec.push_back(clause);
                }
            }
        }
        // a condition that atleast every position has a color in it
        for (i = 0; i < 4; i++) {
            clause.clear();
            for (j = 0; j < 8; j++) {
                clause.push_back(4 * j + i + 1);
            }
            vec.push_back(clause);
        }
    } else {
        // initializing a array consists of colors which is not present in the
        // guess
        vector<int> remaining_colors;
        vector<int> guess_colors;
        vector<int> present_colors;
        for (i = 0; i < 4; i++) {
            guess_colors.push_back(guess[i] / 4);
        }
        int all_colors[8];
        for (i = 0; i < 8; i++) {
            all_colors[i] = 1;
        }
        for (i = 0; i < 4; i++) {
            all_colors[guess_colors[i]] = 0;
        }
        for (i = 0; i < 8; i++) {
            if (all_colors[i] == 1) {
                remaining_colors.push_back(i);
            } else {
                present_colors.push_back(i);
            }
        }

        int r_length = remaining_colors.size();  // remaining length
        int p_length = present_colors.size();    // present length

        // Starting of condition checking here
        // Start with the case that black is 0 and white is also 0
        // this is correct.
        if (black == 0 && white == 0) {
            for (i = 0; i < 4; i++) {
                clause.clear();
                for (j = 0; j < r_length; j++) {
                    int color = remaining_colors[j];
                    clause.push_back(4 * color + i + 1);
                }
                vec.push_back(clause);
            }
        }
        // condition for one white but no black
        if (black == 0 && white == 1) {
            // This for loop is for the condition that no colors is in their own
            // position.
            for (i = 0; i < 4; i++) {
                clause.clear();
                int color = guess[i];
                clause.push_back(-color - 1);
                vec.push_back(clause);
            }
            // testing that atleast one of the colors are present in the next
            // guess
            clause.clear();
            for (i = 0; i < 4; i++) {
                for (j = 0; j < p_length; j++) {
                    int color = present_colors[j];
                    clause.push_back(4 * color + i + 1);
                }
            }
            vec.push_back(clause);
            // Testing that if one color is present at any position then the
            // remaining colors(in guess) will not present in the actual colors.
            for (i = 0; i < p_length; i++) {
                for (j = 0; j < 4; j++) {
                    if (present_colors[i] == guess_colors[j]) continue;
                    int c = present_colors[i];
                    for (k = 0; k < 4; k++) {
                        if (k == j) continue;
                        clause.clear();
                        clause.push_back(-4 * c - j - 1);
                        for (l = 0; l < r_length; l++) {
                            clause.push_back(4 * remaining_colors[l] + k + 1);
                        }
                        vec.push_back(clause);
                    }
                }
            }
        }
        if (black == 0 && white == 2) {
            // This for loop is for the condition that no colors is in their own
            // position.
            for (i = 0; i < 4; i++) {
                clause.clear();
                int color = guess[i];
                clause.push_back(-color - 1);
                vec.push_back(clause);
            }
            // testing that atleast one of the colors are present in the next
            // guess
            clause.clear();
            for (i = 0; i < 4; i++) {
                for (j = 0; j < p_length; j++) {
                    int color = present_colors[j];
                    clause.push_back(4 * color + i + 1);
                }
            }
            vec.push_back(clause);
        }
        if (black == 0 && white == 3) {
            // This for loop is for the condition that no colors is in their own
            // position.
            for (i = 0; i < 4; i++) {
                clause.clear();
                int color = guess[i];
                clause.push_back(-color - 1);
                vec.push_back(clause);
            }
            // testing that atleast one of the colors are present in the next
            // guess
            clause.clear();
            for (i = 0; i < 4; i++) {
                for (j = 0; j < p_length; j++) {
                    int color = present_colors[j];
                    clause.push_back(4 * color + i + 1);
                }
            }
            vec.push_back(clause);
        }
        if (black == 0 && white == 4) {
            // This for loop is for the condition that no colors is in their own
            // position.
            for (i = 0; i < 4; i++) {
                clause.clear();
                int color = guess[i];
                clause.push_back(-color - 1);
                vec.push_back(clause);
            }
            for (i = 0; i < 4; i++) {
                clause.clear();
                for (j = 0; j < p_length; j++) {
                    int color = present_colors[j];
                    clause.push_back(color * 4 + i + 1);
                }
                vec.push_back(clause);
            }
        }
        if (black == 1 && white == 0) {
            clause.clear();
            for (i = 0; i < 4; i++) {
                clause.push_back(guess[i] + 1);
            }
            vec.push_back(clause);
            for (i = 0; i < 4; i++) {
                int color = guess[i];
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    clause.clear();
                    clause.push_back(-color - 1);
                    clause.push_back(-(guess[j] + 1));
                    vec.push_back(clause);

                    clause.clear();
                    clause.push_back(-(color + 1));
                    clause.push_back(4 * guess_colors[i] + j + 1);
                    for (k = 0; k < r_length; k++) {
                        int c = remaining_colors[k];
                        clause.push_back(4 * c + j + 1);
                    }
                    vec.push_back(clause);
                }
            }
        }
        if (black == 1 && white == 1) {
            clause.clear();
            for (i = 0; i < 4; i++) {
                clause.push_back(guess[i] + 1);
            }
            vec.push_back(clause);
            for (i = 0; i < 4; i++) {
                int color = guess[i];
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    clause.clear();
                    clause.push_back(-color - 1);
                    clause.push_back(-(guess[j] + 1));
                    vec.push_back(clause);
                }
                clause.clear();
                clause.push_back(-color - 1);
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    for (k = 0; k < p_length; k++) {
                        int c = present_colors[k];
                        clause.push_back(4 * c + j + 1);
                    }
                }
                vec.push_back(clause);
            }
        }
        if (black == 1 && white == 2) {
            clause.clear();
            for (i = 0; i < 4; i++) {
                clause.push_back(guess[i] + 1);
            }
            vec.push_back(clause);
            for (i = 0; i < 4; i++) {
                int color = guess[i];
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    clause.clear();
                    clause.push_back(-color - 1);
                    clause.push_back(-(guess[j] + 1));
                    vec.push_back(clause);
                }
                clause.clear();
                clause.push_back(-color - 1);
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    for (k = 0; k < p_length; k++) {
                        int c = present_colors[k];
                        clause.push_back(4 * c + j + 1);
                    }
                }
                vec.push_back(clause);
            }
        }
        if (black == 1 && white == 3) {
            clause.clear();
            for (i = 0; i < 4; i++) {
                clause.push_back(guess[i] + 1);
            }
            vec.push_back(clause);
            for (i = 0; i < 4; i++) {
                int color = guess[i];
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    clause.clear();
                    clause.push_back(-color - 1);
                    clause.push_back(-(guess[j] + 1));
                    vec.push_back(clause);
                }
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    clause.clear();
                    clause.push_back(-guess[i] - 1);
                    for (k = 0; k < p_length; k++) {
                        clause.push_back(4 * present_colors[k] + j + 1);
                    }
                    vec.push_back(clause);
                }
            }
        }
        if (black == 2 && white == 0) {
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    for (k = j + 1; k < 4; k++) {
                        clause.clear();
                        clause.push_back(guess[i] + 1);
                        clause.push_back(guess[j] + 1);
                        clause.push_back(guess[k] + 1);
                        vec.push_back(clause);
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (k == i || k == j) continue;
                        clause.clear();
                        clause.push_back(-guess[i] - 1);
                        clause.push_back(-guess[j] - 1);
                        clause.push_back(-guess[k] - 1);
                        vec.push_back(clause);
                    }
                }
            }
        }
        if (black == 2 && white == 1) {
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    for (k = j + 1; k < 4; k++) {
                        clause.clear();
                        clause.push_back(guess[i] + 1);
                        clause.push_back(guess[j] + 1);
                        clause.push_back(guess[k] + 1);
                        vec.push_back(clause);
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (k == i || k == j) continue;
                        clause.clear();
                        clause.push_back(-guess[i] - 1);
                        clause.push_back(-guess[j] - 1);
                        clause.push_back(-(guess[k] + 1));
                        vec.push_back(clause);
                    }
                }
            }
        }
        if (black == 2 && white == 2) {
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    for (k = j + 1; k < 4; k++) {
                        clause.clear();
                        clause.push_back(guess[i] + 1);
                        clause.push_back(guess[j] + 1);
                        clause.push_back(guess[k] + 1);
                        vec.push_back(clause);
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (k == i || k == j) continue;
                        clause.clear();
                        clause.push_back(-guess[i] - 1);
                        clause.push_back(-guess[j] - 1);
                        for (l = 0; l < 4; l++) {
                            if (l == i || l == j || l == k) {
                                continue;
                            }
                            clause.push_back(4 * guess_colors[l] + k + 1);
                        }
                        vec.push_back(clause);
                    }
                }
            }
        }
        if (black == 3 && white == 0) {
            //atleast three colors are in their own position.
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    clause.clear();
                    clause.push_back(guess[i] + 1);
                    clause.push_back(guess[j] + 1);
                    vec.push_back(clause);
                }
            }
            //if three colors are present in their own position, the the 
            // remaining color is not present.
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    for (k = j + 1; k < 4; k++) {
                        clause.clear();
                        clause.push_back(-guess[i] - 1);
                        clause.push_back(-guess[j] - 1);
                        clause.push_back(-guess[k] - 1);
                        for (l = 0; l < 4; l++) {
                            if (l == i || l == j || l == k) continue;
                            clause.push_back(-guess[l] - 1);
                        }
                        vec.push_back(clause);
                    }
                }
            }
        }
    }

    findSAT(); //calling solver within this function
    cout << endl;
}

void code_maker() {
    const char colors[] = "RBGYOPWK"; //it stores which position has which color in it.
    int i, j, k;
    int count = 0;
    int black = 0;
    int white = 0;
    srand(time(0));
    int all_color[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int original[4];
    for (int i = 0; i < 4; i++) {
        int r = rand() % (8 - i);
        original[i] = all_color[r];
    }
    cout << "\n                ";
    for (i = 0; i < 4; i++) {
        cout << colors[original[i]] << " ";
    }
    cout << endl;
    cout << "-------------------------------------" << endl;
    while (1) {
        count++;
        code_breaker(black, white);
        if (unsat) {
            return;
        }
        black = 0;
        white = 0;
        //calculating the number of black and white depending upon the current 
        //guess and the original colors.
        int matched1[4];
        int matched2[4];
        for (i = 0; i < 4; i++) {
            matched1[i] = 0;
            matched2[i] = 0;
        }
        for (i = 0; i < 4; i++) {
            if (guess[i] / 4 == original[i]) {
                black++;
                matched1[i] = 1;
                matched2[i] = 1;
            }
        }
        for (i = 0; i < 4; i++) {
            if (matched1[i] == 1) continue;
            for (j = 0; j < 4; j++) {
                if (j == i) continue;
                if (guess[i] / 4 == original[j]) {
                    if (matched2[j] == 0) {
                        white++;
                        matched2[j] = 1;
                        matched1[i] = 1;
                        break;
                    }
                }
            }
        }
        printf("iteration %2d:   ", count);
        for (i = 0; i < 4; i++) {
            cout << (colors[guess[i] / 4]) << " ";
        }
        cout << "      B-" << black << ",W-" << white;
        cout << endl;
        if (black == 4) return;
    }
}
int main() {
    code_maker(); //calling code maker here.
    return 0;
}