target=findaff1 findaff2 findaff3 findaff4 findaff5
#if defined TARGET_findaff1
# define NUM 1
#endif
#if defined TARGET_findaff2
# define NUM 2
#endif
#if defined TARGET_findaff3
# define NUM 3
#endif
#if defined TARGET_findaff4
# define NUM 4
#endif
#if defined TARGET_findaff5
# define NUM 5
#endif
#include "lang_titles.inc"
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\text{xl=wims(makelist x,-x for x=1 to 20)}
\text{ind=shuffle(40)}
\integer{x1=\xl[\ind[1]]}
\integer{x2=\xl[\ind[2]]}
\integer{x3=\xl[\ind[3]]}
\rational{a=simplify(randint(1..9)*randint(1,-1)/randint(1..7))}
\rational{b=simplify(randint(1..9)*randint(1,-1)/randint(1..7))}
\rational{y1=\a*\x1+\b}
\rational{y2=\a*\x2+\b}
\rational{y3=\a*\x3+\b}
\text{f=\b=0?texmath(\a*x):texmath(\a*x+\b)}

#if defined TARGET_findaff1
\title{TITRE 1}
\integer{k=randint(1..4)}
\text{lstrep=constante,linéaire, affine non linéaire et non constante, non affine}
\rational{b=\k=2?0}
\rational{a=\k=1?0}
\text{f=\b=0?texmath(\a*x):texmath(\a*x+\b)}
\text{f=\a=0?texmath(\b)}

\integer{c=randint(-9..9)}
\text{nonaff=\a*x^2+\b*x+\c,sqrt(\a*x^2+\b),\c / (\a*x+\b)}
\if{\k=4}
   {
  \text{f=randomitem(\nonaff)}
  \text{f=texmath(\f)}
   }
\statement{
  On considère une fonction affine d'expression algébrique
<div class="wimscenter"> \(f(x)=\f) </div>
  Quelle est sa nature&nbsp;?
<div class="wimscenter">\embed{reply1}</div>
}
\answer{f}{\k;\lstrep}{type=radio}
#endif
#if (defined TARGET_findaff5  || defined TARGET_findaff4  || defined TARGET_findaff2  )
#if defined TARGET_findaff2
\title{TITRE 2}
\integer{nbfnct=2}

\text{blist=wims(makelist x/2,-x/2 for x=1 to 6)}
\text{alist=wims(makelist x/2,-x/2 for x=1 to 6)}
\text{blist=shuffle(\blist)}
\text{alist=shuffle(\alist)}
\text{lstcolor=red,blue,green,orange,magenta,cyan}
\text{couleur=rouge,bleu,vert,orange,magenta,cyan}
\text{ind=shuffle(6)}
\text{dessindte=
plot \lstcolor[\ind[1]],\blist[1]
plot \lstcolor[\ind[2]],\blist[2]
plot \lstcolor[\ind[3]],\alist[3]*x+\blist[3]
plot \lstcolor[\ind[4]],\alist[4]*x+\blist[4]
plot \lstcolor[\ind[5]],\alist[5]*x
plot \lstcolor[\ind[6]],\alist[6]*x
}
%%% cadre générique %%%
\text{gridcolor=lightblue}
\text{cadre=
xrange -3,3
yrange -3.5,3.5
gridfill 0,0,5,5,\gridcolor
linewidth 3
vline 1,0,\gridcolor
vline 2,0,\gridcolor
vline 3,0,\gridcolor
vline -1,0,\gridcolor
vline -2,0,\gridcolor
vline -3,0,\gridcolor
hline 0,1,\gridcolor
hline 0,2,\gridcolor
hline 0,3,\gridcolor
hline 0,-1,\gridcolor
hline 0,-2,\gridcolor
hline 0,-3,\gridcolor
linewidth 1
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
linewidth 2
\dessindte
}
%%%%fin du cadre générique %%%
\text{goodari=\couleur[\ind[3]],\couleur[\ind[4]]}
\text{goodgeo=\couleur[\ind[5]],\couleur[\ind[6]]}
\text{goodaut=\couleur[\ind[1]],\couleur[\ind[2]]}
\text{list=\goodari,\goodgeo,\goodaut}
\text{textaff=affines non linéaires non constantes}
\text{textnonaff=constantes}

