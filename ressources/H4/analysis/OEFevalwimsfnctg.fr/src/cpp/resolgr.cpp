target=resolgr1 resolgr2 resolgr3 resolgr4 resolgr5
\author{Régine, Mangeard}
\email{regine@mangeard}
\format{html}

#define TITRE Résolution graphique
#if defined TARGET_resolgr1
# define NUM 1
#endif
#if defined TARGET_resolgr3
# define NUM 3
#endif
#if defined TARGET_resolgr4
# define NUM 4
#endif
#if defined TARGET_resolgr2
# define NUM 2
# endif
#if defined TARGET_resolgr5
# define NUM 5
#endif
\title{TITRE NUM}
%%%% couleur des grilles
\text{gridcolor=lightblue}
\integer{xmin=-10}
\integer{xmax=10}
\integer{ymin=-10}
\integer{ymax=10}

\text{expcomp=On admet que les représentations graphiques ne se coupent pas en dehors du cadre affiché.
}
#if (defined TARGET_resolgr1 || defined TARGET_resolgr3 || defined TARGET_resolgr2 || defined TARGET_resolgr5 )

# if (defined TARGET_resolgr1 || defined TARGET_resolgr3 )
\text{expcomp=}
#  if defined TARGET_resolgr1
\text{typeeq=l'équation}
#   endif
%%%% Choix de 4 points dans le cadre
\integer{x0=random(-4..-2)}
\integer{x1=\x0+random(1..3)}
\integer{x2=\x1+random(1..3)}
\integer{x3=\x2+random(1..3)}
\integer{k=random(1,2)}
\if{\k=1}{
  \integer{y0=random(-5..0)}
  \integer{y1=\y0}
  \integer{y2=\y0}
  \integer{y3=random(3..6)}
  \text{rep0=\x0,\x1,\x2}
  \text{rep1=\x3}
}{
\integer{y0=random(-6..-3)}
\integer{y1=random(0..5)}
\integer{y2=\y1}
\integer{y3=\y1}
\text{rep0=\x0}
\text{rep1=\x1,\x2,\x3}
}
\integer{k2=random(1,2)}
\text{val=\k2=1?=\y0:=\y3}
\text{goodrep=\k2=1?\rep0:\rep1}

%%%% Polynome d'interpollation
\text{f0=\y0*(x-(\x1))*(x-(\x2))*(x-(\x3))/((\x0-(\x1))*(\x0-(\x2))*(\x0-(\x3)))}
\text{f1=\y1*(x-(\x0))*(x-(\x2))*(x-(\x3))/((\x1-(\x0))*(\x1-(\x2))*(\x1-(\x3)))}
\text{f2=\y2*(x-(\x1))*(x-(\x0))*(x-(\x3))/((\x2-(\x1))*(\x2-(\x0))*(\x2-(\x3)))}
\text{f3=\y3*(x-(\x1))*(x-(\x2))*(x-(\x0))/((\x3-(\x1))*(\x3-(\x2))*(\x3-(\x0)))}
\text{f= \f0 + (\f1) +(\f2)+ (\f3)}

\text{courbef=linewidth 2
    plot blue,\f
}
\text{courbeg=}
\text{autrecourbe=}

# endif

# if (defined TARGET_resolgr2 || defined TARGET_resolgr5 )
#   if defined TARGET_resolgr2

\text{typeeq=l'équation}
#   endif
%%%% Choix de 4 points dans le cadre
\integer{orient=random(1,-1)}

\integer{x0=\xmin}
\integer{x1=\x0+random(2..5)}
\integer{x2=\x1+random(3..5)}
%%%% x3 symétrique de x0 par rapport à l'axe de f donc y3=y0
\integer{x3=\x2+\x1-\x0}
\integer{x4=\xmax}
\integer{y0=random(2..5)}
\integer{z0=random(7..\ymax)}
\integer{offset=random(0..5)}
\integer{orientx=random(1,-1)}

\integer{x0=\orientx*(\x0)}
\integer{x1=\orientx*(\x1)}
\integer{x2=\orientx*(\x2)}
\integer{x3=\orientx*(\x3)}
\integer{x4=\orientx*(\x4)}

%%%% préparation de la courbe g
%%%% passe par x0,y0 et s'annule en x1, x2
\rational{c1=(\y0)/(((\x1)-(\x0))*((\x2)-(\x0)))}
\text{g= \c1*(t-(\x1))*(t-(\x2))-(\offset)}
\text{g=\orient*(\g)}
\rational{g0=evalue(\g,t=\x0)}
\text{courbeg=
trange \x0,\x4
 plot red,t,\g
}
\text{val= =g(x)}
\text{autrecourbe=, et d'une fonction <span style="color:red">\(g)</span>}
\text{goodrep=\x1,\x2,\x3}
%%%% préparation de la courbe f
%%%% première parabole
%%%% passe par x0,z0 et s'annule en x1, x2
\rational{c1=(\z0)/(((\x1)-(\x0))*((\x2)-(\x0)))}
\text{f1= \c1*(t-(\x1))*(t-(\x2))-\offset}
\text{f1=\orient*(\f1)}
\rational{f0=evalue(\f1,t=\x0)}
%%%% deuxième parabole
%%%% passe par x3,y3=y0 etx4,y4=y0 s'annule en x2
\rational{c2=(\y0)/(((\x3)-(\x2))*((\x4)-(\x2)))}
\text{f2= -(\c2)*(t-(\x3))*(t-(\x4))+(\y0)-(\offset)}
\text{f2=\orient*(\f2)}
\rational{y3=evalue(\f2,t=\x3)}

\text{courbef=
trange \x0,\x2
 plot blue,t,\f1
trange \x2,\x4
 plot blue,t,\f2
}
#   endif

%%%%# cadre générique %%%%#
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
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
    linewidth 2
\courbef
\courbeg
}
%%%% fin du cadre générique %%%%

#  if (defined TARGET_resolgr3 || defined TARGET_resolgr5 )
%%%% préparation de la question
%%%% choix de la question
\integer{sensineq=random(1..2)}
\integer{strictineq=random(0..1)}
\text{sgt= > }
\text{sge=\ge }
\text{slt= < }
\text{sle=\le }
\text{symb=\slt,\sgt,\sle,\sge}
\integer{j=\sensineq+2*\strictineq}
\text{quest= \(f(x)) \symb[\j] \(g(x))}

%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%%%
\text{tx1=\(\x1)}
\text{tx2=\(\x2)}
\text{tx3=\(\x3)}
\text{tx4=\(\x4)}
\text{tx5=\(\x0)}
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}

\integer{t0=random(-20..-11)}
\integer{t4=random(11..20)}
\text{permut=shuffle(\x1,\x2,\x3,\t4,\t0)}

\text{clicList=
\crocg,\ptvirg,\crocd,\union,\inter,\infg,\infd,\empt,\bracg,\bracd,\permut[1],\permut[2],\permut[3],\permut[4],\permut[5]
}
%%%% taille des symboles et des champs à remplir par clic LxHxnb %%%%
\text{size=60x40x12}

\text{crochg=\strictineq=0?\crocd:\crocg}
\text{crochd=\strictineq=0?\crocg:\crocd}

#   if defined TARGET_resolgr3
\text{typeeq=l'inéquation}
\text{val=\k2=1?\symb[\j] \y0:\symb[\j] \y3}
%%%% préparation de la réponse
   \if{\sensineq=1}{
     \if{\k=1}{
       \text{grep=\k2=1?\crocd,\infg,\ptvirg,\x0,\crochd,\union,\crochg,\x1,\ptvirg,\x2,\crochd:\crocd,\infg,\ptvirg,\x3,\crochd}
      }{
       \text{grep=\k2=2?\crocd,\infg,\ptvirg,\x1,\crochd,\union,\crochg,\x2,\ptvirg,\x3,\crochd:\crocd,\infg,\ptvirg,\x0,\crochd}
      }
    }{
     \if{\k=1}{
       \text{grep=\k2=1?\crochg,\x0,\ptvirg,\x1,\crochd,\union,\crochg,\x2,\ptvirg,\infd,\crocg:\crochg,\x3,\ptvirg,\infd,\crocg}
      }{
       \text{grep=\k2=2?\crochg,\x1,\ptvirg,\x2,\crochd,\union,\crochg,\x3,\ptvirg,\infd,\crocg:\crochg,\x0,\ptvirg,\infd,\crocg}
      }
    }
#   endif
#   if defined TARGET_resolgr5
\text{typeeq=l'inéquation}
\text{val=\symb[\j] g(x)}

%%%% préparation de la réponse
\if{(\sensineq=1 and \orient=1) or (\sensineq=2 and \orient=-1)}{
  \if{\orientx=1}{
    \text{grep=\crochg,\x1,\ptvirg,\x2,\crochd,\union,\crochg,\x3,\ptvirg,\infd,\crocg}
  }{
    \text{grep=\crocd,\infg,\ptvirg,\x3,\crochd,\union,\crochg,\x2,\ptvirg,\x1,\crochd}
  }
}{
  \if{\orientx=1}{
    \text{grep=\crocd,\infg,\ptvirg,\x1,\crochd,\union,\crochg,\x2,\ptvirg,\x3,\crochd}
   }{
    \text{grep=\crochg,\x3,\ptvirg,\x2,\crochd,\union,\crochg,\x1,\ptvirg,\infd,\crocg}
  }
}
#   endif
# endif
%%%% enoncé de l'exo %%%%
\statement{
<div class="wims_columns">
<div class="medium_size">\draw{400,400}{\cadre}</div>
<div class="medium_size">
  Dans le plan muni d'un repère orthonormé \((O,i,j)\),
  on a tracé la courbe représentative d'une fonction
<span style="color:blue">\(f)</span> \autrecourbe.
<p>
\expcomp
</p><p>
  Résoudre graphiquement \typeeq
</p>
<div class="wimscenter"> \(f(x) \val)</div>
#if (defined TARGET_resolgr1 || defined TARGET_resolgr2 )
  Votre réponse : S = \embed{reply 1,3}.
<div class="wims_instruction">
  S'il y a plusieurs solutions, il faut les séparer par une virgule.
</div>
</div></div>
}
%%%% soumission de réponse %%%%
\answer{solution}{\goodrep}{type=set}

# else
  Votre réponse : S = \embed{reply1,\size}.
</div></div>
}
%%%% soumission de réponse %%%%
\answer{}{\grep;\clicList}{type=clickfill}

# endif
#endif

#if defined TARGET_resolgr4
%%%% Choix de 4 points dans le cadre
\integer{orient=random(1,-1)}

\integer{x0=\xmin}
\integer{x1=\x0+random(2..7)}
\integer{x2=\x1+random(2..4)}
\integer{x3=\x2+random(1..\xmax-1-\x2)}
\integer{y1=random(-5..5)}
\integer{y2=\y1-random(1..\y1-\ymin)}
\integer{y3=\y2+random(1..\ymax-\y2)}
\integer{offset=random(0..5)}
\integer{orientx=random(1,-1)}

\integer{x0=\orientx*(\x0)}
\integer{x1=\orientx*(\x1)}
\integer{x2=\orientx*(\x2)}
\integer{x3=\orientx*(\x3)}

%%%% choix de la question
\integer{sensineq=random(1..2)}
\integer{strictineq=random(0..1)}
%%%% choix de la question
\integer{sensineq=random(1..2)}
\integer{strictineq=random(0..1)}
\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le )}
%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%%%
\text{tx1=\(\x1)}
\text{tx2=\(\x2)}
\text{tx3=\(\x3)}
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}
\integer{t0=random(-20..-11)}
\integer{t4=random(11..20)}

