target=alignpts alignpts2

#include "lang_titles.inc"
#include "author.inc"
\precision{10000}
#include "css.inc"
#include "lang.inc"

** donnée de trois vecteurs indépendants
\matrix{V=slib(matrix/invertible 3,3)}

** coordonnées de A: matrice m
\matrix{a=slib(matrix/random 1,3,5)}

** coordonnées de B: A+u
\matrix{u=\V[1;]}
\matrix{b=pari(print([\a]+[\u]))}

** coordonnées de C: A+v
** k=1 alignés, k=2 non alignés
#if defined TARGET_alignpts2
\integer{k=1}
#endif
#if defined TARGET_alignpts
\integer{k=randint(1..2)}
#endif
\matrix{v=\k=1? \u :\V[2;]}
\integer{j=randint(2..5)*random(-1,1)}
\matrix{v= pari(print([\v]*\j))}
\matrix{c=pari(print([\b]+[\v]))}
#if defined TARGET_alignpts2
\integer{ip=random(1..3)}
\integer{ic=random(1..3)}
&& on ne veut pas que le vecteur u soit colinéaire au vecteur de base associé à ic
\if{\u[1]=0 and \u[2]=0 and \ic=3}{\integer{ic=2}}
\if{\u[1]=0 and \u[3]=0 and \ic=2}{\integer{ic=1}}
\if{\u[3]=0 and \u[2]=0 and \ic=1}{\integer{ic=3}}
\if{\ip=1}{
\integer{val=\a[\ic]}
\matrix{a= wims(replace internal item number \ic by t in \a)}
}{
 \if{\ip=2}{
  \integer{val=\b[\ic]}
  \matrix{b= wims(replace internal item number \ic by t in \b)}
 }{
  \integer{val=\c[\ic]}
  \matrix{c= wims(replace internal item number \ic by t in \c)}
 }
}
**preparationde la solution rédigée
** préparation de la solution à afficher
\text{ab1=simplify(\b[1]-\a[1])}
\text{ab2=simplify(\b[2]-\a[2])}
\text{ab3=simplify(\b[3]-\a[3])}
\text{ac1=simplify(\c[1]-\a[1])}
\text{ac2=simplify(\c[2]-\a[2])}
\text{ac3=simplify(\c[3]-\a[3])}
\if{\ic=1}{
  \text{eq11=simplify((\ab1)*(\ac2))}
  \text{eq12=simplify((\ab2)*(\ac1))}
  \text{eq21=simplify((\ab1)*(\ac3))}
  \text{eq22=simplify((\ab3)*(\ac1))}
}
\if{\ic=2}{
  \text{eq11=simplify((\ab1)*(\ac2))}
  \text{eq12=simplify((\ab2)*(\ac1))}
  \text{eq21=simplify((\ab2)*(\ac3))}
  \text{eq22=simplify((\ab3)*(\ac2))}
}
\if{\ic=3}{
  \text{eq11=simplify((\ab1)*(\ac3))}
  \text{eq12=simplify((\ab3)*(\ac1))}
  \text{eq21=simplify((\ab2)*(\ac3))}
  \text{eq22=simplify((\ab3)*(\ac2))}
}
#endif
\text{rep=\k=1? \liste[1]:\liste[2]}

#if defined TARGET_alignpts2
\text{u=\b[1]- (\a[1]),\b[2]-(\a[2]),\b[3]-(\a[3])}
\text{v=\c[1]- (\a[1]),\c[2]-(\a[2]),\c[3]-(\a[3])}
\text{textsol=On veut donc :
\(\eq11 = \eq12) et \(\eq21=\eq22), soit \(t=\val).}
#endif
#if defined TARGET_alignpts
\if{\k=1}{
  \text{textsol=\name_textsol[1]:
\(\overrightarrow{B C}= \j \overrightarrow{A B}\),
  \name_textsol[2]}
}{
  \text{textsol=\name_textsol[3]: \name_textsol[4]}
}
#endif
#if defined TARGET_alignpts2
\text{size=confparm1=1 ? :x-large}
#endif
\statement{
<div class="\style1">
Les points \(A\),\(B\) et \(C\)
 dont les coordonnées dans un repère donné sont respectivement
<div class="wimscenter">
 \(A(\a[1];\a[2];\a[3])\), \(B(\b[1];\b[2];\b[3])\), \(C(\c[1];\c[2];\c[3])\)
</div>
#if defined TARGET_alignpts2
</div><div class="\style2">
Déterminer le réel \(t\) tel que les points soient alignés.
<div>
 Votre réponse : <label for="reply1">Valeur de \(t)</label> \embed{reply1,\size}.
</div>
</div>
#endif
#if defined TARGET_alignpts
sont-ils alignés ?
</div>
<div>
 Votre réponse : les points sont \embed{choice1,\size}.
</div>
#endif
}
#if defined TARGET_alignpts2
\answer{}{\val}{type=numeric}
#endif
#if defined TARGET_alignpts
\choice{}{\rep}{\liste}
#endif
\hint{\name_hint
\(\overrightarrow{A B}\) \name_and
#if defined TARGET_alignpts2
\(\overrightarrow{A C}\).
#endif
#if defined TARGET_alignpts
\(\overrightarrow{B C}\).
#endif
}
\solution{
\name_solution \(\overrightarrow{A B}) \name_and
#if defined TARGET_alignpts2
\(\overrightarrow{A C}\)
#endif
#if defined TARGET_alignpts
\(\overrightarrow{B C}\)
#endif
:
#if defined TARGET_alignpts2
<ul><li>
\name_calcul \(\overrightarrow{A B}): \(\left(\begin{array}{c}\b[1]- (\a[1]) \\ \b[2]-(\a[2]) \\ \b[3]-(\a[3])\end{array}\right)) = \(\left(\begin{array}{c} \ab1 \\ \ab2 \\ \ab3 \end{array}\right))<br>
</li><li>
\name_calcul \(\overrightarrow{A C}): \(\left(\begin{array}{c}\c[1]- (\a[1]) \\ \c[2]-(\a[2]) \\ \c[3]-(\a[3])\end{array}\right)) = \(\left(\begin{array}{c} \ac1 \\ \ac2 \\ \ac3 \end{array}\right))<br>
</li></ul>
#endif
#if defined TARGET_alignpts
\(\overrightarrow{A B})=\(\left(\begin{array}{c} \u[1] \\ \u[2] \\ \u[3]\end{array}\right))
\name_and \(\overrightarrow{B C})= \(\left(\begin{array}{c} \v[1] \\ \v[2] \\ \v[3]\end{array}\right)).<br>
#endif
\textsol
}
