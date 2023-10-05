#include "Hangman.h"
#include <string>
#include <iostream>
using namespace std;

char getLetterFromUser()
{
    char letter;
    while (true)
    {
        cout << "Make a guess: ";
        cin >> letter;

        // Clear input stream if user entered more than one character or non-character input
        if (cin.fail() || cin.get() != '\n')
        {
            cin.clear();                                         // reset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
            cout << "Invalid input. Please enter a single letter.\n";
        }
        else if (!isalpha(letter))
        {
            cout << "Invalid input. Please enter a letter.\n";
        }
        else
        {
            return letter;
        }
    }
}

int main()
{
    Hangman::printTitle();

    // Game set up (greet user, say rules, set word)
    cout << "Welcome to Hangman! Do you want to see the rules? y/[n]: ";
    string showRules;
    getline(cin, showRules);
    if (showRules == "y")
        cout << endl;
    Hangman::printRules();
    cout << endl;

    bool gameIsActive = true;
    do
    {
        // Pick word
        string theWord = "expanse";
        Hangman game(theWord);

        cout << "A random word has been chosen. It has " << theWord.length() << " letters." << endl
             << "The game begins now." << endl
             << "Good luck!" << endl
             << endl;

        while (!game.hasWon())
        {
            game.printMan();
            cout << "Turn " << game.getTurn() << ": " << game.guessProgress() << endl;
            // Ask for guess
            char guess = getLetterFromUser();

            game.guess(guess);
            cout << endl;

            bool gameIsOver = game.hasWon() || game.hasLost();

            if (!gameIsOver)
                continue;

            // Game is now over
            if (game.hasWon())
                cout << "You won!! Well done.";
            if (game.hasLost())
            {
                game.printMan();
                cout << "You lost. Better luck next time!";
            }

            cout << " The word was \"" << theWord << "\"." << endl;
            cout << "Do you want to play again? [y]/n: ";

            string playAgain;
            getline(cin, playAgain);
            if (playAgain == "n")
            {
                cout << "\nThanks for playing!" << endl;
                gameIsActive = false;
            }
            else
                cout << "\nStarting new game..." << endl;

            break;
        }

    } while (gameIsActive);
}