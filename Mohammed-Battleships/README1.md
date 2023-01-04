# Mohammed - Battleships

## Challenge Outline
I was tasked with designing, developing and testing a take on the classic Battleships game.
The idea was to allow a player to play against a CPU in accordance with the normal game rules.

### Game Mechanics

### Objective: 
Sink all of the opponent’s ships before they sink yours.

### Gameplay
Players will arrange their ships on the board horizontally or vertically and without any overlap. 
Players will take turns to fire missiles at a specified coordinate on the opponent’s board (e.g., B2) with the intention to hit an enemy ship. 
The attacking player will be notified whether it was a hit or miss. The game is won when one player has destroyed all the opposing ships completely.

My rendition includes:

* The simultaneous display of both the player’s and enemy’s boards
* Turn taking mechanism - boards are updated with each valid attack
* Error handling to deal with inappropriate user inputs
* Win/Loss/Tie detection and display
* The ability to quit at any time

### Initial Design

As I could forsee my game having a number of unique objects similar to the original game, I opted for an OOP approach to the game.
The objects I initially planned for are listed below:
* Board
* Ship
* Player
* Game

Early on, this 'player' class was separated into a PlayerHandler and CPUHandler. Each would inherit from an abstract base class called GameHandler that represents an entity that can take turns in the game.
I felt this separation of concerns simplified each handler rather than having one monoloth of a player class with all the player logic.

Additionally, I also decided to further decompose the Board into its constituent Board Tiles.
Each tile would store information about whether the tile is empty, hit or being occupied by a ship. The board itself would be a 2D-vector of Tile objects.
Thus, allowing the board class to keep track of each tile's state.

The UML diagram below depicts the archictectural approach I took:

_UML Diagram_

![UML Design](Battleships_UML.png)


## Development

### Agile Approach

Due to the complexity of the challenge coupled with the time constraint, I broke the problem down into a series of manageable phases that I would develop to iteratively reach a 'final' game.
This helped a lot because the challenge was so new to me and it was difficult to ascertain how feasible my proposed features were and how long they would take. Through this approach, the task seemed less
daunting and I was able to tackle each challenge as it came.

Each iteration was defined by its requirements and was then designed, developed and tested in due course.
For my QA process, I conducted manual testing during and after the addition of each new feature to ensure successful integration.
I made to sure to try both valid, invalid and unexpected inputs and account for them where possible.

> Phase 1

* Build a file parser that can extract board dimensions and ship data from a .ini file

> Phase 2

* Display an empty board - must be formatted and aligned
* The X-Axis should be lettered whilst the Y-Axis is numbered

Note: Game logic not required at this point in time.

> Phase 3

* Intuitive Set-Up interface to allow user to select: 
    1. Player vs CPU 
    2. Quit
* Allow user to see target board aswell as their own board showing their ship locations
* Implement working game logic
    * Allow firing at target board
    * Update boards with attack result each turn
    * Notify player of hit ('H') or miss ('M') based on the outcome of their turn
* Catch erroneous inputs
* Support in-game quitting
* Detect a win/Loss/Tie

> Final Phase

* Must fulfil all the requirements stated in phase 3
* Allow user to set board dimensions
* Allow user to choose opponent difficulty

### Decomposition - Epics

In true agile fashion, I decided to break down the major elements of development into a few key epics. I began by using JIRA to create a backlog and series of appropriate tickets.
That said, I found JIRA to be time-consuming to maintain so I transitioned to Trello soon after. As my project was relatively lightweight and I was unsure how long each task would take,
Trello seemed most appropriate as it fulfilled my need to be able to track epics and stories and view their completeness.
 
 _Trello Board_ 

 ![Trello Board](Battleships_Trello.png)

I created a board with a number of epics corresponding to each major component within my game. Each epic had a number of smaller stories within it that outlined the criteria for completion at each stage.
This gave me clear guidelines and expectations at the end of each epic.

After defining the epics, I filled the backlog with all the potential stories that would need to be completed; these were somewhat flexible and subject to change if something became unfeasible or needed clearer explanantion.
When I was ready to start a story, I would move it to the 'In Progress' column. Each story would arise from a specific user requirement. Before regarding a story as 'Done' it would undergo QA testing to ensure it was functioning as expected
(defined in the acceptance criteria of each ticket).

_User Story Example_ 

![User Story Example](Battleships_Story.png)

The image above shows an example user story with clearly outlined acceptance criteria. 
The labels highlight the type of ticket (e.g., story) as well as a reference to the corresponding epic (e.g., Attack Functionality).
Once all the requirements are met and the sub-tasks are complete, it is moved to the 'Done' column.

### Phase 1 - File Parser & OOP skeleton

For the initial phase of development, I put some thought towards the basic classes, properties and methods that would comprise my solution.
I began with a basic 'Board' class with a 'size' property, 2D-array of Board tiles and a vector of ships.

