\text{ListImage=julie.png,
geom.png,
tableau.png,
phonk.png,
inconnu.png,
graphe.png,
algebra.png,
canonick.png}

\text{ListImage=\ListImage[\list]}
\integer{nb_meth=items(\list)}
\text{ListDescr=fille nommée Julie Dédeugénie pour répondre,
  garçon nommé GéOMaitrie,
  fille nommée Métab Laurie,
  fille nommée Phonk Siona,
  garçon nommé Constantin Connu,
  garçon nommé Vlad Egraph,
  fille nommée Chantal Gèbre,
  garçon nommé Canot Nick}
\text{Listdesc=\ListDescr[\list]}

\text{tch1=Je sais <b>répondre</b> sans aide supplémentaire.}
\text{tch2=On peut utiliser un logiciel de <b>géométrie</b>.}
\text{tch3=On peut réaliser des <b>tableaux</b> de valeurs.}
\text{tch4=Il y a un lien entre les <b>fonctions</b>.}
\text{tch5=On peut résoudre une <b>équation</b> pour l'arrivée au sol.}
\text{tch6=On peut utiliser la <b>courbe</b> du trinôme.}
\text{tch7=On peut <b>résoudre</b> un système d'équations.}
\text{tch8=Et si on essayait de <b>factoriser</b> une partie.}
\text{tch9=C'est le moment de trouver ou utiliser des <b>formules</b>.}

\text{tch=\tch1,
\tch2,
\tch3,
\tch4,
\tch5,
\tch6,
\tch7,
\tch8,
\tch9}

\text{tch=\tch[\list2]}

\text{trep=répondre,
 géométrie,
 tableaux,
 fonctions,
 équation,
 courbe,
 résoudre,
 factoriser,
 formules}
\text{trep=\trep[\list2]}

\text{color=yellow,darkturquoise,lightgrey,pink,lightgreen,mediumaquamarine,coral,lightseagreen}
\text{color=\color[\list]}
\text{bch1=slib(text/balloon [\tch[1]],\color[1],250,100,triangle=left-in)}
\text{bch2=slib(text/balloon [\tch[2]],\color[2],250,100,triangle=left-in)}
\text{bch3=slib(text/balloon [\tch[3]],\color[3],250,100,triangle=left-in)}
\text{bch4=slib(text/balloon [\tch[4]],\color[4],250,100,triangle=left-in)}
\text{bch5=slib(text/balloon [\tch[5]],\color[5],250,100,triangle=left-in)}


#if TYPE==1
\text{consigne=<p>Répondre directement ou choisir une méthode qui mènera au résultat.</p>}
#endif

#if TYPE==2
\text{consigne=<p>Lorsqu'on clique sur l'icone, la méthode choisie est présentée sans pouvoir répondre puis on peut choisir
de voir une autre méthode.</p>
<p>Lorsqu'on a trouvé, on peut répondre aux questions en cliquant sur l'icone de répondre.</p>}
#endif

#if TYPE==3
\text{consigne=<p>Lorsqu'on clique sur l'icone, la méthode choisie est présentée et permet de trouver certaines réponses puis on peut choisir
de voir une autre méthode.</p>
<p>Lorsqu'on a trouvé les réponses, on peut répondre aux questions en cliquant sur l'icone de répondre.</p>}
#endif
