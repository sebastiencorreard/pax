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
\text{choixrep=éteinte, allumée}
\text{name_enonce=Voici un circuit électrique contenant générateur, lampes et,
  diodes,diode}
\text{name_question=La lampe rouge est, et la lampe bleue est}
\text{name_answer=Lampe rouge,Lampe verte}
#endif
#if defined TARGET_lampe
\text{listechoix= surtension,tension adaptée, sous-tension}
\text{name_enonce=Les lampes,sont marquées,
  Le générateur est marqué, La  lampe,est en}
\text{name_answer=Lampe}
#endif
#if defined TARGET_lampe2
\text{name_enonce=Les lampes,sont marquées,
  Elles sont en tension adaptée (elles éclairent normalement).}
\text{name_question=Quelle tension doit-on lire sur les plaques signalétiques du générateur}
\text{name_answer=Tension du générateur}
#endif
