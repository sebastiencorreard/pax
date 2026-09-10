target=ombre1 ombre2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_ombre1
\text{n=randint(2..3)}
#endif
#if defined TARGET_ombre2
\text{n=0}
\integer{choix=randint(1..3)}
#endif
\text{posi=shuffle(4)}
\text{list=shuffle(A,B,C,D,E,F)}
\text{list=\list[1..\n+1]}
\text{angle1=randint(100..140)}
\real{angle2=\angle1+randitem(140,160,170)}
\real{angle1=pi/180*\angle1}
\real{angle2=pi/180*\angle2}
\text{A=pari([cos(\angle1),sin(\angle1)])}
\text{B=pari([cos(\angle2),sin(\angle2)])}
\text{P=pari([\B[2]-(\A[2]),\A[1]-(\B[1])]/sin(\angle2-(\angle1)))}
\real{range1=\P[1]-2}
\text{range2=10}
\text{Pos=\P}
\for{j=1 to \n}{
  \text{signe=randitem(1,-1)}
  \real{pos=\P[2]+2*\signe*\posi[\j]}
  \text{Pos=\Pos,\P[1],\pos}
  \real{range2=max(\range2,\pos)}
  \real{range1=min(\range1,\pos)}
}
\text{range=pari([floor(\range1),ceil(\range2)])}
\real{mur=\range[2]-1}
\text{Q1=pari(floor([\mur,(1-(\A[1])*\mur)/(\A[2])]*1000)/1000.)}
\text{Q2=pari(floor([\mur,(1-(\B[1])*\mur)/(\B[2])]*1000)/1000.)}
\real{range1=min(\range[1],min(\Q1[2],\Q2[2]))}
\real{range2=max(\range[2],max(\Q1[2],\Q2[2]))}
\text{range=pari([floor(\range1),ceil(\range2)])}
\text{nom=}
\text{nomfly}
\for{j=1 to \n+1}{
  \text{nom=\nom
string black,\Pos[2*\j-1]-1,\Pos[2*\j],\list[\j]}
}
\for{j=1 to \n+1}{
  \text{nomfly=\nomfly
text black,\Pos[2*\j-1]-1,\Pos[2*\j],medium,\list[\j]}
}
\text{ombreport=linewidth 4
segments black,\Q1,\Q2}
\text{rayon=linewidth 1
arrow \P,\Q1,10,black,
arrow \P,\Q2,10,black}
\text{cone=linewidth 1
segments black,\A,\Q1,\B,\Q2
fill pari(([\A]+[\B]+[\Q1]+[\Q2])/4),lightgrey
}
\text{dessin=xrange \range
yrange \range
vline \mur,0,black
textup black,\mur,\range[1],large,Ecran
linewidth 1
crosshairs black,\Pos
filled
circles black,0,0,1}
#if defined TARGET_ombre1
\text{dessin=\dessin
\ombreport}
\integer{rep=1}
\statement{
  \name_enonce.
  \canvasdraw{400,400}{\dessin
  \nom
linewidth 1
userdraw segment, blue}
  \name_question?
  <div class="wims_instruction">\name_hint</div>
}
\answer{\name_answer}{\rep;\list}{type=radio}{option=shuffle}
\feedback{1=1}{<div class="wimscenter">
  \draw{400,400}{\dessin
\cone
\rayon
\nomfly}</div>
}
#endif
#if defined TARGET_ombre2
\text{rep=\choix=1?segments,\Q1,\Q2}
\text{rep=\choix=2?segments,\A,\Q1,\B,\Q2}
\text{rep=\choix=3?arrows,\P,\Q1,\P,\Q2}
\text{tmp=\choix=1?\ombreport}
\text{tmp=\choix=2?\cone}
\text{tmp=\choix=3?\rayon
\cone}
\text{R=pari([\mur,(\Q1[2]+3*\Q2[1])/2,\mur,(\Q1[2]+\Q2[1])/2,\mur,(\Q1[2]+2*\Q2[1])/4,\mur,(\Q1[2]+2*\Q2[1])])}
\text{dessin=\dessin
precision 100
linewidth 3
snaptopoints \Q1,\Q2,\P,\A,\B,\R}

\statement{
  \name_enonce A.
  \name_question \name_choix[\choix].
  <div class="wimscenter">\embed{r1}</div>
}
\answer{}{[\dessin];\rep}{type=draw}{option=color="green" eqweight split}
\feedback{\sc_reply1<1}{
\if{\choix<3}{\name_feed[\choix;]}
  <div class="wimscenter">
  \draw{400,400}{\dessin
  \tmp}
  </div>
}
#endif
