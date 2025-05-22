# Solitaire Project
Solitaire in C++, the classic card game implemented using Object Oriented Programming-OOP principles. 
This project leverages C++ features like classes, inheritance, and polymorphism to model game components and mechanics.
<br>
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
[**Solitaire Bliss website tutorial**](https://www.solitairebliss.com/blog/how-to-play-solitaire)  
[**Youtube video tutorial**](https://www.youtube.com/watch?v=mqAqy1q6gM8&pp=0gcJCdgAo7VqN5tD)
<br><br>

## Values of Cards:
In ascending order:
- **A (ace)** 
- **2 (two)**
-  **3 (three)**
-  **4 (four)**
-  **5 (five)**
-  **6 (six)**
-  **7 (seven)**
-  **8 (eight)**
-  **9 (nine)**
-  **10 (ten)**
-  **J (jack)**
-  **Q (queen)**
-  **K (king)**

This order is consistent for all houses. Colour or house ***does not*** affect card value.
<br><br>

## Classes Used
The following classes will be used for the code implementation:

### 1. Board
Main class, contains the whole game layout and all the other classes.

### 2. Card
Base card class. Has derived classes, classified into colours and each colour further into houses:
- **Black Card**
   - Spades
   - Clubs
- **Red Card**
   - Hearts
   - Diamonds
     
 Each card will have a char attribute for displayable value and an int attribute for equivalent numeric value.

### 3. Cell
A vector like object that contains an array of cards. Each sub class will have a unique type of array for handling unique arrangements of cards. Has derived classes:
- **Alternate Cell** - only allows alternating colours stacking
-  **House Cell** - only allows cards of a specific house
-  **Free Cell** - allows any kind of card stacking

### 4. Pool
An object that contains 2 **Free cells** to cycle through the pool of available cards. 
One for upside down pile of cards that constitute the pool and one for the turned over cards. Top-most of the turned over cell is pickable.

### 5. Division
An object that contains an array of specific number of a cell subtypes. Two such objects will be used:

- #### A) The Play Division
  Contains an array of 7 **Alternate Cells**, for the 7 randomised stacks, with the nth cell containing n number of cards.
  
- #### B) The Sort Division
  Contains an array of 4 **House Cells**, for sorted ascending ordered stack of each house of cards.  
  Detects win condition. If all 4 cells have the maximum capacity-**13**, it means all cards are sorted and the game ends.
<br><br>

## UML Diagram
[UML image](./solitaire_uml_ss.png)
## Flow State Diagram
