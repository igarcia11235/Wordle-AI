//  Have the program do the guessing to discover the secret wordle word.
//
//  Author: Immanol Garcia, 12/21/23
//
//  Links to wordle dictionary words at:
//    https://www.reddit.com/r/wordle/comments/s4tcw8/a_note_on_wordles_word_list/

/* 
In the example below: 
> An asterisk ' * ' below a letter will represent the color yellow 
which is a letter within the secret word but not in the correct position. 

> Capital letters will represent a letter within the secret word and in the correct position 
*/

/*  Running the program looks like:
        Using file wordsLarge.txt with 12947 words.
        -----------------------------------------------------------

        Enter a secret word or just r to choose one at random: dream
        Trying to find secret word:
               d r e a m

            1. s o r e s
                   * *
            2. s e r e r
                 * *
            3. r a r e r
               * *   *
            4. r a r e e
               * *   *
            5. s a r e e
                 * * *
            6. p a r e r
                 * * *
            7. c a r e r
                 * * *
            8. b a r e r
                 * * *
            9. f a r e r
                 * * *
           10. D a r e r
                 * * *
           11. D e a r e
                 * * *
           12. D e b A r
                 *     *
           13. D R E A r
                       *
           14. D R E A d

           15. D R E A M

        Got it!

     ... and then it runs two more times ...
 */

#include <assert.h> // for assert() sanity checks
#include <ctype.h>  // for toupper()
#include <stdio.h>  // for printf(), scanf()
#include <stdlib.h> // for exit( -1)
#include <string.h> // for strcpy
#include <time.h>   // for time()
#include <stdbool.h> // for next variable

// Declare globals
#define WORD_LENGTH 5                    // All words have 5 letters, + 1 NULL at the end when stored
#define WORDS_FILE_NAME "wordsLarge.txt" // File containing all the possible 5 letter words to be guessed

// For debugging purposes you can uncomment this line of code below and comment #define WORDS_FILE_NAME "wordsLarge.txt"
// #define WORDS_FILE_NAME  "wordsTiny.txt" 

#define MAX_NUMBER_OF_WORDS 12947   // Number of words in the full set of words file
#define true 1                      // Make boolean logic easier to understand
#define false 0                     // Make boolean logic easier to understand

typedef struct wordCount wordCountStruct;
struct wordCount {
  char word[WORD_LENGTH + 1]; // The word length plus NULL
  int score;                  // Score for the word
};

//-----------------------------------------------------------------------------------------
// Read in words from file into array.  We've previously read the data file once
// to find out how many words are in the file.
void readWordsFromFile(
    char fileName[], // Filename we'll read from
    wordCountStruct
        *words,     // Array of words where we'll store words we read from file
    int *wordCount) // How many words.  Gets updated here and returned
{
  FILE *inFilePtr = fopen(fileName, "r"); // Connect logical name to filename
  assert(inFilePtr != NULL);              // Ensure file open worked correctly

  // Read each word from file and store into array, initializing the score for
  // that word to 0.
  char inputString[6];
  *wordCount = 0;
  while (fscanf(inFilePtr, "%s", inputString) != EOF) {
    strcpy(words[*wordCount].word, inputString);
    words[*wordCount].score = 0;
    // printf("%s\n", words[*wordCount].word); // ADDED: print statement to print
    // all the words being read and put into the allWords struct array (for debugging)
    (*wordCount)++;
  }

  // Close the file
  fclose(inFilePtr);
} // end readWordsFromFile(..)

//-----------------------------------------------------------------------------------------
// Comparator for use in built-in qsort(..) function.  Parameters are declared
// to be a generic type, so they will match with anything. This is a two-part
// comparison.  First the scores are compared.  If they are the same, then the
// words themselves are also compared, so that the results are in descending
// order by score, and within score they are in alphabetic order.
int compareFunction(const void *a, const void *b) {
  // Before using parameters we have cast them into the actual type they are in
  // our program and then extract the numerical value used in comparison
  int firstScore = ((wordCountStruct *)a)->score;
  int secondScore = ((wordCountStruct *)b)->score;

  // If scores are different, then that's all we need for our comparison.
  if (firstScore != secondScore) {
    // We reverse the values, so the result is in descending vs. the otherwise
    // ascending order return firstScore - secondScore;   // ascending order
    return secondScore - firstScore; // descending order
  } else {
    // Scores are equal, so check words themselves, to put them in alphabetical
    // order
    return strcmp(((wordCountStruct *)a)->word, ((wordCountStruct *)b)->word);
  }
} // end compareFunction(..)

