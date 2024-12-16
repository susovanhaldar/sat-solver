## Mastermind game
### Game Description
Mastermind is a popular code-breaking game that involves deduction and problem-solving skills. The game consists of 8 colors and 4 slots. The objective of the game is for the Code Breaker to guess the correct sequence of colors set by the Code Maker.
<<<<<<< HEAD
![Image of mastermind game](images/Mastermind.jpg)
<br />You can read more about this game [here](https://en.wikipedia.org/wiki/Mastermind_(board_game)).
<br />You may also play it online [here](https://www.webgamesonline.com/codebreaker/).
### Code Maker
The Code Maker internally sets a sequence of 4 colors from the available 8 colors. The Code Maker's sequence is hidden from the Code Breaker.
### Code Breaker
The Code Breaker tries to guess the sequence of colors set by the Code Maker. After each guess, the Code Breaker receives feedback in the form of black and white pegs.
<<<<<<< HEAD
<br />You can find the full problem description [here](Assignment3.pdf).
=======
You can find the full problem description [here](Assignment3.pdf)
>>>>>>> fe8bcbad06c9ac140d313771d7c34cea78ef939e
### Feedback
The feedback provided by the Code Maker consists of two types of pegs:
- **Black Pegs:** Represent the number of colors that are in the correct position in the guessed sequence.
- **White Pegs:** Represent the number of colors that are present in the Code Maker's sequence but are not in the correct position in the guessed sequence.
###Game Variants
The Mastermind game has two variants:
- **Part 1:** Distinct Colors
In this variant, all the colors in the 4 slots are distinct. The Code Breaker must guess a sequence of 4 unique colors.
- **Part 2:** Repeating Colors
In this variant, colors may repeat. The Code Breaker must guess a sequence of 4 colors, where colors can be repeated.
### Togasat solver
Togasat is a SAT solver that uses a combination of techniques to efficiently solve Boolean satisfiability problems. It is designed to handle large and complex problem instances. Some of the key features of Togasat include:
- Efficient conflict-driven clause learning (CDCL) algorithm
- Advanced variable selection heuristics
- Clause minimization and deletion techniques
- Support for parallel processing
Togasat has been used to solve a wide range of SAT problems, including those arising in formal verification, planning, and cryptography.
<br />To Know more about sat solvers you can read [here](logical_constraints.pdf).
### Solution Approach
To solve the Mastermind game, we can utilize SAT solvers to convert the problem into a Conjunctive Normal Form (CNF). This allows us to efficiently solve the problem using SAT solver algorithms.
<br />By providing an efficient solution to the Mastermind game, we can enable the Code Breaker to make intelligent guesses and ultimately break the code set by the Code Maker.
<<<<<<< HEAD
<br />You can find the full solution description [here](logical_constraints.pdf).
### Cpp solution
For **Part 1** and **Part 2**, you can refer to [task1.cpp](task1.cpp) and [task2.cpp](task2.cpp) respectively
=======
<br />You can find the full solution description [here](logical_constraints.pdf)
>>>>>>> fe8bcbad06c9ac140d313771d7c34cea78ef939e
