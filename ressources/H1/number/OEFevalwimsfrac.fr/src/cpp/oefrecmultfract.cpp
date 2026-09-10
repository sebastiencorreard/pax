target=oefrecmultfract1 oefrecmultfract2 oefrecmultfract3 oefrecmultfract4 oefrecmultfract5
#define TITRE Reconnaître une opération
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

#if defined TARGET_oefrecmultfract1
\title{TITRE 1}
\text{enonc=Mettre en relation les fractions représentant le même nombre :}
\text{ty=correspond}
\text{size=50x200}
\text{b=2,3,4,5,10}
\integer{ch=randint(1..5)}
\integer{a=\b[\ch]*randint(2..9)}
\text{m=demi,tiers,quart,cinquième,dixième}
\text{rep1=Calculer la différence entre \a et \b[\ch],
Faire le produit de \a par \b[\ch],
Trouver la somme de \a et \b[\ch],
Prendre le \m[\ch] de \a}

\text{rep2=\(\a - \b[\ch]),
\(\a \times \b[\ch]),
\(\a + \b[\ch]),
\(\a \times \frac{1}{\b[\ch]})
}
#endif

#if defined TARGET_oefrecmultfract2
\title{TITRE 2}
\text{enonc=Mettre en relation les fractions représentant le même nombre :}
\text{ty=correspond}
\text{size=50x220}
\text{m=a,demi,tiers,quarts,cinquièmes,a,a,a,a,dixièmes}
\matrix{lv=3,10,2
3,10,4
3,10,5
3,5,2
3,5,4
3,5,10
3,4,2
3,4,5
3,4,10
4,10,2
4,10,3
4,10,5
4,5,2
4,5,3
4,5,10
5,10,2
5,10,3
5,10,4}
\integer{ch=randint(1..18)}
\text{lv=row(\ch,\lv)}

\text{rep1=Prendre les \lv[3] \m[\lv[1]] de \lv[2],
Prendre les \lv[1] \m[\lv[2]] de \lv[3],
Prendre les \lv[2] \m[\lv[1]] de \lv[3],
Prendre les \lv[3] \m[\lv[2]] de \lv[1]}

\text{rep2=\(\lv[2] \times \frac{\lv[3]}{\lv[1]}),
\(\lv[3] \times \frac{\lv[1]}{\lv[2]}),
\(\lv[3] \times \frac{\lv[2]}{\lv[1]}),
\(\lv[1] \times \frac{\lv[3]}{\lv[2]})}

#endif

#if defined TARGET_oefrecmultfract3
\title{TITRE 3}

\integer{a=randint(11..99)}
\integer{b=randint(11..59)}
\text{enonc= Calculer les \a % de \b.
<p>Pour trouver le résultat, je choisis le calcul suivant :</p>}
\text{ty=clickfill}
\text{size=120x50}

\text{rep1=\(\b \times \frac{\a}{100})}

\text{rep2=\(\b \times 100),
\(\b \times \a),
\(\b \times \frac{1}{\a}),
\(\b \times \frac{100}{\a})
}
#endif

#if defined TARGET_oefrecmultfract4
\title{TITRE 4}
\text{ty=clickfill}
\text{size=120x50}
\text{prob=228,Combien de kilomètres faut-il parcourir pour faire les \(\frac{2}{3}) d'un voyage de 228 km ?,
93,Jules a dans sa poche 93 billes. <br>Malheureusement &#44; sa poche a un trou &#44; et il en perd les \(\frac{2}{3}).<br>Combien de billes a-t-il perdues ?,
75,Un jardin rectangulaire a une longueur de 75 m.<br>Sa largeur est les \(\frac{2}{3}) de sa longueur.<br> Quelle est la largeur du terrain ?,
48,Au milieu du mois &#44; j'ai encore 48 &euro; d'argent de poche. <br>Je  consacre les \(\frac{2}{3}) à un cadeau.<br> Quelle somme d'argent ai-je dépensée pour le cadeau ?,
414,Dans un collège de 414 élèves &#44; les \(\frac{2}{3}) des élèves viennent à pied.<br>Combien d'élèves viennent à pied ?
}
\integer{ch=randint(1..5)}
\text{prob=row(\ch,\prob)}
\text{enonc=\prob[2]
<p>Pour trouver la réponse, je choisis le calcul suivant :</p>}
\text{rep1=\(\prob[1] \times \frac{2}{3})}

\text{rep2=\(\prob[1] \div \frac{2}{3}),
\(\prob[1] + \frac{2}{3}),
\(\prob[1] - \frac{2}{3})
}
#endif

#if defined TARGET_oefrecmultfract5
\title{TITRE 5}
\text{ty=clickfill}
\text{size=80x50}
\text{prob=228,Combien de kilomètres faut-il parcourir pour faire les \(\frac{2}{3}) d'un voyage de 228 km ?,
93,Jules a dans sa poche 93 billes. <br>Malheureusement &#44; sa poche a un trou &#44; et il en perd les \(\frac{2}{3}).<br>Combien de billes a-t-il perdues ?,
75,Un jardin rectangulaire a une longueur de 75 m.<br> Sa largeur est les \(\frac{2}{3}) de sa longueur.<br> Quelle est la largeur du terrain ?,
48,Au milieu du mois &#44; j'ai encore 48 &euro; d'argent de poche. <br>Je consacre les \(\frac{2}{3}) à un cadeau.<br> Quelle somme d'argent ai-je dépensée pour le cadeau ?,
414,Dans un collège de 414 élèves &#44; les \(\frac{2}{3}) des élèves viennent à pied.<br> Combien d'élèves viennent à pied ?
}
\integer{ch=randint(1..5)}
\text{prob=row(\ch,\prob)}
\text{enonc=\prob[2]
<p>Pour trouver la réponse, je fais le calcul suivant :</p>}
\text{rep1=\(\prob[1]),\(\times),\(\frac{2}{3})
           |\(\frac{2}{3}),\(\times),\(\prob[1]) }

\text{rep2=\(\div),\(\frac{3}{2}),\(\frac{1}{3}),+,-,2,3}
#endif

\statement{
\enonc
<div class="wimscenter">
\embed{r1,\size}
</div>
}

\answer{}{\rep1;\rep2}{type=\ty}{option=shuffle}
