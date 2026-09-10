target=optique2cv
#include "lang_titles.inc"
#include "lang_coul.inc"
\title{TITLE}

#include "author.inc"
\precision{10000}

\integer{f=-randint(3..7)}
\integer{a=randint(floor(\f/2)..2*floor(\f))}

\real{yB=randint(10*\a/3, 2*\a/3*10)/10}
real{yB=randint(10*\a, 4*\a/3*10)/10}
\integer{a=random(1,-1)*\a}
\real{yB=random(1,-1)*\yB}
\integer{a=\a=\f? \a-1}
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
\real{rangex1=1.2*\rangex1}
\real{rangex2=1.2*\rangex2}
\real{rangey=\a<>\f ? max( abs(\yB),abs(\yB1)):abs(\yB)}
\real{rangey=\rangey*1.5}
\real{prop= (\rangex2-\rangex1)/(2*\rangey)}
\integer{taille=600}
\real{prop=\taille*\prop^(-1)}
text{rangey= -\rangey,\rangey}
\text{listecouleur1=purple,orange,navy,skyblue}
\text{listecouleur=shuffle(\listecouleur1)}
\text{couleur1=item(1,\listecouleur)}
\text{couleur2=item(2,\listecouleur)}
\text{coula=randitem(\couleur1,\couleur2)}
\text{s=position(\coula, \listecouleur1)}
\text{coul=item(\s,\listefranc)}
\text{dashline=linewidth 1
dhline 0,\yB, grey
dhline 0,\yB1, grey}
\text{dessin=xrange \rangex1,\rangex2
yrange -\rangey*1.3,\rangey
hline 0,0, black
linewidth 4
vline 0,0,black
linewidth 1
text black, 0.2,-0.2,medium, O
arrow \rangex1+(\rangex2-\rangex1)/20,-\rangey*1.2,\rangex1+(\rangex2-\rangex1)/10,-\rangey*1.2,15, black
}
dpolyline red ,\a1,\yB1,0,\yB
\real{pos=\coula issametext \couleur1? min(0,\yB):min(0,\yB1)}
\text{textup=\coula issametext \couleur1?
textup black,\a,\pos,large,\coul:
textup black,\a1,\pos,large,\coul
}

\text{dessin = \a<>\f? \dessin
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
trange \rangex1,\rangex2
plot green, t, \eq1
linewidth 4
arrow \a,0,\a,\yB,6,\couleur1
arrow \a1,0,\a1,\yB1, 6,\couleur2
\textup
\dashline
}
polyline red, \a,\yB, 0,\yB,-\f,0,\a1,\yB1,\u,\c
polyline blue, \a,\yB,0,\yB1,2*(\a1),\yB1
polyline green, \a,\yB,\u,\u*(\yB)/(\a)
polyline blue, \f,0, \a,\yB,0,\yB1,\a1,\yB1,\u*\yB1
polyline green, \a,\yB,(\a1),\yB1,-(\a),-(\yB)
\text{dessin = \a=\f? \dessin
polyline red, \a,\yB, 0,\yB,-\f,0,\u,\c
polyline blue, \a,\yB
polyline green, \a,\yB,
polyline red, \a,\yB, 0,\yB,-\f,0
polyline blue, \f,0, \a,\yB,0
polyline green, \a,\yB,-(\a),-(\yB)
linewidth 4
arrow \a,0,\a,\yB,6,\couleur1,
arrow \a1,0, \a1,\yB1, 6,\couleur2
\textup
\dashline
}

\text{rep=\coula issametext \couleur1 and \a<0 ? 1}
\text{rep=\coula issametext \couleur2 and \a1<0 ? 4}
\text{rep=\coula issametext \couleur1 and \a>0 ? 2}
\text{rep=\coula issametext \couleur2 and \a1>0 ? 3}
#include "lang.inc"
\statement{\name_instruction
<ul><li>
\embed{reply 1,1}
</li><li>
\embed{reply 1,2}
</li><li>
\embed{reply 1,3}
</li><li>
\embed{reply 1,4}
</li></ul>
<div class="wimscenter">\draw{600,200}{\dessin}
</div>
}
\answer{\name_answertext}{\rep;\question}{type=radio}
