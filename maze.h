#ifndef MAZE_H
#define MAZE_H

extern char maze[9][10];


namespace Maze {

  const char mazes[5][9][10] = {
    {
      "S ## # # ",
      "   # # # ",
      " ### # # ",
      "     # # ",
      "# #### # ",
      "  #    # ",
      " ## ## # ",
      "  #  # # ",
      "#    #  E"
    }, {
      "E        ",
      "### ###  ",
      "# ##   # ",
      "#  # # # ",
      "##  S  # ",
      "   # # # ",
      " ###   # ",
      " #  ###  ",
      "        #"
    }, {
      "S #    # ",
      "  # # ## ",
      " ## #    ",
      "    #  # ",
      "###### # ",
      "       # ",
      "## # ### ",
      " # #    #",
      "   # ## E"
    }, {
      "         ",
      " # ### # ",
      "##   # # ",
      " ### # # ",
      "S  # # #E",
      " # #   ##",
      " # # #   ",
      "## ### # ",
      "       # "
    }, {
      "S # # # #",
      " #       ",
      "  # ## # ",
      " ## # #  ",
      "      # #",
      " #####   ",
      "#      # ",
      "  ##### #",
      "#       E"
    }

  };

  // Hi!
  const char hello[9][10] = {
    "S########",
    "    #    ",
    " ########",
    "         ",
    " ##### # ",
    "         ",
    " # ######",
    "         ",
    "        E"
  };
  
  // LOL GG
  const char gg[9][10] = {
    "         ",
    "         ",
    "         ",
    " ##   ## ",
    "#  # #  #",
    "#    #   ",
    "# ## # ##",
    "#  # #  #",
    " ##   ## "
  };
    
  
  // set the maze to another maze
  void setMaze(const char newMaze[9][10]){
    for (uint8_t r = 0; r < 9; r++)
      for (uint8_t c = 0; c < 9; c++)
        maze[r][c] = newMaze[r][c];
  }

  // randomly generate the maze
  inline void pickMaze(){
    
    // set a random maze using time as a random seed
    setMaze(mazes[micros() % 5]);

  }

}


#endif
