target=imgantgr1,imgantgr2,imgantgr3,imgantgr4,imgantgr5
#include "author.inc"
\precision{100}
#if defined TARGET_imgantgr1
# define NUM 1
#endif
#if defined TARGET_imgantgr2
# define NUM 2
#endif
#if defined TARGET_imgantgr3
# define NUM 3
#endif
#if defined TARGET_imgantgr4
# define NUM 4
#endif
#if defined TARGET_imgantgr5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}

#if defined TARGET_imgantgr1
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \text{fonction=\b/\a*x}
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
 \text{enonce=\(\f\) est une fonction linéaire dont la représentation graphique est donnée ci-dessous.<div class="wimscenter"><img src="\figure" alt=""></div> Quelle est l'image de \a par cette fonction}
 \text{compenonce=L'image de \a par \(\f\) est}
 \integer{rep=\b}
#endif
#if defined TARGET_imgantgr2
 \text{v=wims(values v,-v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \text{fonction=\b/\a*x}
\text{dessin=slib(draw/repere 400,400,0,-10,10,-10,10,1,1,black,grey)}
\text{dessin=wims(line 3 to -1 of \dessin)}
\text{figure=draw(400,400
\dessin
range -10,10,-10,10
plot blue,\fonction
text black,9.5,-0.3,medium,X
text black,-1.5,10,medium,\f(X)
text black,0.9,-0.3,medium,1
text black,-0.6,1.5,medium,1)}
 \text{enonce=\(\f\) est une fonction linéaire dont la représentation graphique est donnée ci-dessous.<div class="wimscenter"><img src="\figure" alt=""></div> Quel nombre a pour image \b par cette  fonction}
 \text{compenonce=Le nombre qui a pour image \b par \(\f\) est}
 \integer{rep=\a}
#endif
#if defined TARGET_imgantgr3
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=-\v[1]}
 \integer{b=-\v[2]}
 \text{fonction=\b/\a*x}
\text{dessin=slib(draw/repere 400,400,0,-10,10,-10,10,1,1,black,grey)}
\text{dessin=wims(line 3 to -1 of \dessin)}
\text{figure=draw(400,400
\dessin
range -10,10,-10,10
plot blue,\fonction
text black,9.5,-0.3,medium,X
text black,-1.5,10,medium,\f(X)
text black,0.9,-0.3,medium,1
text black,-0.6,1.5,medium,1)}
 \text{enonce=\(\f\) est une fonction linéaire dont la représentation graphique est donnée ci-dessous.<div class="wimscenter"><img src="\figure" alt=""></div> Quelle est l'image de \a par cette fonction}
 \text{compenonce=L'image de \a par \(\f\) est}
 \integer{rep=\b}
#endif
#if defined TARGET_imgantgr4
 \text{v=wims(values v,-v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \text{fonction=\b/\a*x}
\text{dessin=slib(draw/repere 400,400,0,-10,10,-10,10,1,1,black,grey)}
\text{dessin=wims(line 3 to -1 of \dessin)}
\text{figure=draw(400,400
\dessin
range -10,10,-10,10
plot blue,\fonction
text black,9.5,-0.3,medium,X
text black,-1.5,10,medium,\f(X)
text black,0.9,-0.3,medium,1
text black,-0.6,1.5,medium,1)}
 \text{enonce=\(\f\) est une fonction linéaire dont la représentation graphique est donnée ci-dessous.<div class="wimscenter"><img src="\figure" alt=""></div>Calculez \(\f(\a))}
 \text{compenonce=\(\f(\a) =)}
 \integer{rep=\b}
#endif
#if defined TARGET_imgantgr5
 \text{v=wims(values v,-v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \text{fonction=\b/\a*x}
\text{dessin=slib(draw/repere 400,400,0,-10,10,-10,10,1,1,black,grey)}
\text{dessin=wims(line 3 to -1 of \dessin)}
\text{figure=draw(400,400
\dessin
range -10,10,-10,10
plot blue,\fonction
text black,9.5,-0.3,medium,X
text black,-1.5,10,medium,\f(X)
text black,0.9,-0.3,medium,1
text black,-0.6,1.5,medium,1)}
 \text{enonce=Soit \(\f\) une fonction linéaire dont la représentation graphique est donnée ci-dessous.<div class="wimscenter"><img src="\figure" alt=""></div> Complétez l'égalité suivante}
 \text{r=()}
 \text{c1=wims(char 1 of \r)}
 \text{c2=wims(char 2 of \r)}
 \text{compenonce=\(\f\) \c1}
 \text{compenonce2=\c2 = \b}
 \integer{rep=\a}
#endif
!! gestionnaire de l'exercice.

\statement{
\enonce <br>
\reponse
<p><b>Votre réponse :</b></p>
<label for="reply1">\compenonce</label> \embed{r1,3} \compenonce2.
}

\answer{réponse}{\rep}{type=numexp}
