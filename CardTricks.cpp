// This program plays a game of "In Between" with the user. The user is asked first if he/she wants
// the ace to be ranked as the highest or lowest card in the game. After that the game starts and
// the program deals two cards and asks the user if he/she thinks that the next card will be in between.
// The game continues until there are no more cards left. The program stores cards in a vector.
// The vector of cards is shuffled using a random number generator algorithm from the paper "Random
// number generators: Good ones are hard to find" by Park and Miller.

// Author: Koba Khitalsihvili
// Date: 3/10/2014

#include<vector>
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<math.h>

using namespace std;

//------------------------------------------------------------------------------------------
//-------------Global variables-----------------------------------------------------------
//-----------------------------------------------------------------------------------------
// Used to generate the next random number
// in the sequence.
// Is used by my_rand()
unsigned int NEXT_MY_RAND = 1;

// The upper bound for my_rand() random number integer generator
int MY_RAND_MAX = 16807;
//-------------------------------------------------------------------------------------------------------
//---------------Prototypes---------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// Decription of the subprograms is in the Subprogram section
string card_name(int card);

int card_ranking(int card);

string card_suit(int card);

void randomize(int seed = 0);

int my_rand(void);

void my_srand(unsigned int seed);

vector<int> initDeck();

void shuffleDeck(vector<int> &deck);

int min(int a, int b);

int max(int a, int b);

//---------------------------------------------------------------------------------------------
//----------------------MAIN PROGRAM----------------------------------------------------------
//----------------------------------------------------------------------------------------------

int main(void)
{
	// User manual
	cout << "You are about to play the card game In Between. You will be dealt\ntwo cards."
    << " Your objective is to determine whether the next card dealt\nwill be in between."
    << " If it is you win. If it is not you lose. The dealt\ncards are removed from "
    << "the deck and the game continues. At the end you\nwill be presented with a win-lose"
    << " record. Good luck!" << endl << endl;
	// Asks user if he/she wants the Ace to be the highest or the lowest
	string userAce;
	cout << "Before we start the game, please let me know whether you want the ace\n"
    << "to be the highest or the lowest ranked card. (h/l): ";
	cin >> userAce;
	// Keeps prompting user to enter either h or l
	while((userAce != "h") && ( userAce != "l")) {
		cout << "Please, enter either h or l: ";
		string userAcee;
		cin >> userAcee;
		userAce = userAcee;
	}
	cout << endl << "-------------------------------------" << endl;
    
	// Sets seed of the my_rand() function to the time at which it is called
	randomize();
    
	// Initializes a vector of integers from 0 to 51 that represents a deck of 52 cards
	vector<int> cardDeck= initDeck();
 	
	// Shuffles the deck
	shuffleDeck(cardDeck);
    
	// Plays game
	int win = 0, lost = 0, // win-lose record
    counter = cardDeck.size();
	
	while(counter >= 3)
	{
		// Deals three random cards from the end of the vector
		int card1 = cardDeck[counter - 1]; // deals the last card in vector
		int card2 = cardDeck[counter - 2]; // deals the prelast card in vector
		int userCard = cardDeck[counter - 3]; // deals the card befor the prelast in vector, user's card
		
		cout << "Your cards are\n";
		cout << "  " << card_name(card1) + " of " + card_suit(card1)
        << setw(20) << card_name(card2) + " of " + card_suit(card2)
        << "\nDo you think the next card will lie between these?(y/n): ";
		string userIn; // user answer
		cin >> userIn;
        
		cout << "Your next card is: " << endl << "  "
        << card_name(userCard) + " of " + card_suit(userCard);
        
		// Determines the ranks of the cards
		int card1Rank = card_ranking(card1),
        card2Rank = card_ranking(card2),
        userCardRank = card_ranking(userCard);
		// Assigns highest or lowest rank to the Ace based on users choice in the beginning
		if(userAce == "l" & (card1 % 13 ==0 || card2 % 13 == 0 || userCard % 13 == 0))
		{
			if(card1 % 13 == 0) {card1Rank = card_ranking(card1) - 13;}
			if(card2 % 13 == 0) {card2Rank = card_ranking(card2) - 13;}
			if(userCard % 13 == 0) {userCardRank = card_ranking(userCard) - 13;}
		}
		// Determines whether the user won and updates the win-lose record
		bool a = (userCardRank > min(card1Rank,card2Rank)) & (userCardRank < max(card1Rank,card2Rank));
		if((a & userIn == "y") || (!a & userIn == "n")) {
			win += 1;
			cout << endl << endl << "You win!" << endl << "-------------------------------------" << endl;
		} else if((!a & userIn == "y") || (a & userIn == "n")) {
			lost += 1;
			cout << endl << endl << "You lose." << endl << "-------------------------------------" << endl;
		}
        
		// Removes dealt cards from the end of the vector
		cardDeck.pop_back();
		cardDeck.pop_back();
		cardDeck.pop_back();
		
		// Updates counter
	    counter = cardDeck.size();
        
		// Shuffle deck
		shuffleDeck(cardDeck);
	}
    
	// Outputs the win-lose record
	cout << endl << setw(4) << "........" << endl
    << "-------------------------------------" << endl << "Total wins: " << win
    << ",  Total lost: " << lost << endl << endl;
    
	return 0;
}



