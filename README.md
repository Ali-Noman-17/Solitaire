# Solitaire Project
Solitaire, the classic card game implemented using Object Oriented Programming-OOP principles. 
The project leverages C++ features like classes, inheritance, and polymorphism to model game components and mechanics.
<br><br>

## Gameplay Description
Cards from a standard 52 card deck are randomly distributed into **7 stacks**. All interactable.
The first stack has exactly one card and each subsequent one has one more card than the previous, with the 7th stack having 7 cards.
All the cards in the stacks are upside down _except_ for the **top-most card**.  

Above the stacks are **4 cell**, for the 4 card houses namely, **spades, clubs, hearts and diamonds**.
Remaining cards are put in a **pool** from where the player can draw cards one by one.  

Every card must be in a stack at all times. Player can only pick up one card or a sequence <sub>(_arranged by player earlier_)</sub> at a time for moving between stacks.
In the 7 randomised cells, player can stack up cards by **descending order** of [values](https://github.com/Ali-Noman-17/Solitaire/new/main?readme=1#values-of-cards) 
but **alternating colours**. Red on red or black on black stacking is **invalid**.
Moving the top-most card of a pile to another will flip over the upside down card underneath. All the upside down cards must be flipped over one by one.
Player's ultimate goal is to stack all the cards into the house specific cells in **ascending order** of [values](https://github.com/Ali-Noman-17/Solitaire/new/main?readme=1#values-of-cards).  

### Links to online tutorials
[**Website tutorial**](https://www.solitairebliss.com/blog/how-to-play-solitaire)  
[**Youtube video tutorial**](https://www.youtube.com/watch?v=mqAqy1q6gM8&pp=0gcJCdgAo7VqN5tD)
<br><br>

## Values of Cards:
In ascending order:
-  **`A` (ace)** 
-  **`2` (two)**
-  **`3` (three)**
-  **`4` (four)**
-  **`5` (five)**
-  **`6` (six)**
-  **`7` (seven)**
-  **`8` (eight)**
-  **`9` (nine)**
-  **`10` (ten)**
-  **`J` (jack)**
-  **`Q` (queen)**
-  **`K` (king)**

This order is consistent for all houses. Colour or house ***does not*** affect card value.
<br><br>

## Classes Structure
The following classes will be used for the code implementation:

### 1. `Board`
Main class, contains the whole game layout and all the other classes.

### 2. `Card`
Base card class. Has derived classes, classified into colours and each colour further into houses:
- **`Black_Card`**
   - `Spades`
   - `Clubs`
- **`Red_Card`**
   - `Hearts`
   - `Diamonds`
     
 Each card will have a char attribute for displayable value and an int attribute for equivalent numeric value.

### 3. `Cell`
A vector like object that contains an array of cards. Each sub class will have a unique type of array for handling unique arrangements of cards. Has derived classes:
- **`Alternate Cell`** - only allows alternating colours stacking
-  **`House Cell`** - only allows cards of a specific house
-  **`Free Cell`** - allows any kind of card stacking

### 4. `Pool`
An object that contains 2 **Free cells** to cycle through the pool of available cards. 
One for upside down cell of cards that constitute the pool and one for the turned over cards. Top-most of the turned over cell is pickable.

### 5. `Division`
An object that contains an array of specific number of a cell subtypes. Two such objects will be used:

- #### A) The `Play Division`
  Contains an array of 7 **`Alternate Cells`**, for the 7 randomised stacks, with the nth cell containing n number of cards.
  
- #### B) The `Sort Division`
  Contains an array of 4 **`House Cells`**, for sorted ascending ordered stack of each house of cards.  
  Detects win condition. If all 4 cells have the maximum capacity i.e **`13`**, it means all cards are sorted and the game ends.
<br><br>

## Technical Aspects
### Initialisation
The game begins by initialising a Board object  and calling it's **`startGame()`** method which initialises all other objects- 
divisions, cells, pool and the deck of 52 cards. Another method **`shuffle()`** then randomly distributes the cards to appropriate cells.

### Game loop
The main loop that, when running represents the game being played. During the loop, the player may attempt to move cards from one Cell to another.
The player may also click on the upside down Pool cell to reveal a card. The game loop terminates when the **`checkWin()`** method in Board yields true.

### Move validation
Each time player attempts to move cards, a **`isValid()`** method from the recipient Cell is called that checks if the move is valid 
according to the cells allowed arrangement of cards. If the move is valid, then a **`move()`** method is called that completes the move.

### Drawing from pool
If the pool is clicked to draw a card, the top-most card in the downside cell is fliped over using the **flipOver()** method 
from the card class and moved to the upside cell. The top-most card in the upside cell is available for moving. 
Repeated draws are allowed and once the downside cell empties into the upside cell, on the next click to draw, 
all the cards are turned over and cycled back to the downside cell. This is managed with **`isEmpty()`** and **`cycleBack()`** methods from pool.

### Checking for win
At the end of each loop iteration, the **`checkWin()`** method from Board is called. It in turn calls the **`isFull()`** function from the sort division,
that checks if all 4 of the House Cells in the Sort Division are at maximum capacity i.e. **`13`**. If yes, the win condition is satisfied and the 
game loop terminates, signifying end of game.

### Save and Load
Player can save the game by pressing the `Save` button that calls the **`saveGame()`** method from Board, writing all the data to a binary file.
A saved game can also be loaded at by choosing the `Saved Game` button that calls the **`loadGame()`** method from Board, 
reading data from the binary file to the Board.
<br><br>

## [UML Diagram](./solitaire-uml.png)
## [Flow State Diagram](./solitaire-flowchart.png)