\text{permut=shuffle(\x1,\x2,\x3,\t0,\t4)}

\text{clicList=
\crocg,\ptvirg,\crocd,\union,\inter,\infg,\infd,\empt,\bracg,\bracd,\permut[1],\permut[2],\permut[3],\permut[4],\permut[5]
}
%%%% taille des symboles et des champs à remplir par clic LxHxnb %%%%
\text{size=60x40x12}
\text{crochg=\strictineq=0?\crocd:\crocg}
\text{crochd=\strictineq=0?\crocg:\crocd}

%%%% préparation de la courbe f
%%%% parabole par interpolation lagrange
%%%% passe par x1,y1 , x2,y2 et x3,y3
rational{f1=(\z0)/(((\x1)-(\x0))*((\x2)-(\x0)))}
\text{f1= \y1*(t-(\x2))*(t-(\x3))/(((\x1)-(\x2))*((\x1)-(\x3)))}
\text{f2= \y2*(t-(\x1))*(t-(\x3))/(((\x2)-(\x1))*((\x2)-(\x3)))}
\text{f3= \y3*(t-(\x2))*(t-(\x1))/(((\x3)-(\x2))*((\x3)-(\x1)))}
\text{f= (\f1)+(\f2)+(\f3)}
\text{f=\orient*(\f)}

