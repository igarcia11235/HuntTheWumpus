/*
 ---------------------------------------------
    Program: Hunt The Wumpus

    Course: CS 211, UIC, Fall 2022
    Author: Immanol Garcia
 ---------------------------------------------
*/

#include <stdio.h>
#include <stdbool.h>    // for the bool type in C
#include <stdlib.h>     // for srand
#include <ctype.h>      // for toupper()

// global constants
#define MAX_LINE_LENGTH 81
#define NUMBER_OF_ROOMS 20

// Room connection values are set as global constants, and don't need to be passed.
// The rooms array is indexed from 0..22, but we don't use the 0th entry and
// only use 1..20.  This approach helps prevent off-by-one indexing errors.

// Used to more conveniently pass all game information between functions.
struct GameInfo {
    int moveNumber;  // Counts up from 1, incrementing for each move
    int personRoom;  // Room 1..20 the person currently is in
    int wumpusRoom;  // Room 1..20 the Wumpus is in
    int pitRoom1;    // Room 1..20 the first pit is in
    int pitRoom2;    // Room 1..20 the second pit is in
    int batRoom1; // ADDED: Room 1..20 the first bat is in
    int batRoom2; // ADDED: Room 1..20 the second bat is in
    int arrow; // ADDED: -1 if arrow is with player, else room number 1..20

    //Initializing the game to have: person, Wumpus, pit1, pit2, bat1, bat2, arrow all in distinct random rooms
};

// Function prototype needed to allow calls in any order between
void checkForHazards(struct GameInfo *theGameInfo, bool *personIsAlive, int** Rooms);

//--------------------------------------------------------------------------------
void displayCave()
{
    printf( "\n"
            "       ______18______             \n"
            "      /      |       \\           \n"
            "     /      _9__      \\          \n"
            "    /      /    \\      \\        \n"
            "   /      /      \\      \\       \n"
            "  17     8        10     19       \n"
            "  | \\   / \\      /  \\   / |    \n"
            "  |  \\ /   \\    /    \\ /  |    \n"
            "  |   7     1---2     11  |       \n"
            "  |   |    /     \\    |   |      \n"
            "  |   6----5     3---12   |       \n"
            "  |   |     \\   /     |   |      \n"
            "  |   \\       4      /    |      \n"
            "  |    \\      |     /     |      \n"
            "  \\     15---14---13     /       \n"
            "   \\   /            \\   /       \n"
            "    \\ /              \\ /        \n"
            "    16---------------20           \n"
            "\n");
}


//--------------------------------------------------------------------------------
void displayInstructions()
{
    printf( "Hunt the Wumpus:                                             \n"
            "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
            "room has 3 tunnels leading to other rooms.                   \n"
            "                                                             \n"
            "Hazards:                                                     \n"
            "1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
            "2. The Wumpus is not bothered by the pits, as he has sucker feet. Usually he is \n"
            "   asleep. He will wake up if you enter his room. When you move into the Wumpus'\n"
            "   room, then he wakes and moves if he is in an odd-numbered room, but stays    \n"
            "   still otherwise.  After that, if he is in your room, he snaps your neck and  \n"
            "   you die!                                                                     \n"
            "                                                                                \n"
            "Moves:                                                                          \n"
            "On each move you can do the following, where input can be upper or lower-case:  \n"
            "1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
            "   then a room number.                                                          \n"
            "2. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
            "3. Enter 'C' to cheat and display current board positions.                      \n"
            "4. Enter 'D' to display this set of instructions.                               \n"
            "5. Enter 'P' to print the maze room layout.                                     \n"
            "6. Enter 'G' to guess which room Wumpus is in, to win or lose the game!         \n"
            "7. Enter 'X' to exit the game.                                                  \n"
            "                                                                                \n"
            "Good luck!                                                                      \n"
            " \n\n");
}//end displayInstructions()


//--------------------------------------------------------------------------------
// Return true if randomValue is already in array
int alreadyFound(int randomValue,      // New number we're checking
                 int *randomNumbers,  // Set of numbers previously found
                 int limit)          // How many numbers previously found
{
    int returnValue = false;

    // compare random value against all previously found values
    for( int i = 0; i<limit; i++) {
        if( randomValue == randomNumbers[i]) {
            returnValue = true;   // It is already there
            break;
        }
    }

    return returnValue;
}


