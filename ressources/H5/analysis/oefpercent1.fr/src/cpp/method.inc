\text{ListImage=julie.png,
dessin.png,
tableau.png,
operater.png,
schema.png,
fraction.png}
\text{ListImage=\ListImage[\list]}
\integer{nb_meth=items(\list)}
\text{ListDesc=fille nommée Julie Dédeugénie pour répondre,
  garçon nommé Lébodé Sinclair pour faire un dessin,
  fille nommée Métab Laurie pour faire des tableaux,
  garçon nommé Léo Pérateur pour utiliser des opérateurs,
  fille nommée Mechet Marie pour réaliser un schéma,
  garçon nommé Gaspard Tition pour utiliser des fractions}
\text{Listdesc=\ListDesc[\list]}

\text{tch=Je sais <b>répondre</b> sans aide supplémentaire.,
 Un <b>dessin</b> peut aider à comprendre l'énoncé.,
 Le problème peut être résolu avec un <b>tableau</b> de proportionnalité.,
 Trouver le bon <b>opérateur</b> est souvent la clef du problème.,
 Réaliser un <b>schéma</b> des ensembles guide vers la solution.,
 Les pourcentages sont des proportions donc des <b>fractions</b>.,
 On peut réaliser un arbre avec les <b>opérateurs</b> sous forme de pourcentages.}

\text{tch=\tch[\list2]}

\text{trep=répondre,dessin,tableau,opérateur,schema,fraction}
\text{trep=\trep[\list2]}

\text{color=yellow,lightblue,lightgrey,paleturquoise,lightsalmon,sandybrown}
\text{color=\color[\list2]}
text{bch1=slib(text/balloon [\tch[1]],\color[1],250,100,triangle=left-in)}
text{bch2=slib(text/balloon [\tch[2]],\color[2],250,100,triangle=left-in)}
text{bch3=slib(text/balloon [\tch[3]],\color[3],250,100,triangle=left-in)}
text{bch4=slib(text/balloon [\tch[4]],\color[4],250,100,triangle=left-in)}
text{bch5=slib(text/balloon [\tch[5]],\color[5],250,100,triangle=left-in)}
text{bch6=slib(text/balloon [\tch[6]],\color[6],250,100,triangle=left-in)}
text{bch7=slib(text/balloon [\tch[7]],\color[7],250,100,triangle=left-in)}
text{bch8=slib(text/balloon [\tch[8]],\color[8],250,100,triangle=left-in)}
text{bch=\bch1,\bch2,\bch3,\bch4,\bch5,\bch6,\bch7,\bch8}

\text{name_help=Voici l'aide pour la méthode}
\text{name_method=la méthode}
#if TYPE==1
\text{consigne=Répondre directement ou choisir une méthode qui mènera au résultat.}
\text{consigne2=Utiliser cette méthode pour trouver une partie de la réponse, la fin sera traitée dans la prochaine étape.}
#endif
#if TYPE==2
\text{consigne=Lorsqu'on clique sur l'icone, la méthode choisie est présentée
  sans pouvoir répondre puis on peut choisir
  de voir une autre méthode.
  Lorsqu'on a trouvé, on peut répondre à la question en cliquant sur l'icone de répondre.}
\text{consigne2=Choisir ensuite soit <b>une autre aide</b> soit de <b>répondre à la question</b>.}
  
\text{name_directanswer=Vous avez choisi de répondre directement.}
\text{name_answer=Coefficient}
#endif
#if TYPE==3
\text{consigne=<p>Lorsqu'on clique sur l'icone, la méthode choisie est présentée
  et permet de trouver certaines réponses puis on peut choisir
  de voir une autre méthode.</p>
  <p>Lorsqu'on a trouvé les réponses, on peut répondre aux questions en cliquant
  sur l'icone de répondre.</p>}
\text{consigne2=Choisir ensuite soit <b>une autre aide</b> soit de <b>répondre à la question</b>.}

#endif
