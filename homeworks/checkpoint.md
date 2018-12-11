Michael Yoshimura, Thomas Young

# Checkpoint 1
#### 0) Guide to current functionalities

  - "wasd" keys to move around on the board


  - Click the 'save' button to save a game state, and the 'load' button to load a game state

  - When battling an enemy, hover over a skill to see more information and click to use it. Click 'run' to try to run

  - The main window your equipment is on the right panel, hover over an item to see more information

  - After a battle, you will be offered a new item. You can either: 

    - Equip: replaces current item with a new item

    - Toss: keep old item

  - There is currently no 'game end'
#### 1) Next checkpoint: We hope we are finished with the basics of the game

  - Generate content/diversify the game

    - Move beyond basic enemy movement

      - Different movement algorithms

    - Bosses

    - Procedurally generate items

    - Improve the dungeon generation

      - Fill in rooms of the dungeon with objects of interest e.g. chests.
  
      - Create different types of rooms to make the dungeon a bit more diverse (treasure rooms, trap rooms, etc.)

    - Make enemies choose their skills intelligently in the battle simulation.

    - Unit tests for these new additions

  - Knowledge required to complete:

    - We will need to research movement algorithms and/or come up with our own

    - As we are taking Intro to Artifical Intelligence we know enough to make our enemy AI good enough to make the game fun.
#### 2) Our Progress

  - Generate content/diversify the game

    - Move beyond basic enemy movement

        - Enemies will follow the player if they get within a certain range, otherwise, they walk around looking for them

    - Bosses

        - Bosses are an enemy fight one level above you at the end of each level.

    - Procedurally generate items

        - Basic Item generation, using prefixes and suffixed to add procedural randomness

        - The items and equipment can be saved and loaded

    - Improve the dungeon generation

      - The board now uses smart tiling to make the walls of the dungeon fit together

      - Floodlighting effect around the player to limit how far they can see in the dungeon.

    - Make enemies choose their skills intelligently in the battle simulation.

    - Unit tests for these new additions

  - Enemies make educated moves in the battle simulation

  - They use minimax to look ahead and asses how good a specific move will be 

    - minimax: https://en.wikipedia.org/wiki/Minimax

  - The enemy learns the players move set in the battle to improve decision making
#### Extras:

- New sprite sheets:
    - New sprite for the player and enemy
- Finally got Travis CI to work with Qt
- We added and ItemFactory and EntityFactory because instantiating enemies and items from Json turned out to be a pain. ItemFactory was especially useful because they are somewhat procedurally generated.

#### 3) User Testing:
We tested three different features:
1) Find and battle an enemy
  - Should make the cost of using a skill more clear
  - The lighting was a nice mechanic
  - It was too easy to run into enemies. We should either decrease the number of enemies or the distance they can see the player.
2) View and equip items
  - Tooltips should pop up faster
  - Increase the information tooltips have
3) Save the game, and reload when the level is beaten
  - We need a way to recover health (it is very hard to beat levels)
  - Have a clear indication that the game was saved. There is no feedback when clicking the saved button.

#### 4) Next Checkpoint:
Up until now, we’ve been trying to implement a ton of features and mechanics, so it will likely not look too great and it probably won’t be balanced enough for fun gameplay. So, we will focus on refining and polishing the graphics, sound, and gameplay. 
- Add the main menu.
- Add game over and winning
- Ideally, we are not adding any more features, but getting the game ready as a product.
- Preparing for project presentation.
- Basic sound and animation
- More items, show item skill description

We are on track: besides some additional item improvement, we will focus on polishing the game.

#### 5) Screenshots:
![Class Composition](https://docs.google.com/drawings/d/e/2PACX-1vQcp-J_FPsAmD4-jyjnHrd3bMwdnSvQYlChoGFL0ri7zYxPZLZR1JmnIIcM57XKVTkxZ3-OZgV1kg5a/pub?w=960&h=720)

#### Enemies follow when close to the player!
![Gameplay Gif](https://thumbs.gfycat.com/BigDaringGuppy-small.gif)

#### Item drops!
![Gameplay Gif](https://thumbs.gfycat.com/RespectfulOrderlyBellsnake-small.gif)

#### Item Tooltips!
![Gameplay Gif](https://thumbs.gfycat.com/LazyLiquidAngelwingmussel-small.gif)
