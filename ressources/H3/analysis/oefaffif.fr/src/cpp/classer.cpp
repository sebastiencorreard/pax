target= classer1 classer2 classer3 classer4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_classer1
\integer{nbfnct=2}
\integer{nonlin=0}
\text{size=175x50x4}
#endif
#if defined TARGET_classer2
\integer{nbfnct=3}
\integer{nonlin=0}
\text{size=175x50x6}
#endif
#if defined TARGET_classer3
\integer{nbfnct=2}
\integer{nonlin=1}
\text{size=175x50x4}
#endif
#if defined TARGET_classer4
\integer{nbfnct=3}
\integer{nonlin=1}
\text{size=175x50x6}
#endif
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{a=random(2..10)}
\integer{b=random(-1,1)*random(2..10)}
\integer{c=random(2..11)}
\integer{d=random(-1,1)*random(2..100)}
\real{d=\d/10}
\integer{e=random(2..100)}
\real{e=\e/10}
\integer{f=random(-1,1)*random(3,5,9,15)}
\integer{g=random(-1,1)*random(2,7,4,8,14)}

\matrix{donnees=\sqrt{\a}x,\b x,\e x,\frac{\f}{\g}x,\frac{\sqrt{\a}}{\g}x
\sqrt{\a}x+\c,\sqrt{\a}x-\c,\b x+\a,\b x-\a,\f x+\e,\f x-\e,\frac{\f}{\g}x+\a,\frac{\sqrt{\a}}{\g} x-\c,\frac{\f}{\g}x+\frac{\a}{\c},\b(x+\c)
\cos(\a x),\sin(\b x),tan(\c x),\b x^2+\a x+\c,\sqrt{\a}x^2+\e x+\c, \frac{\f}{\g}x^2+\frac{\a}{\b} x+\c,\b x^2,(x+\c)(x+\a),(x+\e)^2,(x-\c)^2}

\matrix{sortie=}
\for{i=1 to 3}{
\text{tmp=row(\i,\donnees)}
\text{tmp=shuffle(\tmp)}
\text{line=}
\for{j=1 to \nbfnct}{
\text{tmp1=item(\j,\tmp)}
\text{tmp1=\(x\mapsto \tmp1)}
\text{line=wims(append item \tmp1 to \line)}
}
\text{sortie=wims(append line \line to \sortie)}
}

\text{goodlin=row(1,\sortie)}
\text{goodaff=row(2,\sortie)}
\text{goodaut=row(3,\sortie)}
\text{list=\goodlin,\goodaff,\goodaut}
\if{\nonlin=0}{
\text{goodaff=\goodaff,\goodlin}
\text{enonceaffine=}
}{
\text{enonceaffine=\name_type[4]}
}
\statement{
\name_enonce:
<ul><li>\name_type[1]:
\embed{r1,\size}</li>
<li>\name_type[2] \enonceaffine:
\embed{r2,\size}</li>
<li>\name_type[3]:
\embed{r3,\size}</li>
</ul>
}

\reply{\name_type[1]}{\replin;\list}{type=clickfill}
\reply{\name_type[2] \enonceaffine}{\repaff;\list}{type=clickfill}
\reply{\name_type[3]}{\repaut;\list}{type=clickfill}

\text{tmplin=\replin,\goodlin}
\text{tmplin=wims(listuniq \tmplin)}
\text{replin=wims(listuniq \replin)}
\integer{lin1=items(\tmplin)}
\integer{lin2=items(\replin)}
\condition{\name_type[1]}{\lin1=\nbfnct and \lin2=\nbfnct}
\text{tmpaff=\repaff,\goodaff}
\text{tmpaff=wims(listuniq \tmpaff)}
\integer{aff1=items(\tmpaff)}
\text{repaff=wims(listuniq \repaff)}
\integer{aff2=items(\repaff)}
\integer{tmp=items(\goodaff)}
\condition{\name_type[2] \enonceaffine}{\aff1=\tmp and \aff2=\tmp}
\text{tmpaut=\repaut,\goodaut}
\text{tmpaut=wims(listuniq \tmpaut)}
\integer{aut1=items(\tmpaut)}
\text{repaut=wims(listuniq \repaut)}
\integer{aut2=items(\repaut)}
\condition{\name_type[3]}{\aut1=\nbfnct and \aut2=\nbfnct}

\solution{<ul>
  <li>\name_type[1] : \goodlin</li>
  <li>\name_type[2] : \goodaff</li>
  <li>\name_type[3] : \goodaut</li>
</ul>}
