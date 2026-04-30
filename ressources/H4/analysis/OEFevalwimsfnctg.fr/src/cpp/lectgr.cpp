target=lectgr1 lectgr2 lectgr3 lectgr4 lectgr5
\author{Régine, Mangeard}
\email{regine@mangeard}
\format{html}
#define TITRE Lecture graphique d'image/antécédent
#if defined TARGET_lectgr1
# define NUM 1
#endif
#if defined TARGET_lectgr3
# define NUM 3
#endif
#if defined TARGET_lectgr4
# define NUM 4
#endif
#if defined TARGET_lectgr2
# define NUM 2
# endif
#if defined TARGET_lectgr5
# define NUM 5
#endif
\title{TITRE NUM}
\text{comp=}
%%%% couleur des grilles
\text{gridcolor=lightblue}

#if defined TARGET_lectgr1
\text{typequest=l'image}
\text{verb=est}
\text{typerep=numeric}
%%%% Choix de 4 points dans le cadre
\integer{x3=random(4..6)}
\integer{y3=randint(-4..3)}
\rational{a=(\y3+5)*(\x3^2+1)}
\text{g2=-5+\a/(x^2+1)}
\text{g1=3-10/(x^2+1)}

\integer{x0=random(-4..-2)}
\rational{y0=3-10/((\x0)^2+1)}
\real{x1=randint(-19..20)/10}
\rational{y1=0}
\rational{y2=3}
\real{x2=sqrt(\a/8-1)}
%%%% Polynome d'interpollation
\text{f0=\y0*(x-(\x1))*(x-(\x2))/((\x0-(\x1))*(\x0-(\x2)))}
\text{f1=\y1*(x-(\x0))*(x-(\x2))/((\x1-(\x0))*(\x1-(\x2)))}
\text{f2=\y2*(x-(\x1))*(x-(\x0))/((\x2-(\x1))*(\x2-(\x0)))}
\text{f= \f0 + (\f1) +(\f2)}

\text{courbes=
trange \x0,\x2
    plot red,\f
trange -5,\x0
    plot red,\g1
trange \x2,7
    plot red,\g2
}
\text{quest=\x3}
\text{rep=\y3}

#endif

#if defined TARGET_lectgr2

%%%% Choix de 4 points dans le cadre
\integer{x0=random(-4..-2)}
\integer{x1=\x0+random(1..3)}
\integer{x2=\x1+random(1..3)}
\integer{x3=\x2+random(1..3)}
\integer{y0=random(-5..5)}
\integer{y1=random(-5..5)}
\integer{y2=random(-5..5)}
\integer{y3=random(-5..5)}

%%%% Polynome d'interpollation
\text{f0=\y0*(x-(\x1))*(x-(\x2))*(x-(\x3))/((\x0-(\x1))*(\x0-(\x2))*(\x0-(\x3)))}
\text{f1=\y1*(x-(\x0))*(x-(\x2))*(x-(\x3))/((\x1-(\x0))*(\x1-(\x2))*(\x1-(\x3)))}
\text{f2=\y2*(x-(\x1))*(x-(\x0))*(x-(\x3))/((\x2-(\x1))*(\x2-(\x0))*(\x2-(\x3)))}
\text{f3=\y3*(x-(\x1))*(x-(\x2))*(x-(\x0))/((\x3-(\x1))*(\x3-(\x2))*(\x3-(\x0)))}
\text{f= \f0 + (\f1) +(\f2)+ (\f3)}
\text{courbes=
 plot red,\f
}
\text{typequest=l'image}
\text{typerep=numeric}
\text{verb=est}
\text{quest=\x2}
\text{rep=\y2}
#endif

#if (defined TARGET_lectgr3 || defined TARGET_lectgr4 )
%%%% Choix de 4 points dans le cadre
\integer{x0=random(-4..-2)}
\integer{x1=\x0+random(1..3)}
\integer{x2=\x1+random(1..3)}
\integer{x3=\x2+random(1..3)}
\integer{k=random(1,2)}
\if{\k=1}
{
\integer{y0=random(-5..0)}
\integer{y1=\y0}
\integer{y2=\y0}
\integer{y3=random(3..6)}
\text{rep1=\x0, \x1, \x2}
\text{rep0=\x3}
}
{
\integer{y0=random(-6..-3)}
\integer{y1=random(0..5)}
\integer{y2=\y1}
\integer{y3=\y1}
\text{rep0=\x0}
\text{rep1=\x1,\x2,\x3}
}

%%%% Polynome d'interpollation
\text{f0=\y0*(x-(\x1))*(x-(\x2))*(x-(\x3))/((\x0-(\x1))*(\x0-(\x2))*(\x0-(\x3)))}
\text{f1=\y1*(x-(\x0))*(x-(\x2))*(x-(\x3))/((\x1-(\x0))*(\x1-(\x2))*(\x1-(\x3)))}
\text{f2=\y2*(x-(\x1))*(x-(\x0))*(x-(\x3))/((\x2-(\x1))*(\x2-(\x0))*(\x2-(\x3)))}
\text{f3=\y3*(x-(\x1))*(x-(\x2))*(x-(\x0))/((\x3-(\x1))*(\x3-(\x2))*(\x3-(\x0)))}
\text{f= \f0 + (\f1) +(\f2)+ (\f3)}
\text{courbes=
 plot red,\f
}

#if defined TARGET_lectgr3
\text{typequest=l'antécédent}
\text{typerep=numeric}
\text{verb=est}
   \text{quest=\k=1?\y3:\y0}
   \text{rep=\rep0}
#endif

#if defined TARGET_lectgr4
\text{typequest=les antécédents}
\text{typerep=fset}
\text{verb=sont}
   \text{quest=\y1}
   \text{rep=\rep1}
\text{comp=<div class="wims_instruction">S'il n'y a pas d'antécédent,
  taper <span class="tt">aucun</span>. S'il y en a plusieurs, il faut les séparer par une virgule.</div>}
#endif

#endif

#if defined TARGET_lectgr5
%%%% Choix de 3 points dans le cadre
\integer{x0=random(-4..-2)}
\integer{x1=\x0+random(1..3)}
\integer{x2=2*\x1-\x0}
\integer{y0=random(-4..5)}
\integer{y1=random(-4..5)}
\integer{y1=\y1=\y0?-\y0}
\integer{y1=\y1=\y0?\y1+1}

\integer{y2=\y0}
\integer{y3=\y1>\y0?randint(\y1+1..7):randint(-6..\y1-1)}

%%%% Polynome d'interpollation
\text{f0=\y0*(x-(\x1))*(x-(\x2))/((\x0-(\x1))*(\x0-(\x2)))}
\text{f1=\y1*(x-(\x0))*(x-(\x2))/((\x1-(\x0))*(\x1-(\x2)))}
\text{f2=\y2*(x-(\x1))*(x-(\x0))/((\x2-(\x1))*(\x2-(\x0)))}
\text{f= \f0 + (\f1) +(\f2)}
\text{courbes=
 plot red,\f
}
\integer{k=randint(1..3)}
\if{\k=1}
 {
  \integer{quest=\y0}
  \text{rep=\x0,\x2}
 }
\if{\k=2}
 {
  \integer{quest=\y1}
  \text{rep=\x1}
 }
\if{\k=3}
 {
  \integer{quest=\y3}
  \text{rep=aucun}
 }
\text{typerep=fset}

\text{typequest=le ou les antécédents}
\text{verb=sont}
\text{comp=<div class="wims_instruction">S'il n'y a pas d'antécédent,
  taper <span class="tt">aucun</span>. S'il y en a plusieurs, il faut les séparer par une virgule.</div>}
#endif

%%%%# cadre générique %%%%#
\text{cadre=
xrange -5,7
yrange -6,7
gridfill 0,0,5,5,\gridcolor
linewidth 1
linewidth 2
  parallel -5,-6,-5,7,1,0,13,blue
  parallel -5,-6,7,-6,0,1,13,blue
linewidth 2
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
    linewidth 2
\courbes
}
%%%% fin du cadre générique %%%%

\statement{
<div class="wims_columns">
<div class="medium_size">\draw{400,400}{\cadre}</div>
<div class="medium_size">
  On a dessiné la représentation graphique d'une fonction \(f) définie
  sur &#91;-5;7&#93;.<p>
  Déterminer par lecture graphique \typequest de \quest:
  </p>
<div class="wimscenter">\typequest de \quest \verb:\embed{reply1,3}</div>
\comp
</div>
</div>
}
\answer{}{\rep}{type=\typerep}
