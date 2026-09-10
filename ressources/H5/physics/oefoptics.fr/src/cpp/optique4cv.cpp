target=optique4cv

#include "lang_titles.inc"
\title{TITLE}

#include "author.inc"
\precision{10000}

\integer{f=randint(3..5)}
\integer{a=randint(floor(\f/2)..floor(\f*3/2))}
\integer{a=\a=\f ? \a+1}
\real{yB=randint(10*\a/3, 2*\a/3*10)/10}
real{yB=randint(10*\a, 4*\a/3*10)/10}
\integer{a=random(1,-1)*\a}
\real{yB=random(1,-1)*\yB}
\integer{f=-(\f)}
\integer{f1=-(\f)}
\rational{a1=\a!=\f? 1/(1/(\a)-1/(\f)):100}

\real{yB1= \yB*(\a1)/(\a)}
\function{eq1=(\yB)/(\a)*t}
\function{eq2=(\yB1)/(-\f)*(t-(\f))}
\function{eq3=(\yB)/(\f)*(t+(\f))}
\real{u=\a!=\f? \a1*1.2:-2*\f}
\real{c=evalue(\eq3,t=\u)}
\text{rangex=\a<>\f? wims(sort numeric item \a1,\a,\f,-\f):wims(sort numeric item \a,\f,-\f) }
\real{rangex1= min(item(1,\rangex),-1)}
\real{rangex2= max(item(-1,\rangex),1)}
\real{rangex1=floor(1.2*\rangex1)}
\real{rangex2=ceil(1.2*\rangex2)}
\real{rangey=\a<>\f ? max( abs(\yB),abs(\yB1)):abs(\yB)}
\real{rangey=ceil(\rangey*1.5)}
\real{prop= (\rangex2-\rangex1)/(2*\rangey)}
\integer{taille=600}
\real{prop=\taille*\prop^(-1)}
text{rangey= -\rangey,\rangey}
\text{listecouleur=shuffle(purple,orange,navy,skyblue)}
\text{couleur1=item(1,\listecouleur)}
\text{couleur2=item(2,\listecouleur)}
\text{dashline=linewidth 1
dhline 0,\yB, grey
dhline 0,\yB1,grey}
\real{rangey1=-\rangey*1.3}
\text{dessin=xrange \rangex1,\rangex2
yrange \rangey1, \rangey
hline 0,0,black
arrow \rangex1+(\rangex2-\rangex1)/20,-\rangey*1.2,\rangex1+(\rangex2-\rangex1)/10,-\rangey*1.2,15, black
text \couleur1,\a+0.2,0,large, A
text \couleur2,\a1+0.2,\yB1,large, B'
text \couleur1, \a+0.2,\yB,large, B
text \couleur2, \a1+0.2,0,large, A'
text black, \rangex1,1,small,1
linewidth 1
arrow \a,0,\a,\yB,6,\couleur1
arrow \a1,0,\a1,\yB1,6, \couleur2
linewidth 1
parallel 0,-\rangey/20,0,\rangey/20, 1,0,50, blue
parallel 0,-\rangey/20,0,\rangey/20, -1,0,50, blue
\dashline
}
text black,\f,-0.2,large, F
text black,-(\f),-0.2,large, F'

\text{dessin1 = \a<>\f?
linewidth 4
vline 0,0,black
linewidth 1
text black, 0,-0.2,medium, O
trange \rangex1,\rangex2
plot green, t, \eq1
}
\text{dessinbis=parallel \rangex1,0,\rangex2,0, 0,(\rangey-\rangey1)/10,10 ,grey
parallel \rangex1,0,\rangex2,0, 0,-(\rangey-\rangey1)/10,10,grey
parallel 0,\rangey1,0, \rangey, 1,0,50,grey
parallel 0,\rangey1,0, \rangey, -1,0,50,grey}

\text{dessin2=\a<>\f?
dpolyline red,min(\a,0),\yB, 0,\yB
dpolyline red,-min(-\a,0),\yB, 0,\yB
dpolyline red ,-(\f),0,0,\yB
dpolyline red ,\a1,\yB1,0,\yB
polyline blue, 0,\yB1,abs(\u),\yB1
dpolyline blue, 0,\yB1,\u,\yB1
dpolyline blue ,0,\yB1,\a,\yB
dpolyline blue, 0,\yB1,\f,0
trange 0,\rangex2
plot red , t,\eq3
trange min(\a,0),0
plot red , t,\yB
trange min(-\a,0),0
plot red , t,\yB
trange \rangex1,0
plot blue, t,\eq2
text black,\f,-0.2,large, F
text black,-(\f),-0.2,large, F'
}
\text{dessin1 = \a=\f?
polyline red, \a,\yB, 0,\yB,-\f,0,\u,\c
polyline blue, \a,\yB
polyline green, \a,\yB,
polyline red, \a,\yB, 0,\yB,-\f,0
polyline blue, \f,0, \a,\yB,0
polyline green, \a,\yB,-(\a),-(\yB)
linewidth 4
segment \a,0,\a,\yB,\couleur1
textup black,\a,0,large, \couleur1
segment \a1,0, \couleur2
textup black,\a1,0,large, \couleur2
}
\integer{rep1=-(\rangex1)}
\steps{reply1
reply2}
#include "lang.inc"
\statement{\name_instruction

 \if{\step<=1}{\name_instruction1
 \embed{r1,5}
<p class="wimscenter">
\draw{600,200}{
\dessin
text black,\rangex1+0.2,-0.2,medium,O
vline \rangex1,0,black
}
</p>}
\if{\step>=2}{\name_instruction2 \embed{r2,5}
<p class="wimscenter">
\draw{600,200}{
  \dessin
  \dessinbis
hline black, 0,0
\dessin1
}
</p>
}
<div class="wims_instruction">
\name_warning
</div>
}
\answer{\name_answertext[1]}{\rep1}{type=numeric}
\answer{\name_answertext[1]}{\f1}{type=numeric}
\feedback{1=1}{
<p class="wimscenter">
\draw{600,200}{
\dessin
\dessin1
\dessin2
}
</p>}
