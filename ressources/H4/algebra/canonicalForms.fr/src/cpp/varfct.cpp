target=varfctcarre

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{sa=randitem(-1,1)}
\integer{a=\sa*random(1..5)}
\integer{b=random(-10..10)}
\integer{c=randitem(-1,1)}
\integer{d=random(-10..10)}

\function{ux=maxima(\c*x+\d)}
text{ux=wims(replace internal * by in \ux)}
\rational{x0=-\d/\c} //// abscisse alpha du sommet

\function{f= \a*(\ux)^2+\b}
text{f=wims(replace internal * by in \f)}

\integer{rep1=\a}
\integer{rep2=\a>0?1:2}
\integer{rep3=\a>0?1:2}
\integer{rep4=\x0}
\integer{rep5=\b}
\integer{rep6=\a>0?1:2}
\integer{rep9=\a>0?1:2}
\integer{rep10=\a>0?1:2}
\integer{\nbrac=(\a*\b)>0?0:2}
\integer{\nbrac=\b=0?1}
\integer{rep11=\nbrac + 1}
<div style="background:#F6E497;padding:10px;">

\statement{
On considère la fonction \(f\) définie sur \(\,\RR\) par \(f(x) = \f\).
On note \(P\) la représentation graphique de \(f\) dans un repère du plan.
On étudie le sens de variation de \(f\) sur \(\,\RR\).
<p>
Complétez le texte suivant en insérant ou choisissant les bonnes réponses.
</p>
<div class="wims_question">
<ol><li>
Sous forme développée \(f(x)\) s'écrit \(a*x^2 + b*x + c\) avec \(a\) = \embed{reply1,5}.
</li><li>
On en déduit que la parabole \(P\) est tournée vers le \embed{reply2}, car le coefficient \(a\) est \embed{reply3}
</li><li>
Le sommet S de la parabole \(P\) a pour coordonnées S(\embed{reply4,5}; \embed{reply5,5}).
</li><li>
On en déduit que la fonction \(f\) admet un \embed{reply6} qui vaut \embed{reply7,5} obtenu pour \(x\) = \embed{reply8,5}
</li><li>
Sur l'intervalle &#93; - \infty&#160; ; &#160;\x0 &#93;, la fonction \(f\) est \embed{reply9}.
<br>
Sur l'intervalle &#91; \x0&#160;;&#160; + \infty &#91;, la fonction \(f\) est \embed{reply10}.
</li><li>
Les résultats précédents permettent l'affirmation suivante sur \(f\) \embed{reply11}.
</ol>
</div>
}

\answer{valeur de a}{\rep1}
\answer{Allure de la parabole}{\rep2;haut,bas}{type=menu}{option=shuffle}
\answer{Signe de a}{\rep3;positif,négatif}{type=menu}{option=shuffle}
\answer{Abscisse du sommet}{\rep4}
\answer{Ordonnée du sommet}{\rep5}
\answer{Extremum de f}{\rep6;minimum,maximum}{type=menu}{option=shuffle}
\answer{Valeur extrême de f}{\rep5}
\answer{Pour x = }{\rep4}
\answer{Variation de f avant \x0}{\rep9;strictement décroissante,strictement croissante}{type=menu}{option=shuffle}
\answer{Variation de f après \x0}{\rep10;strictement croissante,strictement décroissante}{type=menu}{option=shuffle}
\answer{Racines de f}{\rep11;aucune racine, une seule racine, deux racines distinctes, on ne sait pas}{type=menu}

\hint{
  Toute fonction du second degré admet une forme canonique :
  \(f(x) = a(x - \alpha)^2 + \beta\).<br>
  Le signe de \(a\) détermine si la parabole \(P\) représentant \(f\)
  est tournée vers le haut ou le bas.<br>
  Le sommet de la parabole est \(S(\alpha ; \beta)\).<br>
  Le sens de variation de la fonction \(f\) s'inverse en \(\alpha\).<br>
  L'extremum de la fonction \(f\) vaut \(\beta\) ;
  il est obtenu pour \(x = \alpha\).<br>
  Lorsque \(beta\) et \(a\) sont de signes contraires,
  la parabole \(P\) croise l'axe des abscisses,
  et donc la fonction \(f\) admet deux racines.
  <p>
  NB : on appelle "racine de \(f\)" toute solution \(x\)
  de l'équation de \(f(x)=0\).
  </p>}
