target=ressyslin1 ressyslin2 ressyslin3 ressyslin4 ressyslin5
#include "author.inc"
#define TITRE Résolution d'un système linéaire
\keywords{linear_system}
\text{ltx=a,m,u,x}
\text{lty=b,n,v,y}
\integer{i=randint(1..4)}
\text{tx=\ltx[\i]}
\text{ty=\lty[\i]}

#if defined TARGET_ressyslin1
\title{TITRE I}
\integer{a=random(1..9)*random(1,-1)}
\integer{b=random(1..9)*random(1,-1)}
\integer{c=random(1..9)*random(1,-1)}
\integer{d=random(1..9)*random(1,-1)}

\integer{c=\c=\a?-1*(\c)}
\rational{x=(\b-(\d))/(\c-(\a))}
\rational{y=\a*(\x)+(\b)}
\text{e1=texmath(\a*\tx+\b)}
\text{e2=texmath(\c*\tx+\d)}
\statement{
  Résoudre le système :
<div class="wimscenter">\( \left \lbrace \begin{array}{rcll} \ty&=&\e1 & (1)\\ \ty&=&\e2 & (2)\end{array} \right .)
</div>

<div class="wimscenter">S={(\embed{reply1,4},\embed{reply2,4})}</div>
}
\answer{ \tx }{\x}{type=numexp}
\answer{ \ty }{\y}{type=numexp}

#endif

#if (defined TARGET_ressyslin2  || defined TARGET_ressyslin3 )

\text{coef=wims(makelist x,-x for x=2 to 9)}
\text{coef=shuffle(\coef)}
\text{lstcoef=random(1,-1),item(1..3,\coef)}
\text{lstcoef=shuffle(\lstcoef)}
\integer{a=\lstcoef[1]}
\integer{b=\lstcoef[2]}
\integer{c=\lstcoef[3]}
\integer{d=\lstcoef[4]}

\integer{det=\a*\d-\b*\c}
\integer{c=\det=0?-1*(\c)}
\integer{det=\a*\d-\b*\c}

#if defined TARGET_ressyslin2
\title{TITRE II}
\integer{x=randint(-9..9)}
\integer{y=randint(-9..9)}
\integer{f1=\a*\x+\b*\y}
\integer{f2=\c*\x+\d*\y}
#endif

#if defined TARGET_ressyslin3
\title{TITRE III}
\integer{f1=randint(-9..9)}
\integer{f2=randint(-9..9)}
\integer{detx=\f1*\d-\b*\f2}
\integer{dety=\a*\f2-\f1*\c}

\rational{x=simplify(\detx/\det)}
\rational{y=simplify(\dety/\det)}
#endif

\text{e1=texmath(\a*\tx+\b*\ty)}
\text{e2=texmath(\c*\tx+\d*\ty)}
\statement{
  Résoudre le système :
<div class="wimscenter">\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & (1)\\ \e2&=&\f2 & (2)\end{array} \right .)
</div>

<div class="wimscenter">S={(\embed{reply1,4},\embed{reply2,4})}</div>
}
\answer{ \tx }{\x}{type=numexp}
\answer{ \ty }{\y}{type=numexp}
#endif


#if defined TARGET_ressyslin4
\title{TITRE IV}
\integer{a=random(10..99)*random(1,-1)}
\integer{b=random(10..99)*random(1,-1)}
\integer{c=random(10..99)*random(1,-1)}
\integer{d=random(10..99)*random(1,-1)}
\integer{x=random(0..20)*random(1,-1)}
\integer{y=random(0..20)*random(1,-1)}

\integer{det=\a*\d-\b*\c}
\integer{c=\det=0?-1*(\c)}
\real{a=\a/10}
\real{b=\b/10}
\real{c=\c/10}
\real{d=\d/10}
\real{f1=\a*\x+\b*\y}
\real{f2=\c*\x+\d*\y}
\text{e1=texmath(\a*\tx+\b*\ty)}
\text{e2=texmath(\c*\tx+\d*\ty)}
\statement{
  Résoudre le système :
<div class="wimscenter">\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & (1)\\ \e2&=&\f2 & (2)\end{array}\right .)
</div>

<div class="wimscenter">S={(\embed{reply1,4},\embed{reply2,4})}</div>
}
\answer{ \tx }{\x}{type=numexp}
\answer{ \ty }{\y}{type=numexp}
#endif

#if defined TARGET_ressyslin5
\title{TITRE V}
\text{lstsqrt=2,3,5,7,8,10,11}
\text{lstsqrt=shuffle(\lstsqrt)}
\integer{s1=\lstsqrt[1]}
\integer{s2=\lstsqrt[2]}
\integer{k=randint(1..2)}
\if{\k=1}
 {
%% x=\a*sqrt(s1) y entier, systeme x*sqrt(s1)+\b*y= entier, \c*x+sqrt(\d*s1)*y=sqrt(\f*s1)
 \integer{a=randint(1..5)}
 \integer{b=randint(1..9)}
 \integer{y=randint(1..9)}
 \integer{e=\a*\s1+\b*\y}
 \integer{c=randint(1..5)}
 \integer{d=randint(1..5)}

 \integer{dd=\d^2*\s1}
 \integer{f=\c*\a+\d*\y}
 \integer{ff=\f^2*\s1}
 \text{e1=x \sqrt{\s1} +\b y}
 \text{f1=\e}
 \text{e2=\c x + \sqrt{\dd} y}
 \text{f2=\sqrt{\ff}}
 \text{x=\a*sqrt(\s1)}
}
\if{\k=2}
 {
%%% x=\a*sqrt(s1) y \b*sqrt(s2), systeme x*sqrt(s2)+y*sqrt(s1)= (a+b)sqrt(s1*s2), \c*sqrt(s1)*x+d*sqrt(s2)*y=c*a*s1+b*d*s2
 \integer{a=randint(1..5)}
 \integer{b=randint(1..9)}
 \integer{y=randint(1..9)}
 \integer{e=\a+\b}
 \integer{ss=\s1*\s2}
 \integer{c=randint(2..5)}
 \integer{d=randint(2..5)}
 \integer{dd=\d^2*\s1}
 \integer{f=\c*\a*\s1+\d*\b*\s2}
 \text{e1=x \sqrt{\s2} + y \sqrt{\s1}}
 \text{f1=\e \sqrt{\ss}}
 \text{e2=\c \sqrt{\s1} x + \d \sqrt{\s2} y}
 \text{f2=\f}
 \text{x=\a*sqrt(\s1)}
 \text{y=\b*sqrt(\s2)}
}
\statement{
  Résoudre le système :
<div class="wimscenter">\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & (1)\\ \e2&=&\f2 & (2)\end{array}\right .)
</div>

<div class="wimscenter">S={(\embed{reply1,7},\embed{reply2,7})}</div>
<div class="wims_instruction">
  Taper <span class="tt">sqrt(..)</span> pour saisir une racine carrée,
  par exemple taper <span class="tt">sqrt(2)</span> pour \(\sqrt{2}).
</div>
}
\answer{ \tx }{\x}{type=formal}
\answer{ \ty }{\y}{type=formal}
#endif
