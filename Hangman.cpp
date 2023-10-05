#include "Hangman.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
using namespace std;

Hangman::Hangman(const string &word)
    : word(word), guessed(word.size(), false), guesses(""), turn(1), hits(0), mistakes(0) {}

string Hangman::getWord() const { return word; }
string Hangman::getGuesses() const { return guesses; }
int Hangman::getTurn() const { return turn; }
int Hangman::getHits() const { return hits; }
int Hangman::getMistakes() const { return mistakes; }

void Hangman::guess(char letter)
{
    turn++;

    // Check if player already guessed letter
    if (find(guesses.begin(), guesses.end(), letter) != guesses.end())
    {
        cout << "Letter already guessed." << endl;
        return;
    }

    // Scan word for letter matches
    bool correct = false;
    for (size_t i = 0; i < word.length(); ++i)
    {
        if (word[i] != letter)
            continue;

        guessed[i] = true;
        correct = true;
    }
    guesses += letter;

    (correct) ? hits++ : mistakes++;
}

void Hangman::printMan() const
{
    string line1 = " ", line2 = " ", line3 = " ", line4 = " ";

    line1 = (mistakes >= 1) ? " (_) " : "     ";
    line3 = (mistakes >= 2) ? "  |  " : "     ";

    line2 = " ";
    (mistakes >= 3) ? line2 += "\\" : line2 += " ";
    (mistakes >= 2) ? line2 += "|" : line2 += " ";
    (mistakes >= 4) ? line2 += "/" : line2 += " ";

    line4 = " ";
    (mistakes >= 5) ? line4 += "/ " : line4 += " ";
    (mistakes >= 6) ? line4 += "\\" : line4 += " ";

    cout << "    _______  " << endl;
    cout << "   |/      | " << endl;
    cout << "   |     " << line1 << endl;
    cout << "   |     " << line2 << endl;
    cout << "   |     " << line3 << endl;
    cout << "   |     " << line4 << endl;
    cout << "   |     " << endl;
    cout << "___|___  " << endl;
}

void Hangman::printRules()
{
    cout << "The rules: " << endl;
    cout << "    - Guess one letter at a time." << endl
         << "    - Repeat guesses aren't penalized." << endl;
}

void Hangman::printTitle()
{
    cout << " _                                                 " << endl
         << "| |                                                " << endl
         << "| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __      " << endl
         << "| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ " << endl
         << "| | | | (_| | | | | (_| | | | | | | (_| | | | |    " << endl
         << "|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_| " << endl
         << "                    __/ |                          " << endl
         << "                   |___/                           " << endl;
}

bool Hangman::hasWon() const
{
    return find(guessed.begin(), guessed.end(), false) == guessed.end();
}

bool Hangman::hasLost() const
{
    return mistakes >= 6;
}

string Hangman::guessProgress() const
{
    string wordProgress;
    for (size_t i = 0; i < word.length(); ++i)
    {
        if (guessed[i])
            wordProgress += word[i];
        else
            wordProgress += "_";
    }
    return wordProgress;
}