// -----------------------------------------------------------------------------------------
// Find a secret word
void findSecretWord(wordCountStruct allWords[], // Array of all the words
                    int wordCount,     // How many words there are in allWords
                    char secretWord[]) // The word to be guessed
{
  char startingGuessWord[ 6] = "soare";  // array to hold best starting word
  char secretWordCopy[6];
  char secretWordCopy3[6];
  char allWordsCopy[6];
  char allWordsCopy2[6];
  char finalLetter[6];

  printf("Trying to find secret word: \n");
  // Display secret word with a space between letters, to match the guess words
  // below.
  printf("       ");
  for (int i = 0; i < WORD_LENGTH; i++) {
    printf("%c ", secretWord[i]);
  }
  printf("\n");
  printf("\n");

  int guessNumber = 1; // increment the current number of guesses
  
  // ******************
  // NOTE: allWords[0].word is the current best guess word which changes after each scoring iteration shown below. 
  // Once qsort() is called a new guess word (allWords[0].word) with the highest score will be used.
  // ******************
  
  // Loop until the secretWord is found
  while (strcmp(allWords[0].word, secretWord) != 0) {
    // for loop that interates through the allWords array until a guess word (allWords[0].word) matches the secretWord
    for (int i = 0; i < wordCount; i++) {
      // qsort to sort the array after being scored after each iteration
      qsort(allWords, wordCount, sizeof(wordCountStruct), compareFunction);

      // guess word will always be the first indexed word of a newly sorted list (allWords[0].word)
      strcpy(allWordsCopy, allWords[0].word);

      // copying secret word in order to blank
      strcpy(secretWordCopy, secretWord);
      strcpy(secretWordCopy3, secretWord);

      // prints the current guess number
      printf("%d. ", guessNumber);

      for (int k = 0; k < 5; k++) {
        
      // if guess word letter is not an exact match to secretWord then it just prints the letter normally (lower case)
      if (allWordsCopy[k] == secretWordCopy[k]) {

        // Adjust scores for exact matches
        for (int m = 0; m < wordCount; m++) {
            strcpy(allWordsCopy2, allWords[m].word);
            if (allWordsCopy2[k] == secretWordCopy[k]) {
                allWords[m].score += 3;
            }
        }
        // ANSI escape code for green color
        printf("\033[1;32m"); // Start green color
        printf("%c ", toupper(allWordsCopy[k])); // Print capitalized letter in green
        printf("\033[0m"); // Reset color to default
        // Blank out matches so the letter isn't read again

        allWordsCopy[k] = ' ';
        secretWordCopy[k] = ' ';
        secretWordCopy3[k] = ' ';
    } else {
      for (int j = 0; j < 5; j++) {
            if (allWordsCopy[k] == secretWordCopy3[j] && allWordsCopy[j] != secretWordCopy3[j] ) {
                // ANSI escape code for yellow color
                printf("\033[1;33m"); // Start yellow color
                printf("%c ", toupper(allWordsCopy[k])); // Print capitalized letter in yellow
                printf("\033[0m"); // Reset color to default
                secretWordCopy3[j] = ' ';
                break;
            }
            else if(j == 4) {
              printf("%c ", allWordsCopy[k]); // Print the letter normally (not found in secret word)
              break;
            }
        }

        // Adjust scores for exact matches or non-matches as before
        for (int m = 0; m < wordCount; m++) {
            strcpy(allWordsCopy2, allWords[m].word);
            if (allWordsCopy[k] == allWordsCopy2[k]) {
                allWords[m].score -= 3;
            }
        }
        
    }
}
printf("\n");

      // Find matching letter in a different position.  Letters that were exact matches have already been blanked out.
      for (int i = 0; i < 5; i++) {
        char c = allWordsCopy[i];
        // Only consider non-blanks
        if (c != ' ') {
          // Step through each possible matching character.
          for (int j = 0; j < 5; j++) {
            //  blank out letter so it is not reused. After a match is found,
            //  break out of comparison loop so that letter does not count for
            //  scoring more than once.
            if (c == secretWordCopy[j]) {
              // for loop to to compare asterisk letter to all the words in allWords to see if a non-exact matching word can be found in allWords and then scores it to += 2
              for (int m = 0; m < wordCount; m++) {
                strcpy(allWordsCopy2, allWords[m].word);
                if (c == allWordsCopy2[j]) {
                  allWords[m].score += 2;
                  //break;
                }
              }
              allWordsCopy[i] = ' ';
              secretWordCopy[j] = ' ';
              break;
            }
            else
            {
              // if no matching letters are found whatsoever a score of -= 1 is given 
              for (int m = 0; m < wordCount; m++)
          {
            strcpy(allWordsCopy2, allWords[m].word);
            if (c != allWordsCopy2[j])
              {
                 
                 allWords[m].score -= 1;
                 break;
              }
          }
            }
          } // end for( int j ...)
        }   // end if( c...
      }     // end for( int i...

      // if statements to put appropriate amount of spaces infront of the display asterisks
      if (guessNumber < 10) {
        printf("   ");
      }
      if (guessNumber > 9 && guessNumber < 100) {
        printf("    ");
      }
      if (guessNumber > 100 && guessNumber < 1000) {
        printf("     ");
      }
      if (guessNumber > 1000 && guessNumber < 10000) {
        printf("      ");
      }
      if (guessNumber > 10000) {
        printf("       ");
      }
      
      printf("\n");

      // increment guess number at the end of each iteration
      guessNumber++;

      // for loop that checks the non-blanked word letters from allWordsCopy to every single word letter in the allWords array and if a non-blanked letter matches with any letter from any word from the allWords array that word is then decremented by -1
      for(int j = 0; j < wordCount; j++)
        {
          strcpy(allWordsCopy2, allWords[j].word);
      for(int w = 0; w < 5; w++)
        {
          for(int h = 0; h < 5; h++)
            {
              if(allWordsCopy[w] == allWordsCopy2[h])
              {
                allWords[j].score -= 1;
              }
            }
          }
      }
      
      // if the guess word is an exact match then break out of both the for & while loop 
      if (strcmp(allWords[0].word, secretWord) == 0) {
        printf("Got it!\n");
        break;
      }
      
    } // end for( int i...)
    //break; // if while loop is acting up with the parameters just use the break to cut out of loop
  } // end while( strcmp()... )
} // end findSecretWord