Meanwhile, I also began working on a fileParser method to extract board and ship data. I had an initial 'settings.h' file
with a 'ShipData' struct that I wanted to use to store parsed file data for the ships.

**_File Parser attempt #1_**

_State Machine Pattern - fileParser()_

![fileParser](fileParser_method.png)

My initial attempt at file parsing utilized a number of functions used to read and parse data from an INI file.
The fileParser() method takes a string containing INI file content as an input and processes it line by line. It uses the State Machine design pattern and consists of 
a number of states (0 to 7). They are used to track the current position in the parsing process.

The 'for' loop at the end of the function iterates over each character in the 'IniData' string. The 'switch' statement inside the loop checks the current state and determines 
how to handle the current character based on that state. For example, when state is '0' (waiting for INI data), the 'switch' logic checks if the current character is a semi-colon (to
start a comment), an open square bracket (to start a section name), or a tab/new line. If the character is any other character, the state is switched to 3 (key started) and is added to the buffer.

_State Machine Pattern - parseFromFile()_

![parseFromFile](parseFromFile_method.png)

The 'parseFromFile' method takes a file path as an input, opens the file in binary read mode, reads the contents of the file into memory, and then calls the 'fileParser' method above with the file
content as an argument.

After getting the file parser to a position where I could ouput the data for the board and ships, it was a challenge trying to allocate the data to the relevant properties in the board and ship classes.
At this point, it was taking too long to solve as I was not fully familiar with the nuances of the language so I made the decision to be flexible and take a new approach.


**_File Parser attempt #2_**

![fileParser2](fileParser2_method.png)

In the second attempt, I decided to reduce the complexity of the function for the time being until I had a working game (part of good programming standards). This method:
1. Takes a string 'fileName'
2. Opens the file and reads all of the lines into a vector of strings.
3. Iterates through the vector of lines and splits each line into three parts using the ':', 'x', and ',' characters as delimiters.
4. Stors the three parts in variables 'key', 'val1', and 'val2'.
5. Outputs the values of 'key', 'val1', and 'val2' to the console.

Here I got to a similar point as attempt one, where I could output the data but I felt I was putting too much emphasis on this first phase so I put this part on hold to prioritise actually rendering a board.

### Phase 2 - Rendering a Board

![displayBoard](displayBoard_method.png)

The above method is responsible for rendering the board. It returns a string interpretation of the board, showing all the ships and their positions.
It is mainly built using for loops. The main loop checks if a tile is occupied and not hit and if so, the ship name is shown. However, an empty tile that has been hit is marked by an M
and a successfully hit tile is marked 'H'.

It was tricky trying to think about how I could show the target board without giving away the board locations. To solve this,
I made another method called 'displayHiddenBoard', which shows a board with ship locations hidden, but hits and misses revealed. It is a solution that works well but I do hope to find
a better solution that reduces the repetition of code in future.

### Phase 3 - Working Game

_**Refined Board Class**_

![board Constructor + Random Populate](board_constructor_randomPop.png)

In order to maintain good coding standards, I ensured regular and thorough testing during these stages of development. This can be seen as I have added appropriate error handling
if the given size is too large or too small.

For MVP purposes, I decided to first randomly populate the board with ships (as shown above). One challenge I had to consider is: 'what if the program takes extremely long to find a random placement?'
In this case, I ensured robustness by having a reasonable maxCount that results in an error if exceeded. This added to my game's robustness.
The ideal scenario is for this method to be a part of an autopopulate feature whilst the default would be to allow the user to place their own ships. However, due to time constraints, this could
not be implemented.

_**Validating and Adding Ships**_

![ship Validation](validateShips_method.png)

The validatePos function is responsible for checking whether or not a ship can be placed in a particular position. It checks whether the ship is within bounds and ensures it is not colliding
with another ship. One highlight is that it checks for parallel and non-parallel ships - allowing more flexibility of placement.

One challenge is that the collision detection for non-parallel ships is inefficient. The use of nested loops result in an O(n^2) time complexity. This means a significant increase in time taken
as the number of ships increase. The ship is then added (addShipToBoard) by updating the '_empty' and '_currentShip' fields of the BoardTile to reflect the presence of the ship.
I solved the inefficiency in the validatePos method by doing the following:
* Moved the check for out-of-bounds positions to the beginning of the function. This prevents unnecessary collision checks if the ship is already known to be out-of-bounds.
* Changed the nested loop that checks for collisions to only run when the ships are not parallel. This reduces the number of checks that need to be performed, since most ships will be parallel.
* Returned false as soon as a collision is detected, rather than continuing to check for more collisions.

_**The improved code can be seen below:**_
![improved ship Validation](validatePosImproved_method.png)



## Evaluation