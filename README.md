# PacMan
The project was created to improve my own C++ programming skills. But most of all it was created just for fun!






https://user-images.githubusercontent.com/46819243/135147671-a6c48631-962b-4237-937a-a60670749f12.mp4





# Used libraries

- [GLEW](http://glew.sourceforge.net/)
- [GLFW](https://www.glfw.org/)
- [ImGui](https://github.com/ocornut/imgui)
- [glm](https://github.com/g-truc/glm)
- [stb](https://github.com/nothings/stb) - stb_image, stb_image_write
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

# Game configuration

Using **config.json** file you could change many game options such as:

- textures - you can add paths to your own textures and change the appearance of the player or the enemies. 
You can also change the textures that indicate the number of lives, as well as individual parts of the map
- map - you could build your own map by creating .txt file and adding it's path to config.
- player initial position 
- amount of enemies
- window size
- start delay in seconds
- amount of *special* points


# Creating new map

The map is created from a txt file which must contain only ***0*** or ***1***. ***0*** represents free space
and ***1*** represents an obstacle. Trying to create a map in txt file with any other characters or different 
line lengths will cause critical error and the game won't start. You could find example of map in [**mapTamplate.txt**](https://github.com/igorpieniek/PacMan/blob/master/maps/mapTemplate.txt).

# Details

## Map Creator 

The main purpose of this creator was to reduce the number of rendered objects on the screen by creating 
only one texture based on the current map contained in a .txt file. 

The algorithm created, tries to define the class of each map cell (for example: turn, straight obstacle,
empty space) using predefined patterns, so it is able to render the appropriate textures for each map cell.
This method is based on **Hit-or-miss transform**. After defining the class of each cell, a process takes 
place in which the map is assembled into a single png image from small pieces of textures (whose paths are 
defined in the config.json file in **mapElementsImg**).

*Caution: textures defined as map elements must be in the same size!*


## Separation of mechanics from the graphic layer
The separation of the mechanics from the graphics layer was achieved by using the mediator and observer 
patterns. Head of mechanical layer is [GameRules](https://github.com/igorpieniek/PacMan/blob/master/src/Gameplay/GameTools/GameRules.h) 
class and main class on the graphic layer is [GraphicGLManager](https://github.com/igorpieniek/PacMan/blob/master/src/Graphic/GraphicManager/GraphicGLManager.h).
They communicate with each other using the created system of events.



## Ghost's move algorithm

Normally, ghosts move in a random way. Before each move, the possible directions of movement are checked 
and then one of them is randomly selected. The opposite direction is excluded from the randomisation to 
prevent the opponent from locking on. The algorithm ([RandMove](https://github.com/igorpieniek/PacMan/blob/master/src/Gameplay/Behaviours/RandMove.h))
is passed to the ghost class using the design pattern "strategy".

### A* algorithm

A custom implementation of the [A*](https://github.com/igorpieniek/PacMan/blob/master/src/Gameplay/Behaviours/Astar/Astar.h) algorithm has been added. In the game it is used to find and determine the shortest path between ghosts 
and their base. To be more specific, it is used after player attacks disabled ghost - in this moment internal ghost's algorithm is changed to A* ([AstarMovement](https://github.com/igorpieniek/PacMan/blob/master/src/Gameplay/Behaviours/Astar/AstarMovement.h))



## Timer

Sometimes a specific function needs to be called after a certain period of time. For this purpose the class 
[Timer](https://github.com/igorpieniek/PacMan/blob/master/src/Gameplay/GenericTools/Timer.h) was created which works 
in a non-blocking way by calling specific functions after a certain time. It is a single shot timer.
