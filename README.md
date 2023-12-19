<div align="center">
<pre>
┏┓━┏┓━━━━━━━━━┏┓━━━━━┏━━━━┓┏┓━━━━━━━━━━┏┓┏┓┏┓━━━━━━━━━━━━━━━━━━━━┏┓
┃┃━┃┃━━━━━━━━┏┛┗┓━━━━┃┏┓┏┓┃┃┃━━━━━━━━━━┃┃┃┃┃┃━━━━━━━━━━━━━━━━━━━━┃┃
┃┗━┛┃┏┓┏┓┏━┓━┗┓┏┛━━━━┗┛┃┃┗┛┃┗━┓┏━━┓━━━━┃┃┃┃┃┃┏┓┏┓┏┓┏┓┏━━┓┏┓┏┓┏━━┓┃┃
┃┏━┓┃┃┃┃┃┃┏┓┓━┃┃━━━━━━━┃┃━━┃┏┓┃┃┏┓┃━━━━┃┗┛┗┛┃┃┃┃┃┃┗┛┃┃┏┓┃┃┃┃┃┃━━┫┗┛
┃┃━┃┃┃┗┛┃┃┃┃┃━┃┗┓━━━━━┏┛┗┓━┃┃┃┃┃┃━┫━━━━┗┓┏┓┏┛┃┗┛┃┃┃┃┃┃┗┛┃┃┗┛┃┣━━┃┏┓
┗┛━┗┛┗━━┛┗┛┗┛━┗━┛━━━━━┗━━┛━┗┛┗┛┗━━┛━━━━━┗┛┗┛━┗━━┛┗┻┻┛┃┏━┛┗━━┛┗━━┛┗┛
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃┃━━━━━━━━━━━━
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┗┛━━━━━━━━━━━━
Text-Based Adventure Game Created in C
</pre>

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

</div>

Welcome to "Hunt the Wumpus"! This is a complete text-based adventure game that takes place in a dark cave consisting of 20 interconnected rooms, each containing various hazards, including the Wumpus, bottomless pits, and bats. The objective of the game is to find an arrow randomly hidden within a cave room and successfully hunt down the Wumpus while avoiding hazards that could lead to the player's demise.

### Game Elements:
- **The Wumpus:** A menacing creature that lurks within the cave. It is not initially active (it's asleep) and moves only under specific conditions (like shooting an arrow and missing).
- **Your Character:** You, the brave hunter, armed with your wits and a single arrow to take down the Wumpus.
- **The Arrow:** Your weapon against the Wumpus. It's placed in a random room within the cave at the start of the game. Retrieve it to have a chance against the Wumpus.
- **Bottomless Pits:** Two rooms within the cave contain pits. Falling into these pits leads to instant death.
- **Bats:** Two mischievous giant bats roam around the cave. Encountering them might result in being whisked away to another room.

### Game Mechanics:
- **Room Navigation:** Move through the cave by entering adjacent rooms (numbered 1-20) to explore and find the Wumpus.

  Here is the map you must navigate (Each number represents a room):
<div align="center">
<pre>
                ______18______             
              /       |       \           
             /      __9__      \          
          /      /     \      \       
         /      /       \      \      
           17     8        10     19       
       | \   / \      /  \   / |    
       |  \ /   \    /    \ /  |    
          |   7     1---2     11  |       
         |   |    /     \    |   |      
          |   6----5     3---12   |       
         |   |     \   /     |   |      
         |    \      4       /   |      
         |     \     |      /    |      
          \     15---14---13     /       
          \   /            \   /       
           \ /              \ /        
              16---------------20           
</pre>
</div>

 
    
-  **Hazards Detection:** Be alert to detect hazards:
    - **Stench:** Indicates the presence of the Wumpus in an adjacent room.
    - **Draft:** Signals the proximity of a bottomless pit in an adjacent room.
    - **Bat Sounds:** Warns you of nearby bats in an adjacent room that might transport you to a different room.
 
    
- **Interaction with Hazards:** Various events occur when encountering hazards:
    - Falling into a pit results in instant death.
    - Encountering the Wumpus leads to different outcomes based on how it's feeling (50% it might kill you and 50% it may run away in an adjacent room).
    - Bats might teleport you to another room.
### Game Controls
- M - Move: Enter 'M' followed by a space and then the room number to move to an adjacent room.

  For Example:
  ```
  You are in room 18.
  
  1. Enter your move (or 'D' for directions): m 9
  You are in room 9. 
  ```
- R - Reset: Enter 'R' then press the enter key to reset the positions of hazards and the player for testing purposes. 

  For Example:
  ```
  Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: 
  Enter the new room number for player: ...ENTER ROOM NUMBER HERE THEN PRESS ENTER TO CHANGE THE NEXT ELEMENT...
  ```
- C - Cheat: Enter 'C' to display the current positions of game elements.
- D - Directions: Enter 'D' to display the instructions and game controls.
- P - Print Maze: Enter 'P' to print the layout of the map.
- G - Guess Wumpus Room: Enter 'G' to guess which room the Wumpus is in and win the game. If you guess incorrectly, you lose.
- S - Shoot Arrow: Enter 'S' to shoot an arrow into adjacent rooms (when the arrow is available).

  For Example:
  ```
  3. Enter your move (or 'D' for directions): m 1
  Congratulations, you found the arrow and can once again shoot. 
  You are in room 1. 
  
  4. Enter your move (or 'D' for directions): s
  Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: 2 8 9
  Wumpus has just been pierced by your deadly arrow! 
  Congratulations on your victory, you awesome hunter you.
  Exiting Program ...
  ```
- X - Exit Game: Enter 'X' to exit the game.


## Installation Instructions
When you execute the program, follow these steps to interact with the game:

1. Compile the Program:
- Compile the program using a C compiler (e.g., GCC).
- For example: gcc main.c -o hunt_the_wumpus

2. Run the Program:
- Execute the compiled program.
- For example: ./hunt_the_wumpus

3. Follow Game Instructions:
- You'll receive instructions on how to play the game by entering 'D' as soon as you run the executable or you can follow the game instructions outlined in this ReadMe.md
- Enter commands accordingly and follow the prompts to interact with the game environment.

Note: This README provides an overview of the game and its functionalities. Detailed explanations of the code's working and comments are present within the source code for reference and understanding.
