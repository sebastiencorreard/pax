target=antecedent
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
/** version nov 2006 - modif casf=1, infinite d'antécédents **/

\integer{xsize=random(8,10,12)}
\integer{ysize=\xsize}
\integer{u=0.25*\xsize}
\integer{v=0.75*\xsize}
\integer{w=0.5*\xsize}

\integer{casf=random(1..5)}

\integer{sign=random(-1,1)}
\integer{a1=random(-\xsize+1..-\v)}
\integer{a2=\sign*random(\u-1..\w+1)}
\integer{a3=-\sign*random(\u..\w+1)}
\integer{a4=random(\v-1..\xsize-1)}
\integer{b1=\casf=1?-random(\u-1..\v+1):\sign*random(\v-1..\xsize-1)}
\integer{b2=-\sign*random(1..\w+1)}
\integer{b3=\sign*random(1..\w+1)}
\integer{b4=\casf=1?random(\u-1..\v+1):-\sign*random(\v-1..\xsize-1)}

/** definition des fonctions ; tirage aléatoire (casf) **/
/** f(a3)= b3 avec coord entières sauf casf=1,5 **/

/** fct affine escalier (casf=1) ou polynomes (casf=2, 3)**/
/** casf = 1 droite (A1A4) avec b1 < y < b4 **/
\function{f=(\casf=1)?min(max(\b1*(x-\a4)/(\a1-\a4) + \b4*(x-\a1)/(\a4-\a1),\b1),\b4)}
\function{f=\casf=2?
 \b1*(x-\a3)*(x-\a2)/((\a1-\a3)*(\a1-\a2))+ \b3*(x-\a2)*(x-\a1)/((\a3-\a2)*(\a3-\a1)) + \b2*(x-\a3)*(x-\a1)/((\a2-\a1)*(\a2-\a3))}
\function{f=\casf=3?
\b1*(x-\a2)*(x-\a3)*(x-\a4)/((\a1-\a2)*(\a1-\a3)*(\a1-\a4)) + \b2*(x-\a1)*(x-\a3)*(x-\a4)/((\a2-\a1)*(\a2-\a3)*(\a2-\a4))+ \b3*(x-\a1)*(x-\a2)*(x-\a4)/((\a3-\a2)*(\a3-\a1)*(\a3-\a4))+ \b4*(x-\a1)*(x-\a2)*(x-\a3)/((\a4-\a2)*(\a4-\a1)*(\a4-\a3))}

/** fctions rationnelles casf==4,5 **/
\function{f=(\casf=4)?\sign*(\a3+\xsize+1)/(x+\xsize+1) + \b3-\sign}
\function{f=\casf=5? \b3 + \b1/(x-\a2)}

/** les questions et réponses **/
\integer{b0=evaluate(\f,x=-\xsize)}

/** question 1 : a3 est un antécedent de b3 **/
\real{rep1=(\casf!=5 and \casf!=1)?\b3:
pari(0.1*floor(10*evaluate(\f,x=\a3)))}

/** question 1Bis : a2 est-il un antécédent de b2 ? **/
\integer{x2=\casf=5?\a2+\sign*random(2..\u):\a2}
\real{fx2=evaluate(\f,x=\x2)}
\integer{sign2=fx2>0?1:-1}
\integer{rep1Bis=(\fx2-\b2<0.1 and \fx2-\b2>-0.1)?1:2}
\text{construct1Bis=segment \x2,0,\x2,\fx2, green
arrow \x2,\fx2,0,\fx2,8, green
text green,\x2,-\sign2*0.8, medium,\x2
}

/** question 2 : antecedents de y2 **/
/** NB : solve, avec des fctions ratio, calcule la val int **/
/** casf=5, asympt x=a2 et y=b3**/
/** casf=1 , si y2 = b1 ou b4, on a une infinité d'antécédents (rep2=-1)**/

\integer{y2=\casf!=5?\sign*random(1..\v+1):\b3+\sign*random(1..\u+1)}

\text{anty2=\casf!=5?solve(\f-\y2,x=-\xsize..\xsize):
solve((\b3-\y2)*(x-\a2)+\b1,x=-\xsize..\xsize)}
\integer{rep2=(\casf=1 and (\y2=\b1 or \y2=\b4))?-1:items(\anty2)}
\text{trep2=(\rep2=-1)?infinité|infinite:\rep2}
\text{construct2 = \rep2==1? arrow \anty2[1],\y2,\anty2[1],0,8, blue
point \anty2[1],\y2,blue}
\text{construct2 = \rep2==2? arrow \anty2[1],\y2,\anty2[1],0,8, blue
arrow \anty2[2],\y2,\anty2[2],0,8, blue
point \anty2[1],\y2,blue
point \anty2[2],\y2,blue }
\text{construct2 = \rep2==3? arrow \anty2[1],\y2,\anty2[1],0,8, blue
arrow \anty2[2],\y2,\anty2[2],0,8, blue
arrow \anty2[3],\y2,\anty2[3],0,8, blue
point \anty2[1],\y2,blue
point \anty2[2],\y2,blue
point \anty2[3],\y2,blue}

/** question 3 , equation f(x) = k **/
/** casf=5 : cas particulier pour solve (cf plus haut) **/
/** rectifier k casf==1 ??? **/
\integer{k=\casf!=5?(-\sign)*random(1..\w+1):\b3-\sign*random(1..\w-2)}
\integer{k=(\casf=1 and \k=\b1)?\b1+random(-1,1)}
\integer{k=(\casf=1 and \k=\b4)?\b4+random(-1,1)}
\text{antk=\casf!=5?solve(\f-\k,x=-\xsize..\xsize):
solve((\b3-\k)*(x-\a2)+\b1,x=-\xsize..\xsize)}
\integer{rep3=items(\antk)}
\text{construct3 = \rep3==1? arrow \antk[1],\k,\antk[1],0,8,red
point \antk[1],\k,red}
\text{construct3 = \rep3==2? arrow \antk[1],\k,\antk[1],0,8,red
arrow \antk[2],\k,\antk[2],0,8,red
point \antk[1],\k,red
point \antk[2],\k,red}
\text{construct3 = \rep3==3? arrow \antk[1],\k,\antk[1],0,8,red
arrow \antk[2],\k,\antk[2],0,8, red
arrow \antk[3],\k,\antk[3],0,8, red
point \antk[1],\k,red
point \antk[2],\k,red
point \antk[3],\k,red}

