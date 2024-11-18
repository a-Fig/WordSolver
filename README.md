## About WordSolver
WordSolver is a command-line application designed to help you dominate word games like WordHunt on iMessage and Spellcast on Discord. By analyzing a matrix of letters, it identifies the highest-scoring words you can create, including options for letter swaps. With WordSolver, you can achieve superhuman gameplay!

## Installation
### Option 1: Compile from Source
1. Clone the project:
   
   in windows powershell run

   git clone https://github.com/a-fig/WordSolver.git
3. Open the project directory in the terminal:
   
   cd WordSolver
5. Compile the program:
   
   g++ -o program main.cpp
7. Run the program:
   
   ./program
### Option 2: Use Precompiled Binary
1. Clone the project:
   
   in windows powershell run

   git clone https://github.com/a-fig/WordSolver.git
3. Open the project directory in the terminal:
   
   cd WordSolver
5. Run the Precompiled program:
   
   ./WordSolver

## Usage
once the program has begun and loaded the word list
1. You will be prompted with "matrix>"
2. go ahead and input a string of lowercase letters on a single line and the program will turn your string into a NxN matrix of letters
3. The program will then display the 15 best words that can be made
4. The program will then ask if you'd like it to find the 5 best words with a single-letter swap, respond with 'y' or 'n'
5. If you said yes it'll also ask if you'd like it to find the 5 best words with a two-letter swap, respond with 'y' or 'n'
6. After that you will be prompted with "matrix>" again, enter '<' to end the program or enter another matrix for it to solve
