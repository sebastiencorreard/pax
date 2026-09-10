target=1 2 3 4 5 6

#include "lang_titles.inc"
#include "lang.inc"

confparm1= vocabulaire
confparm2=forme
confparm3= grid,nogrid
\text{confparm1=\confparm1 notwordof 1 2? 1}
\text{confparm2=\confparm2 notwordof 1 2 3 ? 1}
\text{confparm4=\confparm4 notwordof 0 1 ? 0}
\text{confparm3=\confparm3 notwordof grid nogrid? grid}
\text{confparm3=\confparm4=1?nogrid}

#if defined TARGET_1 || defined TARGET_2 || defined TARGET_3 || defined TARGET_6
\text{name_choix=\confparm1=1?\name_choix[1,2,3]:\name_choix[1,2,4]}
\text{name_choix2=\confparm1=1?\name_choix2[1,2,3]:\name_choix2[1,2,4]}
\text{ch=randint(1..3)}
#endif
%%% angle de fuite
text{th=-2*pi/3}
%%% coefficient de fuite
text{k=0.5}
%%% angle de fuite
\text{th=-3*pi/4}
%%% coefficient de fuite
\text{k=sqrt(2)/2} 0.7
\text{xyz=x,y,z}

\text{P=1,\k*cos(\th),0;0,\k*sin(\th),1}
\text{P=0,\k*cos(\th),1;1,\k*sin(\th),0}
\text{P=\k*cos(\th),1,0;\k*sin(\th),0,1}

\text{nom=shuffle(A,B,C,D,E,G,H,F)}
\if{\confparm2=1}{
  \text{pave=randint(3..6)}
  \text{pave=\pave,\pave,\pave}
}
\if{\confparm2=2}{
  \text{pave=randint(3..6)}
  \text{pave=randint(3..6),\pave,\pave}
  \text{pave=shuffle(\pave)}
}
\if{\confparm2=3}{
  \text{pave=shuffle(6)}
  \text{pave=\pave[1,2,3]}
  1 fait des confusions avec les echelles
  \text{pave=wims(replace internal 1 by 7 in \pave)}
}
\matrix{points=0,0,0
\pave[1],0,0
\pave[1],\pave[2],0
0,\pave[2],0
0,0,\pave[3]
\pave[1],0,\pave[3]
\pave[1],\pave[2],\pave[3]
0,\pave[2],\pave[3]
}
\matrix{cube=1,2,3,4,1
5,6,7,8,5
1,5,2,6,3,7,4,8}

text{transl=\confparm4=1? randitem(-3,-2,0,2,3),randitem(-3,-2,0,2,3),randitem(-3,-2,0,2,3):0,0,0}
\text{transl=\confparm4=1? 1,1,1:0,0,0}
text{transl=0,0,0}

\text{points=pari(tr=[\transl];matrix(8,3,i,j,tr[j])+[\points])}
\text{points2D=pari([\points]*[\P]~)}
#if defined TARGET_5
point demi-entier
\text{pointsdemi=}
\for{j1=1 to 2}{
  \text{S=\cube[\j1;]}
  \integer{cnt=items(\S)}
  \for{j2=1 to \cnt-1}{
    \text{T1=\points[\S[\j2];]}
    \text{T2=\points[\S[\j2+1];]}
    \matrix{pointsdemi=\pointsdemi
pari(([\T1]+[\T2])/2)}
  }
}
\text{S=\cube[3;]}
\integer{cnt=items(\S)}
\for{j2=1 to \cnt/2}{
  \text{T1=\points[\S[2*\j2-1];]}
  \text{T2=\points[\S[2*\j2];]}
  \matrix{pointsdemi=\pointsdemi
pari(([\T1]+[\T2])/2)}
}
\text{pointstiers=}
\for{j1=1 to 2}{
  \text{S=\cube[\j1;]}
  \integer{cnt=items(\S)}
  \for{j2=1 to \cnt-1}{
    \text{T1=\points[\S[\j2];]}
    \text{T2=\points[\S[\j2+1];]}
    \matrix{pointstiers=\pointstiers
pari((2*[\T1]+[\T2])/3)
pari(([\T1]+2*[\T2])/3)}
  }
}
\text{S=\cube[3;]}
\integer{cnt=items(\S)}
\for{j2=1 to \cnt/2}{
  \text{T1=\points[\S[2*\j2-1];]}
  \text{T2=\points[\S[2*\j2];]}
  \matrix{pointstiers=\pointstiers
pari((2*[\T1]+[\T2])/3)
pari(([\T1]+2*[\T2])/3)}
}

