#if defined TARGET_solide1 || defined TARGET_solide2 || defined TARGET_solide3 || defined TARGET_solide4
\text{name_solide=cilinder,prisma,anders}
# if defined TARGET_solide1 || defined TARGET_solide3
\text{name_enonce=Kies de juiste omschrijving van de onderstaande 'objecten'}
# endif
# if defined TARGET_solide2
\text{name_enonce=Leg de correcte verbanden.}
# endif
# if defined TARGET_solide4
\matrix{name_enonce=Geef voor het onderstaande ruimtelijke object
  Het totale aantal vlakken
  Het totale aantal hoekpunten
  Het totale aantal zijden}
# endif
#endif
#if defined TARGET_solide5 || defined TARGET_solide6
\text{name_figure=driehoekig,rechthoekig,zeshoekig,vierkant,
  dodecagonaal,vijfhoekig,achthoekig}
\text{name_enonce=van deze prisma is het grondvlak}
#endif
#if defined TARGET_solide10 || defined TARGET_solide11 || defined TARGET_solide12
\matrix{name_enonce=Geef een vlak parallel aan vlak
  Geef een vlak loodrecht op vlak
  Geef alle loodrechte vlakken op vlak}
#endif
#if defined TARGET_solide7 || defined TARGET_solide8 || defined TARGET_solide9
\matrix{name_enonce=Geef een zijde, aan,op
  Geef de zijden, aan,op}
# if defined TARGET_solide7 || defined TARGET_solide8
\text{name_prop=parallel,parallel}
\text{name_prop2=loodrecht,loodrecht}
# endif
# if defined TARGET_solide9
\text{name_prop=loodrecht,loodrecht}
# endif
#endif
