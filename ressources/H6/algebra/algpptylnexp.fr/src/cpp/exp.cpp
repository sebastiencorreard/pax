target=exp1 exp2 exp3
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}
#if defined TARGET_exp1
\text{l=shuffle(2,3,5,7,11)}
\integer{a=item(1,\l)}
\integer{b=item(2,\l)}
\integer{n=random(2,6)*random(-1,1)}
\integer{m=random(2,6)*random(-1,1)}
\rational{p1=(\n*\a)+(\m*\b)}
\integer{p2=\a*\n}
\integer{p3=-(\a*\n)}
\integer{p4=\n+\m}
\integer{p5=\n-\m}
\text{AA=exp(\a)^\n*exp(\b)^\m,exp(\a)^\n,1/((exp(\a))^\n),exp(\n)*exp(\m),(exp(\n))/(exp(\m))}
#endif
#if defined TARGET_exp2
\text{l=shuffle(x,y,z,u,v)}
\text{a=item(1,\l)}
\text{b=item(2,\l)}
\text{l=shuffle(2,3,5,7,11,13)}
\integer{n=item(1,\l)*random(-1,1)}
\integer{m=item(2,\l)*random(-1,1)}
\function{p1=simplify((\n*\a)+(\m*\b))}
\function{p2=\n*\a}
\function{p3=simplify(-(\n*\a))}
\function{p4=simplify((\n*\a)+(\m*\b))}
\function{p5=simplify((\n*\a)-(\m*\b))}
\text{AA=exp(\a)^\n*exp(\b)^\m,exp(\a)^\n,1/((exp(\a))^\n),exp(\n*\a)*exp(\m*\b),(exp(\n*\a))/(exp(\m*\b))}
#endif
#if defined TARGET_exp1 || defined TARGET_exp2
\text{BB=\p1,\p2,\p3,\p4,\p5}
\integer{cas=random(1..5)}
\function{A=item(\cas,\AA)}
\function{B=item(\cas,\BB)}
#endif
#if defined TARGET_exp3
\text{l=shuffle(x,y,z,u,v)}
\text{x=item(1,\l)}
\integer{a=random(2..15)}
\text{l=shuffle(2,3,5,7,11,13)}
\integer{n=item(1,\l)}
\integer{s=random(-1,1)}
\integer{m0=item(2,\l)}
\integer{m=item(2,\l)*\s}

\text{u=\s=1?\n\x+\m:\n\x-\m0}
\text{oppu=\s=1?-\n\x-\m:-\n\x+\m0}

\text{AA=\a,\a^{\x},\a^{\u},e^{\u},\a e^{\x},\frac{1}{e^{\u}},\frac{1}{\a^{\u}}}
\text{BB=ln(\a),\x*ln(\a),ln(\a)(\u),\u,\x + ln(\a),\oppu,ln(\a)(\oppu)}
\integer{cas=random(1..7)}
\function{A=item(\cas,\AA)}
\function{B=item(\cas,\BB)}
#endif
\statement{
<div class="wims_question">
#if defined TARGET_exp1 || defined TARGET_exp2
On donne \(A = \A \), où exp désigne la fonction exponentielle.
<p>
Réécrire \(A) sous la forme exp(\(p)), où \(p\) est
# if defined TARGET_exp1
un entier relatif.
# endif
# if defined TARGET_exp2
une expression sans exponentielle.
# endif
</p>
#endif
#if defined TARGET_exp3
  On considère l'expression \(A = \A \).
  Réécrire \(A) sous la forme exp(\(B)).
<div class="wims_instruction">
exp désigne la fonction exponentielle de base e.
</div>
#endif
<div class="wimscenter">
<label for="reply1">\(A \) = exp </label> (\embed{reply1,15}).</div>
</div>}
#if defined TARGET_exp1
\answer{}{\B}{type=litexp}
#endif
#if defined TARGET_exp2 || defined TARGET_exp3
\answer{}{\B}{type=formal}
#endif
\hint{
Les règles de calcul des exponentielles sont :
<div class="wimscenter">
#if defined TARGET_exp3
\( e = exp(1)\) et \( e^x = exp( x )\) <br>
\( a^x = e^{x ln(a)} = exp(x ln(a))\) avec \(a > 0 \) et \( x \in \RR\).
<br>
#endif
\(\exp (a + b) = \exp(a) \times \exp(b) \)<br>
\(\exp ( a - b ) = \frac{\exp(a)}{\exp(b)}\)<br>
\(\exp(n\times a) = \exp(a)^n \) <br>
\(\exp(-a) = \frac{1}{\exp(a)} \)
</div>
}
#if defined TARGET_exp3
\feedback{0=0}{
Voici un corrigé :<br>
\if{\cas=1}{\( \a = e^{\ln(\a)} = \exp(\ln(\a)) )}
\if{\cas=2}{Par définition de la fonction exponentielle de base \(\a) : \( \a^{t} = e^{\ln(\a) \times t} = \exp( t \ln(\a))) .}
\if{\cas=3}{Par définition de la fonction exponentielle de base \(\a) : \(\a^{t} = e^{\ln(\a) \times t} = \exp( \ln(\a) \times t)) .<br>
  Donc \( \a^{\u} = \exp( \ln(\a) \times (\u))).}
\if{\cas=4}{ \( e^{\u} = \exp(\u) \) (notation puissance).}
\if{\cas=5}{\(\a = e^{\ln(\a)}\) donc \(\a e^{\x} = e^{\ln(\a)}\times e^{\x} = e^{\ln(\a)+\x} = \exp(\ln(\a)+\x)\)}
\if{\cas=6}{\( \frac{1}{e^{\u}} = e^{-(\u)} = \exp(\oppu)\)}
\if{\cas=7}{\( \frac{1}{\a^{\u}} = \a^{-(\u)} = \a^{\oppu} = e^{\ln(\a)(\oppu)} = \exp(\ln(\a)(\oppu))\)}
}
#endif
