#if defined TARGET_flageu || defined TARGET_flagas || defined TARGET_flagaf || defined TARGET_flagam || defined TARGET_flagoc || defined TARGET_flagall || defined TARGET_flagbig
\text{name_instruction=Establish the correspondance between the flags and
  the countries}
\text{name_answer=The correspondance}
#endif
#if defined TARGET_mapall || defined TARGET_mapbig
\text{af=of Africa}
\text{am=of America}
\text{as=of Asia}
\text{eu=of Europe}
\text{oc=of Oceanic}
\text{continent=}
#endif
#if defined TARGET_mapeu || defined TARGET_mapas || defined TARGET_mapaf || defined TARGET_mapam || defined TARGET_mapoc || defined TARGET_mapall || defined TARGET_mapbig
\text{name_instruction=What is this country,
  This is a country of}
\text{name_answer=Name of the country,Continent}
# if defined TARGET_mapeu
 \text{continent=of Europe}
# endif
# if defined TARGET_mapas
 \text{continent=of Asia}
# endif
# if defined TARGET_mapaf
 \text{continent=of Africa}
# endif
# if defined TARGET_mapam
 \text{continent=of American continent}
# endif
# if defined TARGET_mapoc
 \text{continent=of Oceanic countries}
# endif
#endif
