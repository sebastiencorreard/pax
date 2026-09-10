target=oefvocaboper1 oefvocaboper2 oefvocaboper3 oefvocaboper4 oefvocaboper5

#include "author.inc"

#if defined TARGET_oefvocaboper1
# define NUM 1
#endif
#if defined TARGET_oefvocaboper2
# define NUM 2
#endif
#if defined TARGET_oefvocaboper3
# define NUM 3
#endif
#if defined TARGET_oefvocaboper4
# define NUM 4
#endif
#if defined TARGET_oefvocaboper5
# define NUM 5
#endif
#include "lang_titles.inc"
#if defined TARGET_oefvocaboper1
\integer{large=5}
\text{nb1=randint(20..49)}
\text{nb2=randint(6..19)}
\text{quest= le produit, la somme, la différence}
\integer{res1=\nb1*\nb2}
\integer{res2=\nb1+\nb2}
\integer{res3=\nb1-\nb2}
\text{rep=\res1,\res2,\res3}
\text{enonc= <li>\nb1 \(\times) \nb2 = \res1</li>
<li>\nb1 + \nb2 = \res2</li>
<li>\nb1 - \nb2 = \res3</li>}
\integer{a=randint(1..3)}
text{deb=Le nombre}
text{fin= est \quest[\a] des nombres \nb1 et \nb2.}
#endif

#if defined TARGET_oefvocaboper2
\integer{large=12}
\text{nb1=randint(20..49)}
\text{nb2=randint(6..19)}
text{rep= Le produit, La somme, La différence}
\integer{res1=\nb1*\nb2}
\integer{res2=\nb1+\nb2}
\integer{res3=\nb1-\nb2}
\text{quest=\res1,\res2,\res3}
\text{enonc= <li>\nb1 \(\times) \nb2 = \res1</li>
<li>\nb1 + \nb2 = \res2</li>
<li> \nb1 - \nb2 = \res3</li>}
\integer{a=randint(1..3)}
text{deb=Le nombre \quest[\a] est }
text{fin= des nombres \nb1 et \nb2.}
#endif

#if defined TARGET_oefvocaboper3
\integer{large=5}
\text{nb1=randint(20..49)}
\text{nb2=randint(6..19)}
text{quest1= facteur, terme, terme}
text{quest2= du produit,de la somme,de la différence}
text{quest3=deuxième,premier}
\integer{res=\nb1*\nb2}
\integer{nb3=randint(1..\res-3)}
\integer{nb4=\res-\nb3}
\integer{nb5=\nb3+\res}
\text{rep=\nb1,\nb2,\nb3,\nb4,\nb5,\nb3}
\text{enonc= <li>\nb1 \(\times) \nb2 = \res</li>
<li>\nb3 + \nb4 = \res</li>
<li>\nb5 - \nb3 = \res</li>}
\integer{a=randint(1..6)}
\integer{b=(\a)/2}
\integer{c=\b*2-\a+1}
text{deb=Le nombre }
text{fin= est le \quest3[\c] \quest1[\b] \quest2[\b] qui donne \res.}
#endif

#if defined TARGET_oefvocaboper4
\integer{large=12}
\text{nb1=randint(20..49)}
\text{nb2=randint(6..19)}
text{quest1= facteur, terme, terme}
text{quest2= du produit,de la somme,de la différence}
text{quest3=deuxième,premier}
\integer{res=\nb1*\nb2}
\integer{nb3=randint(1..\res-3)}
\integer{nb4=\res-\nb3}
\integer{nb5=\nb3+\res}
\text{nb=\nb1,\nb2,\nb3,\nb4,\nb5,\nb3}
\text{enonc= <li>\nb1 \(\times) \nb2 = \res</li>
<li> \nb3 + \nb4 = \res</li>
<li>\nb5 - \nb3 = \res</li>}
text{rep=facteur,facteur,terme,terme,terme,terme}
\integer{a=randint(1..6)}
\integer{b=(\a)/2}
\integer{c=\b*2-\a+1}
text{deb=Le nombre \nb[\a] est le \quest3[\c]}
text{fin=  \quest2[\b] qui donne \res.}
#endif

#if defined TARGET_oefvocaboper5
\integer{large=12}
\text{nb=3,4,5,6,7,8,9,11,12,13,14,15,16,17,18}
\text{nb=shuffle(\nb)}
\integer{res1=\nb[1]*\nb[2]}
\integer{res2=\nb[3]+\nb[4]}
\integer{res3=abs(\nb[5]-\nb[6])}

\if{\nb[5]>\nb[6]}
 {\text{nb=\nb[1],\nb[2],\nb[3],\nb[4],\nb[5],\nb[6],\res1,\res2,\res3}}
{\text{nb=\nb[1],\nb[2],\nb[3],\nb[4],\nb[6],\nb[5],\res1,\res2,\res3}}

\text{nb=\nb[1],\nb[2],\nb[3],\nb[4],\nb[5],\nb[6],\res1,\res2,\res3}
\text{enonc= <li>\nb[1] \(\times) \nb[2] = \nb[7]</li>
<li>\nb[3] + \nb[4] = \nb[8]</li>
<li>\nb[5] - \nb[6] = \nb[9]</li>}
\integer{a=randint(1..9)}
\integer{b=(\a)/2}
\integer{c=\b*2-\a+1}
text{rep=un facteur,un facteur,un terme,un terme,un terme,un terme,un produit,une somme,une différence}
text{deb=Le nombre \nb[\a] est }
text{fin=  .}
#endif
#include "lang.inc"
\statement{
  <ul>\enonc</ul>
  <div class="spacer">\deb \embed{r1,\large} \fin</div>
}

\answer{}{\rep[\a]}
