\text{methoddir=gifs/images/methods/}
\text{ListImage=julie.png,
operater.png,
fraction.png,
tableau.png}
\text{ListImage=\ListImage[\list]}
\integer{nb_meth=items(\list)}
\text{ListDescr=pour répondre directement,
  pour calculer la quantité d'une part du partage,
  pour utiliser des proportions,
  pour utiliser un tableau de proportionnalité}
\text{Listdesc=\ListDescr[\list]}

\text{tch=Je sais répondre <b>sans aide</b>.,
Je choisis de calculer la quantité d'une <b>part</b> du partage.,
Je choisis de calculer des <b>proportions</b>.,
Je choisis d'utiliser un <b>tableau de proportionnalité</b>.
}

\text{tch=\tch[\list2]}

\text{color=yellow,lightblue,lightgrey,paleturquoise,lightsalmon}
\text{color=\color[\list]}
\text{bch1=slib(text/balloon [\tch[1]],\color[1],250,100,triangle=left-in)}
\text{bch2=slib(text/balloon [\tch[2]],\color[2],250,100,triangle=left-in)}
\text{bch3=slib(text/balloon [\tch[3]],\color[3],250,100,triangle=left-in)}
\text{bch4=slib(text/balloon [\tch[4]],\color[4],250,100,triangle=left-in)}

\text{consigne=<p>Répondre directement ou choisir l'aide.</p>}