\text{pointsdemi2D=pari(round(1000*[\pointsdemi]*[\P]~)/1000.)}
\text{pointstiers2D=pari(round(1000*[\pointstiers]*[\P]~)/1000.)}
#endif
\if{\confparm3 iswordof grid}{
  \text{grid=1}
  \text{grid=grid 1,1,grey,\grid,\grid,6,grey}
}{
  \text{grid=}
}
\real{size=pari(vecmax(abs([\points]*[\P]~ )))}
\real{size1=1.2*\size}
\real{size2=1.5*\size}
\text{picsize=500,500}
\text{dec=0.4} decalage des noms
\text{axe=}
\text{unit=}
\if{\confparm4=0}{
  \text{axe=arrow 0,0,2*\size1*\P[1;1],2*\size1*\P[2;1],10,grey
  arrow 0,0,\size2*\P[1;2],1.5*\size1*\P[2;2],10,grey
  arrow 0,0,\size2*\P[1;3],\size2*\P[2;3],5,grey
  text black,2*(\size1-0.7)*\P[1;1]+0.1,2*(\size1-0.7)*\P[2;1]+\dec,large,\xyz[1]
  text black,(\size2-0.7)*\P[1;2]+0.1,(\size2-0.5)*\P[2;2]+\dec,large,\xyz[2]
  text black,(\size2-0.7)*\P[1;3]+0.1,(\size2-0.7)*\P[2;3]+\dec,large,\xyz[3]
  text black,\P[1;1]-\dec,\P[2;1],large,1
  text black,\P[1;2]+\dec,\P[2;2],large,1
  text black,\P[1;3]+\dec,\P[2;3],large,1
  }
  \text{unit=crosshairs black,\P[1;1],\P[2;1]
crosshairs black,\P[1;2],\P[2;2]
crosshairs black,\P[1;3],\P[2;3]}
}
\text{dessinprelim=xrange -\size1,\size2
yrange -\size1,\size2
axis
comment axisnumbering
opacity 255,255
linewidth 2
\axe
precision 10
linewidth 1
\grid
}

\text{face1=\points2D[\cube[1;];]}
\text{face2=\points2D[\cube[2;];]}
\text{arete=\points2D[\cube[3;];]}
\text{face1=wims(replace internal ; by , in \face1)}
\text{face2=wims(replace internal ; by , in \face2)}
\text{arete=wims(replace internal ; by , in \arete)}
\text{dessinprelim=\dessinprelim
opacity 255,255
linewidth 3
polyline brown,\face1
polyline brown,\face2
segments brown,\arete
linewidth 2
\unit
fontfamily bold 10pt Ariel}

\text{drawnom=}
\text{drawcoord=}
\text{drawcoordbase=}
#if defined TARGET_1 || defined TARGET_2
\text{s=randint(1..8)}
\for{k=1 to 8}{
  \text{tmp=string black,\points2D[\k;1],\points2D[\k;2]+\dec,\nom[\k]}
  \text{drawnom=\drawnom
  \tmp}
  \if{\k!=\s}{
    \real{test=\points[\k;2]= 0 ? -1.5*\dec:1.5*\dec}
    \text{tmp=centered
    string black,\points2D[\k;1]+\test,\points2D[\k;2]+\dec,(wims(replace internal , by ; in \points[\k;]))}
  }{
    \text{tmp=string black,\points2D[\k;1],\points2D[\k;2]+\dec,\nom[\k]}
  }
  \text{drawcoordbase=\drawcoordbase
  \tmp}
  \real{test=\points[\k;2]=0 ? -1.5*\dec:1.5*\dec}
  \text{tmp=centered
  string black,\points2D[\k;1]+\test,\points2D[\k;2]+\dec,\nom[\k](wims(replace internal , by ; in \points[\k;]))}
  \text{drawcoord=\drawcoord
  \tmp}
}
#endif
#if defined TARGET_3 || defined TARGET_4 ||  defined TARGET_5 || defined TARGET_6
\text{s=randitem(3,6,7,8)}
\for{k=1 to 8}{
  \if{\k iswordof 1 2 4 5}{
    \real{test=\points[\k;2]= 0 ? -1.5*\dec:1.5*\dec}
    \text{tmp=centered
string black,\points2D[\k;1]+\test,\points2D[\k;2]+\dec,\nom[\k](wims(replace internal , by ; in \points[\k;]))}
  }{
# if defined TARGET_3
  \text{tmp=string black,\points2D[\k;1],\points2D[\k;2]+\dec,\nom[\k]}
# else
  \text{tmp=}
# endif
}
\text{drawcoordbase=\drawcoordbase
  \tmp}
\text{tmp=\nom[\k]: wims(replace internal , by ; in \points[\k;])}
\text{tmp=centered
string black,\points2D[\k;1],\points2D[\k;2]+\dec,\tmp}
\text{drawcoord=\drawcoord
  \tmp}
}
#endif
\text{coord=\points[\s;]}
\text{pointstosnap=wims(replace internal ; by , in \points2D)}
text{points2D=wims(rows2lines \points2D)}
#if defined TARGET_4 || defined TARGET_6
\text{rep=\points2D[\s;]}
#endif
#if defined TARGET_5
%%% choix entre les points au milieu ou au tiers
\text{h=randitem(12,24)}
\text{s=shuffle(\h)}
\text{pointsnew2D=\h=12? \pointsdemi2D:\pointstiers2D}
\text{pointstosnap=\h=12? \pointstosnap,\pointsdemi2D: \pointstosnap,\pointstiers2D}
\text{pointstosnap=wims(replace internal ; by , in \pointstosnap)}
\text{rep=\pointsnew2D[\s[1];]}
\text{ss=1}
%% points qui ne coincident pas avec un point de base en 2D
\text{points2D_=wims(rows2lines \points2D)}
\while{\rep islineof \points2D_ and \ss < \h}{
  \text{ss=\ss+1}
  \text{rep=\pointsnew2D[\s[\ss];]}
}
\text{coord=\h=12?\pointsdemi[\s[\ss];]:\pointstiers[\s[\ss];]}
#endif
#if defined TARGET_6
ch:
1=abscisse, 2=ordonnée, 3=altitude
\text{valeur=\points[;\ch]}
\text{valeur=randitem(\valeur)}
\text{rep=}
\for{j=1 to 8}{
  \if{\points[\j;\ch]=\valeur}{
    \text{rep=wims(append item \points2D[\j;] to \rep)}
  }
}
#endif
\text{dessin=\dessinprelim}
\text{dessinfeed=\dessinprelim}
#if defined TARGET_1
\text{dessin=\dessin
\drawcoord}
#endif
#if defined TARGET_2 || defined TARGET_3 || defined TARGET_5 || defined TARGET_4 || defined TARGET_6
\text{dessin=\dessin
\drawcoordbase}
#endif
#if defined TARGET_1 || defined TARGET_2 || defined TARGET_3
\text{dessinfeed=\dessinfeed
centered
string blue,\points2D[\s;1],\points2D[\s;2]+\dec,\nom[\s](wims(replace internal , by ; in \points[\s;]))
}
#endif
#if defined TARGET_4 || defined TARGET_5
# if defined TARGET_4
\real{test=\points2D[\s;2]= 0 ? -1.5*\dec:1.5*\dec}
\text{tmp=centered
string black,\points2D[\s;1]+\test,\points2D[\s;2]+\dec,(wims(replace internal , by ; in \points[\s;]))}
# endif
# if defined TARGET_5
\text{tmp=centered
string black,\rep[1],\rep[2]+\dec,(wims(replace internal , by ; in \coord))}
# endif
\text{dessinfeed=\dessinfeed
\drawcoordbase
crosshairs green,\rep
\tmp
}
#endif

