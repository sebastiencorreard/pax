\title{Question 1229 Probabilité}
\keywords{mental_calculation,probability,events,independent_events}

\text{quest=random(le même résultat,le même résultat,le même résultat,face,pile)}
\integer{a=randint(2,3,4)}
\text{atxt=slib(numeration/ecriturelettre \a)}
\text{enonce=On lance \a fois une pièce de monnaie équilibrée.<br>Quelle est la probabilité d&#39;avoir \atxt fois \quest &#63;<br>Réponse &#58;}
\text{enonceb=}
\rational{rep=\quest issametext le même résultat?simplify(2*(1/2)^\a):simplify((1/2)^\a)}
\text{feedback=\quest issametext le même résultat?Cela revient à l'événement avoir \atxt pile ou \atxt face.:\(\left(\frac{1}{2}\right)^\a\)}