%%%% Préparation de la droite
%%%% passe par x1,y1 et x3,y3
\rational{c=((\y3)-(\y1))/((\x3)-(\x1))}
\text{g= (\c)*(t-(\x3))+(\y3)}
\text{g=\orient*(\g)}

\text{cadrefct=
trange \xmin,\xmax
 plot green,t,\g
trange \xmin,\xmax
 plot red,t,\f
}

%%%% cadre générique %%%%
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
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
    linewidth 2
\cadrefct
}
%%%% fin du cadre générique %%%%


%%%% préparation de la question
\text{symb=\slt,\sgt,\sle,\sge}
\text{symbtex=\lt,\gt,\le,\ge}
\integer{j=\sensineq+2*\strictineq}
\text{quest= \(f(x) \symbtex[\j] g(x)\)}

%%%% préparation de la réponse
\if{(\sensineq=1 and \orient=1) or (\sensineq=2 and \orient=-1)}{
  \if{\orientx=1}{
    \text{grep=\crochg,\x1,\ptvirg,\x3,\crochd}
  }{
    \text{grep=\crochg,\x3,\ptvirg,\x1,\crochd}
  }
}{
  \if{\orientx=1}{
    \text{grep=\crocd,\infg,\ptvirg,\x1,\crochd,\union,\crochg,\x3,\ptvirg,\infd,\crocg}
  }{
    \text{grep=\crocd,\infg,\ptvirg,\x3,\crochd,\union,\crochg,\x1,\ptvirg,\infd,\crocg}
  }
}

%%%%%%%%%%%% enoncé de l'exo %%%%%%%%%%%%
\statement{
<div class="wims_columns">
<div class="medium_size">\draw{400,400}{\cadre}</div>
<div class="medium_size">
  Dans le plan muni d'un repère orthonormé \((O,i,j)\),
  on a tracé la courbe représentative d'une fonction
<span style="color:red">\(f)</span> et
  d'une fonction affine <span style="color:green">\(g)</span>.
<p>On admet que les représentations graphiques ne se coupent
  pas en dehors du cadre affiché.</p>
<p>Résoudre graphiquement l'inéquation suivante :</p>
<div class="wimscenter">\quest</div>
  Votre réponse : S = \embed{reply1,\size}
</div>
</div>
}
%%%%%%%% soumission de réponse %%%%%%%%
\answer{}{\grep;\clicList}{type=clickfill}
#endif
