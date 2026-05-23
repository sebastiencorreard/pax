target=table2x2 table2x3 table2x4 table2x5 table2x6 table2x7 table3x3 table3x4 table3x5 table4x4

#include "header.inc"
#define TIT Arithmetic table

#if #TARGET (table2x2)
 \title{TIT 2x2}
# define ROWS 2
# define COLS 2
#endif

#if #TARGET (table2x3)
 \title{TIT 2x3}
# define ROWS 2
# define COLS 3
#endif

#if #TARGET (table2x4)
 \title{TIT 2x4}
# define ROWS 2
# define COLS 4
#endif

#if #TARGET (table2x5)
 \title{TIT 2x5}
# define ROWS 2
# define COLS 5
#endif

#if #TARGET (table2x6)
 \title{TIT 2x6}
# define ROWS 2
# define COLS 6
#endif

#if #TARGET (table2x7)
 \title{TIT 2x7}
# define ROWS 2
# define COLS 7
#endif

#if #TARGET (table3x3)
 \title{TIT 3x3}
# define ROWS 3
# define COLS 3
#endif

#if #TARGET (table3x4)
 \title{TIT 3x4}
# define ROWS 3
# define COLS 4
#endif

#if #TARGET (table3x5)
 \title{TIT 3x5}
# define ROWS 3
# define COLS 5
#endif

#if #TARGET (table4x4)
 \title{TIT 4x4}
# define ROWS 4
# define COLS 4
#endif

#include "common.inc"
#include "total.inc"
