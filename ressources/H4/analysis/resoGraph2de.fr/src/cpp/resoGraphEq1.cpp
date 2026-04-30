target=resoGraphEq1
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
/** version nov. 2004 **/

\integer{cas=random(1..5)}
\integer{xsize=cas!=3?4*random(2..4):4*random(2,3)}
\integer{ysize=random(8..12)}
\integer{sign=random(-1,1)}

\integer{a1=random(-\xsize+1..-0.5*\xsize-1)}
\integer{b1=random(-0.5*\ysize..0.5*\ysize)}
\integer{a2=random(-0.5*\xsize+1..0)}
\integer{a3=random(2..0.5*\xsize+1)}
\integer{b3=random(-0.5*\ysize..0.5*\ysize)}
\integer{a4=random(0.5*\xsize+1..\xsize-1)}

\text{dot=.}

/** cas 1 : deux simples droites (A1A3A4) et (A3A4') **/

\integer{a1=\cas==1?-\xsize}
\integer{a4=\cas==1?\xsize}
\integer{b4=\cas==1?random(-0.5*\ysize..0.5*\ysize+1)}
\integer{b1=\cas==1?random(-0.5*\ysize-1..0.5*\ysize)}
\integer{a3=\cas==1?random(-\xsize+2..\xsize-2)}
\rational{b3=\cas==1?\b1+(\a3-\a1)*(\b4-\b1)/(\a4-\a1)}
\rational{d1=\cas==1?\b1+\sign*random(1..0.5*\ysize-1)}
\function{f=\cas==1?\b4*(x-\a1)/(\a4-\a1) + \b1*(x-\a4)/(\a1-\a4)}
\function{g=\cas==1?\d1*(x-\a3)/(\a1-\a3) + \b3*(x-\a1)/(\a3-\a1)}
\text{sol=\cas==1?\a3}
\text{ysol=\cas==1?\b3}

/** cas 2 : Cf parabole passant par A1 A2 et A3 et
Cg la droite A1 A3 **/

\rational{a2=\cas==2?0.5*(\a1+\a3)}
\integer{b1=\cas==2?\sign*random(1..0.5*\ysize)}
\integer{b3=\cas==2?\sign*random(0..0.5*\ysize-1)}
\rational{b2=\cas==2?0.5*(\b1+\b3)-\sign*random(2..0.5*\ysize)}

\function{g=\cas==2?\b1*(x-\a3)/(\a1-\a3) + \b3*(x-\a1)/(\a3-\a1)}
\function{f=\cas==2? \b2*(x-\a1)*(x-\a3)/((\a2-\a3)*(\a2-\a1))+ \b1*(x-\a2)*(x-\a3)/((\a1-\a2)*(\a1-\a3)) + \b3*(x-\a1)*(x-\a2)/((\a3-\a2)*(\a3-\a1))}

\text{sol=\cas==2?\a1,\a3}
\text{ysol=\cas==2?\b1,\b3}

/** cas 3 : Cf parabole passant par A1 A3 A4 et Cg tangente en A3 **/

\integer{a3=\cas==3?random(-0.5*\xsize+1..0.5*\xsize-1)}
\integer{b3=\cas==3?(\b1)+\sign*random(2..0.5*\ysize-2)}
\integer{b4=\cas==3?(\b1)-\sign*random(2..0.5*\ysize-2)}

\function{f=\cas==3? \b4*(x-\a1)*(x-\a3)/((\a4-\a3)*(\a4-\a1))+ \b1*(x-\a4)*(x-\a3)/((\a1-\a4)*(\a1-\a3)) + \b3*(x-\a1)*(x-\a4)/((\a3-\a4)*(\a3-\a1))}
\function{df=\cas==3?diff(\f,x)}
\real{m3=\cas==3?evaluate(\df,x=\a3)}
\function{g=\cas==3?\m3*(x-\a3)+ \b3}
\text{sol=\cas==3?\a3}
\text{ysol=\cas==3?\b3}

/** cas 4 : g parabole passant par A1 A2 A4 et Cf parabole A1 A2' et A4 de sens inversé **/

\integer{u=\cas==4?0.5*\ysize}

\integer{a1=\cas==4?random(-\xsize+1..-0.5*\xsize+1)}
\integer{a4=\cas==4?random(0.5*\xsize-1..\xsize-1)}
\integer{b4=\cas==4?random(0.5*\ysize..0.5*\ysize)}
\rational{a2=\cas==4?0.5*(\a1+\a4)+random(-1..1)}
\rational{b2=\cas==4?0.5*(\b1+\b4)+\sign*random(1..\u-1)}
\rational{d2=\cas==4?0.5*(\b1+\b4)-\sign**random(1..\u-1)}

\function{g=\cas==4? \b2*(x-\a1)*(x-\a4)/((\a2-\a4)*(\a2-\a1))+ \b1*(x-\a2)*(x-\a4)/((\a1-\a2)*(\a1-\a4)) + \b4*(x-\a1)*(x-\a2)/((\a4-\a2)*(\a4-\a1))}
\function{f=\cas==4? \d2*(x-\a1)*(x-\a4)/((\a2-\a4)*(\a2-\a1))+ \b1*(x-\a2)*(x-\a4)/((\a1-\a2)*(\a1-\a4)) + \b4*(x-\a1)*(x-\a2)/((\a4-\a2)*(\a4-\a1))}

\text{sol=\cas==4?\a1,\a4}
\text{ysol=\cas==4?\b1,\b4}

