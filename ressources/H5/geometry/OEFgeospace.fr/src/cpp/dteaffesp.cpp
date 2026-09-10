target=dteaffesp

#include "author.inc"
\precision{10000}
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"
 d'après un ex de Marie-Claude David
\text{size=confparm1=1 ? :x-large}

** donnée de trois vecteurs indépendants
\matrix{A=slib(matrix/invertible 3,3)}

**équation de la première droite
\matrix{u=\A[1;]}
\matrix{m=slib(matrix/random 1,3,5)}
\matrix{d1=pari(print([\u]*t+[\m]))}

**équation de la deuxième droite

\integer{k=randint(1..3)}

vecteur directeur

\matrix{v=\k=1? \u :\A[2;]}
\integer{j=randint(1..5)*random(-1,1)}
\matrix{v= pari(print([\v]*\j))}

cas parallèles ou confondues
\if{\k=1}{
  point de la deuxième droite
  \integer{p=randint(0..3)} si p=0, les droites sont confondues
  \matrix{n=pari(print([\A[2;]]*\p+[\m]-2*[\u]))}
  \matrix{d2=pari(print([\v]*t+[\n]))}
  réponse
  \text{rep=\p=0? confondues:strictement parallèles}
}

cas sécantes
\if{\k=2}{
  point de la deuxième droite
  \integer{p=randint(1..3)}
  \matrix{n=pari(print([\m]-\p*[\u]))}
  \matrix{d2=pari(print([\v]*t+[\n]))}
  réponse
  \text{rep=sécantes}
}
cas non coplanaires
\if{\k=3}{
  point de la deuxième droite
  \integer{p=randint(0..3)}
  \matrix{n=pari(print([\A[3;]]+[\m]-\p*[\u]))}
  \matrix{d2=pari(print([\v]*t+[\n]))}
  réponse
  \text{rep=non coplanaires}
}

\matrix{d1=texmath(\d1[1;1]),texmath(\d1[1;2]),texmath(\d1[1;3])}
\matrix{d2=texmath(\d2[1;1]),texmath(\d2[1;2]),texmath(\d2[1;3])}

\statement{
<div class="\style1">
<p>On considère deux droites de l'espace:</p>
<p> La droite \(d_1) passe par le point \(A(\m[1];\m[2];\m[3])) et a pour vecteur directeur \(\vec{u})\((\u)).</p>
<p> La droite \(d_2) passe par le point \(B(\n[1];\n[2];\n[3])) et a pour vecteur directeur \(\vec{v})\((\v)).</p>
On s'intéresse à leur position relative.
</div>
<div class="\style2">
 Votre réponse : Les deux droites sont \embed{choice1}.
 </div>
}

\choice{}{\rep}{\liste}
\hint{<ul>
<li> Si les vecteurs \(\vec{u}) et \(\vec{v}) sont colinéaires, les droites sont strictement
parallèles ou confondues.
<ul>
<li> Elles sont confondues si \(\overrightarrow{A B}) et \(\vec{u}) sont colinéaires.
</li><li> Elles sont strictement parallèles sinon.
</li></ul></li>
<li> Si les vecteurs \(\vec{u}) et \(\vec{v}) ne sont pas colinéaires,
 les droites sont sécantes ou non coplanaires.
<ul>
<li> Elles sont sécantes si les vecteurs \(\vec{u}), \(\vec{v}) et \(\overrightarrow{A B})
sont coplanaires.
</li><li> Elles sont non coplanaires sinon.
</li></ul></li>
</ul>
}