//--------------------------------------------------------------------------------
// Fill this array with unique random integers 1..20
void setUniqueValues(int *randomNumbers,   // Array of random numbers
                     int size)              // Size of random numbers array
{
    int randomValue = -1;

    for( int i = 0; i < size; i++) {
        do {
            randomValue = rand() % NUMBER_OF_ROOMS + 1;   // random number 1..20
        } while (alreadyFound(randomValue, randomNumbers, i));
        randomNumbers[i] = randomValue;
    }
}


//--------------------------------------------------------------------------------
// Set the Wumpus, player, bats and pits in distinct random rooms
void initializeGame(struct GameInfo *gameInfo)   // All game settings variables
{
    int *randomNumbers;
    randomNumbers = malloc(sizeof(int) * 7); // Dynamic Array of 7 unique values 1..20, to be used in initializing cave hazards locations

    // Initialize cave room connections
    //       ______18______
    //      /      |       \
    //     /      _9__      \
    //    /      /    \      \
    //   /      /      \      \
    //  17     8        10    19
    // |  \   / \      /  \   / |
    // |   \ /   \    /    \ /  |
    // |    7     1---2     11  |
    // |    |    /     \    |   |
    // |    6----5     3---12   |
    // |    |     \   /     |   |
    // |    \       4      /    |
    // |     \      |     /     |
    //  \     15---14---13     /
    //   \   /            \   /
    //    \ /              \ /
    //    16---------------20


    // Select some unique random values 1..20 to be used for 2 bats rooms, 2
    // pits rooms, Wumpus room, and initial player room
    setUniqueValues(randomNumbers, 7);
    // Use the unique random numbers to set initial locations of hazards, which
    //    should be non-overlapping.

    gameInfo->personRoom = randomNumbers[0];
    gameInfo->wumpusRoom = randomNumbers[1];
    gameInfo->pitRoom1 = randomNumbers[2];
    gameInfo->pitRoom2 = randomNumbers[3];
    gameInfo->batRoom1 = randomNumbers[4]; // setting random location for bat1
    gameInfo->batRoom2 = randomNumbers[5]; // setting random location for bat2
    gameInfo->arrow = randomNumbers[6]; // setting random location for arrow to be picked up
    // Initializing the game to have: person, Wumpus, pit1, pit2, bat1, bat2, arrow all in distinct random rooms

    gameInfo->moveNumber = 1;

    free(randomNumbers); // Free up the space from randomNumbers

}// end initializeBoard(...)


//--------------------------------------------------------------------------------
// Returns true if nextRoom is adjacent to current room, else returns false.
int roomIsAdjacent( int tunnels[ 3],     // Array of adjacent tunnels
                    int nextRoom)        // Desired room to move to
{
    return( tunnels[0] == nextRoom ||
            tunnels[1] == nextRoom ||
            tunnels[2] == nextRoom
    );
}


//--------------------------------------------------------------------------------
// Display where everything is on the board.
void displayCheatInfo(struct GameInfo gameInfo)
{
    printf( "Cheating! Game elements are in the following rooms: \n"
            "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow    \n"
            "%4d %7d %5d %4d %4d %5d %5d\n\n",
            gameInfo.personRoom,
            gameInfo.wumpusRoom,
            gameInfo.pitRoom1,
            gameInfo.pitRoom2,
            gameInfo.batRoom1, // Display what room bat1 is in
            gameInfo.batRoom2, // Display what room bat2 is in
            gameInfo.arrow // Display what room the arrow is in
    );
}// end displayCheatInfo(...)


