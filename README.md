# 42_so_long - The Lettuce Magician
This project is a very small 2D game. Its purpose is to work with textures, sprites, and some other very basic gameplay elements.

![so_long](https://github.com/m-bartos/42_so_long/assets/28412526/d26f6fce-0aa9-4d4f-b785-274825eb22d4)

## Game:
The player’s goal is to collect every collectible (lettuce) present on the map with the magician, and then escape
choosing the shortest possible route without touching the enemy (skull).
* The player can move in 4 directions: up, down, left, and right with WSAD keys
* The player is not able to move into walls
* At every move, the current number of movements is displayed in the shell and on the screen
* The game can be closed by clicking the ESC key or cross on the window’s frame 

## Maps:
* The maps are located in the map folder with .ber suffix
* You can create your own map
* The map can be composed of only these 6 characters:
  - 0 for an empty space
  - 1 for a wall
  - C for a collectible
  - E for a map exit
  - P for the player’s starting position
  - B for the enemy’s position
* The map must contain 1 exit, at least 1 collectible, and 1 starting position to
be valid
* The map must be rectangular
* The map must be closed/surrounded by walls
* Valid path in the map is checked

## What I learned during this project:
- How to set up a new external library (makefile, documentation, etc.)
- How to work with graphical library MLX42
- How to handle windows, events (hooks), pictures and textures, colors, etc
- Got more familiar with structs and struct pointers

## Thanks and credits to:
* [rone3190 - wizard image](https://rone3190.itch.io/wizard-128x128)
* [Leatherplaid - wall image](https://leatherplaid.itch.io/pixel-walls-and-floor-64x64-and-128x128)
* [TwicePeace - gate images](https://twicepeace.itch.io/rpg-maker-maps)
* [Game Assets - skull and bone images](https://free-game-assets.itch.io/free-undead-loot-game-icons?download)