// -----------------------------------------------------------------------------------------
int main() {
  char wordsFileName[81]; // Stores the answers file name

  strcpy(wordsFileName,
         WORDS_FILE_NAME); // Set the filename, defined at top of program.

  srand((unsigned)time(
      NULL)); // Seed the random number generator to be current time

  // Declare space for all the words, of a maximum known size.
  wordCountStruct allWords[MAX_NUMBER_OF_WORDS];

  // Start out the wordCount to be the full number of words.  This will decrease
  // as
  //    play progresses each time through the game.
  int wordCount = 0; // MAX_NUMBER_OF_WORDS MAYBE CHANGE TO MAX

  // The secret word that the computer will try to find, plus the return
  // character from fgets.
  char secretWord[WORD_LENGTH + 1];
  char userInput[81]; // Used for menu input of secret word

  // Read in words from file, update wordCount and display information
  readWordsFromFile(wordsFileName, allWords, &wordCount);
  printf("Using file %s with %d words. \n", wordsFileName, wordCount);

  // Run the word-guessing game three times
  for (int i = 0; i < 3; i++) {
    // Reset secret Word
    strcpy(secretWord, "");
    // Display prompt
    printf("-----------------------------------------------------------\n");
    printf("\n");
    printf("Enter a secret word or just r to choose one at random: ");
    scanf(" %s", userInput);
    // Eliminate the return character at end or userInput if it is there
    int length = (int)strlen(userInput);
    if (userInput[length] == '\n') {
      userInput[length] = '\0';
    }
    strcpy(secretWord, userInput); // Store the secret word from user input

    // If input was 'r' then choose a word at random.
    if (strlen(secretWord) <= 1) {
      // Randomly select a secret word to be guessed.
      int randomIndex = rand() % wordCount;
      strcpy(secretWord, allWords[randomIndex].word);
    }

    // Run the game once with the current secret word
    findSecretWord(allWords, wordCount, secretWord);
  }

  printf("Done\n");
  printf("\n");
  return 0;
} // end main()