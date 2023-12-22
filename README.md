# Wordle AI in C

This C program simulates an AI player for the popular word-guessing game Wordle. The program attempts to guess the secret word through intelligent guesswork and scoring mechanisms.

## Overview

- **Author**: Immanol Garcia
- **Date**: 12/21/23
- **Algorithm Approach**: The AI utilizes a scoring system to refine its guesses and improve accuracy by comparing word similarity and positions.

## How it Works

1. **Word Selection**: The program can either accept a user-input secret word or randomly choose one from a provided word list.
2. **Guessing Mechanism**: The AI employs a strategy to guess the secret word, displaying each guess and its scoring.
3. **Scoring System**:
   - Correct letters in the correct position are displayed in uppercase.
   - Letters in the secret word but not in the correct position are represented by lowercase letters.
4. **Iteration & Refinement**: The AI refines its guesses based on the scoring received and adjusts subsequent guesses accordingly.

## Files Included

- `wordleAI.c`: The main C file containing the Wordle AI logic.
- `wordsLarge.txt`: File containing a substantial word list used for guessing.
- `wordsTiny.txt` (commented out): Smaller word list for debugging purposes.

## Running the Program

1. Compile the C file using a C compiler.
2. Run the compiled executable.
3. Provide a secret word or select 'r' for a random word.
4. Observe the AI's guessing process and scoring until the secret word is found.
5. The program runs the guessing process three times, refining its strategies with each iteration.

## Notes

- The program utilizes a smart guessing mechanism by comparing guessed words with the secret word and refining its choices based on scoring.
- The scoring system guides the AI in making informed guesses to arrive at the correct word.

---

Feel free to adapt and expand this description to fit the specific details, nuances, or additional features of your program.
