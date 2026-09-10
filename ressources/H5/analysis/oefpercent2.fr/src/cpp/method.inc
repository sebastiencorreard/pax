\text{ListImage=julie.png,
tableau.png,
operater.png,
schema.png,
kpart.png,
inconnu.png,
graphe.png}
\text{ListImage=\ListImage[\list]}
\integer{nb_meth=items(\list)}
\text{ListDescr=fille nommée Julie Dédeugénie pour répondre,
  fille nommée Métab Laurie,
  garçon nommé Léo Pérateur,
  fille nommée Mechet Marie,
  garçon nommé Lucas Particulier,
  garçon nommé Constantin Connu,
  garçon nommé Côme André Currente}
\text{Listdesc=\ListDescr[\list]}

\text{tch=Je sais <b>répondre</b> sans aide supplémentaire.,
 Le problème peut être résolu avec des <b>tableaux</b> de proportionnalité.,
 Trouver le bon <b>opérateur</b> est souvent la clef du problème.,
 Réaliser un <b>schéma</b> guide vers la solution.,
 On peut se servir d'une valeur <b>particulière</b>.,
 On peut utiliser une <b>lettre</b> pour désigner la valeur initiale inconnue.,
 On peut calculer le pourcentage d'augmentation chaque année par rapport à l'année <b>précédente</b>,
 On peut calculer le pourcentage de chaque valeur par rapport à celle de <b>2015</b>.,
 Utiliser la <b>lettre</b> \(x) pour désigner le prix initial pour justifier la dernière réponse.}

\text{tch=\tch[\list2]}

\text{color=yellow,lightgrey,paleturquoise,lightsalmon,blueviolet,lightgreen,orange}
\text{color=\color[\list]}
\text{bch1=slib(text/balloon [\tch[1]],\color[1],250,100,triangle=left-in)}
\text{bch2=slib(text/balloon [\tch[2]],\color[2],250,100,triangle=left-in)}
\text{bch3=slib(text/balloon [\tch[3]],\color[3],250,100,triangle=left-in)}
\text{bch4=slib(text/balloon [\tch[4]],\color[4],250,100,triangle=left-in)}
\text{bch5=slib(text/balloon [\tch[5]],\color[5],250,100,triangle=left-in)}
\text{bch6=slib(text/balloon [\tch[6]],\color[6],250,100,triangle=left-in)}

#if TYPE==1
\text{consigne=<p>Répondre directement ou choisir une méthode qui mènera au résultat.</p>}
#endif

#if TYPE==2
\text{consigne=<p>Lorsqu'on clique sur l'icone, la méthode choisie est présentée sans pouvoir répondre puis on peut choisir
de voir une autre méthode.</p>
<p>Lorsqu'on a trouvé, on peut répondre aux questions en cliquant sur l'icone de répondre.</p>}
#endif
