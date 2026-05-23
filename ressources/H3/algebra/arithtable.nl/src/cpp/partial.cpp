target=partial2x2 partial2x3 partial2x4 partial3x3 partial3x4

#include "header.inc"
#define TIT Partial table
#define PARTIAL 1

#if #TARGET (partial2x2)
 \title{TIT 2x2}
# define ROWS 2
# define COLS 2
 \text{matrix=1,0;0,0}
#endif

#if #TARGET (partial2x3)
 \title{TIT 2x3}
# define ROWS 2
# define COLS 3
 \text{matrix=1,0,0;0,1,0}
#endif

#if #TARGET (partial2x4)
 \title{TIT 2x4}
# define ROWS 2
# define COLS 4
 \text{matrix=1,0,1,0;0,1,0,0}
#endif

#if #TARGET (partial3x3)
 \title{TIT 3x3}
# define ROWS 3
# define COLS 3
 \text{matrix=1,1,0;1,0,0;0,0,1}
#endif

#if #TARGET (partial3x4)
 \title{TIT 3x4}
# define ROWS 3
# define COLS 4
 \text{matrix=1,0,1,1;1,0,0,0;0,1,1,0}
#endif

#include "partial1.inc"
#include "common.inc"
#include "partial2.inc"

