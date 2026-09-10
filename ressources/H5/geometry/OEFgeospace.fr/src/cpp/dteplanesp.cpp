target=dteplanesp
#include "author.inc"
\precision{10000}
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

** donnée de trois vecteurs indépendants
\matrix{A=slib(matrix/invertible 3,3)}

\matrix{u=\A[1;]}
\matrix{v=\A[2;]}
\matrix{w=\A[3;]}
\matrix{m=slib(matrix/random 1,3,5)}
\matrix{n=slib(matrix/random 1,3,5)}
\integer{a= randint(1..5)*random(-1,1)}
\integer{b= randint(1..5)*random(-1,1)}
\integer{c= randint(1..5)*random(-1,1)}
\integer{d= randint(1..5)*random(-1,1)}
\integer{k=randint(1..3)}

*** cas secant
\if{\k=3}{
  \text{rep=3}
}{
** on remplace u par une combinaison lineaire de v et w
  \matrix{oldu=\u}
  \matrix{u= pari(print([\v]*\a+[\w]*\b))}
*** cas inclu
  \if{\k=1}{
    \text{rep=1}
*** on remplace n de sorte que AB soit dans le plan
    \matrix{n=pari(print([\v]*\c+[\w]*\d+[\m]))}
   }{
*** cas parallèle
    \text{rep=2}
*** on remplace n de sorte que AB ne soit pas dans le plan
    \matrix{n=pari(print([\v]*\c+[\w]*\d+[\m]+[\oldu]*\a))}
  }
}

\statement{
<div class="\style1">
 <p> On considère une droite et un plan de l'espace.</p>
 <p> La droite \(d) passe par le point \(A(\m[1];\m[2];\m[3]))
  et a pour vecteur directeur \(\vec{u})\((\u)).</p>
 <p> Le plan \(P) passe par le point \(B(\n[1];\n[2];\n[3]))
  et a pour vecteurs directeurs \(\vec{v})\((\v)) et \(\vec{w})\((\w)).
 </p>
</div>
<div class="\style2">
 Votre réponse :
 La droite \(d) est \embed{reply1}
</div>
}

\answer{}{\k ;\liste}{type=menu}
\hint{<ul>
<li> Si les vecteurs \(\vec{u}), \(\vec{v}) et \(\vec{w}) sont coplanaires,
la droite est parallèle ou incluse dans le plan.
<ul>
<li> Elle est incluse dans le plan si \(\overrightarrow{A B}), \(\vec{v})
et \(\vec{w}) sont coplanaires.
</li><li> Elle est strictement parallèle au plan sinon.
</ul>
</li>
<li> Si les vecteurs \(\vec{u}), \(\vec{v}) et \(\vec{w}) ne sont pas coplanaires,
 la droite est sécante avec le plan.
</li>
</ul>
}
\feedback{\reply1 notsametext \liste[\k] and \k==1}{
  \(\vec{u}) = \a*\(\vec{v}) +\b*\(\vec{w})<br>
  La droite est donc incluse dans le plan ou strictement parallèle<br>
  De plus, \(\overrightarrow{A B})= \c*\(\vec{v}) +\d*\(\vec{w})<br>,
  donc la droite est incluse dans le plan.}
\feedback{\reply1 notsametext \liste[\k] and \k==2}{
  \(\vec{u}) = \a*\(\vec{v}) +\b*\(\vec{w})<br>
  La droite est donc incluse dans le plan ou strictement parallèle.<br>
  De plus, \(\overrightarrow{A B}) n'est pas une combinaison linéaire de \(\vec{v}) et \(\vec{w}) <br>
  donc la droite est strictement parallèle au plan.}
\feedback{\reply1 notsametext \liste[\k] and \k==3}{
  \(\vec{u}), \(\vec{v}) et \(\vec{w})ne sont pas coplanaires,
  donc la droite est sécante avec le plan.}