\statement{
<div class="wimscenter">\draw{400,400}{\cadre}</div>
 On a tracé les représentations graphiques de 6 fonctions.
  Classer ces fonctions selon leur nature.

<ul><li>fonctions \textaff&nbsp;:
\embed{r1,\size}</li>
<li>fonctions linéaires&nbsp;:
\embed{r2,\size}</li>
<li>fonctions \textnonaff&nbsp;:
\embed{r3,\size}</li>
</ul>
}
#else
# if defined TARGET_findaff5
\title{TITRE 5}
\integer{nbfnct=3}
# endif
# if defined TARGET_findaff4
\title{TITRE 4}
\integer{nbfnct=2}
# endif
\integer{nonlin=1}
\text{size=220x60x5}
\language{fr}
\range{-5..5}
\author{Régine Mangeard}
\email{regine@mangeard.fr}
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
\matrix{donnees=\bx+\sqrt{\a},\a x-\c,\c x+\a,x-\a,\e+\a x,-\e+\b x,\b x-\frac{\f}{\c},\frac{\sqrt{\a}}{\c} +\c x,\c x+\frac{\a}{\c},\c(\b+\frac{x}{\c})
\sqrt{\a}x,\b x,\e x,\frac{\f}{\c}x,\frac{\sqrt{\a}}{\c}x
\cos(\a x),\frac{\c}{x},\b x^2+\a x+\c,\sqrt{\a}x^2+\e x+\c, \frac{\f}{\g}x^2+\frac{\a}{\b} x+\c,\b x^2,(x+\c)(x+\a),(x+\e)^2,(x-\c)^2}
\matrix{sortie=}
\for{i=1 to 3}{
\text{tmp=row(\i,\donnees)}
\text{tmp=shuffle(\tmp)}
\text{line=}
\for{j=1 to \nbfnct}{
\text{tmp1=item(\j,\tmp)}
\text{tmp1=\(f(x)= \tmp1)}
\text{line=wims(append item \tmp1 to \line)}
}
\text{sortie=wims(append line \line to \sortie)}
}
\text{goodari=row(1,\sortie)}
\text{goodgeo=row(2,\sortie)}
\text{goodaut=row(3,\sortie)}
\text{list=\goodari,\goodgeo,\goodaut}
\text{textaff=affine non linéaire}
\text{textnonaff=non affine}
\statement{
  Classer les fonctions suivantes suivant leur nature.
<ul>
<li>fonctions \textaff&nbsp;:
\embed{r1,\size}</li>
<li>fonctions linéaires&nbsp;:
\embed{r2,\size}</li>
<li>fonctions \textnonaff&nbsp;:
\embed{r3,\size}</li>
</ul>
}
#endif
\reply{ fonctions affines non linéaires }{\repari;\list}{type=clickfill}
\reply{ fonctions linéaires }{\repgeo;\list}{type=clickfill}
\reply{ fonctions non affines }{\repaut;\list}{type=clickfill}
\text{tmpari=\repari,\goodari}
\text{tmpari=wims(listuniq \tmpari)}
\text{repari=wims(listuniq \repari)}
\integer{ari1=items(\tmpari)}
\integer{ari2=items(\repari)}
\condition{ fonctions affines non linéaires }{\ari1=\nbfnct and \ari2=\nbfnct}
\text{tmpgeo=\repgeo,\goodgeo}
\text{tmpgeo=wims(listuniq \tmpgeo)}
\integer{geo1=items(\tmpgeo)}
\text{repgeo=wims(listuniq \repgeo)}
\integer{geo2=items(\repgeo)}
\integer{geo=items(\goodgeo)}
\condition{ fonctions linéaires }{\geo1=\nbfnct and \geo2=\nbfnct}
\text{tmpaut=\repaut,\goodaut}
\text{tmpaut=wims(listuniq \tmpaut)}
\integer{aut1=items(\tmpaut)}
\text{repaut=wims(listuniq \repaut)}
\integer{aut2=items(\repaut)}
\condition{ fonctions non affines }{\aut1=\nbfnct and \aut2=\nbfnct}
#endif
#if defined TARGET_findaff3
\title{TITRE 3}
\text{g=\a*x}
\text{h=\b}
\statement{
  On considère une fonction affine d'expression algébrique
<div class="wimscenter"> \(f(x)=\f) </div>

  Décomposer cette fonction affine en la somme d'une fonction \(g) linéaire et d'une fonction \(h) constante&nbsp;:

<div class="wimscenter">\(f(x)=g(x)+h(x))</div>
<ul>
<li>\(g(x))=\embed{reply1,5}</li>
<li>\(h(x))=\embed{reply2,5}</li>
</ul>
}
\answer{g(x)}{\g}{type=algexp}
\answer{h(x)}{\h}{type=algexp}

#endif
