#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function declarations
void initialize_scores(int* scores, int players);
void player_input(int& money_rack, int& shooting_capability);
void simulate_shooting(int player_index, int money_rack, int shooting_capability, int& score);
void find_winner(int* scores, int players);
void start_game(int players);

int main() {
    srand(time(nullptr)); // Seed random number generator
    int play_again;

    do {
        int players;

        // Welcome message and input for number of players
        cout << "Welcome to the basketball shooting contest!" << endl;
        cout << "Enter the number of players: ";
        cin >> players;

        // Ensure there are at least 2 players
        if (players < 2) {
            cout << "You need at least 2 players to play!" << endl;
            return 1;
        }

        // Start the game
        start_game(players);

        // Ask if the user wants to play again
        cout << "Do you want to play again? (1 for yes, 0 for no): ";
        cin >> play_again;

    } while (play_again == 1); // Loop to restart the game if the user chooses to play again

    cout << "Thanks for playing!" << endl;

    return 0;
}

// Initialize scores for all players to 0
void initialize_scores(int* scores, int players) {
    for (int i = 0; i < players; i++) {
        scores[i] = 0; // Initialize scores to zero
    }
}

// Input function for player's money rack and shooting capability
void player_input(int& money_rack, int& shooting_capability) {
    // Prompt for money-ball rack (between 1 and 5)
    do {
        cout << "Where do you want to put your money-ball rack? Enter 1-5: ";
        cin >> money_rack;
    } while (money_rack < 1 || money_rack > 5);

    // Prompt for shooting capability (between 1 and 99)
    do {
        cout << "Enter your shooting capability, from 1 to 99: ";
        cin >> shooting_capability;
    } while (shooting_capability < 1 || shooting_capability > 99);
}

// Function to simulate shooting for a player
void simulate_shooting(int player_index, int money_rack, int shooting_capability, int& score) {
    cout << "Player " << player_index + 1 << ":" << endl; // Display player number

    // Loop through 5 racks
    for (int rack = 1; rack <= 5; rack++) {
        int rack_score = 0;
        cout << "Rack " << rack << ": ";

        // If the rack is the selected money-ball rack
        if (rack == money_rack) {
            // Simulate 5 money balls
            for (int j = 0; j < 5; j++) {
                if (rand() % 100 < shooting_capability) {
                    cout << "M "; // Made money ball worth 2 points
                    rack_score += 2;
                } else {
                    cout << "_ "; // Missed money ball
                }
            }
        } else {
            // Simulate 5 regular shots
            for (int j = 0; j < 5; j++) {
                if (rand() % 100 < shooting_capability) {
                    cout << "X "; // Made shot worth 1 point
                    rack_score += 1;
                } else {
                    cout << "_ "; // Missed shot
                }
            }
        }

        cout << "| " << rack_score << " pts" << endl; // Display points for the rack
        score += rack_score; // Add rack score to the total score

        // Starry rack occurs between racks 2 and 3, and 4 and 5
        if (rack == 2 || rack == 4) {
            int starry_score = 0;
            cout << "Starry: ";
            // Simulate 1 Starry ball shot
            if (rand() % 100 < shooting_capability) {
                cout << "S         "; // Made Starry ball worth 3 points
                starry_score += 3;
            } else {
                cout << "_         "; // Missed Starry ball
            }
            cout << "| " << starry_score << " pts" << endl;
            score += starry_score; // Add Starry score to the total score
        }
    }

    cout << "Total: " << score << " pts" << endl << endl; // Display total score for the player
}

// Function to find and display the winner
void find_winner(int* scores, int players) {
    int winner_index = 0; // Index of the player with the highest score

    // Loop to find the player with the highest score
    for (int i = 1; i < players; i++) {
        if (scores[i] > scores[winner_index]) {
            winner_index = i; // Update winner index
        }
    }

    // Display the winner
    cout << "Player " << winner_index + 1 << " is the winner!" << endl;
}

// Function to start the game, handle player inputs, and simulate shooting for all players
void start_game(int players) {
    // Dynamic array to store scores
    int* scores = new int[players];
    initialize_scores(scores, players); // Initialize all scores to 0

    // Loop through each player
    for (int i = 0; i < players; i++) {
        int money_rack, shooting_capability, score = 0;
        player_input(money_rack, shooting_capability); // Get player input
        simulate_shooting(i, money_rack, shooting_capability, score); // Simulate shooting for the player
        scores[i] = score; // Store the player's score
    }

    find_winner(scores, players); // Find and display the winner

    // Free the dynamically allocated memory for scores
    delete[] scores;
}
