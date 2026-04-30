target=vocabaff1 vocabaff2 vocabaff3 vocabaff4 vocabaff5
#if defined TARGET_vocabaff1
# define NUM 1
#endif
#if defined TARGET_vocabaff2
# define NUM 2
#endif
#if defined TARGET_vocabaff3
# define NUM 3
#endif
#if defined TARGET_vocabaff4
# define NUM 4
#endif
#if defined TARGET_vocabaff5
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

#if defined TARGET_vocabaff1
\statement{
  On considère une fonction affine d'expression algébrique:
<div class="wimscenter"> \(f(x)=\f) </div>
<ul>
<li>Que vaut son coefficent directeur: <label for="reply1">\(a=)</label>\embed{reply1,3}</li>
<li>Que vaut son ordonnée à l'origine: <label for="reply2">\(b=)</label>\embed{reply2,3}</li>
</ul>
}
\answer{a}{\a}{type=numeric}
\answer{b}{\b}{type=numeric}
#endif
#if defined TARGET_vocabaff2
\text{lstfct=constante,linéaire,affine non linéaire et non constante}
\integer{i=randint(1..3)}
\text{typefct=\lstfct[\i]}
\text{lstrep=parallèle à l'axe des abscisses, passant par l'origine, ne passant pas par l'origine et non parallèle aux axes, parallèle à l'axe des ordonnéees}
\statement{
  La représentation graphique d'une fonction <span style="color:red">\typefct</span>
  est une droite:<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>
}
\answer{}{\i;\lstrep}{type=radio}
#endif
#if defined TARGET_vocabaff3
%%%% couleur des grilles
\real{b=randint(-30..30)/10}
\rational{a2=simplify(\a+randint(1..3)*randint(1,-1))}
\real{b2=\b+random(0.5,1,-0.5,-1)}
\integer{k=randint(1..3)}
\if{\k=1}
 {
 \rational{b2=\b}
 }
\if{\k=2}
 {
 \rational{a2=\a}
 }
\text{g=\a2*x+\b2}
\text{f=\a*x+\b}

%%%% cadre générique ###
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
plot red,\f
plot green,\g
}
\text{lstrep=l'ordonnée à l'origine mais pas le coefficient directeur,le coefficient directeur mais pas l'ordonnée à l'origine, ni le coefficient directeur ni l'ordonnée à l'origine, le coefficient directeur et l'ordonnée à l'origine}
%%%% fin du cadre générique ##
\statement{
<div class="float_left spacer">\draw{400,400}{\cadre}</div>
  On considère deux fonctions affines <span style="color:red">\(f)</span> et
<span style="color:green">\(g)</span>
  dont on a tracé les représentations graphiques ci-contre.
<p>
  Que semblent-elles avoir en commun&nbsp;?
</p>
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>

}
\answer{}{\k;\lstrep}{type=radio}
#endif
#if defined TARGET_vocabaff4
\text{data=même ordonnée à l'origine, se coupent sur l'axe des ordonnées, se coupent sur l'axe des abscisses,sont parallèles
  même coefficient directeur, sont parallèles,se coupent sur l'axe des ordonnées, se coupent sur l'axe des abscisses
}
\text{cedata=randomrow(\data)}
\integer{i=randint(2..4)}
\text{quest=\cedata[1] \cedata[\i]}
\integer{rep=\i=2?1:2}
\statement{
  La phrase suivante est elle juste&nbsp;?
<div class="wimscenter"> Les représentations graphiques de deux fonctions
  affines ayant \quest </div>
\embed{reply1}
}
\answer{}{\rep;Vrai, Faux}{type=radio}
#endif
#if defined TARGET_vocabaff5
\integer{i=randint(1..3)}
\rational{a=\i=3?0}
\integer{rep=\a>0?1:2}
\integer{rep=\a=0?3}
\text{f=\a=0?texmath(\b):texmath(\a*x+\b)}
\statement{
  On considère une fonction affine d'expression algébrique
<div class="wimscenter"> \(f(x)=\f) </div>
<p>
  Déterminer son sens de variation.
</p>
\embed{reply1}
}
\answer{sens}{\rep;Strictement croissante,Strictement décroissante,Constante}{type=radio}
#endif
