#if defined TARGET_nomsymbol || defined TARGET_nomsymbolcorr
\text{name_feed=Voici la correspondance entre le symbole et
 le nom du composant.}
\matrix{name_data=moteur,du
  générateur,du
  résistance,de la
  ampèremètre,de l'
  voltmètre,du
  interrupteur fermé,de l'
  interrupteur ouvert, de l'
  lampe,de la
  diode électroluminescente,de la}
# if defined TARGET_nomsymbol
\text{name_instruction=Cliquer sur le symbole}
# endif
# if defined TARGET_nomsymbolcorr
\text{name_instruction=Glisser-déposer le symbole du
  composant électrique sur son nom.}
# endif
#endif
#if defined TARGET_diode
\text{choixrep=uit,aan}
\text{name_enonce=Hier zie je een electrisch schema van een stroombron (Batterij),
  lampjes en, lampjes en, een paar dioden,een diode}
\text{name_question= De rode lamp is, De blauwe lamp is}
\text{name_answer=rode lamp,blauwe lamp}
#endif
#if defined TARGET_lampe
\text{listechoix=te hoge spanning,correcte spanning, te lage spanning}
\text{name_enonce=De lampen,zijn bedoeld voor,
  De Batterij,heeft dus een}
\text{name_answer=Lamp}
#endif
#if defined TARGET_lampe2
\text{name_question=Welke spanning geeft de batterij}
\text{name_answer=Welke spanning geeft de batterij}
#endif
