target=syslin1 syslin2 syslin3 syslin4 syslin5
#include "author.inc"
\keywords{linear_system}
#define TITRE Systèmes linéaires
#if defined TARGET_syslin1
\title{TITRE I}
\integer{a=random(1..9)}
\integer{b=random(1..9)}
\integer{c=random(1..9)}
\integer{d=random(1..9)}
\integer{a2=random(1..9)}
\integer{b2=random(1..9)}
\integer{c2=random(1..9)}
\integer{d2=random(1..9)}
\integer{e1=random(1..9)}
\integer{e2=random(1..9)}
\text{data=texmath(\a*x+\b*y),texmath(\c*x + \d*y),\e1,\e2,1
\e1,\e2,texmath(\a*x+\b*y),texmath(\c*x + \d*y),1
  texmath(\a*x+\b*y),texmath(\c*x + \d*y),0,0,1
  texmath(\a*x+\b*y),texmath(\c*x + \d*y),texmath(\a2*x+\b2*y),texmath(\c2*x + \d2*y),1
  texmath(\a*x),texmath( \d*y),\e1,\e2,1
  texmath(\a*x^2 -\b*y),texmath(\c*x -\d),\e1,\e2,2
  texmath(\a*x -\b*y),texmath(\c*x + \d*y^2),\e1,\e2,2
  texmath(\a*xy + \b*y),  \frac{\c}{x},\e1,\e2,2
  texmath(\a*x) - \sqrt{y}, \c x + \d y,\e1,\e2,2
}
\text{cedata=randomrow(\data)}
\text{w=\cedata[1],\cedata[2]}
\text{e1=\cedata[3]}
\text{e2=\cedata[4]}
\integer{rep=\cedata[5]}
\statement{
  Le système
<div class="wimscenter">\( \left \lbrace \begin{array}{rcll} \w[1]&=&\e1 & (1)\\ \w[2]&=&\e2 & (2)\end{array} \right .)
</div>
  est-il un système linéaire ?
<div class="wimscenter">
\embed{reply1}
</div>
}
\answer{ Système linéaire ? }{\rep;Oui,Non}{type=radio}
#endif
#if defined TARGET_syslin2
\title{TITRE II}
\integer{a=random(1..9)}
\integer{b=random(1..9)}
\integer{c=random(1..9)}
\integer{d=random(1..9)}
\integer{a2=random(1..9)}
\integer{b2=random(1..9)}
\integer{c2=random(1..9)}
\integer{d2=random(1..9)}
\integer{e1=random(1..9)}
\integer{e2=random(1..9)}
\integer{b=\a=\b?\b+1} ## pour eviter (x,y) et (y,x) solution
\text{w=texmath(\a*x+\b*y),texmath(\c*x + \d*y)}
\text{data=Le système \(S) a pour solution un unique réel,2
  Les inconnues du système \(S) sont \(x) et \(y),1
  Les solutions du système \(S) sont des couples de réels,1
  Chaque équation du système \(S) représente l'équation d'une droite du plan,1
  Si le couple \((x,y)) est solution du système \(S)&#44; alors le couple \((y,x)) est aussi solution,2
  Les solutions du système \(S) sont les couples \((y,x)) qui vérifient chacune des deux équations de \(S),2
  Les solutions du système \(S) sont les couples \((x,y)) qui vérifient l'une ou l'autre des équations de \(S),2
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
  Soit \(S) le système
<div class="wimscenter">\( \left \lbrace \begin{array}{rcll} \w[1]&=&\e1 & (1)\\ \w[2]&=&\e2 & (2)\end{array}\right .)
</div>
\quest.
<div class="wimscenter">
\embed{reply1}
</div>
}
\answer{Réponse }{\rep;Vrai,Faux}{type=radio}
#endif