//----------------------------------------------------------------------------------------------------
//-----------------Subprograms-----------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

string card_name(int card)
{	// Arguments
	//    card - an integer in the range 0..51, designating a card from a
	//           standard bridge deck.
	// Returns the name of its argument
	// (e.g, returns "2" for "2 of Spades", "Jack" for "Jack of Clubs", ...)
    
	string cardname = "";
	string jack = "Jack", queen = "Queen", king = "King", ace = "Ace";
	// Determines the card name based on intervals [0,12],[13,25],[26,38],[39,51]
	if((card >= 0) & (card <=12)) // interval [0,12]
	{
		switch(card){
            case 0: cardname = ace; break;
            case 10: cardname = jack; break;
            case 11: cardname = queen; break;
            case 12: cardname = king; break;
            default: cardname = to_string(static_cast<long long>(card+1));
                
		}
	}
	else if((card >= 13) & (card <= 25)) // interval [13,25]
	{
		switch(card - 13){
            case 0: cardname = ace; break;
            case 10: cardname = jack; break;
            case 11: cardname = queen; break;
            case 12: cardname = king; break;
            default: cardname = to_string(static_cast<long long>(card-12));
                
		}
	}
	else if((card >= 26) & (card <= 38)) // interval [26,38]
	{
		switch(card - 26){
            case 0: cardname = ace; break;
            case 10: cardname = jack; break;
            case 11: cardname = queen; break;
            case 12: cardname = king; break;
            default: cardname = to_string(static_cast<long long>(card-25));
                
		}
	}
	else if((card >= 39) & (card <= 51)) // interval [39,51]
	{
		switch(card - 39){
            case 0: cardname = ace; break;
            case 10: cardname = jack; break;
            case 11: cardname = queen; break;
            case 12: cardname = king; break;
            default: cardname = to_string(static_cast<long long>(card-38));
                
		}
	}
    
	return cardname;
}
//////////////////////////////////////////////////////////
int card_ranking(int card)
{	// Arguments
	//    card - an integer in the range 0..51, designating a card from a
	//           standard bridge deck.
	// Returns the rank of its argument
	// (e.g, returns 2 for "2 of spades", 11 for "Jack of Clubs", ...)
	int cardrank;
	// Determines the card rank based on intervals [0,12],[13,25],[26,38],[39,51]
	if((card >= 0) & (card <=12))
	{
		switch(card){
            case 0: cardrank = 14; break;
            case 10: cardrank = 11; break;
            case 11: cardrank = 12; break;
            case 12: cardrank = 13; break;
            default: cardrank = (card+1);
                
		}
	}
	else if((card >= 13) & (card <= 25))
	{
		switch(card - 13){
            case 0: cardrank = 14; break;
            case 10: cardrank = 11; break;
            case 11: cardrank = 12; break;
            case 12: cardrank = 13; break;
            default: cardrank = (card - 12);
                
		}
	}
	else if((card >= 26) & (card <= 38))
	{
		switch(card - 26){
            case 0: cardrank = 14; break;
            case 10: cardrank = 11; break;
            case 11: cardrank = 12; break;
            case 12: cardrank = 13; break;
            default: cardrank = (card - 25);
                
		}
	}
	else if((card >= 39) & (card <= 51)) {
		switch(card - 39){
            case 0: cardrank = 14; break;
            case 10: cardrank = 11; break;
            case 11: cardrank = 12; break;
            case 12: cardrank = 13; break;
            default: cardrank = (card - 38);
                
		}
	}
	return cardrank;
    
}
///////////////////////////////////////////////////////////////////////////////
string card_suit(int card)
{	// Arguments
	//    card - an integer in the range 0..51, designating a card from a
	//           standard bridge deck.
	// Returns the suit of its argument
	// (e.g, returns "Spades" for "2 of Spades", "Clubs" for "Jack of Clubs", ...)
    
	string cardsuit = "";
	string spades = "Spades", clubs = "Clubs", diamonds = "Diamonds", hearts = "Hearts";
	// Determines the card suit based on intervals [0,12],[13,25],[26,38],[39,51]
	if((card >= 0) & (card <=12)) {cardsuit = spades;}
	else if((card >= 13) & (card <= 25)) {cardsuit = hearts;}
	else if((card >= 26) & (card <= 38)) {cardsuit = clubs;}
	else if((card >= 39) & (card <= 51)) {cardsuit = diamonds;}
    
	return cardsuit;
}
//////////////////////////////////////////////////////////////////////////
void my_srand(unsigned int seed)
{	// This routine is used to initialize the
	// sequence of random numbers produced by
	// my_rand()
	//
	// Arguments:
	//   seed - used to provide the next random
	//          number in sequence.
	//          Supply any number here.
	// Side Effect:
	//   Alters the global variable, NEXT_MY_RAND
	
	NEXT_MY_RAND = seed;
}

