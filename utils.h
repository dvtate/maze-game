#ifndef UTILS_H
#define UTILS_H

// a POD data structure to hold coordinates.
struct coord9x9 {
  unsigned int r : 4, 
               c : 4; 

};

// used for storing D-pad input
struct inputDir {
  bool up    : 1,
       down  : 1,
       left  : 1,
       right : 1;
};

// used for storing sub-grid values
struct subgrid_t {
  // matrix is more programmer-friendly
  // bit-field is more memory-optimized
  // save memory, save lives ;)
  bool m00 : 1, m01 : 1, m02 : 1,
       m10 : 1, m11 : 1, m12 : 1,
       m20 : 1, m21 : 1, m22 : 1;
};


#endif
