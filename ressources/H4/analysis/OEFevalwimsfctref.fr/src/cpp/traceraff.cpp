target=traceraff1 traceraff2 traceraff3 traceraff4 traceraff5
#define TITRE Tracer de fonctions affines
#if defined TARGET_traceraff1
# define NUM 1
#endif
#if defined TARGET_traceraff2
# define NUM 2
#endif
#if defined TARGET_traceraff3
# define NUM 3
#endif
#if defined TARGET_traceraff4
# define NUM 4
#endif
#if defined TARGET_traceraff5
# define NUM 5
#endif
#include "lang_titles.inc"
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}

#if (defined TARGET_traceraff1 || defined TARGET_traceraff2 )
\text{dessindte=}
#if defined TARGET_traceraff1
\text{lstcolor=red,green,blue,orange}
\text{couleur=rouge,vert,bleu,orange}
\integer{nbfnct=4}
#endif
#if defined TARGET_traceraff2
\text{lstcolor=red,green,blue,orange,magenta,cyan}
\text{couleur=rouge,vert,bleu,orange,magenta,cyan}
\integer{nbfnct=6}
#endif
\text{alist=1,2,3,4,-1,-2,-3,-4,1/2,1/3,3/2,2/3,1/4,3/4,-1/2,-1/3,-3/2,-2/3,-1/4,-3/4}
\text{blist=wims(makelist x/2 for x=-7 to 7)}
\text{flist=}
\for{a in \alist}{
  \for{b in \blist}{
    \rational{b2=simplify(\b)}
    \text{f=\b2=0?\a*x:\a*x+\b2}
    \text{flist=wims(append item \f to \flist)}
  }
}
\text{flist=shuffle(\flist)}
\text{lstfoncs=}
\for{i=1 to \nbfnct}{
  \text{f=\(texmath(\flist[\i]))}
  \text{lstfoncs=wims(append item \f to \lstfoncs)}
  \text{dessindte=\dessindte
plot \lstcolor[\i],\flist[\i]
  }
}
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
\dessindte
}
\text{size=80x150x75}

