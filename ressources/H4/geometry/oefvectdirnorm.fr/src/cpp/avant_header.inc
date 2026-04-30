\author{Euler,Académie de Versailles}
%%% GM %%%
\language{\lang}
\email{euler.wims@ac-versailles.fr}
\format{html}
\computeanswer{no}

\if{\lang=fr}{
#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose
\keywords{colinéarité}
#endif
#if defined TARGET_06memenorme
\keywords{norme}
#endif
#if defined TARGET_04egaux || defined TARGET_05oppose || defined TARGET_07memenormenoncoli
\keywords{colinéarité,norme}
#endif

\credits{Figure réalisée avec \img{\imagedir/logo_GGB.png} GeoGebra}
}
