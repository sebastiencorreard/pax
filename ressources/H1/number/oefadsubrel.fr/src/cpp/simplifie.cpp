target=simplifie1 simplifie2

#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{sign1=random(+,-)}
\text{sign2=random(+,-)}
\text{sign3=random(+,-)}
\text{sign4=random(+,-)}
\text{oper=random(+,-)}
\integer{nb1=random(1..100)}
\integer{nb2=randint(1..100)}
\integer{nb3=randint(1..100)}
\integer{nb4=randint(1..100)}

#if defined TARGET_simplifie1
\title{TITRE 1}
\text{TYPE=correspond}
\matrix{liste1=\((+\nb1)+(-\nb2)),\(\nb1-\nb2)
\((-\nb1)+(+\nb2)),\(-\nb1+\nb2)
\((-\nb1)+(-\nb2)),\(-\nb1-\nb2)
\((+\nb1)+(+\nb2)),\(\nb1+\nb2)
\((+\nb1)-(-\nb2)),\(\nb1+\nb2)}
\matrix{liste2=\((-\nb1)-(+\nb2)),\(-\nb1-\nb2)
\((-\nb1)-(-\nb2)),\(-\nb1+\nb2)
\((+\nb1)-(+\nb2)),\(\nb1-\nb2)}
\text{mix1=shuffle(rows(\liste1))}
\text{mix2=shuffle(rows(\liste2))}
\matrix{question1=\liste1[\mix1[1..2];]
\liste2[\mix2[1..2];]}
\text{mix=shuffle(rows(\question1))}
\matrix{question2=\question1[\mix[1..4];]}
\text{question=Associer chaque expression de gauche à son expression simplifiée de droite.}
#endif

#if defined TARGET_simplifie2
\title{TITRE 2}
\text{TYPE=raw}
\text{expression= \( ( \sign1\nb1 ) {\oper} ( \sign2\nb2 ) \) }
\if{\sign1=+}{\text{rep=\nb1}}{\text{rep=-\nb1}}
\if{\oper=+}{\if{\sign2=+}
                    {\text{rep=\rep+\nb2}}
                    {\text{rep=\rep-\nb2}}}
            {\if{\sign2=+}
                    {\text{rep=\rep-\nb2}}
                    {\text{rep=\rep+\nb2}}}
\text{question=<b>Simplifier</b> l'expression suivante (on ne demande pas de la calculer)&nbsp;:}
#endif

\statement{\char<p>\question

#if defined TARGET_simplifie1
<div class="wims_instruction">Simplifier une somme ou une différence de deux nombres relatifs revient à l'écrire sans parenthèses.</div>
<div class="wimscenter">\embed{reply1}</div>
#endif
#if defined TARGET_simplifie2
<div class="wims_instruction"><ul><li>Simplifier une somme ou une différence de deux nombres relatifs revient à l'écrire sans parenthèses.</li>
<li>On ne change pas l'ordre des termes.</li></ul></div>
<label for="reply1">\expression =</label>\embed{reply1,8}
#endif
}

#if defined TARGET_simplifie1
\answer{}{\question2[;1];\question2[;2]}{type=\TYPE}{option=split}
#endif

#if defined TARGET_simplifie2
\answer{}{\rep}{type=\TYPE}{option=nospace}
#endif

\hint{<p>Pour simplifier une expression, on utilise les régles suivantes&nbsp;:</p>
<ul><li>On peut supprimer les parenthèses du premier nombre et son signe s'il est positif.</li>
<li>Lorsqu'il s'agit d'une addition, on supprime le signe + de l'addition et les parenthèses du nombre qui suit.
<dl><dt>Concrètement, on retiendra que, par exemple&nbsp;:</dt>
<dd>\({+} ( +\nb4 ) \) s'écrit \( {+} \nb4 \)</dd>
<dd>\({+} ( -\nb4 ) \) s'écrit \( - \nb4 \)</dd></dl></li>
<li>Lorsqu'il s'agit d'une soustraction, on la transforme en addition de l'opposé puis on supprime le signe + de l'addition et les parenthèses du nombre qui suit.
<dl><dt>Concrètement, on retiendra que, par exemple&nbsp;:</dt>
<dd>\({-} ( +\nb4 ) \) devient \( {+} (-\nb4) \) qui s'écrit \( - \nb4 \)</dd>
<dd>\({-} ( -\nb4 ) \) devient \( {+} (+\nb4) \) qui s'écrit \( {+} \nb4 \)</dd></dl></li></ul>}

\text{char=wims(char 1 of \reply1)}
\feedback{\char issametext +}{<div class="macss">Le signe + du premier nombre est inutile.<p>Vous pouvez le supprimer.</p></div>}