/** cas 5 : g arc parabole A1 A2 A3 croisant arc parabole f A1' A2 et A4 de sens inversé **/

\integer{a4=\cas==5?\a3}
\integer{b4=\cas==5?\b3+\sign*random(2..4)}
\rational{b2=\cas==5?0.5*(\b1+\b4)+\sign*random(1..3)}
\integer{d1=\cas==5?\b1-\sign*random(1..4)}

\function{f=\cas==5? \b2*(x-\a1)*(x-\a4)/((\a2-\a4)*(\a2-\a1))+ \d1*(x-\a2)*(x-\a4)/((\a1-\a2)*(\a1-\a4)) + \b4*(x-\a1)*(x-\a2)/((\a4-\a2)*(\a4-\a1))}
\function{g=\cas==5? \b2*(x-\a1)*(x-\a3)/((\a2-\a3)*(\a2-\a1))+ \b1*(x-\a2)*(x-\a3)/((\a1-\a2)*(\a1-\a3)) + \b3*(x-\a1)*(x-\a2)/((\a3-\a2)*(\a3-\a1))}
\text{sol=\cas==5?\a2}
\text{ysol=\cas==5?\b2}

\integer{n=items(\sol)}

/** preparation des graphiques **/

\text{black=120,120,120}
\real{labelf=evaluate(\f,x=0.5*\xsize)}
\real{labelg=evaluate(\g,x=-0.5*\xsize)}
\real{sign1=\ysol[1]<0?1:0}
\real{sign2=\ysol[2]<0?1:0}
\real{sign3=\ysol[3]<0?1:0}
\text{labelsol=\n==1?darrow \sol[1],\ysol[1],\sol[1],0,8,red
text red,\sol[1],\sign1*0.5,small,\sol[1]
linewidth 4
point \sol[1],\ysol[1],red
point \sol[1],0,red
}
\text{labelsol=\n==2?darrow \sol[1],\ysol[1],\sol[1],0,8,red
darrow \sol[2],\ysol[2],\sol[2],0,8,red
text red,\sol[1],\sign1*0.5,small,\sol[1]
text red,\sol[2],\sign2*0.5,small,\sol[2]
linewidth 4
point \sol[1],\ysol[1],red
point \sol[1],0,red
point \sol[2],\ysol[2],red
point \sol[2],0,red}
\text{labelsol=\n==3?darrow \sol[1],\ysol[1],\sol[1] ,0,8,red
text red,\sol[1],\sign1*0.5,small,\sol[1]
darrow \sol[2],\ysol[2],\sol[2] ,0,8,red
darrow \sol[3],\ysol[3],\sol[3] ,0,8,red
text red,\sol[2],\sign2*0.5,small,\sol[2]
text red,\sol[3],\sign3*0.5,small,\sol[3]
linewidth 4
point \sol[1],\ysol[1],red
point \sol[1],0,red
point \sol[2],\ysol[2],red
point \sol[2],0,red
point \sol[3],\ysol[3],red
point \sol[3],0,red
}
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
point 1,0,black
point 0,1,black
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
\statement{<div class="wims_columns">
  <div class="medium_size img_col">
<div class="wimscenter">
\draw{400,400}{
xrange -\xsize,\xsize
yrange -\ysize,\ysize
parallel -\xsize,-\ysize,-\xsize,\ysize,1,0,2*\xsize+1,grey
parallel -\xsize,-\ysize,\xsize,-\ysize,0,1,2*\ysize+1,grey
hline 0,0,\black
vline 0,0,\black
arrow 0,0,1,0,8,\black
arrow 0,0,0,1,8,\black
text black,-0.5,-0.3,small,O
text black,-0.7,1,small,J
text black,1,-0.3,small,I
text blue,0.5*\xsize,\labelf,medium,y=f(x)
text green,-0.5*\xsize,\labelg,medium,y=g(x)
\ticks
linewidth 1.5
plot blue,\f
plot green,\g}
  </div></div>
  <div class="medium_size text_col">
<p>\name_enonce1</p>
<p>
\name_enonce2[1;] [-\xsize, \xsize].
\name_enonce2[2;]
\name_enonce2[3;]
</p>
<div class="wimscenter">\name_question: \embed{reply1,10} </div>
</div></div>
}

\hint{\name_hint}
\answer{\name_answer}{\sol}{type = set}

/** afficher les constructions graphiques en solution **/
\text{repOK = wims(listintersect \sol and \reply1)}
\integer{nbrepOK = items(\repOK)}

\condition{\name_cond}{\nbrepOK!=0}

\feedback{\dot isin \reply1}{<b>\name_arrondi:</b>
<span style="color:red">\name_feed1</span>}

\feedback{0==0}{\name_feed2:
<div class="wimscenter">
\draw{350,350}{
xrange -\xsize,\xsize
yrange -\ysize,\ysize
parallel -\xsize,-\ysize,-\xsize,\ysize,1,0,2*\xsize+1,grey
parallel -\xsize,-\ysize,\xsize,-\ysize,0,1,2*\ysize+1,grey
hline 0,0,\black
vline 0,0,\black
arrow 0,0,1,0,8,\black
arrow 0,0,0,1,8,\black
text \black,-0.5,-0.3,small,O
text \black,1,-0.3,small,I
text \black,-0.7,1,small,J
text blue,0.5*\xsize,\labelf,medium,y=f(x)
text green,-0.5*\xsize,\labelg,medium,y=g(x)
linewidth 1.5
plot blue,\f
plot green,\g
\labelsol
}</div>
}