#if defined TARGET_6
\text{dessinfeed=\dessin
\drawcoordbase
crosshairs green,\rep
}
#endif
#if defined TARGET_4 || defined TARGET_5 || defined TARGET_6
\text{dessin=\dessin
snaptopoints \pointstosnap}
#endif
\text{dessinurl=canvasdraw(\picsize
\dessin)}

#if defined TARGET_1
\statement{
<label for="reply1">
  \name_instruction[1] \name_choix2[\ch] \name_instruction[2] \nom[\s]
</label>: \embed{r1,4}
\dessinurl
<div class="wims_instruction">\name_warning</div>
}
\answer{\nom[\s]: \name_choix[\ch] }{\coord[\ch]}{type=numexp}
#endif
#if defined TARGET_2
\statement{
\name_instruction \nom[\s]:
  (\embed{r1,4};\embed{r2,4};\embed{r3,4})
\dessinurl
<div class="wims_instruction">\name_warning</div>
}
\answer{\nom[\s]: \name_choix[1]}{\coord[1]}{type=numexp}
\answer{\nom[\s]: \name_choix[2]}{\coord[2]}{type=numexp}
\answer{\nom[\s]: \name_choix[3]}{\coord[3]}{type=numexp}
#endif
#if defined TARGET_3
\statement{
\name_instruction \nom[\s]:
  (\embed{r1,4};\embed{r2,4};\embed{r3,4})
\dessinurl
<div class="wims_instruction">\name_warning</div>
}
\answer{\nom[\s]: \name_choix[1]}{\coord[1]}{type=numexp}
\answer{\nom[\s]: \name_choix[2]}{\coord[2]}{type=numexp}
\answer{\nom[\s]: \name_choix[3]}{\coord[3]}{type=numexp}
#endif
#if defined TARGET_4 || defined TARGET_5
\text{coord=wims(replace internal , by ; in \coord)}
\statement{
\name_instruction (\coord).
\embed{r1,500x500}
<div class="wims_instruction">\name_warning
\name_warning_magn</div>
}
\answer{}{[\dessin]; crosshairs,\rep}{type=draw}
#endif
#if defined TARGET_6
\statement{
\name_instruction[1] \name_choix2[\ch] \name_instruction[2] \valeur.
\embed{r1,500x500}
<div class="wims_instruction">\name_warning</div>
}
\answer{}{[\dessin]; crosshairs,\rep}{type=draw}
#endif
%%% feedback
#if defined TARGET_1
\feedback{\sc_reply1<1}{
\name_feed[1] \nom[\s] \name_feed[2] (\coord[1];\coord[2];\coord[3]),
\name_choix2[\ch] \name_feed[3] \coord[\ch].
}
#endif
#if defined TARGET_2 || defined TARGET_3
\feedback{\sc_reply1<1}{
\name_feed[1] \nom[\s] \name_feed[2] (\coord[1];\coord[2];\coord[3]).
}
#endif
\feedback{1=1}{
\canvasdraw{\picsize}{
\dessinfeed}
}
