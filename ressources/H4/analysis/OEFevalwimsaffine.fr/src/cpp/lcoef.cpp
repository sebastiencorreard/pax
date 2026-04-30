target=lcoef1,lcoef2,lcoef3,lcoef4,lcoef5
#include "author.inc"
\precision{100}
#if defined TARGET_lcoef1
# define NUM 1
#endif
#if defined TARGET_lcoef2
# define NUM 2
#endif
#if defined TARGET_lcoef3
# define NUM 3
#endif
#if defined TARGET_lcoef4
# define NUM 4
#endif
#if defined TARGET_lcoef5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}

#if defined TARGET_lcoef1
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{b=randitem(1,-1)*\v[1]}
 \text{fonction=\b*x}
 \text{good=x\mapsto \b x}
 \integer{c=-\b}
 \text{bad=x\mapsto \frac{1}{\b}x,x\mapsto \c x,x\mapsto -\frac{1}{\b}x}
 \text{question=Quelle est la fonction \(\f\) représentée}
#endif
#if defined TARGET_lcoef2
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{b=randitem(1,-1)*\v[1]}
 \text{fonction=1/\b*x}
 \text{good=\frac{1}{\b}}
 \integer{c=-\b}
 \text{bad=texmath(-1/(\b)),\b,\c}
 \text{question=Quel est le coefficient de la fonction \(\f\)}
#endif
#if defined TARGET_lcoef3
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \text{fonction=\b/\a*x}
 \text{good=x\mapsto \frac{\b}{\a}x}
 \text{bad=x\mapsto -\frac{\b}{\a}x,x\mapsto \frac{\a}{\b}x,x\mapsto -\frac{\a}{\b}x,x\mapsto\a x,x\mapsto\b x}
 \text{question=Quelle est la fonction \(\f\) représentée}
#endif
#if defined TARGET_lcoef4
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \text{fonction=-\b/\a*x}
 \text{good=-\frac{\b}{\a}}
 \text{bad=\frac{\b}{\a},\frac{\a}{\b},-\frac{\a}{\b},\a,\b}
 \text{question=Quel est le coefficient de la fonction \(\f\)}
#endif
#if defined TARGET_lcoef5
 \text{v=wims(values v for v=4 to 9)}
 \integer{c=randint(15..25)}
 \text{v=shuffle(\v)}
 \integer{a=-\v[1]}
 \integer{b=\v[2]}
 \text{fonction=\b/\a*x}
 \text{question=Quelle est l'image de \c par cette fonction}
 \text{good=simplify(\c*\b/\a)}
 \text{bad=simplify(\b/\a),simplify((\c*\b+2)/\a),simplify(\a/\b),simplify(\a/\b*\c)}
#endif
!! gestionnaire de l'exercice.

\text{dessin=slib(draw/repere 400,400,0,-10,10,-10,10,1,1,black,grey)}
\text{dessin=wims(line 3 to -1 of \dessin)}
\text{figure=draw(400,400
\dessin
range -10,10,-10,10
plot blue,\fonction
text black,9.5,-0.3,medium,X
text black,-1.5,10,medium,\f(X)
text black,0.9,-0.3,medium,1
text black,-0.5,1.5,medium,1)}

\text{lettres=A,B,C,D,E,F,G,H}
\text{bad=shuffle(\bad,\good)}
\text{po=positionof(\good,\bad)}
\text{reponse=<ul>}
\integer{nb=items(\bad)}
\for{i=1 to \nb}{
 \text{reponse=\reponse<li><b>\lettres[\i]</b> : \(\bad[\i]\)</li>}
}
\text{reponse=\reponse</ul>}
\text{Good=item(\po,\lettres)}
\text{Bad=wims(item 1 to \nb of \lettres)}
\text{enonce=Soit \(\f\) une fonction linéaire dont la représentation graphique est donnée ci-contre.}
\statement{\enonce<br>
\question ?
\reponse
<div class="wimscenter"><img src="\figure" alt=""></div>

<b>Votre réponse :</b>
<div class="wimscenter">
  La bonne réponse est la \embed{r1}.
</div>}

\answer{réponse}{\po;\Bad}{type=menu}
