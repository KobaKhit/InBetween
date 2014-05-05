#InBetween
##User manual 
This program plays the card game In Between with the user. The user will be first asked whether he/she wants the ace to be ranked as the highest or the lowest card in the game.  Then the user is dealt two cards and asked if he thinks that the next card is going to be in between. After user responds the program deals the card and informs the user whether he lost or won. Then the program deals two cards. The game continues until there are no cards left in the deck. At the end the program informs the user of his/her win-lose record.

##System manual
The program has two global variables: `MY_RAND_MAX` and `NEXT_MY_RAND`.  `MY_RAND_MAX`  is an integer set to 16807 and is used by the `my_rand ()` function to produce random integers in the interval [1, 16807).  `NEXT_MY_RAND` is an unsigned integer type set to 1 and is used by `my_srand()` function to initialize the random generating function `my_rand()`.
The program has ten prototypes:

1.	`string card_name(int card)`
Takes in an integer in the range 0..51, designating a card from a standard bridge deck. Returns the name of its argument (ex.g. 2 for of Spades, Jack for Jack of clubs).

2.	`int card_ranking(int card)`
Takes in an integer in the range 0..51, designating a card from a standard bridge deck. Returns the rank of its argument  (e.g, returns 2 for "2 of spades", 11 for "Jack of Clubs", ...).

3.	`string card_suit(int card)`
Takes in an integer in the range 0..51, designating a card from a standard bridge deck. Returns the suit of its argument (e.g, returns "Spades" for "2 of Spades", "Clubs" for "Jack of Clubs", ...).

4.	`int my_rand(void)`
Does not take any arguments. It is my implementation of the random number generation algorithm “Real Version 2” from the paper "Random number generators: Good ones are hard to find" by Park and Miller.
Generates a random integer between in the interval [1, MY_RAND_MAX).

5.	`void my_srand(unsigned int seed)`
This routine is used to initialize the sequence of random numbers produced by `my_rand()`. Takes an integer used to provide the next random number in sequence. It has a side effect that alters the global variable, NEXT_MY_RAND. 

6.	`randomize(int seed)`
Takes in an integer that is used as a seed for the `my_rand()` function. When provided 0 arguments, it sets the system random number generator `my_rand()` to a random seed based on the current clock time. When provided 1 argument, it uses that argument as a seed for `my_rand()`.

7.	`vector<int> initDeck()`
Does not take any arguments. Initializes a vector of 52 cards where the elements of a vector are integers in the interval [0,1,2,...,51]. It uses a for loop that every nth iteration inserts the n number to the end of the vector.

8.	`void shuffleDeck(vector<int> &deck)`
Takes in a vector passed by reference. Shuffles a vector by swapping the nth element in vector with the ith element where n is set to the number of elements in the vector and i is a randomly generated integer by function `my_rand()`. After every swap n is decreased by 1. The swapping continues until n is zero.

9. & 10.	`int min(int a, int b) and int max(int a, int b)`
Both take in two integers. `min(a,b)` returns the smaller of the two and `max(a,b)` does the opposite.


Before I start explaining the program I want to indicate what cards correspond to what integers in the interval [0,51]. Let the numbers 0...12 designate Ace through King of Spades, 13...25 designate Ace through King of Hearts, 26...38 designate Ace through King of Clubs, and 39...51 designate Ace through King of Diamonds.	
The program starts with outputting the user manual and asking if the user wants Ace to be ranked as the highest or the lowest card. User should input “h” for highest or “l” for lowest.  The program will keep asking for input using a while loop until user inputs either “h” or “l”. Then, the program calls the procedure `randomize()` which sets the random number generator `my_rand()` to a random seed based on the current clock time. Then the program produces a vector of 52 integers from 0 to 51 and stores that vector in the variable called `cardDeck` which represents a deck of cards. After the card deck is produced the program calls the procedure `shuffleDeck()` which takes a vector `cardDeck`  and shuffles it. After that the program does a while loop which plays the game until there are no cards left in the deck. Eevery iteration the three integers from the end of the vector `cadDeck` are stored in variables `card1`, `card1`, `userCard`. The program outputs the names of  cards using the `card_name()` function. Then the ranks of those cards are stored in variables `card1Rank`, `card1Rank`, `userCardRank` using the `card_ranking()` function. Then  the program uses an if statement that sets the rank of  the ace as the highest or the lowest based on user’s response in the beginning of the program. Since ace is the 13th card (assuming we start our count from 0) the if statement changes the rank of cards that correspond to integers divisible by 13 only, i.e. aces. Then the program determines whether the rank of the users card is in between the ranks of the other cards using the if else if statement. The program outputs whether user won or lost and stores wins and losses and outputs the record in the end of the game. At the end of each iteration the last three elements are removed from the end of the `cardDeck` vector and then the `cardDeck` vector is shuffled. After there are no more cards left user is presented with his win-loss record.

####Running CardTricks
The program `CarTricks.cpp` runs in XCode and Microsoft Visual Studio 2010. Just download it or copy paste it, and run it.

##Test Log
Below is the screen shot of what the end of the program looks like in MVS 2010
![screen](http://i.imgur.com/gTq6cDm.png?1)













