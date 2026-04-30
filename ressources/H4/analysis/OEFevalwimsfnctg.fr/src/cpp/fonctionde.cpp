target=fonctionde1 fonctionde2 fonctionde3 fonctionde4 fonctionde5

\author{Régine, Mangeard}
#define TITRE Être fonction de
#if defined TARGET_fonctionde1
# define NUM 1
#endif
#if defined TARGET_fonctionde3
# define NUM 3
#endif
#if defined TARGET_fonctionde4
# define NUM 4
#endif
#if defined TARGET_fonctionde2
# define NUM 2
# endif
#if defined TARGET_fonctionde5
# define NUM 5
#endif
\title{TITRE NUM}
#if defined TARGET_fonctionde1
%%%% couleur des grilles
\text{gridcolor=lightblue}

%%%%# cadre générique %%%%#
\text{cadre=
xrange -2,2
yrange -2.5,2.5
gridfill 0,0,5,5,\gridcolor
linewidth 3
vline 1,0,\gridcolor
vline 2,0,\gridcolor
vline -1,0,\gridcolor
vline -2,0,\gridcolor
hline 0,1,\gridcolor
hline 0,2,\gridcolor
hline 0,-1,\gridcolor
hline 0,-2,\gridcolor
linewidth 1
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
}
%%%% fin du cadre générique %%%%
%%%% tracé d'une fonction affine par morceau
\text{xl=wims(makelist x/10 for x=-20 to 20)}
\text{xl=shuffle(\xl)}
\text{yl=\xl}
\text{xl=item(1..6,\xl)}
\text{xl=wims(sort numeric item \xl)}
\text{gr1=\cadre
polyline red,\xl[1],\yl[1],\xl[2],\yl[2],\xl[3],\yl[3],\xl[4],\yl[4],\xl[5],\yl[5],\xl[6],\yl[6]
}
%%%% tracé d'une mauvaise fonction affine
\text{ind=shuffle(6)}
\rational{x1=\xl[\ind[1]]}
\rational{x2=\xl[\ind[2]]}
\text{xl=wims(replace item number \ind[1] by \x2 in \xl)}
\text{xl=wims(replace item number \ind[2] by \x1 in \xl)}
\text{gr2=\cadre
polyline red,\xl[1],\yl[1],\xl[2],\yl[2],\xl[3],\yl[3],\xl[4],\yl[4],\xl[5],\yl[5],\xl[6],\yl[6]
}
%%%% tracé d'une fonction constante
\rational{a=randint(-20..20)/10}
\text{gr3=\cadre
segment -2,\a,2,\a,red
}
\text{gr4=\cadre
segment \a,-2.5,\a,2.5,red
}

%%%% tracé d'une cubique
\rational{a=randint(-20..20)/10}
\rational{b=randint(-20..20)/10}
\text{gr5=\cadre
plot red,x*(x-\a)*(x-\b)
}
%%%% tracé d'une courbe fermée
\rational{a=randint(5..20)/10}
\rational{b=randint(5..20)/10}
\text{gr6=\cadre
ellipse 0,0,\a,\b,red
}
\text{data=1,\gr1
2,\gr2
1,\gr3
2,\gr4
1,\gr5
2,\gr6
}
\text{ind=shuffle(6)}

\text{grep=}
%%% choix de graph1
\if{\ind[1]=1}
 {\text{graph1=\gr1}
  \text{grep=wims(append item 1 to \grep)}
 }
\if{\ind[1]=2}
 {\text{graph1=\gr2}
 }
\if{\ind[1]=3}
 {\text{graph1=\gr3}
  \text{grep=wims(append item 1 to \grep)}
 }
\if{\ind[1]=4}
 {\text{graph1=\gr4}
 }
\if{\ind[1]=5}
 {\text{graph1=\gr5}
  \text{grep=wims(append item 1 to \grep)}
 }
\if{\ind[1]=6}
 {\text{graph1=\gr6}
 }

%%% choix de graph2
\if{\ind[2]=1}
 {\text{graph2=\gr1}
  \text{grep=wims(append item 2 to \grep)}
 }
\if{\ind[2]=2}
 {\text{graph2=\gr2}
 }
\if{\ind[2]=3}
 {\text{graph2=\gr3}
  \text{grep=wims(append item 2 to \grep)}
 }
