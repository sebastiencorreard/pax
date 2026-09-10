target=pbdeg21 pbdeg22 pbdeg23 pbdeg24 pbdeg25
\author{Régine, Mangeard;Maguy, Bruno}
\email{regine@mangeard.fr}
\format{html}
\keywords{equations, trinomial,roots}
#if defined TARGET_pbdeg21
# define NUM 1
#endif
#if defined TARGET_pbdeg22
# define NUM 2
#endif
#if defined TARGET_pbdeg23
# define NUM 3
#endif
#if defined TARGET_pbdeg24
# define NUM 4
#endif
#if defined TARGET_pbdeg25
# define NUM 5
#endif
#include "lang_titles.inc"
\text{dessin=
 xrange -15,15
 yrange -15,15
 parallel -15,-15,-15,15,1,0,30,gray
 parallel -15,-15,15,-15,0,1,30,gray
 linewidth 2
 arrow 0,-15,0,15,10,blue
 arrow -15,0,15,0,10,blue
 segment -0.2,1,0.2,1,black
 segment 1,-0.2,1,0.2,black
 text black,-0.7,1.5,small,1
 text black,0.7,-0.5,small,1
}
#if (defined TARGET_pbdeg21 || defined TARGET_pbdeg22 || defined TARGET_pbdeg23)
#if defined TARGET_pbdeg21
\integer{cas=randint(1..3)}
#endif
#if defined TARGET_pbdeg22
\integer{cas=2}
#endif
#if defined TARGET_pbdeg23
\integer{cas=2}
#endif
\integer{xs=randint(-3..3)}
\integer{ys=random(-3,-2,-1,0,0,0,1,2,3)}
\integer{x1=-15-randint(1..3)}
\integer{y1=randint(-20..20)}
\rational{a=(\y1-\ys)/(\x1-\xs)^2}
\text{f=\a*(x-\xs)^2+\ys}
\text{p=texmath(maxima(expand(\f)))}
\if{\cas=3}{
 \integer{xm=\a>0?\xs+sqrt((15-\ys)/\a):\xs+sqrt((\ys-15)/\a)}
 \integer{x2=randint(-10..\xm)}
 \rational{y2=evaluate(\f,x=\x2)}
 \rational{u=(\y2-\y1)/(\x2-\x1)}
 \rational{v=\y1-\u*\x1}
 }
\if{\cas=2}{
 \rational{u=2*\a*(\x1-\xs)}
 \rational{v=\y1-\u*\x1}
 }
\if{\cas=1}{
 \rational{u=2*\a*(\x1-\xs)}
 \rational{v=\a<0?\y1-\u*\x1+randint(1..3):\y1-\u*\x1-randint(1..3)}
 }

#if defined TARGET_pbdeg21
 \text{ladroite=plot green,\u*x+\v}
 \text{d=texmath(\u*x+\v)}
\text{tsol=}
#endif
#if defined TARGET_pbdeg22
 \text{dessin=animate 10,0.5,0
 \dessin
 }
 \text{ladroite= plot green,(\u+s*20-10)*x+\v}
 \text{d=texmath(t*x+\v)}
 \rational{t1=\u}
 \rational{t2=-2*\a(\x1+\xs)}
\text{lstt=\t1=\t2?\t1:\t1,\t2}
 rational{t=\u}
\text{a1=\a}
\text{a3=wims(replace internal / by , in \a1)}
\integer{a4=\a3[2]}
\text{eq0=texmath(maxima(expand(\a4*(\f - t*x -\v))))}
\text{eq2=wims(replace internal x^2 by , in \eq0)}
\text{eq2=wims(replace internal x by , in \eq2)}
\text{eq2=wims(replace internal t by *t in \eq2)}

\text{a2=\eq2[1]}
\text{a2=\a2=?1}
\text{b2=texmath(\eq2[2]+\eq2[3])}
\text{c2=\eq2[4]}
\text{tsol=On veut que l'équation \(\p=\d\) ait une seule solution,
  c'est-à-dire que le discriminant de \(\eq0=0\) soit nul.
  <div class="wimscenter">
\(\Delta=(\b2)^2-4\times (\a2) \times (\c2)=0 \Leftrightarrow t=\u\) ou \(t= \t2\)
</div>
}
#endif
#if defined TARGET_pbdeg23
 \text{dessin=animate 10,0.5,0
 \dessin
 }
 \text{ladroite= plot green,\u*x+\v+s*20-10}
 \text{d=texmath(\u*x+t)}
 \rational{t=\v}
\text{a1=\a}
\text{a3=wims(replace internal / by , in \a1)}
\integer{a4=\a3[2]}
\text{eq0=texmath(maxima(expand(\a4*(\f - \u*x -t))))}
\text{eq2=wims(replace internal x^2 by , in \eq0)}
\text{eq2=wims(replace internal x by , in \eq2)}
\text{a2=\eq2[1]}
\text{a2=\a2=?1}
\text{b2=\eq2[2]}
\text{c2=\eq2[3]}
\text{tsol=On veut que l'équation \(\p=\d) ait une seule solution,
  c'est-à-dire que le discriminant de \(\eq0=0) soit nul.
  <div class="wimscenter">
\(\Delta=(\b2)^2-4\times \a2 \times (\c2)=0 \Leftrightarrow t=\v)
</div>
}
#endif
\text{dessin=\dessin
 plot red,\f
 \ladroite
}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{300,300}{\dessin}</div>
  <div class="medium_size text_col">
  On a représenté une parabole \(\mathcal{P}) d'équation:
  <div class="wimscenter"> \(\mathcal{P}:y=\p)</div>
  ainsi que la droite \(\mathcal{D}) d'équation:
  <div class="wimscenter">\(\mathcal{D}:y=\d)</div>
 </div>
