target=nbdergraph nbdergraph2
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
(version fevrier 05)

\integer{cas=random(1..4)}
\integer{xsize=random(4..6)}
\integer{ysize=\xsize}

\integer{sign1=random(-1,1)}
\integer{sign2=random(-1,1)}

/** cas 1 : Cf hyperbole et tangente en A3 **/

\integer{a1=\cas==1?\sign1*random(-\xsize..-0.5*\xsize-1)}
\integer{b1=\cas==1?\sign2*random(2..0.5*\ysize)}
\integer{a3=\cas==1?random(-0.5*\xsize+1..0.5*\xsize-1)}
\integer{b3=\cas==1?\sign2*random(1..0.5*\ysize-1)}
\function{f=\cas==1? \b3*(\a3-\a1)/(x-\a1)}
\text{ensdef=\cas==1?\(\RR\setminus\{\a1\})}

/** cas 2 : Cf cubique et Cg sa tangente en A3 proche du sommet **/

\integer{a1=\cas==2?random(-\xsize..-0.5*\xsize-2)}
\integer{a2=\cas==2?\sign2*random(2..0.5*\xsize-1)}
\integer{a3=\cas==2?-\sign2*random(2..0.5*\xsize-1)}
\integer{a4=\cas==2?random(0.5*\xsize+2..\xsize)}
\integer{b1=\cas==2?random(-0.5*\ysize+1..0.5*\ysize-1)}
\integer{b4=\cas==2?\b1+ random(-1..1)}
\integer{b3=\cas==2?\b1+\sign1*random(2..0.5*\ysize-1)}
\integer{b2=\cas==2?\b1-\sign1*random(2..0.5*\ysize-1)}

\function{f=\cas==2?\b1*(x-\a2)*(x-\a3)*(x-\a4)/((\a1-\a2)*(\a1-\a3)*(\a1-\a4)) + \b2*(x-\a1)*(x-\a3)*(x-\a4)/((\a2-\a1)*(\a2-\a3)*(\a2-\a4))+ \b3*(x-\a1)*(x-\a2)*(x-\a4)/((\a3-\a2)*(\a3-\a1)*(\a3-\a4))+ \b4*(x-\a1)*(x-\a2)*(x-\a3)/((\a4-\a2)*(\a4-\a1)*(\a4-\a3))}


/** cas 3 : Cf parabole et Cg sa tangente proche d'un chge var **/

\integer{a1=\cas==3?-\xsize+1}
\integer{a3=\cas==3?\sign1*random(2..0.5*\xsize)}
\integer{a4=\cas==3?\xsize-1}
\rational{b1=\cas==3?\sign1*0.5*random(0..\ysize-1)}
\rational{b4=\cas==3?-\sign1*0.5*random(0..\ysize-1)}
\rational{b3=\cas==3?\b1+(\b4-\b1)*(\a3-\a1)/(\a4-\a1)+
\sign2*0.5*random(2..5)
}

/** cas 4 : Cf parabole et Cg sa tangente proche d'un chge var **/

\integer{a1=\cas==4?-\xsize+1}
\integer{a3=\cas==4?\sign1*random(2..0.5*\xsize)}
\integer{a4=\cas==4?\xsize-1}
\rational{b1=\cas==4?\sign1*random(0.5\ysize-1..\ysize-1)}
\rational{b4=\cas==4?\sign1*random(0.5\ysize-1..\ysize-1)}
\rational{b3=\cas==4?-\sign1*random(0.5\ysize-1..1)}

\function{f=\cas>2? \b3*(x-\a1)*(x-\a4)/((\a3-\a4)*(\a3-\a1))+ \b1*(x-\a3)*(x-\a4)/((\a1-\a3)*(\a1-\a4)) + \b4*(x-\a1)*(x-\a3)/((\a4-\a3)*(\a4-\a1))}

\text{ensdef=\cas>1?\(\,\RR)}

\function{df=diff(\f,x)}
\real{m=evaluate(\df,x=\a3)}
\function{g=\m*(x-\a3)+ \b3}

/** préparation du graphique **/

\integer{ysize=\cas==3?\xsize+1}

/** si b3 non entier, afficher une val décimale de b3 pour yA **/
\real{yA=cas<3?\b3:pari(floor(100*\b3)/100)}


\real{labelf=evaluate(\f, x=-\xsize+0.5)}

\real{absm=pari(abs(\m))}
\integer{deltax=\absm<1?2:1}
\integer{x3=\a3+\deltax}
\real{h=evaluate(\g, x=\x3)}
\integer{change=(\h<-\xsize+1 or \h>\xsize-1 or \x3<-\xsize+1 or
\x3>\xsize-1)?1:0}
\integer{x3=\change==1?\a3-\deltax}
\real{y3=evaluate(\g, x=\x3)}
\real{y3=pari(floor(100*\y3)/100)}

