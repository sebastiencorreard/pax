#if defined TARGET_flageu || defined TARGET_flagas || defined TARGET_flagaf || defined TARGET_flagam || defined TARGET_flagoc || defined TARGET_flagall || defined TARGET_flagbig
\text{name_instruction=Établir la correspondance correcte entre les drapeaux et les
  pays&nbsp;}
\text{name_answer=La correspondance}
#endif
#if defined TARGET_mapall || defined TARGET_mapbig
\text{af=africain}
\text{am=américain}
\text{as=asiatique}
\text{eu=européen}
\text{oc=océanique}
\text{continent=}
#endif
#if defined TARGET_mapeu || defined TARGET_mapas || defined TARGET_mapaf || defined TARGET_mapam || defined TARGET_mapoc || defined TARGET_mapall || defined TARGET_mapbig
\text{name_instruction=Quel est ce pays,
  C'est un pays}
\text{name_answer=Nom du pays,Continent}
# if defined TARGET_mapeu
\text{continent=d'Europe}
# endif
# if defined TARGET_mapas
\text{continent=d'Asie}
# endif
# if defined TARGET_mapaf
\text{continent=d'Afrique}
# endif
# if defined TARGET_mapam
\text{continent=du continent américain}
# endif
# if defined TARGET_mapoc
\text{continent=de l'Océanie}
# endif
#endif
