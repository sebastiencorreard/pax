target=typed2x2 typed2x3 typed2x4 typed3x3 typed3x4

#include "header.inc"

#define PARTIAL 1
#define TYPED 1

#if defined TARGET_typed2x2
# define NUM 2x2
# define ROWS 2
# define COLS 2
 \text{matrix=1,0;0,0}
#endif

#if defined TARGET_typed2x3
# define NUM 2x3
# define ROWS 2
# define COLS 3
 \text{matrix=1,0,0;0,1,0}
#endif

#if defined TARGET_typed2x4
# define NUM 2x4
# define ROWS 2
# define COLS 4
 \text{matrix=1,0,1,0;0,1,0,0}
#endif

#if defined TARGET_typed3x3
# define NUM 3x3
# define ROWS 3
# define COLS 3
 \text{matrix=1,1,0;1,0,0;0,0,1}
#endif

#if defined TARGET_typed3x4
# define NUM 3x4
# define ROWS 3
# define COLS 4
 \text{matrix=1,0,1,1;1,0,0,0;0,1,1,0}
#endif

#include "lang_titles.inc"
#include "partial1.inc"
#include "lang.inc"
#include "common.inc"
#include "typed.inc"
