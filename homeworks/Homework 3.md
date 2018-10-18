Michael Yoshimura, Thomas Young

Homework 3

**1) Our plan for this homework: Board and Graphics**
 Setup all development frameworks: Github, Travis CI, QT Creator, Catch
* The board is going to be the first working piece of the game. While the content of this
portion is similar to that of the Maze game, the underlying structures are different in
our implementation to make the dungeon more interactive.
    * Walls, floors, enemies.
    * Generation: Rooms, hallways, and a guaranteed path from the entrance to exit.
    *  Basic Enemy and player movement.
    * The Game class, which will manage turns and rendering
    * Data persistence of the board (saving and loading the board)
    *  Unit tests for the board
*  After playing around with QT, it would be advantageous to integrate QT from the start,
so we want to make this project use graphics as soon as possible.
* The Game class will get the state of the board, and render a scene
*  Knowledge required to complete:
    * Although we know how QT will generally integrate, it is still the largest
unknown, along with getting all development technologies to work together
nicely.
    * Data persistence may prove difficult. However, we have knowledge of JSON
game serialization in Unity, so JSON serialization in QT will roughly translate.
    *  Dungeon generation algorithms: we will use a simpler generation algorithm that
will get us rooms and hallways based on a grid.

**2) Accomplishments**
We were successful in setting up all of the development frameworks except for Catch2 because
have not been able to write unit tests yet. This also
goes for Travis CI. In addition, it might be better to
use the canned testing framework that Qt provides.
We were successful in creating the board that
generates a map that resembles a dungeon, and a
player and enemies that have basic movement. Below
are the implementation details of each class.

Graphics
* The graphics for this stage is a conversion from the terminal graphics to using the
QGraphicsScene and the QGraphicsView to render image-based sprites.
* The way Qt works to efficiently render lots of objects is to instantiate them as a
QGraphicsItem and add them to the QGraphicsScene. As such, a direct application of
flyweight was not very useful. However, the board still uses flyweight when assigning its
tile objects. (see the Board bullet point).
* Besides the graphics view, there is some non-functional GUI there that will be
implemented in the next homework, as it needs the PlayerEntity class to work.
* The graphics class also reroutes the input from the keyboard to the game, which is a bit
different from what we expected to have, which had the game receive input directly.

* Board
    * The board was implemented successfully closely following our proposed architecture.
    *  The command design pattern was successfully used in handling input to move tiles
    * The board generates a dungeon that generates rooms and is guaranteed to be solvable.
    *  The board uses a flyweight pattern by having references to a single wall, empty, and
player tile, and assigns each tile to be a pointer to that reference. The enemy tiles are
not implemented as a flyweight.

* Game
    * The game was also implemented closely to the proposed structure: it only handles
input, turns, and holds a reference to the board.

**3) Our plan for the next homework: Basic Battle Simulator:**
* The first prototype of the battle simulation
    * The battle between the player and the enemy
    * Basic Skills

    * Data persistence of the skills
    *  Basic Items
    * Stats and Modifiers
    * Interface for the battle simulation
    * Unit tests for the battle simulation
* Knowledge required to complete:
    * We don’t know how to use Qt specifically for GUI, but we should learn those
skills in time for this homework 4.
   * We will be working in JSON reading and generating objects with unique stats,
which we have some experience in Unity.


Currently, we are roughly on track with the content. We have the knowledge to make Qt work
for the GUI required for the battle simulator.
4) Here is a screenshot of the game:
![Alt Text](https://thumbs.gfycat.com/SoulfulPerfectKangaroo-small.gif)
