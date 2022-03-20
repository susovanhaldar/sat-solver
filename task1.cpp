#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include "togasat.hpp"
using namespace std;
vector<vector<int>> vec; //global vector used to store clauses
int unsat = 0;
int iteration = 0;
int guess[4]; //this global array will store the current guess by code-breaker
std::vector<int> clause; //this global vector stores clauses temporarily.
int i, j, k, l, m;
void findSAT() {
    togasat::Solver solver;
    for (int i = 0; i < vec.size(); i++) {
        solver.addClause(vec[i]);
    }
    togasat::lbool status = solver.solve(); //solving all the clauses
    if (status == 1) {
        unsat = 1; //if unsat it will set unsat variable to 1, so that the code maker can stop here
    }
    solver.guess_solution(guess); //this function is in togasat 
}
void code_breaker(int black, int white) {
    if (iteration++ == 0) {
        // first initialize the condition that if one color is present in one
        // position then it will not present in other position.
        for (i = 0; i < 8; i++) {
            for (k = 4 * i; k < 4 * i + 4; k++)
                for (j = k + 1; j < 4 * i + 4; j++) {
                    clause.clear();
                    clause.push_back(-k - 1);
                    clause.push_back(-j - 1);
                    vec.push_back(clause);
                }
        }
        // second initialize the condition that if any color present in any
        // position, then other colors cannot present in that position. it is
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
        int remaining_colors[4];
        int guess_colors[4];
        for (i = 0; i < 4; i++) {
            guess_colors[i] = guess[i] / 4;
        }
        int all_colors[8];
        for (i = 0; i < 8; i++) {
            all_colors[i] = 1;
        }
        for (i = 0; i < 4; i++) {
            all_colors[guess_colors[i]] = 0;
        }
        k = 0;
        for (i = 0; i < 8; i++) {
            if (all_colors[i] == 1) {
                remaining_colors[k++] = i;
            }
        }
        // Starting of condition checking here
        // Start with the case that black is 0 and white is also 0
        if (black == 0 && white == 0) {
            for (i = 0; i < 4; i++) {
                clause.clear();
                for (j = 0; j < 4; j++) {
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
                int color = guess_colors[i];
                for (j = 0; j < 4; j++) {
                    if (j == i) {
                        continue;
                    }
                    clause.push_back(4 * color + j + 1);
                }
            }
            vec.push_back(clause);
            // Testing that if one color is present at any position then the
            // remaining colors will not present in the guess.
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (j == i) {
                        continue;
                    }
                    int c = guess_colors[i];
                    for (k = 0; k < 4; k++) {
                        if (k == j) continue;
                        clause.clear();
                        clause.push_back(-4 * c - j - 1);
                        for (l = 0; l < 4; l++) {
                            clause.push_back(4 * remaining_colors[l] + k + 1);
                        }

                        vec.push_back(clause);
                    }
                }
            }
        }
        if (black == 0 && white == 2) {
            // no colors can be in their current position .
            for (i = 0; i < 4; i++) {
                clause.clear();
                clause.push_back(-(guess[i] + 1));
                vec.push_back(clause);
            }
            // atleast one of the colors is present in the actual colors
            clause.clear();
            for (i = 0; i < 4; i++) {
                int color = guess_colors[i];
                for (j = 0; j < 4; j++) {
                    if (j != i) {
                        clause.push_back(4 * color + j + 1);
                    }
                }
            }
            vec.push_back(clause);
        }
        if (black == 0 && white == 3) {
            // no colors can be in their current position .
            for (i = 0; i < 4; i++) {
                clause.clear();
                clause.push_back(-(guess[i] + 1));
                vec.push_back(clause);
            }
            // atleast one of the colors is present in the actual color
            clause.clear();
            for (i = 0; i < 4; i++) {
                int color = guess_colors[i];
                for (j = 0; j < 4; j++) {
                    if (j != i) {
                        clause.push_back(4 * color + j + 1);
                    }
                }
            }
            vec.push_back(clause);
        }
        if (black == 0 && white == 4) {
            // all colors are present but their positions are different.
            for (i = 0; i < 4; i++) {
                clause.clear();
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    int color = guess_colors[j];
                    clause.push_back(color * 4 + i + 1);
                }
                vec.push_back(clause);
            }
        }
        if (black == 1 && white == 0) {
            //atleast one color is present in it's current position.
            clause.clear();
            for (i = 0; i < 4; i++) {
                clause.push_back(guess[i] + 1);
            }
            vec.push_back(clause);
            // If one colors is present (i.e. its own place) then the
            // remaining colors will not present.
            for (i = 0; i < 4; i++) {
                int color = guess[i];
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    clause.clear();

                    clause.push_back(-(color + 1));
                    for (k = 0; k < 4; k++) {
                        int c = remaining_colors[k];

                        clause.push_back(4 * c + j + 1);
                    }
                    vec.push_back(clause);
                }
            }
        }
        if (black == 1 && white == 1) {
            //at least one color is present in it's current position
            clause.clear();
            for (i = 0; i < 4; i++) {
                clause.push_back(guess[i] + 1);
            }
            vec.push_back(clause);
            // If one color is present in its own position then the remaining
            // colors will not present in their own position.
            for (i = 0; i < 4; i++) {
                int color = guess[i];
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    clause.clear();
                    clause.push_back(-color - 1);
                    clause.push_back(-(guess[j] + 1));
                    vec.push_back(clause);
                }
                // atleast one of the colors which is not in their place, present
                // in the original colors.
                clause.clear();
                clause.push_back(-color - 1);
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    for (k = 0; k < 4; k++) {
                        if (k == j || k == i) continue;
                        int c = guess_colors[k];
                        clause.push_back(4 * c + j + 1);
                    }
                }
                vec.push_back(clause);
            }
        }
        if (black == 1 && white == 2) {
            //at least one color is present in it's original position
            clause.clear();
            for (i = 0; i < 4; i++) {
                clause.push_back(guess[i] + 1);
            }
            vec.push_back(clause);
            //If one colors is present in its own position then the
            // remaining colors will not present in their own position
            // also at least one of the remaining colors will present
            //in the next guess.
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
                    for (k = 0; k < 4; k++) {
                        if (k == j || k == i) continue;
                        int c = guess_colors[k];
                        clause.push_back(4 * c + j + 1);
                    }
                }
                vec.push_back(clause);
            }
        }
        if (black == 1 && white == 3) {
            //at least one color is present in it's original position
            clause.clear();
            for (i = 0; i < 4; i++) {
                clause.push_back(guess[i] + 1);
            }
            vec.push_back(clause);
            //If one colors is present in its own position then the 
            //remaining colors will notpresent in their own position,
            // but they will present in the next guess.
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (j == i) continue;
                    clause.clear();
                    clause.push_back(-guess[i] - 1);
                    for (k = 0; k < 4; k++) {
                        if (k == i || k == j) {
                            continue;
                        }
                        clause.push_back(4 * guess_colors[k] + j + 1);
                    }
                    vec.push_back(clause);
                }
            }
        }
        if (black == 2 && white == 0) {
            //at least two color is in their own place.
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
            //if two colors are in their own place  then the remaining
            //colors will not be there in the guess.
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (k == i || k == j) continue;
                        clause.clear();
                        clause.push_back(-guess[i] - 1);
                        clause.push_back(-guess[j] - 1);
                        for (l = 0; l < 4; l++) {
                            clause.push_back(4 * remaining_colors[l] + k + 1);
                        }
                        vec.push_back(clause);
                    }
                }
            }
        }
        if (black == 2 && white == 1) {
            //at least two color is in their own place.
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
            //if two colors are present in their own place then the remaining 
            //colors will not present in their own place.
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
            //at least two color is in their own place.
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
            //if two color is present in their own place, then the remaining
            // colors positions will be interchanged.
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
            //atleast three of the colors must be in their own place.
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    clause.clear();
                    clause.push_back(guess[i] + 1);
                    clause.push_back(guess[j] + 1);
                    vec.push_back(clause);
                }
            }
            //if three colors are in their own place, then the remaining color
            // is not present.
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
    //after adding all the clauses in the global vector, here we are calling 
    //the solver through the function findSAT.
    findSAT();
    cout << endl;
}

void code_maker() {
    const char colors[] = "RBGYOPWK"; //color code for individual position
    int i, j, k;
    int count = 0;
    int black = 1;
    int white = 0;
    srand(time(0));
    int all_color[] = {0, 1, 2, 3, 4, 5, 6, 7}; //this is used for random array
    int original[4];
    for (int i = 0; i < 4; i++) {
        int r = i + rand() % (8 - i);
        original[i] = all_color[r];
        all_color[r] = all_color[i];
    }
    cout << "\n                ";
    for (i = 0; i < 4; i++) {
        cout << colors[original[i]] << " ";
    }
    cout << endl;
    cout << "-------------------------------------" << endl;
    while (1) {
        count++;
        code_breaker(black, white); //calling code breaker here
        if (unsat) {
            return;
        }
        black = 0;
        white = 0;
        //calculating number of black
        for (i = 0; i < 4; i++) {
            if (guess[i] / 4 == original[i]) {
                black++;
            }
        }
        //calculating number of white.
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (j == i) continue;
                if (guess[i] / 4 == original[j]) {
                    white++;
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
    code_maker(); //calling the code maker here
    return 0;
}