target=2term0 3term0 3term1 4term0 4term1 4term2 5term0 5term1 5term2 5term3 6term0 6term1 7term0 8term0

#include "header.inc"

#if #TARGET (2term0)
 \title{2 èlena}
 \integer{style=1}
#endif

#if #TARGET (3term0)
 \title{3 èleni}
 \integer{style=2}
#endif

#if #TARGET (3term1)
 \title{3 èleni z oklepaji}
 \integer{style=3}
#endif

#if #TARGET (4term0)
 \title{4 èleni}
 \integer{style=4}
#endif

#if #TARGET (4term1)
 \title{4 èleni in 1 oklepaj}
 \integer{style=5}
#endif

#if #TARGET (4term2)
 \title{4 èleni in 2 oklepaja}
 \integer{style=6}
#endif

#if #TARGET (5term0)
 \title{5 èlenov}
 \integer{style=7}
#endif

#if #TARGET (5term1)
 \title{5 èlenov in 1 oklepaj}
 \integer{style=8}
#endif

#if #TARGET (5term2)
 \title{5 èlenov in 2 oklepaja}
 \integer{style=9}
#endif

#if #TARGET (5term3)
 \title{5 èlenov in 3 oklepaji}
 \integer{style=10}
#endif

#if #TARGET (6term0)
 \title{6 èlenov}
 \integer{style=11}
#endif

#if #TARGET (6term1)
 \title{6 èlenov 1 oklepaj}
 \integer{style=12}
#endif

#if #TARGET (7term0)
 \title{7 èlenov}
 \integer{style=13}
#endif

#if #TARGET (8term0)
 \title{8 èlenov}
 \integer{style=14}
#endif

#include "confparm3.inc"
#include "common.inc"
