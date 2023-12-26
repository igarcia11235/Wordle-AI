<div align="center">
<pre>
  _        ___   ___   ___   _     ____       __    _ 
 \ \    / / / \ | |_) | | \ | |   | |_       / /\  | |
  \_\/\/  \_\_/ |_| \ |_|_/ |_|__ |_|__     /_/--\ |_|
 -------------------------------------------------------
Intelligent Word Guessing in C
</pre>

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

</div>

This C program simulates an AI player for the popular word-guessing game Wordle. The program attempts to guess the secret word through intelligent guesswork and scoring mechanisms.

## Overview
- **Algorithm Approach**: The AI utilizes a scoring system to refine its guesses and improve accuracy by comparing word similarity and positions.

## How it Works

1. **Word Selection**: The program can either accept a user-input secret word or randomly choose one from a provided word list.
2. **Scoring System**:
   - Exact Letter Matches: Correct letters in the correct position are colored green and displayed in uppercase. For each correct letter in the correct position, the score for related words is increased.
   - Partial Letter Matches: Letters in the secret word but not in the correct position are colored yellow and displayed in uppercase. Partial matches help narrow down possibilities but aren't in the correct positions, influencing the AI to reconsider letter placements.
   - No Letter Matches: Letters in the guessed word that do not match any letter in the target word are displayed lowercase and receive a negative score.
3. **Iteration & Refinement**: The AI continuously refines its guesses based on the accumulated scores, discarding less likely words and favoring those with higher scores.


## Files Included

- `wordleAI.c`: The main C file containing the Wordle AI logic.
- `wordsLarge.txt`: File containing a substantial 5-letter word list used for guessing.
- `wordsTiny.txt` (commented out): Smaller 5-letter word list used for debugging purposes.

## Running the Program

1. Compile the C file using a C compiler. (e.g., GCC).
2. Run the compiled executable.
3. Provide a secret word or select 'r' for a random word.
4. Observe the AI's guessing process and scoring until the secret word is found.
5. The program runs the guessing process three times, refining its strategies with each iteration.


## Installation Instructions
When you execute the program, follow these steps to interact with the game:

1. Compile the Program:
- Compile the program using a C compiler (e.g., GCC).
- For example: gcc main.c -o wordle_ai

2. Run the Program:
- Execute the compiled program.
- For example: ./wordle_ai

3. Follow Game Instructions:
- Provide a secret word or select 'r' for a random word to be given to the computer.
- Observe the AI's guessing process and scoring until the secret word is found.
- The program runs the guessing process three times, using the previous secret word as a starting guess word with each iteration.
-
-
-
- You'll receive instructions on how to play the game by entering 'D' as soon as you run the executable or you can follow the game instructions outlined in this ReadMe.md
- Enter commands accordingly and follow the prompts to interact with the game environment.

## Notes

- The program utilizes a smart guessing mechanism by comparing guessed words with the secret word and refining its choices based on scoring.
- The scoring system guides the AI in making informed guesses to arrive at the correct word.

---

Feel free to adapt and expand this description to fit the specific details, nuances, or additional features of your program.
