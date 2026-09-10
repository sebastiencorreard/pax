target=lieutransf1 lieutransf2
#include "author.inc"

#if defined TARGET_lieutransf1
# define NUM 1
#endif
#if defined TARGET_lieutransf2
# define NUM 2
#endif
#include "lang_titles.inc"
#if defined TARGET_lieutransf1
\text{quest=Déterminer le lieu du milieu \(I) du segment \([F M])}
\function{rayon=r/2}
\text{tfeed=Soit \(h) l'homothétie de centre \(F) et de rapport 0.5&nbsp;:<br>
\(I) est l'image de \(M) et \(\Omega) est l'image de \(O) par \(h).<br>
Donc \(\overrightarrow{\Omega I}=0.5 \overrightarrow{O M}) donc \(R=\frac{r}{2}).}
#endif
#if defined TARGET_lieutransf2
# define NUM 2
\text{quest=Déterminer le lieu du point \(H)}
\function{rayon=a/2}
\text{tfeed=Le triangle \(F H O) est rectangle en \(H), donc \(H) appartient au
cercle de diamètre \([F O]).<br>
Donc le centre \(\Omega) est le milieu du segment \([F O]) et le rayon est \(R=\frac{a}{2}).}
#endif
\text{lstvec=\(\overrightarrow{F \Omega}),\(\overrightarrow{F O}),\(\overrightarrow{F I}),\(\overrightarrow{F M}),\(\overrightarrow{O M}),\(\overrightarrow{O H}),\(\overrightarrow{F H}),\(\overrightarrow{I H}),\(\overrightarrow{I O})}
\rational{angleM=randint(5..10)/12}
\integer{r=randint(2..4)}
\integer{xF=-4}
\integer{yF=-2}
\real{xM=\r*cos(\angleM*pi)}
\real{yM=\r*sin(\angleM*pi)}
\real{xI=(\xM+\xF)/2}
\real{yI=(\yM+\yF)/2}
\real{a=(\yM-\yF)/(\xM-\xF)}
\real{xH=(\a*\xF-\yF)/(\a+1/\a)}
\real{yH=-\xH/\a}
\rational{xW=\xF/2}
\rational{yW=\yF/2}
#if defined TARGET_lieutransf1
\real{R=\r}
\text{suitedessin=
 point \xW,\yW,red
 copy \xW,\yW,-1,-1,-1,-1,mathfonts/109/Omega.gif
 linewidth 1
 segment \xF,\yF,0,0,green
 circle \xW,\yW,\R*30,green
}
\integer{rep1=2}
\text{typec=cercle}
#else
\real{df=(\xF)^2+(\yF)^2}
\real{R=sqrt(\df)}
\real{del=\df-(\r)^2}
\real{xP=(\xF*(\r)^2-sqrt(\del))/\df}
\real{xQ=(\xF*(\r)^2+sqrt(\del))/\df}
\real{yP=((\r)^2-\xF*\xP)/\yF}
\real{yQ=((\r)^2-\xF*\xQ)/\yF}
\real{r2=sqrt(\xM^2+\yM^2)}
\real{xP=-\r*(\yF*sqrt(\del)-\xF*\r)/\df}
\real{xQ=\r*(\yF*sqrt(\del)+\xF*\r)/\df}
\real{yP=\r*(\xF*sqrt(\del)+\yF*\r)/\df}
\real{yQ=-\r*(\xF*sqrt(\del)-\yF*\r)/\df}

\text{suitedessin=
 point \xW,\yW,red
 copy \xW,\yW,-1,-1,-1,-1,mathfonts/109/Omega.gif
 linewidth 1
 segment \xF,\yF,0,0,green
 circle \xW,\yW,\R*30,green
 dsegment \xF,\yF,\xP,\yP,green
 dsegment \xF,\yF,\xQ,\yQ,green

 linewidth 5
 points green,\xP,\yP,\xQ,\yQ
 text black,\xP,\yP,medium,P
 text black,\xQ,\yQ,medium,Q
}
\integer{rep1=3}
\text{typec=arc de cercle \(Q O P)}
#endif
\text{size=80x50x1}
\text{mstep=r1
r2,r3,r4
r5}
\text{dessin=
 xrange -5,5
 yrange -5,5
 circle 0,0,\r*60,blue
 segment \xF,\yF,\xM,\yM,blue
 dsegment 0,0,\xH,\yH,orange
 linewidth 5
 points red,0,0,\xF,\yF,\xM,\yM,\xI,\yI,\xH,\yH
 text red,0,0,medium,O
 text blue,\xF,\yF,medium,F
 text blue,\xM,\yM,medium,M
 text red,\xI,\yI,medium,I
 text orange,\xH,\yH,medium,H
}

\steps{\mstep}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
 \if{\step=3}{\draw{300,300}{\dessin
 \suitedessin}
 }{
 \draw{300,300}{\dessin}
 }
</div>
 <div class="medium_size text_col">
  <p>
  Dans le plan, soit \((C)) un cercle de centre \(O) et de rayon \(r)
  et \(F) un point extérieur à \((C)).<br>
  Un point \(M) décrit le cercle \((C)).<br>
  Le point \(H) est le projeté orthogonal du point \(O) sur la droite \((F M)).
  </p>
  \quest.
  \if{\step=1}{
    <div class="wimscenter"> Il s'agit d'\embed{repy1}</div>
  }{
    <p> Il s'agit d'un \typec de centre \(\Omega).</p>
    \if{\step=2}{
      Donner une égalité vectorielle caractérisant ce centre.
      <div class="wimscenter">\embed{reply2,\size}=\embed{reply3,3}\embed{reply4,\size}</div>
    }{
      avec \(\overrightarrow{F\Omega}=\frac{1}{2}\overrightarrow{F O}).
      <p>
       Déterminer le rayon \(R) de ce cercle en fonction du rayon \(r) de \((C))
       et de la distance \(a=F O).
      </p>
      <div class="wimscenter"> \(R\)=\embed{reply5,5}</div>
    }
  }
  </div></div>
}
\answer{nature du lieu}{\rep1;un point,un cercle, un arc de cercle, une droite}{type=menu}
\answer{}{\lstvec1;\lstvec}{type=clickfill}
\answer{}{\coef}{type=numeric}
\answer{}{\lstvec2;\lstvec}{type=clickfill}
\answer{}{\rayon}{type=function}
\condition{(\reply2 issametext \lstvec[1] and \reply4 issametext \lstvec[2] and \reply3=0.5) or (\reply2 issametext \lstvec[2] and \reply4 issametext \lstvec[1] and \reply3=2)}
\feedback{1=1}{\tfeed}
