target=resoGraphIn1
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{xsize=random(8,10,12)}
\integer{ysize=random(8..12)}
\integer{casf=random(1..7)}

/** casf < 7 **/

\integer{k=\casf!=7?random(-\ysize+3..\ysize-3)}
\integer{a1=-\xsize}
\integer{a2=random(-0.5*\xsize+1..-1)}
\integer{a3=random(2..0.5*\xsize-1)}
\integer{a4=\xsize}

\text{courbef=\name_courbe[1]}
\text{courbeg=\name_courbe[1]}

\integer{b1=\casf!=7?random(-1,1)*random(\ysize-4..\ysize)}
\integer{b1=(\casf!=7 and \b1==\k or \b1==\k+1 or \b1==\k-1)?random(1..2)-\k}
\integer{b2=\casf!=7?\k}
\integer{b3=\casf!=7?\k}
\integer{b4=\casf!=7?random(-1,1)*random(\ysize-4..\ysize)}
\integer{b4=(\casf!=7 and \b4==\k or \b4==\k+1 or \b4==\k-1)?random(1..2)-\k}

/** casf 7 : interpolation cubique monotone (1 pt intersection) **/

\integer{sign=\casf==7?random(-1,1)}
\integer{b1=\casf==7?\sign*random(\ysize-6..\ysize)}
\integer{b2=\casf==7?\sign*random(1..\ysize-4)}
\integer{b3=\casf==7?-\sign*random(1..\ysize-4)}
\integer{b4=\casf==7?-\sign*random(\ysize-6..\ysize)}
\integer{k=\sign==1?\b2:\b3}

/** casrel==0 pour inégalité stricte ; casrel==1 sinon **/
\integer{casrel=random(0,1)}

\function{f=\casf==1?\b1*(x-\a3)/(\a1-\a3) + \b3*(x-\a1)/(\a3-\a1)}
\function{f=\casf==2? \b2*(x-\a3)*(x-\a4)/((\a2-\a4)*(\a2-\a3))+ \b3*(x-\a2)*(x-\a4)/((\a3-\a2)*(\a3-\a4)) + \b4*(x-\a3)*(x-\a2)/((\a4-\a2)*(\a4-\a3))}
\function{f=\casf==3?\b2*(x-\a3)*(x-\a1)/((\a2-\a1)*(\a2-\a3))+ \b3*(x-\a2)*(x-\a1)/((\a3-\a2)*(\a3-\a1)) + \b1*(x-\a3)*(x-\a2)/((\a1-\a2)*(\a1-\a3))}
\function{f=\casf==4?\b4*(x-\a2)/(\a4-\a2) + \b2*(x-\a4)/(\a2-\a4)}
\function{f=\casf==5?(\a2+\xsize+1)/(x+\xsize+1) + \b2-1 }
\function{f=\casf==6?-(\a3+\xsize+1)/(x+\xsize+1)+\b3+1}
\function{f=\casf==7?
\b1*(x-\a2)*(x-\a3)*(x-\a4)/((\a1-\a2)*(\a1-\a3)*(\a1-\a4)) + \b2*(x-\a1)*(x-\a3)*(x-\a4)/((\a2-\a1)*(\a2-\a3)*(\a2-\a4))+ \b3*(x-\a1)*(x-\a2)*(x-\a4)/((\a3-\a2)*(\a3-\a1)*(\a3-\a4))+ \b4*(x-\a1)*(x-\a2)*(x-\a3)/((\a4-\a2)*(\a4-\a1)*(\a4-\a3))}

/** absc. des points d'intersection, et leurs ordonnées **/
/** il y a n points d'intersection et n=1 ou n=2 **/

\text{soleq=(\casf==1 or \casf==6)?\a3 }
\text{soleq=(\casf==2 or \casf==3)?\a2,\a3 }
\text{soleq=(\casf==4 or \casf==5)?\a2}
\text{soleq=(\casf==7 and \sign==1)?\a2}
\text{soleq=(\casf==7 and \sign==-1)?\a3}

\integer{n=(\casf==2 or \casf==3)?2:1}
\text{ysoleq=\k}

/** liste des choix de réponse **/

