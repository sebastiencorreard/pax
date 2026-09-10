\text{ListImage=julie2.png,
dessin2.png,
schema3.png,
KPart.png,
inconnu3.png,
phonk3.png,
graphe.png,
algorithm.png}

\text{ListImage=\ListImage[\list]}
\integer{nb_meth=items(\list)}
\text{ListDescr=fille nommée Julie Dédeugénie pour répondre,
  garçon nommé Lébodé Sainclair,
  fille nommée Méchet Marie,
  garçon nommé Lucas Particulier,
  garçon nommé Constantin Connu,
  fille nommée Phonk Siona,
  garçon nommé Vlad Egraph,
  fille nommée Chantal Goritme}
\text{Listdesc=\ListDescr[\list]}

\text{tch1=Je sais <b>répondre</b> sans aide supplémentaire.}
\text{tch2=Je propose de faire un <b>dessin</b> pour illustrer le problème.}
\text{tch3=Réaliser un <b>schéma</b> aide à comprendre l'énoncé.}
\text{tch4=J'aimerai étudier d'abord un <b>cas particulier</b>.}
\text{tch5=On pourrait utiliser une lettre pour désigner l'inconnue et écrire une <b>équation</b>.}
\text{tch6=Il y a un lien avec une <b>fonction</b> \(x \mapsto x^n) et peut-être une autre fonction.}
\text{tch7=Un <b>graphique</b> adapté peut donner une réponse approximative.}
\text{tch8=J'imagine un <b>algorithme</b> pour estimer ce nombre avec une bonne précision.}

\text{tch=\tch1,
\tch2,
\tch3,
\tch4,
\tch5,
\tch6,
\tch7,
\tch8}

\text{tch=\tch[\list2]}

\text{trep=répondre,
dessin,
schéma,
cas particulier,
équation,
fonction,
graphique,
algorithme}
\text{trep=\trep[\list2]}

\text{color=yellow,lightblue,lightsalmon,blueviolet,palegreen,pink,mediumaquamarine,lightgreen}
\text{color=\color[\list]}
\text{bch1=slib(text/balloon [\tch[1]],\color[1],250,100,triangle=left-in)}
\text{bch2=slib(text/balloon [\tch[2]],\color[2],250,100,triangle=left-in)}
\text{bch3=slib(text/balloon [\tch[3]],\color[3],250,100,triangle=left-in)}
\text{bch4=slib(text/balloon [\tch[4]],\color[4],250,100,triangle=left-in)}
\text{bch5=slib(text/balloon [\tch[5]],\color[5],250,100,triangle=left-in)}
\text{bch6=slib(text/balloon [\tch[6]],\color[6],250,100,triangle=left-in)}
\text{bch7=slib(text/balloon [\tch[7]],\color[7],250,100,triangle=left-in)}
\text{bch8=slib(text/balloon [\tch[8]],\color[8],250,100,triangle=left-in)}
\text{bch=\bch1,\bch2,\bch3,\bch4,\bch5,\bch6,\bch7,\bch8}

\text{consigne2=Choisir ensuite soit <b>une autre aide</b> soit de <b>répondre à la question</b>.}
\text{name_help=Voici l'aide pour la méthode}
\text{name_method=la méthode}
#if TYPE==1
\text{consigne=Répondre directement ou choisir une méthode qui mènera au résultat.}
#endif
#if TYPE==2
\text{consigne=Lorsqu'on clique sur l'icone, la méthode choisie est présentée
  sans pouvoir répondre puis on peut choisir
  de voir une autre méthode.
  Lorsqu'on a trouvé, on peut répondre à la question en cliquant sur l'icone de répondre.}
#endif
#if TYPE==3
\text{consigne=<p>Lorsqu'on clique sur l'icone, la méthode choisie est présentée
  et permet de trouver certaines réponses puis on peut choisir
  de voir une autre méthode.</p>
  <p>Lorsqu'on a trouvé les réponses, on peut répondre aux questions en cliquant
  sur l'icone de répondre.</p>}
#endif