///////////////////////////////////////////////////////////////////////////
int my_rand(void)
{	// Arguments - none.
	// My implementation of the random number generation algorithm from the paper
	// "Random number generators: Good ones are hard to find" by Park and Miller.
	// Generates a random integer between 1 and a global variable MY_RAND_MAX.
    
	long double a = MY_RAND_MAX,
    m = 2147483647.0,
    q = 127773.0,
    r = 2836.0,
    lo,
    hi,
    test;
    
    hi = floor((NEXT_MY_RAND / 127773.0) + 0.5); // is equivalent to Trunc(seed/q) in the original algorithm
    lo = NEXT_MY_RAND - q * hi;
    test = a * lo - r * hi;
    
    if(test > 0.0) {NEXT_MY_RAND = test;}
    else{NEXT_MY_RAND = test + m;}
    
    long double random_real =  NEXT_MY_RAND / m; // the random floating point number between 0 and 1
	int random_int = floor(random_real * a + 0.5); // random integer between 1 and a where a is 16807
    
    return(random_int);
}
///////////////////////////////////////////////////////////////////////////////
void randomize(int seed )
{	// Arguments
	//      seed - an integer that is used as a seed for the my_rand() function
	// When provided 0 arguments, it sets the system random number generator
	// my_rand() to a random seed based on the current clock time. When provided 1 argument,
	// it uses that argument as a seed for my_rand().
    
	if(seed == 0)
	{
		my_srand((unsigned int) time(0));
	}
	else {my_srand(seed);}
}
//////////////////////////////
vector<int> initDeck()
{ // Initializes a vector of 52 cards (0,1,2,...,51)
	vector<int> cardDeck;
	for(int i = 0;i <= 51; i++)
	{
		cardDeck.push_back(i); // adds a card to the end of vector in each iteration
	}
    
	return cardDeck;
}
/////////////////////////////////
void shuffleDeck(vector<int> &deck)
{	// Arguments
	//    deck - a vector with cards passed by reference.
	// Shuffles a vector by swapping the nth element in vector with the ith element where
	// n is set to the size of the vector and i is a randomly generated integer by function my_rand().
	// After every swap n is decreased by 1.
    
	int n = deck.size() - 1, // sets n to 51
    i = 0;
	while(n >= 0)
	{
		// generates random integers in interval [0,n]
		i = static_cast<int>(my_rand() / static_cast<double>(MY_RAND_MAX + 1) * n);
		// swaps the ith and nth cards in vector																	
		int a = deck[i],													
        b = deck[n];
		deck[i] = deck[n];
		deck[n] = a;
        
        n=n-1; // decreases n by 1
	}
}
/////////////////////////
int min(int a, int b)
{	// Arguments 
	//		a,b - integers
	// Returns the smallest of two
	int min;
	if(a < b || a == b) {min = a;}
	else{min = b;}
    
	return min;	 
}
/////////////////////////
int max(int a,int b)
{	// Arguments
	//		a,b - integers
	// Returns the greatest of two
	int max;
	if(a > b || a == b) {max = a;}
	else{max = b;}
    
	return max;	 
}