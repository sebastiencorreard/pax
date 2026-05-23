#if defined TARGET_seriestat
\text{name_human=jongens,meisjes}
\text{name_enonce=De lengte van de,
  garçons van het plaatselijke jeugdvoetbal elftal is}
\text{name_question=Maak de onderstaande tabel verder af}
\text{name_head=Lengte,Aantal,Frequentie}
\text{name_inst=Rond de frequenties af op 0.1% nauwkeurig.}
\text{name_hint=Hier zie je het Histogram}
#endif
#if defined TARGET_repartition || defined TARGET_repartition2
\text{name_enonce1=Hier onder staat de verdeling van de  behaalde cijfers
  door, leerlingen.}
\text{name_head=Klassenverdeling v/d cijfers,Aantal,Cumulatieve aantal, Frequentie}
#endif
#if defined TARGET_repartition
\text{name_inst=Geef je antwoorden op 1 decimaal nauwkeurig}
#endif
#if defined TARGET_repartition2
\text{name_enonce2=Hier onder staat de ingevulde tabel,
  We gaan nu met wat andere cijfers aande slag.
  Vul ook deze tabel verder in}
\text{name_inst=Geef je antwoorden op 1 decimaal nauwkeurig}
#endif
#if defined TARGET_effpourcent || defined TARGET_pourcentstat || defined TARGET_pourcentcirc || defined TARGET_pourcentangle
\text{listefr=rood, blauw,oranje,grijs, groen, paar}
\text{name_effectif=Aantallen}
\text{name_enonce=Hieronder zie je een cirkeldiagram die een populatie van,
  individuen met,eigenschappen weergeeft}
#endif
#if defined TARGET_effpourcent
\text{name_question=Vul de onderstaande tabel in
  (rond je uitkomsten af op gehele getallen)}
#endif
#if defined TARGET_pourcentstat
\text{name_question=Geef het aantal individuen voorgesteld door de kleur }
\text{name_inst=rond je getal af op "helen"}
\text{name_answer=Aantal individuen}
#endif
#if defined TARGET_pourcentcirc
\text{name_question=Bereken het percentage individuen met
  de eigenschap weergegeven door de kleur}
\text{name_answer=Percentage}
#endif
#if defined TARGET_pourcentangle
\text{name_question= Wat is de hoek in graden die hoort bij het aantal individuen
  met de eigenschap}
\text{name_inst=Rond je getal af op hele graden nauwkeurig.}
\text{name_answer=Hoek}
#endif
#if defined TARGET_Moyennesetcoef
\text{name_enonce=NNNN heeft gemiddeld een,
  gehaald voor wiskunde (het aantal toetsen was XXXX)<br>
  Voor frans heeft NNNN een,
  gemiddeld gescoord (het aantal toetsen was  YYYY) en<br>
  voor natuurkunde heeft NNNN  een,
  gemiddeld (het aantal toetsen was  ZZZZ).
  Wat is het totale gemiddelde van NNNN
    (Rond je antwoord af op 1 cijfer achter de komma nauwkeurig)}
\text{name_answer=Totaal gemiddelde}
#endif
#if defined TARGET_mediane
\text{name_enonce=Les tailles arrondies à un nombre entier de centimètres de,
  garçons d'un club de football sont les suivantes&nbsp;}
\text{name_question=Calculer la médiane de cette série statistique.}
\text{name_answer=La médiane est égale à,Médiane}
\matrix{name_hint=Attention : ne pas oublier de ranger les tailles par ordre croissant.,
  Ensuite, la médiane est la valeur centrale (ou la moyenne des deux valeurs centrales).}
\text{name_feed1=Attention : ne pas oublier de ranger les tailles
  par ordre croissant.}
\text{name_feed2=Attention : vous confondez la moyenne et la médiane.}
\text{name_feed3=Attention : La médiane se trouve parmi un des
  nombres de la série, ou de la moyenne de deux d'entre eux.}
#endif
#if defined TARGET_meanw || defined TARGET_mean
\text{name_question=Bereken van deze statistische reeks,
  het gemiddelde,de maximale waarde,de minimale waarde,
  de spreidingsbreedte}
\text{name_answer=Gemiddelde,Maximum,Minimum,Spreidingsbreedte}
\text{name_feed=De spreidingsbreedte is het maximum - het minimum.}
\text{name_head=Waarden, Coeff.}
#endif
#if defined TARGET_meanw
\text{name_enonce=Zie hier een statistische reeks met bijbehorende coefficienten}
#endif
#if defined TARGET_mean
\text{name_enonce=Zie hier een statistische reeks}
#endif
#if defined TARGET_baton
\text{matiere=randitem(mathématiques,français,physique,chimie,géographie,histoire,anglais,biologie)}
\text{name_enonce=Après un contrôle de,
  le professeur dresse un tableau des notes obtenues par les élèves de la classe&nbsp;}
\matrix{name_head=Note,sur 20
  Nombre d'élèves,ayant la note, indiquée au-dessus}
\text{name_question=Représenter la série des notes par un diagramme en bâtons,
  en glissant/déposant les bâtons dans le dessin.}
\text{name_cond=Le diagramme est correct}
\text{name_feed=La hauteur du bâton pour,la note,les notes,n'est pas correcte.}
#endif
#if defined TARGET_Moyenne
\text{name_enonce=heeft voor een eerste proefwerk het cijfer XXXX gehaald,
  Voor een tweede proefwerk behaalde een YYYY.
  Voor een derde proefwerk haalde het cijfer.
  Wat is NNNN's gemiddelde cijfer?
  Rond je uitkomst af op 1 cijfer achter de komma
}
\text{name_answer=Moyenne annuelle}
#endif