\text{ens1a=[-\xsize, \soleq[1]]}
\text{ens1b= &#91; -\xsize &#44; \soleq[1] &#91; }

\text{ens21a= \n==1? [\soleq[1], \xsize] }
\text{ens22a= \n==2? [\soleq[1], \soleq[2]]}
\text{ens21b= (\n==1)? &#93;\soleq[1] &#44; \xsize&#93;}
\text{ens22b= (\n==2)? &#93;\soleq[1] &#44; \soleq[2] &#91;}
\text{ens31a= (\n==1)? {\soleq[1]} }
\text{ens31b= (\n==1)? \(\,\emptyset)}
\text{ens32a= (\n==2)? [\soleq[2], \xsize]}
\text{ens32b=(\n==2)? &#93; \soleq[2] &#44; \xsize &#93;}
\text{ens4 = [-\xsize, \xsize]}
\text{ens52a = \ens1a \(\cup) \ens32a}
\text{ens52b = \ens1b \(\cup) \ens32b}
\text{I1=<i>I</i><sub>1</sub>}
\text{I2=<i>I</i><sub>2</sub>}
\text{I3=<i>I</i><sub>3</sub>}
\text{I4=<i>I</i><sub>4</sub>}
\text{I5=<i>I</i><sub>5</sub>}
\text{I6=<i>I</i><sub>6</sub>}
\text{I7=<i>I</i><sub>7</sub>}
\text{I8=<i>I</i><sub>8</sub>}
\text{I9=<i>I</i><sub>9</sub>}
\text{choixint= (\n==1)?\ens1a,\ens1b,\ens21a,\ens21b,\ens31a,\ens31b,\ens4:
\ens1a,\ens1b,\ens22a,\ens22b,\ens32a,\ens32b,\ens4,\ens52a,\ens52b}

\text{choix=(\n==1)?\I1,\I2,\I3,\I4,\I5,\I6,\I7:
\I1,\I2,\I3,\I4,\I5,\I6,\I7,\I8,\I9}

\real{fxmin=evaluate(\f,x=-\xsize)}
\real{fxmax=evaluate(\f,x=\xsize)}
\real{xmil=\n==2?0.5*(\soleq[1]+\soleq[2])}
\real{fxmil=\n==2?evaluate(\f,x=\xmil)}

/*****************************************************/
/** liste des numéros des bonnes reponses **/
\text{repsol=0}
/** construction des bonnes réponses (en deux temps)**/
\text{repsol=( \casrel==0 and \fxmin < \k )?\repsol,2}
\text{repsol=( \casrel==1 and \fxmin < \k )?\repsol,1}
\text{repsol=(\n==2 and \casrel==0 and \fxmil < \k )?\repsol,4}
\text{repsol=(\n==2 and \casrel==1 and \fxmil < \k )?\repsol,3}
\text{repsol=(\casrel==0 and \fxmax < \k )?\repsol,simplify(2*\n+2)}
\text{repsol=( \casrel==1 and \fxmax < \k )?\repsol,simplify(2*\n+1)}
/** eliminer le zéro restant dans repsol dans les autres cas **/
\integer{l=items(\repsol)}
\text{repsol1=\l>1?item(2..\l,\repsol)}
/** si n=1 et repsol=1,3 c'est que l'ens des sol. est l'int de def entier **/
\text{repsol1=(\n==1 and \repsol1[1]==1 and \repsol1[2]==3)?7}
/** cas où l'ens des sol. est une union d'int. **/
\text{repsol1=(\n==2 and \repsol1[1]==1 and \repsol1[2]==5)?8}
\text{repsol1=(\n==2 and \repsol1[1]==2 and \repsol1[2]==6)?9}

/** preparation de la solution graphique **/

\text{black=120,120,120}

\text{ticks=text black,-1,-20,small,-20
text black,-1,-15,small,-15
text black,-1,-10,small,-10
text black,-1,-5,small,-5
text black,-1,5,small,5
text black,-1,10,small,10
text black,-1,15,small,15
text black,-1,20,small,20
text black,-10,-0.2,small,-10
text black,-5,-0.2,small,-5
text black,5,-0.2,small,5
text black,10,-0.2,small,10
linewidth 3
point 0,1,black
point 1,0,black
point -10,0,black
point -5,0,black
point 5,0,black
point 10,0,black
point 0,-20,black
point 0,-15,black
point 0,-10,black
point 0,-5,black
point 0,5,black
point 0,10,black
point 0,15,black
point 0,20,black}

\text{ll=\n==1?\k,\fxmin,\fxmax:\fxmil,\k,\fxmin,\fxmax}
\text{ll=wims(sort numeric items \ll)}
\integer{yfloor=\ll[1]}
\integer{yceiling=\ll[-1]}

\integer{ymin=(\yfloor>0)?-1:\yfloor-1}
\integer{ymax=(\yceiling<0)?1:\yceiling+1}

\text{coordseg1=(\l==1 and \repsol1==7)?-\xsize,\xsize}
\text{coordseg1=(\repsol1[1] isitemof 1,2)?-\xsize,0,\soleq[1],0}
\text{coordseg1=(\n==1 and \repsol1 isitemof 3,4)?\soleq[1],0,\xsize,0}
\text{coordseg1=(\n==2 and \repsol1 isitemof 8,9)?-\xsize,0,\soleq[1],0}
\text{coordseg1=(\n==2 and \repsol1 isitemof 3,4)?\soleq[1],0,\soleq[2],0}
\text{coordseg2=(\n==2 and \repsol1 isitemof 8,9)?\soleq[2],0,\xsize,0}

\integer{psize=(\casrel==0)?0:5}
\integer{borne1=\soleq[1]}
\integer{borne2=(\n==2)?\soleq[2]:\borne1}
\text{diambornexclue=(\n==1 and \repsol1[1]==2 and \repsol1[2]==4)?10:0}

\text{dline = \n==1?dsegment \soleq[1],\k,\soleq[1],0,red:
dsegment \soleq[1],\k,\soleq[1],0,red
dsegment \soleq[2],\k,\soleq[2],0,red}

\statement{<div class="wims_columns">
  <div class="medium_size img_col">
  <div class="wimscenter">
\draw{400,400}{
xrange -\xsize,\xsize
yrange \ymin,\ymax
parallel -\xsize,\ymin,-\xsize,\ymax,1,0,2*\xsize+1,grey
parallel -\xsize,\ymin,\xsize,\ymin,0,1,-\ymin+\ymax+1,grey
hline 0,0,\black
vline 0,0,\black
arrow 0,0,1,0,8,\black
arrow 0,0,0,1,8,\black
text black,-0.5,-0.3,small,O
text black,1,-0.3,small,I
text black,-0.5,1,small,J
\ticks
text blue,\xsize-2.5,\fxmax,medium,y=f(x)
text green,-\xsize + 1.5,\k+1,medium,y=\k
linewidth 1.5
plot blue,\f
plot green,\k}
</div></div>
<div class="medium_size text_col">
\name_enonce0 [-\xsize, \xsize].
\name_enonce1 \(y = \k\).
\if{\n==2}{\name_enonce2[1] \name_enonce2[2] \soleq[1] \name_and \soleq[2]}
  {\name_enonce2[1] \name_enonce2[3] \soleq}.
<p>
\name_enonce3
\(f(x)\) \if{\casrel==0}{\(<)}{\(\leq)} \(\k\) \name_in [-\xsize, \xsize].
</p>
<div>\name_set:
<ul class="inline">
<li>\I1 = \choixint[1]</li>
<li>\I2 = \choixint[2]</li>
<li>\I3 = \choixint[3]</li>
<li>\I4 = \choixint[4]</li>
<li>\I5 = \choixint[5]</li>
<li>\I6 = \choixint[6]</li>
<li>\I7 = \choixint[7]</li>
\if{\n==2}{
<li>\I8 = \choixint[8]</li>
<li>\I9 = \choixint[9]</li>}
</ul>
  \name_question \(\mathcal{S}\) =
 <div class="wimscenter">\embed{reply1}</div>
</div>
</div></div>
}

\hint{\name_hint}
\answer{\name_answer}{\repsol1 ; \choix}{type=radio}

\feedback{(\repsol1== 1 and \I2 issametext \reply1) or
(\repsol1== 3 and \I4 issametext \reply1) or
(\repsol1== 1 and \I2 issametext \reply1) or
(\repsol1== 3 and \I4 issametext \reply1) or
(\repsol1== 5 and \I6 issametext \reply1)}
{<b>Explication.</b> \name_feed[1;]}

\feedback{(\repsol1== 2 and \I1 issametext \reply1) or
(\repsol1== 4 and \I3 issametext\reply1) or
(\repsol1== 2 and \I1 issametext \reply1) or
(\repsol1== 4 and \I3 issametext \reply1) or
(\repsol1== 6 and \I5 issametext \reply1)}
{<b>Explication.</b>\name_feed[2;].}

\feedback{(\repsol1!=7 and \I7 issametext \reply1)}{
  \name_feed1 \name_feed2[1] [-\xsize, \xsize] \name_feed2[2..-1]}

\feedback{(\n==1 and \repsol1!=6 and \I6 issametext \reply1)}{
  \name_feed1 \name_feed3.}

/** montrer la lecture graphique anyway **/
\feedback{1==1}{\name_sol \name_feed[1], \name_feed[2]
  \(f(x)\)
  \if{\casrel==0}{\(<\)}{\(\leq\)} \(g(x)\) \name_feed[3]:
<div class="wimscenter">
\draw{350,350}{
xrange -\xsize,\xsize
yrange \ymin,\ymax
parallel -\xsize,\ymin,-\xsize,\ymax,1,0,2*\xsize+1,grey
parallel -\xsize,\ymin,\xsize,\ymin,0,1,-\ymin+\ymax+1,grey
hline 0,0,\black
vline 0,0,\black
arrow 0,0,1,0,8,\black
arrow 0,0,0,1,8,\black
text \black,-0.5,-0.3,small,O
text \black,1,-0.3,small,I
text \black,-0.5,1,small,J
\ticks
text blue,\xsize-2.5,\fxmax,medium,y=f(x)
text green,-\xsize+1.5,\k+1,medium,y=\k
linewidth 1.5
plot blue,\f
plot green,\k
\dline
text red,\soleq[1],-0.5,small,\soleq[1]
text red,\soleq[2],-0.5,small,\soleq[2]
circle \borne1,0,\diambornexclue,red
linewidth 2
segment \coordseg1,red
segment \coordseg2,red
linewidth \psize
point \borne1,0,red
point \borne2,0,red}
</div>
}
