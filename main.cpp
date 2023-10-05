#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
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

    string getWord() const { return word; }
    string getGuesses() const { return guesses; }
    int getTurn() const { return turn; }
    int getHits() const { return hits; }
    int getMistakes() const { return mistakes; }

    void guess(char letter);
    void printMan() const;
    bool hasWon() const;
    bool hasLost() const;
    string guessProgress() const;
};

Hangman::Hangman(const string &word)
    : word(word), guessed(word.size(), false), guesses(""), turn(1), hits(0), mistakes(0) {}

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

    return 0;
}