//--------------------------------------------------------------------------------
// Display room number and hazards detected
void displayRoomInfo( struct GameInfo gameInfo, int** Rooms)
{
    // Retrieve player's current room number and display it
    int currentRoom = gameInfo.personRoom;
    printf("You are in room %d. ", currentRoom);

    // Retrieve index values of all 3 adjacent rooms
    int room1 = Rooms[currentRoom][0];
    int room2 = Rooms[currentRoom][1];
    int room3 = Rooms[currentRoom][2];

    // Display hazard detection message if Wumpus is in an adjacent room
    int wumpusRoom = gameInfo.wumpusRoom;
    if( room1 == wumpusRoom || room2 == wumpusRoom || room3 == wumpusRoom) {
        printf("You smell a stench. ");
    }

    // Display hazard detection message if a pit is in an adjacent room
    int pit1Room = gameInfo.pitRoom1;
    int pit2Room = gameInfo.pitRoom2;
    if( room1 == pit1Room || room1 == pit2Room ||
        room2 == pit1Room || room2 == pit2Room ||
        room3 == pit1Room || room3 == pit2Room
            ) {
        printf("You feel a draft. ");
    }

    //ADDED: Display hazard detection message if a bat is in an adjacent room
    int bat1Room = gameInfo.batRoom1;
    int bat2Room = gameInfo.batRoom2;
    if( room1 == bat1Room || room1 == bat2Room ||
        room2 == bat1Room || room2 == bat2Room ||
        room3 == bat1Room || room3 == bat2Room
            ) {
        printf("You hear rustling of bat wings. ");
    }

    printf("\n\n");
}//end displayRoomInfo(...)


//--------------------------------------------------------------------------------
// If the player just moved into a room with a pit, the person dies.
// If the person just moved into the Wumpus room, then if the room number is odd
// the Wumpus moves to a random adjacent room.
void checkForHazards(
        struct GameInfo *gameInfo, // Hazards location and game info
        bool *personIsAlive,     // Person is alive, but could die depending on the hazards
        int** Rooms) // ADDED: Dynamic array of Rooms

{
    // retrieve the room the person is in
    int personRoom = gameInfo->personRoom;

    // Check whether there is a pit
    if( personRoom == gameInfo->pitRoom1 || personRoom == gameInfo->pitRoom2) {
        // Person falls into pit
        printf("Aaaaaaaaahhhhhh....   \n");
        printf("    You fall into a pit and die. \n");
        *personIsAlive = false;
        return;
    }

    // Check for the Wumpus
    if( personRoom == gameInfo->wumpusRoom) {
        // To make it easier to test, in this version of the program the Wumpus always
        // moves if it is currently in an odd-numbered room, and it moves into the
        // lowest-numbered adjacent room.  In the version that is more fun to play
        // (but harder to test), the Wumpus has a 75% chance of moving, and a 25%
        // chance of staying and killing you.  The "more fun" code is commented out below.

        // Wumpus is there. 75% change of Wumpus moving, 25% chance of it killing you
        // Generate a random number 1..100
        //if(  (rand() % 100) < 75) {
        if( gameInfo->wumpusRoom %2 == 1) {
            // You got lucky and the Wumpus moves away
            printf( "You hear a slithering sound, as the Wumpus slips away. \n"
                    "Whew, that was close! \n");
            // Choose a random adjacent room for the Wumpus to go into
            //gameInfo->wumpusRoom = Rooms[ personRoom][ rand() % 3];
            gameInfo->wumpusRoom = Rooms[ personRoom][ 0];  // Choose the lowest-numbered adjacent room
        }
        else {
            // Wumpus kills you
            printf(    "You briefly feel a slimy tentacled arm as your neck is snapped. \n"
                       "It is over.\n");
            *personIsAlive = false;
            return;
        }
    }

    if( personRoom == gameInfo->batRoom1 || personRoom == gameInfo->batRoom2)
    {
        int randomNewRoom = -1;    // The value to hold what new room the player is going to be dropped in

        do { // do while loop to drop the player off in some new room
            randomNewRoom = rand() % NUMBER_OF_ROOMS + 1;
        } while (randomNewRoom == gameInfo->personRoom);

        int playerOldRoom = gameInfo->personRoom; // Holds players old room
        gameInfo->personRoom = randomNewRoom; // Move the player to the new room
        printf("Woah... you're flying! \n");
        printf("You've just been transported by bats to room %d.\n", gameInfo->personRoom);

        do { // do while loop to find new random room location that is not where the player is now nor where other bats are or were
            randomNewRoom = rand() % NUMBER_OF_ROOMS + 1;
        } while (randomNewRoom == gameInfo->personRoom ||
                 randomNewRoom == gameInfo->batRoom1  ||
                 randomNewRoom == gameInfo->batRoom2 );

        if( playerOldRoom == gameInfo->batRoom1) { // if statement to compare their current location to the room the player came from.
            gameInfo->batRoom1 = randomNewRoom; // Since the player left batRoom1 it must change to a new room
        }
        else { // if statement to compare their current location to the room the player came from.
            gameInfo->batRoom2 = randomNewRoom; // Since the player left batRoom2 it must change to a new room
        }

        int playerRoom = gameInfo->personRoom;
        if( playerRoom == gameInfo->batRoom1 || playerRoom == gameInfo->batRoom2 || // if statement to handle pit, wumpus, and bats hazards in player's new room if present.
            playerRoom == gameInfo->pitRoom1 || playerRoom == gameInfo->pitRoom2 ||
            playerRoom == gameInfo->wumpusRoom) {
            checkForHazards(gameInfo, personIsAlive, Rooms); // function that is recursively called to for bats so you're not dropped in a room with other bats
        }
    }

    if( personRoom == gameInfo->arrow) { // if statement if the person picks up arrow
        printf("Congratulations, you found the arrow and can once again shoot. \n");
        gameInfo->arrow = -1; // arrow value is now -1 to indicate it is now with the player

        return;
    }

}//end checkForHazards(...)


