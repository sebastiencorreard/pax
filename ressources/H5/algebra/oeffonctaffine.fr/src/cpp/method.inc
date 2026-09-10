\text{ListImage=repondre2.jpg,
dessin2.jpg,
schemari.jpg,
tableau1.jpg,
graphe1.jpg,
inconnu2.jpg,
inequat1.jpg,
phonk2.jpg,
recursif1.jpg
}
\text{ListImage=julie.png,
dessin.png,
schema.png,
tableau.png,
graphe.png,
inconnu.png,
inequat.png,
phonk.png,
recursif.png
}

\text{ListImage=\ListImage[\list]}
\integer{nb_meth=items(\list)}
\text{ListDescr=fille nommée Julie Dédeugénie,
  garçon nommé Lébodé Sinclair,
  fille nommée Mechet Marie,
  fille nommée Métab Laurie,
  garçon nommé Vlad Egraf,
  garçon nommé Constantin Connu,
  fille nommée Ines Coassion,
  fille nommée Phonk Siona,
  garçon nommé Côme André Curante}
\text{Listdesc=\ListDesc[\list]}

\text{tch=Je sais répondre sans aide supplémentaire.,
  Un dessin peut aider à comprendre l'énoncé.,
  Un bon schéma peut permettre de résoudre le problème.,
  On peut calculer astucieusement avec un tableau de valeurs.,
  Un graphique peut donner rapidement une réponse approximative voire exacte.,
  On peut utiliser des lettres pour désigner les paramètres inconnus.,
  La résolution d'une inéquation est utile ici.,
  Avec les formules on peut utiliser sa calculatrice graphique.,
  L'utilisation de suites numériques permet des calculs rapides.,
  Réaliser un tableau ou utiliser un tableur facilite la résolution du problème.}

\text{tch=\tch[\list2]}

\text{color=yellow,lightblue,lightsalmon,lightgrey,mediumaquamarine,lightgreen,paleturquoise,pink,orange}
\text{color=\color[\list]}

#if TYPE==1
\text{consigne=<p>Répondre directement ou choisir une méthode qui mènera au résultat.</p>}
#else
\text{consigne=<p>Des méthodes vous sont proposées et vous pouvez chercher les réponses par vous-mêmes.</p>
<p>Lorsque vous cliquerez dessus, la méthode que vous avez choisie sera présentée puis vous pourrez choisir
d'en voir une autre. Lorsque vous avez trouvé, vous pouvez répondre aux questions en cliquant sur répondre.</p>}
#endif
