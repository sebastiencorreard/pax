target=vectcolin

#include "author.inc"
\precision{10000}
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{size=confparm1=1 ? :x-large}
** donnée de trois vecteurs indépendants
\matrix{V=slib(matrix/invertible 3,3)}

%% coordonnées de A: matrice m
\matrix{a=slib(matrix/random 1,3,5)}

%% coordonnées de B: A+u
\matrix{u=\V[1;]}
\rational{j=randint(4..11)*random(-1,1)/random(1,2,3)}
\matrix{u= pari(print([\u]*\j))}

\matrix{b=pari(print([\a]+[\u]))}

%% coordonnées de C: A+v
%% k=1 alignés, k=2 non alignés
\integer{k=randint(1..2)}

\matrix{v=\k=1? \u :\V[2;]}
\rational{j=randint(2..5)*random(-1,1)/random(1,7,11,13)}
\matrix{v= pari(print([\v]*\j))}
\matrix{c=pari(print([\b]+[\v]))}
\text{rep=\k=1? \liste[1]:\liste[2]}
\if{\k=1}{
  \text{textsol=\name_textsol1[1]
  <div class="wimscenter">\(\overrightarrow{v}= \j \overrightarrow{u}\)
</div> \name_textsol1[2]}
}{
  \text{textsol=\name_textsol2}
}
\statement{
<div class="\style1">
\name_enonce[1]
<p class="wimscenter">
 \(\overrightarrow{u}\left(\begin{array}{c} \u[1] \\ \u[2] \\ \u[3]\end{array}\right)\),
  \(\overrightarrow{v}\left(\begin{array}{c} \v[1] \\ \v[2] \\ \v[3]\end{array}\right)\)
</p>
 \name_enonce[2]?
</div>
<div class="\style2">
 \name_answer \embed{choice1,\size}.
</div>
}

\choice{}{\rep}{\liste}
\hint{\name_hint}
\solution{
\textsol}