//--------------------------------------------------------------------------------
// Prompt for and reset the positions of the game hazards and the person's location,
// useful for testing.  No error checking is done on these values.
void resetPositions(struct GameInfo *theGameInfo)
{
    printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n");
    // In the scanf below note that we put the space at the beginning of the scanf so
    // that any newline left over from a previous input is not read in and used as
    // the next move. Another option is having getchar() after the scanf() statement.
    scanf(" %d %d %d %d %d %d %d", &theGameInfo->personRoom, &theGameInfo->wumpusRoom,
          &theGameInfo->pitRoom1, &theGameInfo->pitRoom2, &theGameInfo->batRoom1, &theGameInfo->batRoom2, &theGameInfo->arrow);
    printf("\n");
}


//--------------------------------------------------------------------------------
int main(void) {
    struct GameInfo gameInfo;   // Used to more easily pass game info variables around
    bool personIsAlive = true;  // Used in checking for end of game
    bool wumpusIsAlive = true;  // Used in checking for end of game
    char typeOfMove;            // Used to handle user input letter
    int nextRoom;               // User input of destination room number, used on a 'M' type move
    int *shootRoom; // Dynamic array to get the user input of the room the user wants to shoot in
    int numOfShots; // Number of total shots the user wants to make

    int ** Rooms = (int**)malloc(sizeof(int*) * 21);  // Allocate space for the rows
    for (int i = 0; i < 21; i++) {
        Rooms[i] = (int*)malloc(3 * sizeof(int)); // Allocate space for the columns
    }

    // inserting values for rooms and adjacent rooms in the 2D allocated array:
    Rooms[0][0] = 0; Rooms[0][1] = 0; Rooms[0][2] = 0; Rooms[1][0] = 2; Rooms[1][1] = 5; Rooms[1][2] = 8; Rooms[2][0] = 1; Rooms[2][1] = 3;
    Rooms[2][2] = 10; Rooms[3][0] = 2; Rooms[3][1] = 4; Rooms[3][2] = 12; Rooms[4][0] = 3; Rooms[4][1] = 5; Rooms[4][2] = 14; Rooms[5][0] = 1;
    Rooms[5][1] = 4; Rooms[5][2] = 6; Rooms[6][0] = 5; Rooms[6][1] = 7; Rooms[6][2] = 15; Rooms[7][0] = 6; Rooms[7][1] = 8; Rooms[7][2] = 17;
    Rooms[8][0] = 2; Rooms[8][1] = 5; Rooms[8][2] = 8; Rooms[9][0] = 8; Rooms[9][1] = 10; Rooms[9][2] = 18; Rooms[10][0] = 2; Rooms[10][1] = 9;
    Rooms[10][2] = 11; Rooms[11][0] = 10; Rooms[11][1] = 12; Rooms[11][2] = 19; Rooms[12][0] = 3; Rooms[12][1] = 11; Rooms[12][2] = 13;
    Rooms[13][0] = 12; Rooms[13][1] = 14; Rooms[13][2] = 20; Rooms[14][0] = 4; Rooms[14][1] = 13; Rooms[14][2] = 15; Rooms[15][0] = 6;
    Rooms[15][1] = 14; Rooms[15][2] = 16; Rooms[16][0] = 15; Rooms[16][1] = 17; Rooms[16][2] = 20; Rooms[17][0] = 7; Rooms[17][1] = 16;
    Rooms[17][2] = 18; Rooms[18][0] = 9; Rooms[18][1] = 17; Rooms[18][2] = 19; Rooms[19][0] = 11; Rooms[19][1] = 18; Rooms[19][2] = 20;
    Rooms[20][0] = 13; Rooms[20][1] = 16; Rooms[20][2] = 19;

    // Seed the random number generator.  Change seed to time(0) to change output each time.
    // srand(time(0));
    srand(1);

    // Set random initial values for person, Wumpus, bats and pits
    initializeGame( &gameInfo);

    // Main playing loop.  Break when player dies, or player kills Wumpus
    while (personIsAlive && wumpusIsAlive) {

        // Display current room information: Room number, hazards detected
        displayRoomInfo( gameInfo, Rooms);

        // Prompt for and handle move
        printf("%d. Enter your move (or 'D' for directions): ", gameInfo.moveNumber);
        // Note the extra space in the scanf below between the opening quote " and the %c.
        //    This skips leading white space in the input so that the newline left over from
        //    a previous move is not read in and used as the current move.  An alternative
        //    is using getchar() after the scanf() statement.
        scanf(" %c", &typeOfMove);

        typeOfMove = toupper(typeOfMove);  // Make uppercase to facilitate checking

        // Check all types of user input and handle them.  This uses if-else-if code
        //   rather than switch-case, so that we can take advantage of break and continue.
        if( typeOfMove == 'D') {
            displayCave();
            displayInstructions();
            continue;       // Loop back up to reprompt for the same move
        }
        else if( typeOfMove == 'P') {
            // To assist with play, display the cave layout
            displayCave();
            continue;       // Loop back up to reprompt for the same move
        }
        else if( typeOfMove == 'M') {
            // Move to an adjacent room,
            // Note the extra space in the scanf below between the opening quote " and the %c.
            //    This skips leading white space in the input so that the newline left over from
            //    a previous move is not read in and used as the current move.  An alternative
            //    is using getchar() after the scanf() statement.
            scanf(" %d", &nextRoom);

            if( roomIsAdjacent( Rooms[ gameInfo.personRoom], nextRoom)) {
                gameInfo.personRoom = nextRoom;        // move to a new room
                // Check if pit or wumpus is present in this new room
                checkForHazards(&gameInfo, &personIsAlive, Rooms);
            }
            else {
                printf("Invalid move.  Please retry. \n");
                continue;        // Doesn't count as a move, so retry same move.
            }
        }
        else if( typeOfMove == 'C') {
            // Display Cheat information
            displayCheatInfo(gameInfo);
            continue;        // Doesn't count as a move, so retry same move.
        }
        else if( typeOfMove == 'R') {
            // Specify resetting the hazards and person positions, useful for testing
            resetPositions( &gameInfo);
            continue;        // Doesn't count as a move, so retry same move.
        }
        else if( typeOfMove == 'G') {
            // Prompt for room number guess and see if user has found the Wumpus
            int wumpusRoomGuess = 0;
            printf("Enter room (1..20) you think Wumpus is in: ");
            scanf(" %d", &wumpusRoomGuess);
            // See if userguess was correct, for a win or loss.
            if( gameInfo.wumpusRoom == wumpusRoomGuess) {
                printf("You won!\n");
            }
            else{
                printf("You lost.\n");
            }
            break;
        }
        //ADDED: ELSE IF STATEMENT FOR THE ARROW
        else if( typeOfMove == 'S') {
            // shoot at an adjacent room,
            // Note the extra space in the scanf below between the opening quote " and the %c.
            //    This skips leading white space in the input so that the newline left over from
            //    a previous move is not read in and used as the current move.  An alternative
            //    is using getchar() after the scanf() statement.

            if(gameInfo.arrow == -1) { // Whenever arrowRoom is -1 you have the ability to shoot the arrow
                printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
                scanf(" %d", &numOfShots); // Accepting user input for the total amount of shots

                shootRoom = malloc(sizeof(int) * numOfShots); // Allocating space for an array to hold each room the user wants to shoot into

                if (numOfShots > 3 || numOfShots < 0) // if statement to check if the total amount of shots do not exceed 3 or go below 0
                {
                    printf("Invalid move. Please retry. ");
                }
                else
                {
                    for (int i = 0; i < numOfShots; i++) { // for loop to loop over each number of shots inserted

                        scanf(" %d", &shootRoom[i]); // user input of each room the user wants to shoot into
                    }

                    gameInfo.arrow = gameInfo.personRoom; /* arrowRoom will no longer be -1 and instead be in whatever
                    room the player is in (whether the player was grants the arrow or picked it up*/

                    for (int i = 0; i < numOfShots; i++) // for loop to loop over each number of shots inserted and determine the outcome of each arrow shot
                    {

                        if (roomIsAdjacent(Rooms[gameInfo.arrow], shootRoom[i])) // if statement to check is the arrow the user tried to shoot in is a valid adjacent room
                        {
                            gameInfo.arrow = shootRoom[i];        // moves arrow at current indexed room

                            if (gameInfo.arrow == gameInfo.wumpusRoom) { // if statement that activates when an arrow hits the wumpus winning the game
                                printf("Wumpus has just been pierced by your deadly arrow! \n"
                                       "Congratulations on your victory, you awesome hunter you.");
                                wumpusIsAlive = false;
                            }
                            if (gameInfo.arrow == gameInfo.personRoom) { // if statement that activates when an arrow travels a path that hits you, losing the game
                                printf("You just shot yourself.\n"
                                       "Maybe Darwin was right. You're dead.");
                                personIsAlive = false;
                            }
                        }
                        else{
                            printf("Room %d is not adjacent.  Arrow ricochets...\n", shootRoom[i]); // Print function for when the room is not adjacent

                            gameInfo.arrow = Rooms[gameInfo.arrow][0]; // Move arrow to lowest numbered adjacent rooms

                            if( gameInfo.arrow == gameInfo.personRoom) { // if statement if the arrow ricochets and hits the player, thus killing the player
                                personIsAlive = false;
                                printf( "You just shot yourself, and are dying.\n"
                                        "It didn't take long, you're dead.\n");
                            }
                            if( gameInfo.arrow == gameInfo.wumpusRoom) { // If it ricochets into room where Wumpus is, thus killing the Wumpus
                                wumpusIsAlive = false;
                                printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
                                        "Accidental victory, but still you win!\n");
                            }
                        }
                    }
                    gameInfo.wumpusRoom = Rooms[ gameInfo.wumpusRoom][ 0]; // Wumpus moves when the arrow ended up hitting nothing
                }
                free(shootRoom); // free the shootRoom array
            }
            else {
                printf("Sorry, you can't shoot an arrow you don't have. Go find it. \n"); // Print function when the user has no arrow
            }
        }
        else if( typeOfMove == 'X') {
            // Exit program
            personIsAlive = false;   // Indicate person is dead as a way to exit playing loop
            break;
        }

        // Increment the move number
        gameInfo.moveNumber = gameInfo.moveNumber + 1;

    }//end while(personIsAlive && wumpusIsAlive)

    // for loop to free the dynamically allocated array
    for(int i=0; i<21; i++) { // for loop to free the space used to store the adjacent rooms for each room
        free( Rooms[i] );
    }
    // Free the space used for the 20 room pointers
    free(Rooms);

    printf("\nExiting Program ...\n");
    return 0;
} // end brackets for main()
