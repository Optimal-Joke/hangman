#include <string>
#include <vector>
using namespace std;

#ifndef HANGMAN_H
#define HANGMAN_H

class Hangman
{
private:
    const string word;
    vector<bool> guessed;
    string guesses;
    int turn;
    int hits;
    int mistakes;

public:
    Hangman(const string &word);

    static void printRules();
    static void printTitle();

    string getWord() const;
    string getGuesses() const;
    int getTurn() const;
    int getHits() const;
    int getMistakes() const;

    void guess(char letter);
    void printMan() const;
    bool hasWon() const;
    bool hasLost() const;
    string guessProgress() const;
};

#endif