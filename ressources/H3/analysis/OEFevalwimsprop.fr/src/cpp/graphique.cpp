target=graphique1 graphique2 graphique3 graphique4 graphique5

#include "author.inc"
#if defined TARGET_graphique1
# define NUM 1
#endif
#if defined TARGET_graphique2
# define NUM 2
#endif
#if defined TARGET_graphique3
# define NUM 3
#endif
#if defined TARGET_graphique4
# define NUM 4
#endif
#if defined TARGET_graphique5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"
\integer{cx=randitem(2,4,5)}
\integer{cy=randitem(4,5,10)}
\integer{p=randint(9..13)}
\text{donnees=0,0,randint(6..8),\p,randint(12..16),\p,20,randint(17..19)}

#if defined TARGET_graphique1
 \text{name=slib(lang/fname fr,boy)}
 \integer{p=randint(9..13)}
 \text{donnees=0,0,randint(6..8),\p,randint(12..16),\p,20,randint(17..19)}
 \text{enonce=Le graphique ci-dessous représente la distance parcourue, en kilomètres, par \name en fonction du temps en heures.}
 \text{don=randrow(Quelle est la durée du trajet de \name,(\donnees[7]-\donnees[1])/\cx
  Combien de temps dure sa pause,(\donnees[5]-\donnees[3])/\cx)}
 \text{question=item(1,\don)}
 \text{unit=Heures}
 \real{rep=item(2,\don)}
 \text{namey=100km}
#endif
#if defined TARGET_graphique2
 \text{name=slib(lang/fname fr,boy)}
 \text{enonce=Le graphique ci-dessous représente la distance parcourue, en kilomètres, par \name en fonction du temps en heures.}
 \text{question=Quelle distance a-t-il parcouru}
 \integer{p=randint(9..13)}
 \text{donnees=0,0,randint(6..8),\p,randint(12..16),\p,20,randint(17..19)}
 \text{unit=Kilomètres}
 \real{rep=(\donnees[8]-\donnees[2])/\cy}
 \text{namey=100km}
#endif
#if defined TARGET_graphique3
 \text{name=slib(lang/fname fr,boy)}
 \text{enonce=Le graphique ci-dessous représente la distance parcourue, en kilomètres, par \name en fonction du temps en heures.}
 \text{question=Quelle est la vitesse moyenne de \name sur le trajet}
 \integer{p=randint(9..13)}
 \text{donnees=0,0,randint(6..8),\p,randint(12..16),\p,20,randint(17..19)}
 \text{unit=km/h.<div class="wims_instruction">Arrondir le résultat à l'unité.</div>}
 \integer{rep=100*(\donnees[8]-\donnees[2])/(\donnees[7]-\donnees[1])*\cx/\cy}
 \text{namey=100km}
#endif
#if defined TARGET_graphique4
 \text{enonce=Le graphique ci-dessous représente le volume d'eau, en litres, contenu dans un réservoir en fonction du temps.}
 \integer{p=randint(9..13)}
 \integer{p2=randint(3..6)}
 \text{donnees=0,randint(3..6),randint(3..5),\p,randint(8..10),\p2,randint(12..16),\p2,20,randint(17..19)}
 \text{don=randrow(Combien de litres d'eau le réservoir contient-il au début du relevé,1000*\donnees[2]/\cy
  Combien de litres d'eau le réservoir contient-il à la fin du relevé,1000*\donnees[10]/\cy
  Combien de litres d'eau le réservoir contient-il quand il commence à se vider,1000*\donnees[4]/\cy)}
 \text{question=item(1,\don)}
 \integer{rep=item(2,\don)}
 \text{unit=Litres.<div class="wims_instruction">Arrondir le résultat à l'unité.</div>}
 \text{namey=1000L}
#endif
#if defined TARGET_graphique5
 \text{enonce=Le graphique ci-dessous représente le volume d'eau, en litres, contenu dans un réservoir en fonction du temps.}
 \integer{p=randint(9..13)}
 \integer{p2=randint(3..6)}
 \text{donnees=0,randint(3..6),randint(3..5),\p,randint(8..10),\p2,randint(12..16),\p2,20,randint(17..19)}
 \text{don=randrow(Pendant combien de temps le bassin se vide-t-il,(\donnees[5]-\donnees[3])/\cx)}
 \text{question=item(1,\don)}
 \real{rep=item(2,\don)}
 \text{unit=Heures.}
 \text{namey=1000L}
#endif
\text{question=\question&nbsp;}
\text{dessin=slib(draw/repere 480,480,40,0,20,0,20,1,1,black,grey)}
\text{dessin=\dessin
range -2,22,-2,22
text black,-2,\cy+0.4,medium,\namey
text black,\cx-0.3,-0.3,medium,1H
linewidth=2
polyline red,\donnees}
\text{figure=draw(480,480
\dessin)}

\statement{
\enonce
\question?
<div class="wimscenter"><img src="\figure" alt=""></div>
<div class="spacer">
<label for="reply1"><b>Votre réponse</b>:</label> \embed{r1,5} \unit.
</div>}

\answer{}{\rep}{type=numexp}