\if{\ind[2]=4}
 {\text{graph2=\gr4}
 }
\if{\ind[2]=5}
 {\text{graph2=\gr5}
  \text{grep=wims(append item 2 to \grep)}
 }
\if{\ind[2]=6}
 {\text{graph2=\gr6}
 }

%%% choix de graph3
\if{\ind[3]=1}
 {\text{graph3=\gr1}
  \text{grep=wims(append item 3 to \grep)}
 }
\if{\ind[3]=2}
 {\text{graph3=\gr2}
 }
\if{\ind[3]=3}
 {\text{graph3=\gr3}
  \text{grep=wims(append item 3 to \grep)}
 }
\if{\ind[3]=4}
 {\text{graph3=\gr4}
 }
\if{\ind[3]=5}
 {\text{graph3=\gr5}
  \text{grep=wims(append item 3 to \grep)}
 }
\if{\ind[3]=6}
 {\text{graph3=\gr6}
 }
%%% choix de graph2
\if{\ind[4]=1}
 {\text{graph4=\gr1}
  \text{grep=wims(append item 4 to \grep)}
 }
\if{\ind[4]=2}
 {\text{graph4=\gr2}
 }
\if{\ind[4]=3}
 {\text{graph4=\gr3}
  \text{grep=wims(append item 4 to \grep)}
 }
\if{\ind[4]=4}
 {\text{graph4=\gr4}
 }
\if{\ind[4]=5}
 {\text{graph4=\gr5}
  \text{grep=wims(append item 4 to \grep)}
 }
\if{\ind[4]=6}
 {\text{graph4=\gr6}
 }

\statement{
  Lesquelles de ces courbes peuvent être la représentation graphique
  d'une fonction ?
<ul class="inline">
    <li>\embed{reply 1,1} : \draw{200,200}{\graph1}</li>
    <li>\embed{reply 1,2} : \draw{200,200}{\graph2}</li>
    <li>\embed{reply 1,3} : \draw{200,200}{\graph3}</li>
    <li>\embed{reply 1,4} : \draw{200,200}{\graph4}</li>
</ul>
}
\answer{}{\grep;1,2,3,4}{type=checkbox}
#endif