\statement{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6 large-7">
  On a tracé \nbfnct représentations graphiques de fonctions affines.
  Associer expression algébrique et couleur de tracé de fonctions affines.
<div class="wimscenter">\embed{r1,\size}</div>
  </div>
  <div class="cell auto">
    \draw{400,400}{\cadre}
  </div>
</div>
}
\answer{Réponse}{\lstfoncs;\couleur}{type=correspond}
#endif
#if defined TARGET_traceraff3
\text{blist=wims(makelist x/2 for x=-4 to 4)}
\rational{b=randitem(\blist)}
\text{alist=wims(makelist x/2 for x=-4 to 4)}
\rational{a=randitem(\alist)}
\text{f=\a*x+\b}
\integer{j1=2*\b+6}
\integer{j2=2*(\a+\b)+6}
\integer{j3=2*(-\a+\b)+6}
\text{goodrep=A\j1,B\j2,C\j3}
\text{dessinpts=}
\for{i=-6 to 6}{
  \integer{j=\i+6}
  \text{dessinpts=\dessinpts
   point 0,\i/2,red
   text black,-0.3,\i/2,medium,A\j
   point 1,\i/2,red
   text black,0.7,\i/2,medium,B\j
   point -1,\i/2,red
   text black,-1.3,\i/2,medium,C\j
  }
}
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
linewidth 5
\dessinpts
}
\text{f=\b=0?texmath(\a*x):texmath(\f)}
\text{f=\a=0?texmath(\b)}
\statement{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6 large-7">
  On considère une fonction affine d'expression algébrique
<div class="wimscenter"> \(f(x)=\f) </div>
<label for="reply1">Nommer deux points appartenant à sa représentation graphique.</label>
<div class="wimscenter">\embed{r1,5}</div>
  </div>
  <div class="cell auto">
    \draw{400,400}{\cadre}
  </div>
</div>
}
\answer{points}{\rep}{type=fset}
\condition{points}{\rep[1] isitemof \goodrep and \rep[2] isitemof \goodrep}
#endif
#if (defined TARGET_traceraff4 || defined TARGET_traceraff5 )
# if defined TARGET_traceraff4
\text{blist=wims(makelist x/2 for x=-4 to 4)}
\rational{b=randitem(\blist)}
\text{alist=wims(makelist x for x=-3 to 3)}
\rational{a=randitem(\alist)}
\integer{p=1}
# endif
# if defined TARGET_traceraff5
\text{blist=wims(makelist x for x=-2 to 2)}
\rational{b=randitem(\blist)}
\text{alist=wims(makelist x for x=-2 to 2)}
\integer{p=randint(2,3,4)}
\rational{a=randitem(\alist)/\p}
# endif
\text{f=\b=0?texmath(\a*x):texmath(\a*x+\b)}
\text{f=\a=0?texmath(\b)}
%%%% cadre générique ###
\text{gridcolor=lightblue}
\text{cadre=
xrange -5,5
yrange -5,5
gridfill 0,0,5,5,\gridcolor
linewidth 3
vline 1,0,\gridcolor
vline 2,0,\gridcolor
vline 3,0,\gridcolor
vline 4,0,\gridcolor
vline 5,0,\gridcolor
vline -1,0,\gridcolor
vline -2,0,\gridcolor
vline -3,0,\gridcolor
vline -4,0,\gridcolor
vline -5,0,\gridcolor
hline 0,1,\gridcolor
hline 0,2,\gridcolor
hline 0,3,\gridcolor
hline 0,4,\gridcolor
hline 0,5,\gridcolor
hline 0,-1,\gridcolor
hline 0,-2,\gridcolor
hline 0,-3,\gridcolor
hline 0,-4,\gridcolor
hline 0,-5,\gridcolor
linewidth 1
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
}
\text{image=draw(400,400
\cadre)
}
\text{image2=draw(400,400
\cadre
fcircle 0,\b,10,green)
}
\text{image3=
\cadre
fcircle 0,\b,10,green
fcircle \p,\a*\p+\b,10,green
}
%%%% fin du cadre générique ##
\text{donnees=slib(draw/repere 400,400,0,-5,5,-5,5,1,1,black,grey)}

\text{tmp=row(1,\donnees)}
%%%%coordonnéées de l'origine du repère
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
%%%%échelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}
\integer{fx0=\Ox}
\integer{fy0=\Oy+\b*\ey}
\integer{fx0m=\fx0-\ex /3}
\integer{fy0m=\fy0-\ey /3}
\integer{fx0p=\fx0+\ex /3}
\integer{fy0p=\fy0+\ey /3}

\integer{fx1=\Ox+\p*\ex}
\integer{fy1=\Oy+(\a*\p+\b)*\ey}
\integer{fx1m=\fx1-\ex /3}
\integer{fy1m=\fy1-\ey /3}
\integer{fx1p=\fx1+\ex /3}
\integer{fy1p=\fy1+\ey /3}

\steps{r1
r2}
\statement{
On considère une fonction affine d'expression algébrique
<div class="wimscenter"> \(f(x)=\f) </div>
\if{\step=1}{
Cliquer au point d'abscisse \(x_0=0) appartenant à sa représentation graphique.
<div class="wimscenter">
\embed{reply1}
</div>
}{
  Cliquer maintenant au point d'abscisse \(x_1=\p)
<div class="wimscenter">
\embed{reply2}
</div>
}
}
\answer{A(x0)}{\image;rectangle,\fx0m,\fy0m,\fx0p,\fy0p}{type=coord}
\answer{B(x1)}{\image2;rectangle,\fx1m,\fy1m,\fx1p,\fy1p}{type=coord}
\solution{\draw{400,400}{\image3}}
#endif