#if defined TARGET_syslin3
\title{TITRE III}
\text{data=Un système linéaire peut ne pas avoir de solution,1
  Un système linéaire peut avoir un couple solution unique,1
  Un système linéaire peut avoir une infinité de couples solutions,1
  Un système linéaire peut avoir exactement deux couples solutions,2
  Deux systèmes linéaires équivalents ont exactement les mêmes solutions,1
  En élevant au carré l'une des deux équations d'un système linéaire&#44; on obtient un système équivalent,2
  En multipliant par un réel non nul l'une des deux équations d'un système linéaire&#44; on obtient un système équivalent,1
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
  Cocher la bonne réponse.
<div class="wimscenter">\quest.</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{ Réponse }{\rep;Vrai,Faux}{type=radio}
#endif

#if defined TARGET_syslin4
\title{TITRE IV}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\integer{c=random(1..9)}
\integer{d=random(1..9)}
\integer{k=random(1..6)}
\integer{e1=random(1..9)}
\integer{e2=random(1..9)}
\if{\k=1}
 {
 \integer{x=0}
 \rational{y=\e1 / \b}
 \rational{e2=\d*\y}
 \integer{rep=1}
 }
\if{\k=2}
 {
 \integer{y=0}
 \rational{x=\e1 / \a}
 \rational{e2=\c*\x}
 \integer{rep=1}
 }
\if{\k=3}
 {
 \integer{x=randint(-5..5)}
 \rational{y=(\e1 -\a*\x) / \b}
 \rational{e2=\c*\x+\d*\y}
 \integer{rep=1}
 }
\if{\k=4}
 {
 \integer{x=0}
 \rational{y=\e1 / \b}
 \rational{e2=-\d*\y}
 \integer{rep=2}
 }
\if{\k=5}
 {
 \integer{y=0}
 \rational{x=\e1 / \a}
 \rational{e2=\c*\x+randint(1..5)}
 \integer{rep=2}
 }
\if{\k=6}
 {
 \integer{x=randint(-5..5)}
 \rational{y=(\e1 -\a*\x) / \b}
 \rational{e2=\c*\x+\d*\y-randint(1..5)}
 \integer{rep=2}
 }
\text{w=texmath(\a*x+\b*y),texmath(\c*x + \d*y)}
\statement{
  Le couple (\x,\y) est-il solution du système
<div class="wimscenter">\( \left \lbrace \begin{array}{rcll} \w[1]&=&\e1 & (1)\\ \w[2]&=&\e2 & (2)\end{array}\right .)
</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{ Solution ? }{\rep;Oui,Non}{type=radio}
#endif

#if defined TARGET_syslin5
\title{TITRE V}
\integer{a=random(1..9)}
\integer{b=random(1..9)}
\integer{c=random(1..9)}
\integer{d=random(1..9)}
\integer{e=random(1..9)}
\integer{f=random(1..9)}
\integer{det=\a*\c-\b*\d}
\integer{d=\det=0?\d+1}

\integer{k=random(1..5)}
\if{\k=1}
{
  \integer{n=randint(2..5)}
  \integer{m=random(1..5)}
  \integer{a2=\n*\a}
  \integer{b2=\n*\b}
  \integer{e2=\n*\e}
  \integer{c2=\m*\c}
  \integer{d2=\m*\d}
  \integer{f2=\m*\f}
  \integer{rep=1}
}
\if{\k=2}
{
  \integer{a2=\a+\c}
  \integer{b2=\b+\d}
  \integer{e2=\e+\f}
  \integer{c2=\c-\a}
  \integer{d2=\d-\b}
  \integer{f2=\f-\e}
  \integer{rep=1}
}
\if{\k=3}
{
  \integer{n=randint(2..5)}
  \integer{m=random(1..5)}
  \integer{a2=\n*\a}
  \integer{b2=\n*\b}
  \integer{e2=\n*\e}
  \integer{c2=\m*\a}
  \integer{d2=\m*\b}
  \integer{f2=\m*\e}
  \integer{rep=2}
}
\if{\k=4}
{
  \integer{n=randint(2..5)}
  \integer{m=random(1..5)}
  \integer{a2=\n*\a}
  \integer{b2=\n*\b}
  \integer{e2=\e}
  \integer{c2=\m*\c}
  \integer{d2=\m*\d}
  \integer{f2=\f}
  \integer{rep=2}
}
\if{\k=5}
{
  \integer{n=randint(2..5)}
  \integer{a2=\n*\a}
  \integer{b2=\n*\b}
  \integer{e2=\n*\e}
  \integer{c2=\c-\a}
  \integer{d2=\d-\b}
  \integer{f2=\f-\e}
  \integer{rep=1}
}

\text{u1=texmath(\a*x+\b*y)}
\text{v1=texmath(\c*x+\d*y)}
\text{u2=texmath(\a2*x+\b2*y)}
\text{v2=texmath(\c2*x+\d2*y)}
\statement{
  Les systèmes
<div class="wimscenter">
\(S_1 : \left \lbrace \begin{array}{rcll} \u1&=&\e & (1)\\ \v1&=&\f & (2)\end{array}\right .)
  et \(S_2 : \left \lbrace \begin{array}{rcll} \u2&=&\e2 & (1)\\ \v2&=&\f2 & (2)\end{array}\right .)
</div>
  sont-ils équivalents ?
<div class="wimscenter">\embed{reply1}</div>
}
\answer{ Systèmes équivalents ? }{\rep;Oui,Non}{type=radio}
#endif