#if defined TARGET_fonctionde2
\text{tvar=a,b,l,k,s,t,u,v}
\integer{k=randint(1..4)}
\text{tx=\tvar[2*\k-1]}
\text{ty=\tvar[2*\k]}
\integer{a=randint(2..9)*randint(1,-1)}
\integer{b=randint(2..9)*randint(1,-1)}
\integer{c=randint(2..9)*randint(1,-1)}
\text{data=\a*\tx+\b*\ty=\c,(\c-\b*\ty)/\a,(\c-\a*\tx)/ \b
\a*\tx=\c*(\b-\ty),\c*(\b-\ty)/ \a,\b-\a*\tx /\c
(\a*\tx+\b*\ty)/\c=0,-\b*\ty/\a,-\a*\tx / \b
}
\text{cedata=randomrow(\data)}
\text{quest=\(texmath(\cedata[1]))}
\text{rep1=\cedata[2]}
\text{rep2=\cedata[3]}
\statement{
  On considère la formule liant \(\tx) et \(\ty) :
<div class="wimscenter">\quest</div>
<ol>
<li>Exprimer \(\tx) en fonction de \(\ty) :
\(\tx=)\embed{reply1,7}</li>
<li>Exprimer \(\ty) en fonction de \(\tx) :
\(\ty=)\embed{reply2,7}</li>
</ol>}
\answer{\tx}{\rep1}{type=formal}
\answer{\ty}{\rep2}{type=formal}
#endif
#if defined TARGET_fonctionde3
\integer{k=randint(1..3)}
\if{\k=1}{
  \text{eq=\(l=l_0(1+a(t-t_0)))}
  \text{exp=\(l_0) est la longueur d'un objet à la température \(t_0), \(l) est la longueur du même objet à la température \(t), \(a) est le coefficient de dilatation. Exprimer \(t) en fonction de \(l,l_0,a) et \(t_0).}
  \function{rep=(l / l_0 - 1) / a + t_0}
  \text{consigne=Taper <span class="tt">l_0</span> pour \(l_0) et n'omettez pas l'opérateur <span class="tt">*</span> quand c'est nécessaire.}
  \text{val=t}
 }
\if{\k=2}{
  \text{eq=\(\frac{1}{R}=\frac{1}{R_1}+\frac{1}{R_2})}
  \text{exp=\(R_1) et \(R_2) sont des résistances électriques cablées en parallèle. \(R) est nommée la résistance équivalente. Exprimer \(R) en fonction de \(R_1) et \(R_2).}
  \function{rep=(R_1*R_2)/(R_1+R_2)}
  \text{val=R}
  \text{consigne=Taper <span class="tt">R_1</span> pour \(R_1) et n'omettez pas l'opérateur <span class="tt">*</span> quand c'est nécessaire.}
 }
\if{\k=3}{
  \text{eq=\(S=2\times L \times h+ 2 \times h \times l + L \times l)}
  \text{exp=\(S) est la surface extérieure d'une boite sans couvercle de longueur \(L), de largeur \(l) et de hauteur \(h).
    Exprimer \(h) en fonction de \(S,L) et \(l).}
  \function{rep=(S- L*l)/(2*(L+l))}
  \text{consigne=N'omettez pas l'opérateur <span class="tt">*</span> quand c'est nécessaire.}
  \text{val=h}
}
\statement{
  Soit \eq où \exp
<div class="wims_instruction">\consigne</div>
<div class="wimscenter"> \val= \embed{reply1}</div>
}
\answer{formule}{\rep}{type=algexp}
#endif
#if defined TARGET_fonctionde4
\integer{a=randint(2..9)}
\integer{b=randint(2..9)}
\integer{c=randint(2..9)}
\matrix{data=je double,*2
  je triple,*3
  j'ajoute \a,+\a
  je soustrais \b,-\b
  je divise par \c,/ \c
}
\text{ind=shuffle(5)}
\text{action=\data[\ind[1];1] puis \data[\ind[2];1], enfin \data[\ind[3];1]}
\text{rep=((x\data[\ind[1];2])\data[\ind[2];2])\data[\ind[3];2]}

\statement{Je choisis un nombre \(x) et je fais trois opérations:
<div class="wimscenter">\action</div>
  Donner le nombre \(N(x)) ainsi obtenu en fonction de \(x):
<div class="wimscenter">N(x) = \embed{reply1,7}</div>
}
\answer{nombre obtenu}{\rep}{type=formal}
#endif
#if defined TARGET_fonctionde5
\integer{k=randint(1,2)}
\integer{x0=0}
\integer{x1=\x0+randint(1..3)}
\integer{x2=\x1+randint(1..3)}
\integer{x3=\x2+randint(1..3)}
\integer{y0=randint(-3..3)}
\integer{y1=\y0+randint(2..5)}
\integer{y3=\y1+randint(2..5)}
\if{\k=1}
  {
  \rational{y2=randint(\y1*10+1..\y3*10-1)/10}
  }
  {
  \integer{y2=\y1-randint(0..5)}
  }
%%%%# cadre générique %%%%#
\integer{xmin=-10}
\integer{xmax=10}
\integer{ymin=-10}
\integer{ymax=10}
\text{cadre=
xrange \xmin,\xmax
yrange \ymin,\ymax
linewidth 1
  parallel \xmin,\ymin,\xmin,\ymax,0.2,0,100,\gridcolor
  parallel \xmin,\ymin,\xmax,\ymin,0,0.2,100,\gridcolor
linewidth 2
  parallel \xmin,\ymin,\xmin,\ymax,1,0,21,gray
  parallel \xmin,\ymin,\xmax,\ymin,0,1,21,gray
linewidth 2
arrow 0,\ymin,0,\ymax,10,black
arrow \xmin,0,\xmax,0,10,black
text black,-0.8,\ymax-1,medium,L
text black,\xmax-1,-0.8,medium,N
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
    linewidth 2
lines red,\x0,\y0,\x1,\y1,\x2,\y2,\x3,\y3
}

\statement{
  Voici la représentation graphique d'une grandeur \(L) en fonction d'une grandeur \(N).
<div class="wimscenter">\draw{400,400}{\cadre}</div>
  La grandeur \(N) peut-elle être fonction de la grandeur \(L)?
<div>
\embed{reply1}
</div>
}
\answer{}{\k;Oui,Non}{type=radio}
#endif
