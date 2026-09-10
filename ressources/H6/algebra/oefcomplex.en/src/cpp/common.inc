\language{en}
\range{-5..5}
#if defined TARGET_eqmod
\precision{3000}
#elif defined TARGET_Trianglequilat || defined TARGET_sqrt || defined TARGET_cbrt
\precision{1000}
#else
\precision{10000}
#endif
\format{html}
#if defined TARGET_Trianglequilat
\author{Bernadette, Perrin-Riou}
\email{bernadette.m.riou@orange.fr}
#else
\author{Gang, XIAO}
\email{xiao@unice.fr}
#endif
#if defined TARGET_argask || defined TARGET_arggiven || defined TARGET_cbrt || defined TARGET_fraction || defined TARGET_modsum2 || defined TARGET_pentaroot || defined TARGET_quadpoly || defined TARGET_suminv || defined TARGET_sumofi
\computeanswer{no}
#else
\computeanswer{yes}
#endif
