#if defined TARGET_1 || defined TARGET_2 || defined TARGET_3 || defined TARGET_6
\text{name_choix=abscisse, ordonnée, altitude,côte}
\text{name_choix2=l'abscisse, l'ordonnée, l'altitude,la cote}
#endif
#if defined TARGET_1 || defined TARGET_2 || defined TARGET_3
\text{name_feed=Le point, a comme coordonnées, est}
#endif
#if defined TARGET_1
\text{name_instruction=Donner, du point}
#endif
#if defined TARGET_2 || defined TARGET_3
\text{name_instruction=Donner les coordonnées du point}
#endif
#if defined TARGET_4 || defined TARGET_5
\text{name_instruction=Cliquer sur le point de coordonnées}
#endif
#if defined TARGET_6
\text{name_instruction=Cliquer sur les sommets du pavé dont, est }
#endif

\text{name_warning=Les coordonnées de certains sommets du pavé sont écrites sur la figure.}

\text{name_warning_magn=Seuls certains points sont cliquables, contenant la solution.}