\text{labelA=text red, \a3, \b3 +0.5, medium, A
linewidth 3
point \a3, \b3,red}
\text{labelB=text red, \x3, \y3 +0.5, medium, B
linewidth 3
point \x3, \y3,red}

/** val. de pente m arrondie au dixieme **/
\real{m0=(\y3-\yA)/(\x3-\a3)}
\real{m1=pari(floor(10*\m0)/10)}
\real{m2=pari(ceil(10*\m0)/10)}
\real{mi=(\m1+\m2)/2}
\real{rep=\m0<\mi?\m1:\m2}

\text{ticks=text black, -1, -20, small, -20
text black, -1, -15, small, -15
text black, -1,-10,small, -10
text black, -1,-5,small, -5
text black, -1, 5,small, 5
text black, -1, 10, small, 10
text black, -1, 15, small, 15
text black, -1, 20, small, 20
text black, -10, -0.2, small, -10
text black, -5, -0.2, small, -5
text black, 5, -0.2,small, 5
text black, 10, -0.2,small, 10
linewidth 3
point 1,0, black
point 0,1, black
point -10,0, black
point -5,0, black
point 5, 0, black
point 10, 0, black
point 0, -20, black
point 0, -15, black
point 0, -10, black
point 0, -5, black
point 0, 5, black
point 0, 10, black
point 0, 15, black
point 0, 20, black
}
\text{enonce=wims(replace internal CCCC by C in \name_enonce)}
\text{feed2=wims(replace internal MMMM by \m0 in \name_feed2)}
\statement{
<div class="wims_columns">
<div class="medium_size img_col">
<div class="wimscenter">
\draw{380,380}{
xrange -\xsize,\xsize
yrange -\ysize,\ysize
parallel -\xsize,-\ysize,-\xsize,\ysize,1,0, 2*\xsize+1, grey
parallel -\xsize,-\ysize,\xsize,-\ysize,0,1, 2*\ysize+1, grey
hline 0,0,black
vline 0,0,black
#if defined TARGET_nbdergraph
ancien : arrow 0,0,1,0,8, black
ancien : arrow 0,0,0,1,8, black
#endif
#if defined TARGET_nbdergraph2
line 0,0,1,0,8, black
line 0,0,0,1,8, black
#endif
text black, -0.5,-0.3,small, O
text black, 1,-0.3,small, I
text black, -0.5,1,small, J
\labelA
\labelB
text blue, -\xsize+0.5,\labelf, medium, y=f(x)
\ticks
linewidth 1.5
plot blue, \f
plot green, \g
}
</div></div>
<div class="medium_size text_col">
<p>\enonce[1] \((O; I, J )\). \enonce[2] \ensdef.
  \enonce[3] (\a3, \yA).</p>
<div class="wims_question">
#if defined TARGET_nbdergraph
#endif
#if defined TARGET_nbdergraph
\name_question[1] (\x3, \y3), \name_question[2] \(f'(\a3)\) \name_question[3]
#endif
#if defined TARGET_nbdergraph2
\name_question[1 ](\x3, \y3).
\name_question[2]? \name_question[3]
#endif
<div class="wimscenter">
#if defined TARGET_nbdergraph
<label for="reply1">\(f'(\a3)\) =</label> \embed{reply1, 10}
#endif
#if defined TARGET_nbdergraph2
<label for="reply2">\(f'\)</label>(\embed{reply2, 3})
<label for="reply1"> = </label>\embed{reply1, 10}
#endif
</div>
</div>
</div>
</div>
}
\hint{\name_hint}

\answer{\name_answer \(f'(\a3)\) :}{\rep}{type = numeric}{option=comma}
#if defined TARGET_nbdergraph2
\answer{}{\a3}{type=formal}
#endif
\integer{bonsigne=\m!=0 and \reply1*\m<0?0:1}
\feedback{\bonsigne==0}{\name_feed1[1] \(\a3\), \name_feed1[2] \(f'(\a3)\) \name_feed1[3]
<br>\name_feed1[4] \(\a3\), \name_feed1[5] \(f'(\a3)\) \name_feed1[6]}

\feedback{0==0}{\feed2[1] \(f'(\a3)) \feed2[2] \rep.
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
arrow \a3,\b3,\x3,\b3, 8, red
arrow \x3,\b3,\x3,\y3, 8, red
text black, -0.5,-0.3,small, O
text black, 1,-0.3,small, I
text black, -0.5,1,small, J
text blue, \xsize-2,\labelf, medium, y=f(x)
text green, -\xsize+2,\labelg, medium, T
\labelA
\labelB
linewidth 1.5
plot blue, \f
plot green, \g
linewidth 3
point \a3, \b3, red}
</div>
}
