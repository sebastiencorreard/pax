target=oefencad2
\language{fr}
\range{-5..5}
\author{Bernadette, Perrin-Riou;Gérard,Lauton}
\email{bernadette.m.riou@orange.fr}
\computeanswer{yes}
\format{html}
\precision{100}
#include "lang_titles.inc"
#include "lang.inc"
\real{a=randint(0..9)*random(-1,1)}
\real{b=randint(\a+1..10)}
\real{c=randint(0..9)*random(-1,1)}
\real{d=randint(\c+1..10)}
\integer{u=randint(-9..9)}
\integer{v=random(1,-1)*randint(1..9)}
\integer{w=randint(-9..9)}

\text{expr= (x-(\u))^2+(\v)*(y-(\w))^2}
\function{expr1=simplify(\expr)}
\text{expr1=texmath(\expr1)}
\text{expr=texmath(\expr)}
\text{texxu=texmath(x-(\u))}
\text{texyw=texmath(y-(\w))}
\real{M1= \b-(\u)}
\real{m1= \a-(\u)}
\real{Mx= max((\M1)^2,(\m1)^2)}
\real{mx= min(min((\M1)^2,(\m1)^2),max(0,(\m1)*(\M1)))}

\real{M2= \d-(\w)}
\real{m2= \c-(\w)}
\real{My= max((\M2)^2,(\m2)^2)}
\real{my= min(min((\M2)^2,(\m2)^2),max(0,(\m2)*(\M2)))}
\real{vmy = \v * \my}
\real{vMy = \v * \My}
\real{solm= min(\mx+(\v)*(\my),\mx+(\v)*(\My))}
\real{solM= max(\Mx+(\v)*(\my),\Mx+(\v)*(\My))}
\statement{
\name_enonce \({\a < x < \b}\) \name_and \({\c < y < \d}\).
  <label for="reply1">\name_question[1] \(\expr1\) \name_question[2] :</label>
  <div class="wimscenter">\embed{reply 1,8}
  <label for="reply2">\(< \expr1 < \)</label>\embed{reply 2,8}.</div>
}
\answer{Minimum}{\solm}{type=default}
\answer{Maximum}{\solM}{type=default}
#include "solencad2.inc"
\hint{\name_hint}
