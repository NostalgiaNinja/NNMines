# NNMines
Nostalgia Ninja's implementation of a Minesweeper clone, written in SDL 2.0 C++

## What is this?
This is a full implementation of Minesweeper, written in just under a month on and off to learn SDL 2.0 and C++ for game development.

## Building:

To build the Minesweeper Clone, you'll need to consider which target you're going to run for:

### Windows:

Open the SLN file, adjust your SDL 2.0 include and library files and build as appropriate.

### Linux:

Make sure SDL2, SDL2-Image and SDL2-TTF dev are installed from your Linux distributor.  You will need to change the #includes so that they go to the right path (SDL2/SDL*.h where * is your library that needs to be opened.  Check the SDL2 documentation for more info.)

run ```make```

run ```./NNMines```
