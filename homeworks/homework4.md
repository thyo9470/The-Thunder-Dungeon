# Checkpoint 4
#### 2) Guide to current functionalities:
- "wasd" keys to move around on the board
- Click the 'save' button to save a game state, and the 'load' button to load a game state
- When battling an enemy, click a skill button to activate a skill, or 'run' to attempt to run away
- Also, to avoid confusion, speed and magic attributes currently don't do anything
- There is currently no 'game end'
#### 1) Basic Battle Simulator: Have a battle simulator that is functional.
- First prototype of the battle simulation
  - The battle between the player and the enemy
  - Skills
    - Data persistence of the skills
  - Items
  - Stats and Modifiers
  - Interface for the battle simulation
  - Unit tests for the battle simulation
  - Knowledge required to complete:
  - We don’t know how to use QT specifically for GUI, but we should learn those skills in time for this homework 4.
  - We will be working in JSON reading and generating objects with unique stats, which we have some experience in Unity.
#### 2) Our Progress
- From the previous plan (Homework 3):
  - Added data persistence to the board. Clicking load and save buttons in the board window will load and save a board state.
  - Added the qt test case framework along with a few test cases
- The battle:
  - We have a fully functional battle system! From the maze to enemy encounter, to defeating and going back to the enemy, the basic game is now playable.
- Skills:
    - Added skills that can affect multiple stats of an entity with modifiers
    - Did not add data persistence - this will be implemented in a database style instead, where instead of saving an entire skill to JSON, we will save a skill_id, and load in the skill from a JSON database. 
- Items:
    - Not implemented yet
- Stats and Modifiers:
    - We did not implement a specific stat class: all modifiers directly and permanently affect the stat. 
- Unit Tests:
    - Basic unit tests test skill and modifier features
- Major differences in architecture:
    - The fight window was added as the easiest solution to adding a separate fight scene
    - We decided that advanced stats was not necessary. We realize that it would take a lot of time to implement this, and decided that using float values as stats in the entity class would be adequate.
    - The enemy and player don't seem to need inherited classes, so they are both just entities
#### 3) Next checkpoint: We hope we are finished with the basics of the game.
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

Overall, we have had to slim down some features because of their complexity. We are slightly behind because we haven't written thorough test cases, and we haven't implemented items. With more test cases, hopefully we will also include TravisCI.

#### 2) Screenshots:
![Class Composition](https://docs.google.com/drawings/d/e/2PACX-1vQrfcu6v2jyOQ42V3YtGEZHcU6cZK9IEUcNFRKwhaGztiwEENUXf6QrWTqffoCGkia8X-5r8OHV8c0H/pub?w=960&h=720)

Note that the window normally stays in place: only during recording does the window seem to move around.
![Gameplay Gif](https://thumbs.gfycat.com/ScarceDeliriousDassie-small.gif)