</div>

#if defined TARGET_pbdeg21
  Combien y a-t-il de points d'intersection entre la parabole et la droite?
<div class="wimscenter">\embed{reply1}</div>
}
\answer{nb points}{\cas;Aucun point, Un point, Deux points distincts}{type=radio}
#endif
#if defined TARGET_pbdeg22
  Pour quelle(s) valeur(s) de \(t\) la droite \(\mathcal{D}\) est-elle tangente à la parabole
  \(\mathcal{P}\)?<br>
<div class="wimscenter"><label for="reply1">valeur(s) de \(t\)</label>=\embed{reply1}</div>
<div class="wims_instruction"> S'il y a plusieurs valeurs, les séparer par une virgule.
  Donner la ou les valeurs sous forme de fraction.</div>
}
\answer{\(t\)}{\lstt}{type=fset}
#endif
#if defined TARGET_pbdeg23
  Pour quelle valeur de \(t\) la droite \(\mathcal{D}\) est-elle tangente à la parabole
  \(\mathcal{P}\)?
<div class="wimscenter"><label for="reply1">\(t\)=</label>\embed{reply1}</div>
}
\answer{t}{\t}{type=numexp}
#endif
\solution{\tsol}
#endif

#if defined TARGET_pbdeg24
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(-5..5)}
\integer{c=randint(-9..9)}
\integer{d=randint(1..5)*randint(1,-1)}
\text{fact=texmath(x-\d)}
\text{g=\a*x^2+\b*x+\c}
\text{f=(x-\d)*(\g)}
\text{tf=texmath(maxima(expand(\f)))}
\integer{yd=evaluate(\g,x=\d)}
\integer{del=(\b)^2-4*\a*\c}
\integer{nbsol=\yd=0?0:1}
\integer{isol=\del>0?2:1}
\integer{isol=\del<0?0}
\integer{nbsol=\nbsol+\isol}
\statement{
  On considère la fonction f, définie sur \(\,\RR\), par \(f(x)= \tf\).
<ol>
<li> Déterminer une fonction polynôme \(g\) de degré 2 telle que :
<div class="wimscenter">\(f(x)=(\fact)g(x)\)</div>

<div class="wimscenter"><label for="reply1">\(g(x)\)=</label>\embed{reply1}</div>
</li>
<li> Combien l'équation \(\tf=0\) possède-t-elle de solutions distinctes dans \(\,\RR\)?
<div class="wimscenter"> <label for="reply2">Nombre de solutions :</label>
  \embed{reply2}</div>
</li>
</ol>}
\answer{g}{\g}{type=function}
\answer{nb solutions}{\nbsol}{type=numeric}
#endif

#if defined TARGET_pbdeg25
\integer{a=randint(1..2)}
\text{xl=wims(makelist x,-x for x=1 to 10)}
\text{xl=shuffle(\xl)}
\rational{xa=\xl[1]/randint(2..5)}
\rational{xb=\xl[2]/randint(2..5)}
\integer{cn=1}
\while{\cn < 10 and \xa=-(\xb)}{
 \rational{xb=\xl[2]/randint(2..5)}
  \integer{cn=\cn+1}
}
\if{\xa=-\xb}{
  \rational{xa=\xl[1]/3}
  \rational{xb=\xa+1}
}
\if{\a=1}{
 \rational{x1=\xa<\xb?\xa:\xb}
 \rational{x2=\xa<\xb?\xb:\xa}
 }{
 \rational{x1=abs(\xa)<abs(\xb)?\xa:\xb}
 \rational{x2=abs(\xa)<abs(\xb)?\xb:\xa}
 }
\rational{s=\a=1?simplify(\x1+(\x2)):simplify(\x1-(\x2))}
\rational{p=\a=1? \x1*(\x2):-(\x1)*\x2}
\rational{d=(\s)^2-4*(\p)}
\text{ts=\s}
\text{ts=wims(replace internal / by , in \ts)}
\text{ts=items(\ts)=1?\ts[1]:\frac{\ts[1]}{\ts[2]}}
\rational{tp=\x1*(\x2)}
\text{tp=wims(replace internal / by , in \tp)}
\text{tp=items(\tp)=1?\tp[1]:\frac{\tp[1]}{\tp[2]}}

\text{eq1=\a=1?x+y=\ts:x-y=\ts}
\text{eq2=x y=\tp}
\text{equat=texmath(x^2-\s*x+\p=0)}
\statement{
  Résoudre le système, avec
  \if{\a=1}{\(x \leq y)}{\(|x| \leq |y|)} :
<div class="wimscenter">\(\begin{cases}\eq1\\ \eq2\end{cases})
</div>
<div class="wimscenter">
  <label for="reply1">Valeur de \(x)</label>:\embed{reply 1,10}
</div><div class="wimscenter">
  <label for="reply2">Valeur de \(y)</label>:\embed{reply 2,10}
</div>}
\answer{x1}{\x1}{type=numexp}
\answer{x2}{\x2}{type=numexp}
\solution{
Les nombres \(x\) et \if{\a=1}{\(y\)}{\(-y\)} ont pour somme \(\ts\) et pour produit
\(\p\) ; ils sont donc solutions de l'équation du second degré:
<div class="wimscenter">\(\equat).</div>
<p>Le discriminant de ce polynôme est égal à \(\d), ses racines
 sont \if{\a=1}{
 \(\x1) et \(\x2).}{ \(\x1) et \(-(\x2)).}
Le problème posé a donc comme solution \((\x1,\x2)\).
</p>
}
#endif
