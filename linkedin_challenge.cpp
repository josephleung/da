/*
Can you solve this ?
You are given a deck containing N cards. While holding the deck facedown:

1. Deal all the cards facedown onto a table into Y piles like you would if you were playing with a group of people (i.e. card 1 to P1, card 2 to P2, ..., card Y to PY, card Y + 1 to P1, etc).
2. Combine all the piles into a deck by placing P1 onto P2, then P1+P2 onto P3, and so on. This is a round.
3. Pick up the deck from the table and repeat steps 1-2 until the deck is in the original order.
4. For each round, vary the pile count according to a repeating pattern. Start with 3 piles, then 4, then 5, then loop back to 3, then 4 and so on.

Write a program to determine how many rounds it will take to put a deck back into the original order. This will involve creating a data structure to represent the order of the cards. Do not use an array. This program should be written in C only. It should take a number of cards in the deck as a command line argument and write the result to stdout. Please ensure the program compiles and runs correctly (no pseudo-code). This isn't a trick question; it should be fairly straightforward.

Bonus: Output how many rounds should be completed before the deck is adequately shuffled from the original deck for a person who is casually playing a game with cards. Provide your methodology in a comment block.
*/

#include <unordered_map>
#include <list>
#include <iostream>
#include <algorithm>
#include <array> // this is only used to store the pile count pattern

/* Bonus Answer:
 * Until we know the definition of "shuffled" is, we cannot
 * determine whether the desk is adequately shuffled or not.
 * similar to how most random generators on silicon are not
 * "true" random number generators but just functions that 
 * generate psuedo-random number. Each iteration of the 
 * deal increasingly increases the randomness of the cards.
 * The most "random" the cards would at half of the deals. 
 * so if the cards to 108 deals to return to the original
 * position, then it would take 54 shuffles to reach "peak"
 * randomness. However, 2 or 3 deals would be enough for the
 * deck to be shuffled enough for play. 
 */

/// number of piles pattern
constexpr std::array<int, 3> pile_pattern = {{ 3, 4, 5 }};

/// Checks if the deck/list is in the original order
/// @param begin start iterator
/// @param end end iterator
template <typename It>
bool check_order(It begin, It end) {
    return std::is_sorted(begin, end);
}

// pretty prints the deck/list
/// @param begin start iterator
/// @param end end iterator
template <typename It>
void pretty_print(It begin, It end) {
    for ( /*  */ ;begin != end; ++begin) {
        // not going to worry about the trailing ", " here
        std::cout << *begin << ", ";
    }

    std::cout << std::endl;
}

/// takes the piles and consolidates them into one deck or pile
/// @param piles a reference to the piles of cards
/// @param num_piles the number of piles in @param piles
std::list<int> consolidate(std::unordered_map<int, std::list<int>> &piles, int num_piles) {
    // consolidate the piles. we can splice the lists
    // to save some time with mem move and allocations
    // and cause the challenge asked us to not use an array
    std::list<int> deck;
    for (int pile = 0; pile < num_piles; ++pile) {
        deck.splice(deck.end(), piles[pile]);
    }

    return deck;
}

/// distrubutes the deck into @param num_piles piles
/// @param deck the deck of cards to distribute
/// @param num_piles the number of piles in @param piles
std::unordered_map<int, std::list<int>> distribute(std::list<int> &deck, int num_piles) {
    // redistribute the cards. this is a bid different since
    // we aren't making cards anymore but using the consoldated
    // deck from the first iteration.
    std::unordered_map<int, std::list<int>> piles;
    int pile = 0;

    while (!deck.empty()) {
        int card = deck.front();
        deck.pop_front();

        piles[pile].push_front(card);
        pile = (pile + 1) % num_piles;
    }

    return piles;
}


int main(int argv, char **argc) {
    // since this ia a challenge, not going any 
    // input cleaning or error checking
    int num_cards = atoi(argc[1]);

    // the key is the pile number and the value is 
    // a list of card in that pile. Not using an array
    // cause challenge asked not to and also so we can
    // splice lists together when picking them up from
    // the table. Cards are represented by a single
    // number from [0 to num_cards)
    std::unordered_map<int, std::list<int>> piles;

    // the deck. its a list so we can splice then together
    // when consolodating and not have to "copy" the cards
    // around. the cards are represented by a single number
    std::list<int> deck;

    // populate with cards, we could do this on the fly during
    // our first distribution, but this cuts down on code redundancy
    for (int i = 0; i < num_cards; ++i){ deck.push_back(i); }

    bool original_order = false; // is deck in original order
    int num_distributed = 0; // number of times cards have been delt
    int pile_pattern_idx = 0; // index of the pile count pattern

    while (!original_order) {
        // pretty print for debugging
        pretty_print(deck.begin(), deck.end());
        
        piles = distribute(deck, pile_pattern[pile_pattern_idx]);
        deck = consolidate(piles, pile_pattern[pile_pattern_idx]);

        original_order = check_order(deck.begin(), deck.end());
        
        ++num_distributed;
        pile_pattern_idx = (pile_pattern_idx + 1) % pile_pattern.size(); // go to next pile count
    }

    std::cout << "Operation took " << num_distributed << " deals to return the deck to the original order" << std::endl;
}