/** preparation du graphique **/

\text{coordC=-\xsize+0.5,\b0}

\integer{ysize=(\k==\xsize or \k==-\xsize)?\xsize+1}
\text{ticks=text black,-1, -20, small,-20
text black,-1, -15, small,-15
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
text blue,\coordC,medium,C
linewidth 3
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
point 0,20,black
}
\statement{
<div class="wims_columns">
  <div class="medium_size img_col"><div class="wimscenter">
\draw{350,350}{
xrange -\xsize,\xsize
yrange -\ysize,\ysize
parallel -\xsize,-\ysize,-\xsize,\ysize,1,0, 2*\xsize+1, grey
parallel -\xsize,-\ysize,\xsize,-\ysize,0,1, 2*\ysize+1, grey
hline 0,0,black
vline 0,0,black
arrow 0,0,1,0,8, black
arrow 0,0,0,1,8, black
text black,-0.5,-0.2,small,O
text black,1,-0.3,small,I
text black,-0.5,1,small,J
\ticks
text blue,coordC,medium, C
linewidth 1
plot blue,\f
linewidth 5
plot \a3,\rep1,blue
}
</div></div>
  <div class="medium_size text_col">
<p>
\name_enonce[1]
\if{\casf!=5}{\name_enonce[2] \(I) = [-\xsize ,\xsize]}{
  \name_enonce[3] \(I\) = &#91;-\xsize ,\a2&#91; \cup &#93; \a2,\xsize &#93;}
\name_enonce[4] \(C\).
\name_precision (\a3, \rep1).
</p>
\name_question[1;]:
<ul><li>
 \a3 \name_question[2;1] \embed{reply1,4} \name_question[2;2] \(f\).
</li><li>
 \x2 \embed{reply2} \name_question[3;1] \b2 \name_question[3;2] \(f\).
</li><li>
\y2 \name_question[4;1] \embed{reply3, 8} \name_question[4;2] \(f\).
</li><li>
\name_question[5;1] \(f(x) = \k\) \name_question[5;2] \embed{reply4,4}
` \name_question[5;3] [-\xsize ,\xsize].
</li>
</ul>
</div></div>
}

\hint{\name_hint}

\answer{}{\rep1}{type=numeric}
\answer{\a2 antécédent de \b2 dans I}{\rep1Bis ; \name_choix}{type=radio}
\answer{}{\trep2}{type=atext}
\answer{}{\rep3}{type=numeric}

/** montrer la lecture graphique solution **/

\solution{
<div class="wims_columns">
  <div class="medium_size img_col">
  <div class="wimscenter">
\draw{350,350}{
xrange -\xsize,\xsize
yrange -\ysize,\ysize
parallel -\xsize,-\ysize,-\xsize,\ysize,1,0, 2*\xsize+1, grey
parallel -\xsize,-\ysize,\xsize,-\ysize,0,1, 2*\ysize+1, grey
hline 0,0,black
vline 0,0,black
arrow 0,0,1,0,8, black
arrow 0,0,0,1,8, black
text black,-0.5,-0.3,small,O
text black,1,-0.3,small,I
text black,-0.5,1,small,J
linewidth 1
plot black, \f
linewidth 1.5
plot blue,\y2
\construct2
plot red,\k
\construct1Bis
\construct3
segment \a3, \rep1,\a3,0, green
arrow \a3, \rep1,0, \rep1,8, green
text green,\a3,-\sign*0.8, medium, \a3
text green,\sign-0.5,\rep1 + 0.2, medium, \rep1
text blue,\xsize-3,\y2+0.8,medium, y= \y2
text red,-\xsize+2,\k+0.8,medium, y= \k
linewidth 6
point \a3,\rep1,green}
</div></div>
<div class="medium_size text_col">
<p style="color:green">
\a3 \name_question[2;] \rep1 \name_by \(f) \name_sol1[3] \(f(\a3) = \rep1).
</p><p style="color:green">
\x2 \if{\rep1Bis=1}{\name_choix[1]}{\name_choix[2]} \name_sol1[2] \b2 \name_by \(f)
\name_car \(f(\x2)) \if{\rep1Bis==1}{=}{\(\neq)} \b2.
</p>
<p style="color:blue"">
\name_sol2[1] \(y = \y2) \name_sol2[2]
\if{\rep2=1}{\name_sol2[3]}{\if{\rep2=-1}{\name_sol2[4]}{\rep2} \name_sol2[5]},
 \y2 \name_sol2[6] xxxx
\if{\rep2=1}{\name_sol2[7]}{
  \if{\rep2=-1}{\name_sol2[8]}{\rep2 \name_sol2[9]}
  }
 \name_by \(f) \name_in \(I\).
 </p><p style="color:red">
\name_sol2[1] \(y = \k\) \if{\rep3==0}{\name_sol2[11]}
{\name_sol2[6] \rep3 \name_sol2[12]}
\name_sol2[13] \(f(x) = \k\)
\if{\rep3==0}{\name_sol2[14]}{\name_has \rep3 \name_sol2[15]} \name_in \(I).
</p><p>
\name_sol3
</p>
</div></div>}
