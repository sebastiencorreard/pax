target=solsyslin1 solsyslin2 solsyslin3 solsyslin4 solsyslin5
#include "author.inc"
#define TITRE Solution d'un système linéaire
\keywords{linear_system}
\text{ltx=a,m,u,x}
\text{lty=b,n,v,y}
\integer{i=randint(1..4)}
\text{tx=\ltx[\i]}
\text{ty=\lty[\i]}

#if defined TARGET_solsyslin1
\title{TITRE I}
\text{tab=<table class="wimscenter wimsborder"><tr><td>a</td><td>b</td><td>c</td></tr><tr><td>a'</td><td>b'</td><td>c'</td></tr></table>}
\text{S=\( \left \lbrace \begin{array}{rcll} a x + b y&=&c & (1)\\ a' x + b' y&=&c' & (2)\end{array}\right .)}
\text{data=Si \(a b'=a' b)&#44; alors le système \S a un unique couple solution,2
  Si \(a b'=a'b)&#44; alors le système \S a une infinité de couples solutions,2
  Si \(a b'=a'b)&#44; alors le système \S n'a aucun couple solution,2
  Si \(a b'=a'b)&#44; alors le système \S n'a aucun couple solution ou bien une infinité de couples solutions,1
  Si \(a b' \not =a'b)&#44; alors le système \S n'a aucun couple solution,2
  Si \(a b' \not =a'b)&#44; alors le système \S a un unique couple solution,1
  Si \tab est un tableau de proportionnalité&#44; alors le système \S a une infinité de couples solutions,1}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}


#endif
#if defined TARGET_solsyslin2
\title{TITRE II}
\integer{a=random(1..9)*random(1,-1)}
\integer{b=random(1..9)*random(1,-1)}
\integer{c=random(1..9)*random(1,-1)}
\integer{d=random(1..9)*random(1,-1)}
\integer{k=randint(1..4)}
\text{e1=\ty}
\text{e2=\ty}
\if{\k=1}
 {
 \integer{i=randint(2..5)}
 \text{e2=\i\ty}
 \integer{c=\a*\i}
 \integer{d=\b*\i}
 \integer{rep=3}
 }
\if{\k=2}
 {
 \integer{c=\a}
 \text{e2=\ty}
 \integer{\rep=\d=\b?3:1}
 }
\if{\k=3}
 {
 \integer{i=randint(2..5)}
 \text{e2=\i\ty}
 \integer{c=\a*\i}
 \integer{d=\b*(\i-randint(1..3))}
 \integer{rep=1}
 }
\if{\k=4}
 {
  \if{\c=\a}
   {
    \integer{rep=\d=\b?3:1}
   }
   {
    \integer{rep=2}
   }
 }
\text{f1=texmath(maxima(\a*\tx+\b))}
\text{f2=texmath(maxima(\c*\tx+\d))}
#endif

#if (defined TARGET_solsyslin3  || defined TARGET_solsyslin4 )
#if defined TARGET_solsyslin3
\title{TITRE III}
\integer{a=random(1..9)*random(1,-1)}
\integer{b=random(1..9)*random(1,-1)}
\integer{e=random(1..9)*random(1,-1)}
\integer{c=random(1..9)*random(1,-1)}
\integer{d=random(1..9)*random(1,-1)}
\integer{f=random(1..9)*random(1,-1)}
#else
\title{TITRE IV}
\integer{a=random(1..99)*random(1,-1)}
\integer{b=random(1..99)*random(1,-1)}
\integer{e=random(1..99)*random(1,-1)}
\integer{c=random(1..99)*random(1,-1)}
\integer{d=random(1..99)*random(1,-1)}
\integer{f=random(1..99)*random(1,-1)}
\real{a=\a / 10}
\real{b=\b / 10}
\real{c=\c / 10}
\real{d=\d / 10}
\real{e=\e / 10}
\real{f=\f / 10}
#endif
\integer{k=randint(1..3)}
\if{\k=1}
 {
  \integer{i=randint(2..5)*randint(1,-1)}
  \real{c=\i*\a}
  \real{d=\i*\b}
  \real{f=\i*\e}
  \integer{rep=3}
 }
\if{\k=2}
 {
  \integer{i=randint(2..5)*randint(1,-1)}
  \real{c=\i*\a}
  \real{d=\i*\b}
  \real{f=random((\i-randint(1..3))*\e,-\i*\e)}
  \integer{rep=1}
 }
\if{\k=3}
 {
 \real{det=\a*(\c) - (\b)*(\d)}
 \integer{rep=2}
 \if{\det=0}
   {
   \real{det2=\a*(\f) - (\b)*(\e)}
   \integer{rep=\det2=0?3:1}
   }
 }
\text{e1=texmath(maxima(\a*\tx+\b*\ty))}
\text{e2=texmath(maxima(\c*\tx+\d*\ty))}
\real{f1=\e}
\real{f2=\f}
#endif


#if defined TARGET_solsyslin5
\title{TITRE V}
\text{lstsqrt=2,3,5,7,8,10,11}
\text{lstsqrt=shuffle(\lstsqrt)}
\integer{s1=\lstsqrt[1]}
\integer{k=randint(1..3)}
\integer{a=random(1..9)}
\integer{b=random(1..9)}
\integer{c=random(1..9)}
\integer{d=random(1..9)}
\integer{e=random(1..9)*random(1,-1)}
\integer{f=random(1..9)*random(1,-1)}
\if{\k=1}
 {
 \integer{c=\a*\b}
 \text{e1=\a \sqrt{\s1} x +\s1 y}
 \text{f1=\e}
 \text{e2=\c x + \b \sqrt{\s1} y}
 \text{f2=\f}
 \integer{rep=1}
}
\if{\k=2}
 {
 \text{f1=\c \sqrt{\s1}}
 \integer{f=\b*\c}
 \integer{c=\a*\b}
 \text{e1=\a \sqrt{\s1} x +\s1 y}
 \text{e2=\c x + \b \sqrt{\s1} y}
 \text{f2=\f}
 \integer{rep=3}

}
\if{\k=3}
 {
 \text{e1=\a \sqrt{\s1} x +\d y}
 \text{f1=\e}
 \text{e2=\c x + \b \sqrt{\s1} y}
 \text{f2=\f}
 \real{det=\a*\s1*(\b) - (\c)*(\d)}
 \integer{rep=\det=0?1:2}
 }
#endif
#if defined TARGET_solsyslin1
\statement{
<p>
  Cocher la bonne réponse.
</p>
\quest

<div class="wimscenter">\embed{reply1}</div>
}
\answer{Vrai-Faux }{\rep;Vrai,Faux}{type=radio}
#else
\statement{
  Cocher le nombre de solutions du système.
<div class="wimscenter">\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & (1)\\ \e2&=&\f2 & (2)\end{array}\right .)
</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{Nombre de solutions }{\rep;Aucune,un couple unique, une infinité de couples}{type=radio}
#endif
