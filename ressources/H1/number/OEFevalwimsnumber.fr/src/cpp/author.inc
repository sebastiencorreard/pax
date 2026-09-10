#if defined TARGET_arrondiunit || defined TARGET_arrondiunitguide || defined TARGET_arrondix || defined TARGET_arrondixguide || defined TARGET_arrondixrelie || defined TARGET_plusproche
\language{fr}
\author{Lionel, Verbecq}
\email{lionel.verbecq@ac-versailles.fr}
\format{html}
\precision{10000}
#else
# if defined TARGET_oefecrit2 || defined TARGET_oefecrit3 || defined TARGET_oefecrit4 || defined TARGET_oefecrit5
\author{Jean-Luc,Donadoni;Christophe, Caillet}
# else
\langage{fr}
\author{Jean-Luc,Donadoni}
# endif
\email{jluc.donadoni@laposte.net}
\format{html}
\range{-5..5}
\computeanswer{no}
#endif
