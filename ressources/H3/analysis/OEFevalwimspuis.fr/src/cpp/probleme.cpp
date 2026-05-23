target=probleme1 probleme2 probleme3 probleme4 probleme5
#define TITRE Problème
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

#if defined TARGET_probleme1
 \title{TITRE 1}
 \text{name=slib(lang/fname fr,boy)}
 \integer{nb=randint(5..7)}
 \integer{a=randint(2..4)}
 \text{type=randitem(riz,blé)}
 \text{enonce=\name dispose de \nb bols. Il les remplit de la façon suivante :
 <ul>
  <li>Il met \a grains de \type dans le premier.</li>
  <li>Dans le deuxième il met \a fois plus de grains que dans le premier.</li>
  <li>Dans le troisième il met \a fois plus de grains que dans le deuxième.</li>
  <li>ainsi de suite jusqu'au dernier.</li>
 </ul>}
 \text{question=Combien met-il de grains de \type dans le dernier bol}
 \text{good=\(\a^\nb)}
 \text{bad=\(\a\times \nb)}
#endif

#if defined TARGET_probleme2
 \title{TITRE 2}
 \text{name=slib(lang/fname fr,boy)}
 \integer{nb=randint(5..7)}
 \integer{a=randint(2..4)}
 \text{type=randitem(riz,blé)}
 \text{enonce=\name est jardinier il décide de planter des fleurs dans une pelouse. Pour cela il a réalisé \nb trous. Pour être sur qu'au moins une fleur pousse dans chacun des trous, il dispose \a graines dans chacun d'entre eux.}
 \text{question=Combien met-il de graines en tout}
 \text{bad=\(\a^\nb)}
 \text{good=\(\a\times \nb)}
#endif

#if defined TARGET_probleme3
 \title{TITRE 3}
 \text{name=slib(lang/fname fr,boy)}
 \integer{nb=randint(5..7)}
 \integer{a=randint(2..4)}
 \text{type=randitem(riz,blé)}
 \text{enonce=<b>Arbre généalogique</b>
\name a réalisé son arbre généalogique. Le nom de chaque personne de sa famille est à une position précise de l'arbre. Sur la première ligne il y a les noms de ses deux parents ; sur la deuxième les noms de ses quatre grands-parents et ainsi de suite.}
 \text{question=Combien y-a-t-il de noms sur la ligne \nb}
 \text{good=\(2^\nb)}
 \text{bad=\(2\times \nb)}
#endif

#if defined TARGET_probleme4
 \title{TITRE 4}
 \text{name=slib(lang/fname fr,boy)}
 \integer{nb=randint(5..7)}
 \integer{a=randint(2..4)}
 \text{type=randitem(riz,blé)}
 \text{enonce=<b>Messagerie électronique</b>
\name envoie un message électronique à \a de ses amis. Le lendemain chacun d'entre eux envoie également le même message à \a de leurs amis et ainsi de suite.}
\text{question=En supposant que deux personnes ne reçoivent jamais deux fois ce message électronique, combien de personnes l'auront reçu dans \nb jours}
 \text{good=\(\a^\nb)}
 \text{bad=\(\a\times \nb)}
#endif

#if defined TARGET_probleme5
 \title{TITRE 5}
 \text{name=slib(lang/fname fr,boy)}
 \integer{nb=randint(5..7)}
 \integer{a=randint(2..4)}
 \text{type=randitem(riz,blé)}
 \text{enonce=Un groupe d'amis décident de faire une course en relai. Chacun d'eux
 court une distance de \a kilomètres.}
\text{question=Ils sont \nb. Quelle est la longueur de cette course}
 \text{bad=\(\a^\nb) kilomètres}
 \text{good=\(\a\times \nb) kilomètres}
#endif

\statement{
\enonce
\question ?}

\choice{Réponse}{\good}{\bad}
