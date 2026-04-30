target=solution1 solution2 solution3 solution4 solution5

#include "author.inc"
#include "lang_titles.inc"

\text{inc=randrow(x,y
u,v
a,b)}
\text{x=\inc[1]}
\text{y=\inc[2]}

#if defined TARGET_solution1
 \text{v=wims(values v,-v for v=1 to 9)}
 \text{v=shuffle(\v)}
 \text{enonce=Soit l'équation <div class="wimscenter">\(\v[1]*\x + \v[2] = \v[3]*\x+\v[4]).</div>}
 \text{n1=simplify((\v[4]-\v[2])/(\v[1]-\v[3]))}
 \text{n2=simplify(-\n1)}
 \integer{n3=randitem(-1,1)}
 \text{n3=simplify(\n1+\n3)}
 \text{n1=texmath(\n1)}
 \text{n2=texmath(\n2)}
 \text{n3=texmath(\n3)}
 \text{good=\(\n1) est solution de cette équation.}
 \text{bad=\(\n2) est solution de cette équation.,\(\n3) est solution de cette équation.,Cette équation n'a pas de solution.}
#endif
#if defined TARGET_solution2
 \text{v=wims(values v,-v for v=1 to 9)}
 \text{v=shuffle(\v)}
 \text{enonce=Soit l'équation <div class="wimscenter">\((\v[1]*\x + \v[2])(\v[3]*\x+\v[4]) = 0).</div>}
 \text{n1=simplify(-\v[2]/(\v[1]))}
 \text{n2=simplify(-\v[4]/(\v[3]))}
 \text{n1=texmath(\n1)}
 \text{n2=texmath(\n2)}
 \text{good=\(\n1) et \(\n2) sont les deux solutions de cette équation.}
 \text{bad=\(\n1) est la seule solution de cette équation.,\(\n2) est la seule solution de cette équation.,Cette équation n'a pas de solution.}
#endif
#if defined TARGET_solution3
 \integer{a=randitem(2,3,5,6,7,8)}
 \text{enonce=Soit l'équation <div class="wimscenter">\(\x^2 - \a = 0).</div>}
 \text{n1=sqrt(\a)}
 \text{n2=-sqrt(\a)}
 \text{n1=texmath(\n1)}
 \text{n2=texmath(\n2)}
 \text{good=\(\n1) et \(\n2) sont les deux solutions de cette équation.}
 \text{bad=\(\n1) est la seule solution de cette équation.,\(\a) est solution de cette équation.,Cette équation n'a pas de solution.}
#endif
#if defined TARGET_solution4
 \text{v=wims(values v,-v for v=1 to 9)}
 \text{v=shuffle(\v)}
 \text{coeffs=slib(matrix/givenrank 2,2,2,5)}
 \text{a=row(1,\coeffs)}
 \text{b=row(2,\coeffs)}
 \integer{c=\a[1]*\v[1]+\a[2]*\v[2]}
 \integer{d=\b[1]*\v[1]+\b[2]*\v[2]}
 \text{t1=texmath(simplify(\a[1]*\x+\a[2]*\y))}
 \text{t2=texmath(simplify(\b[1]*\x+\b[2]*\y))}
 \text{enonce=Soit le système d'équations
  <div class="wimscenter">\(\left\lbrace\begin{array}{ccc}\t1&=&\c\\ \t2&=&\d\end{array}\right.)</div>}
 \text{good=\((\v[1];\v[2])) est le couple solution de ce système d'équations.}
 \text{bad=\(\v[1]) est une solution de ce système d'équations.,\(\v[1]) et \(\v[2]) sont les deux solutions de ce système d'équations.,Ce système d'équations n'a pas de solution.}
#endif
#if defined TARGET_solution5
 \text{v=wims(values v for v=1 to 9)}
 \text{v=shuffle(\v)}
 \integer{ch=randint(1..2)}
 \text{sy=item(\ch,<,>)}
 \text{enonce=Soit l'inéquation :
  <div class="wimscenter">\(\v[1]\x + \v[2] \sy \v[3]).</div>}
 \text{n1=simplify((\v[3]-\v[2])/\v[1])}
 \text{n2=item(\ch,-1,1)}
 \text{n2=simplify(\n1+\v[4]*\n2)}
 \text{n1=texmath(\n1)}
 \text{n2=texmath(\n2)}
 \text{sens=item(\ch,inférieurs,supérieurs)}
 \text{good=Tous les nombres strictements \sens à \(\n1) sont solutions de cette inéquation.}
 \text{bad=\(\n1) est solution de cette inéquation.,\(\n2) est la seule solution de cette inéquation.,Cette inéquation n'a pas de solution.}
#endif
\statement{
\enonce
  Parmi les affirmations suivantes laquelle est vraie ?}

\choice{Réponse}{\good}{\bad}
