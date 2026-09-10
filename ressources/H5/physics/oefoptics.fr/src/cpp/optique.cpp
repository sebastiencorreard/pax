target=optique1 optique2 optique3 foyer foyercalcul optique4 foyercv optique3cv optique3cv2

#include "lang_titles.inc"
#include "lang_coul.inc"
\title{TITLE}
confparm1 : 1 conv 2 div 3 divergente convergente
\integer{Ndiv =\confparm1=1 ? -1: 1}
\integer{Ndiv = \confparm1= or \confparm1 = 3 ? randitem(1,-1)}

#if defined TARGET_optique1
\integer{Ndiv = randitem(1,-1)}
#endif
#if defined TARGET_optique2
 \text{mot=1}
#endif

#include "author.inc"
\precision{10000}

\integer{f=randint(3..6)}
\integer{a=randint(floor(abs(\f/2))..2*floor(abs(\f)))}
\real{yB=randint(10*\a/3, 2*\a/3*10)/10}
\integer{a=random(1,-1)*\a}

\real{yB=random(1,-1)*\yB}
\integer{f=\f*(\Ndiv)}
#if defined TARGET_optique2
\integer{a=\a=\f? \a-1}
#endif
\rational{a1=\a!=\f? 1/(1/(\a)-1/(\f)):100}
\rational{yB1= \yB*(\a1)/(\a)}

\function{eq1=(\yB)/(\a)*t}
\function{eq2=(\yB1)/(-\f)*(t-(\f))}
\function{eq3=(\yB)/(\f)*(t+(\f))}
\rational{u=\a!=\f? \a1*1.2:-2*\f}
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
\text{listecouleur1=purple,orange,navy,skyblue}
\text{listecouleur=shuffle(\listecouleur1)}
\text{couleur1=item(1,\listecouleur)}
\text{couleur2=item(2,\listecouleur)}
\text{coula=\couleur1}
\text{s=position(\coula, \listecouleur1)}
\text{listefranc=\listefranc=? \listecouleur}
\text{coul=item(\s,\listefranc)}
\real{rangey1=-\rangey*1.3}
\real{rangey2=\rangey}
\text{dessin=xrange \rangex1,\rangex2
  yrange \rangey1,\rangey2
  hline 0,0, black
  linewidth 1
  arrow \rangex1+(\rangex2-\rangex1)/20,-\rangey*1.2,\rangex1+(\rangex2-\rangex1)/10,-\rangey*1.2,15, black
}
\text{dashline=linewidth 1
dhline 0,\yB, grey
dhline 0,\yB1, grey}
#if defined TARGET_optique1 || defined TARGET_optique2 || defined TARGET_optique3 || defined TARGET_optique3cv || defined TARGET_optique3cv2 || defined TARGET_foyer || defined TARGET_foyercv
  dessin de la lentille
\text{dessin = \dessin
  linewidth 4
  vline 0,0,black
  linewidth 1
  text black, 0.2,-0.2,medium, O
  }
#endif
#if defined TARGET_foyer || defined TARGET_foyercv || defined TARGET_foyercalcul || defined TARGET_optique4
  echelle + text A, ..
\text{dessin=\dessin
  parallel 0,-\rangey/20,0,\rangey/20, 1,0,50, blue
  parallel 0,-\rangey/20,0,\rangey/20, -1,0,50, blue
  text \couleur1,\a+0.1,0,large, A
  text \couleur2,\a1+0.1,\yB1,large, B'
  text \couleur1, \a+0.1,\yB,large, B
  text \couleur2, \a1+0.1,0,large, A'
  \dashline
  }
#endif
#if defined TARGET_optique1 ||defined TARGET_optique2 || defined TARGET_optique3 || defined TARGET_optique3cv || defined TARGET_optique3cv2
  dessin des rayons
  rouge incident parallèle à l'axe
  bleu émergent parallèle à l'axe
  vert passant par le centre optique
\text{dessin = \a<>\f ? \dessin
  dpolyline red,min(\a,0),\yB, 0,\yB
  dpolyline red,-min(-\a,0),\yB, 0,\yB
  dpolyline red, -(\f),0,0,\yB
  dpolyline red, \a1,\yB1,0,\yB
  dpolyline blue, 0,\yB1,\u,\yB1
  dpolyline blue, 0,\yB1,\a,\yB
  dpolyline blue, 0,\yB1,\f,0}
\text{dessin = \a=\f? \dessin
  polyline red, \a,\yB, 0,\yB,-\f,0,\u,\c
  polyline blue, \a,\yB
  polyline green, \a,\yB,
  polyline red, \a,\yB, 0,\yB,-\f,0
  polyline blue, \f,0, \a,\yB,0
  polyline green, \a,\yB,-(\a),-(\yB)}
#endif
#if defined TARGET_optique1 ||defined TARGET_optique2 || defined TARGET_optique3 || defined TARGET_foyer || defined TARGET_optique3cv || defined TARGET_optique3cv2
\if{\a!=0}{
  \text{trangechoice= \a<0? trange \a,0
  plot red, t,\yB:
  trange -\a,0
  plot red, t,\yB}
}
\text{dessin = \a<>\f ? \dessin
  polyline blue, 0,\yB1,abs(\u),\yB1
  trange 0,\rangex2
  plot red, t,\eq3
  \trangechoice
  trange \rangex1,0
  plot blue, t,\eq2
  trange \rangex1,\rangex2
  plot green, t, \eq1
}
#endif
#if defined TARGET_optique1 || defined TARGET_foyer || defined TARGET_foyercv || defined TARGET_foyercalcul
  dessin des objet et image
\text{dessin = \a<>\f ? \dessin
  linewidth 4
  segment \a,0,\a,\yB,\couleur1
  segment \a1,0,\a1,\yB1, \couleur2
  \dashline
}
#endif
#if defined TARGET_optique2 || defined TARGET_optique4
  \real{pos=min(0,\yB)}
\text{textup=\mot=1? textup black,\a,\pos,large,\coul}
\text{dessin = \a<>\f ? \dessin
  linewidth 4
  arrow \a,0,\a,\yB,6,\couleur1
  arrow \a1,0,\a1,\yB1, 6,\couleur2
  \textup
  \dashline
}
\text{dessin = \a=\f? \dessin
  linewidth 4
  arrow \a,0,\a,\yB,6,\couleur1
  arrow \a1,0, \a1,\yB1, 6,\couleur2
  \textup
  \dashline
}
#endif

#if defined TARGET_optique3
\text{dessin = \a<>\f ? \dessin
  linewidth 4
  arrow \a,0,\a,\yB,6,\couleur1
  \dashline
}
#endif

#if defined TARGET_optique1 ||defined TARGET_optique3 || defined TARGET_optique3cv || defined TARGET_optique3cv2
\text{dessin = \a=\f? \dessin
  linewidth 4
  arrow \a,0,\a,\yB,6,\couleur1
  \dashline
}
#endif

#if defined TARGET_foyercalcul || defined TARGET_optique4 || defined TARGET_foyercv || defined TARGET_optique3cv || defined TARGET_optique3cv2
\text{dessin1 = \a<>\f?
  linewidth 4
  vline 0,0,black
  linewidth 1
  text black, 0.2,-0.2,medium, O
  trange \rangex1,\rangex2
  plot green, t, \eq1
}

\text{dessin2=\a<>\f?
  dpolyline red,min(\a,0),\yB, 0,\yB
  dpolyline red,-min(-\a,0),\yB, 0,\yB
  dpolyline red, -(\f),0,0,\yB
  dpolyline red, \a1,\yB1,0,\yB
  polyline blue, 0,\yB1,abs(\u),\yB1
  dpolyline blue, 0,\yB1,\u,\yB1
  dpolyline blue, 0,\yB1,\a,\yB
  dpolyline blue, 0,\yB1,\f,0
  trange 0,\rangex2
  plot red, t,\eq3
  trange min(\a,0),0
  plot red, t,\yB
  trange min(-\a,0),0
  plot red, t,\yB
  trange \rangex1,0
  plot blue, t,\eq2
  text black,\f,-0.2,large, F
  text black,-(\f),-0.2,large, F'
  linewidth 4
  segment \a,0,\a,\yB,\couleur1
  segment \a1,0,\a1,\yB1, \couleur2
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
  segment \a1,0,\a1,\yB1, \couleur2
  \dashline
}
\real{aa=abs(round(1000*(\a1-(\a)))/1000)}
\real{ayB=round(1000*abs(\yB))/1000}
\real{ayB1=round(1000*abs(\yB1))/1000}
\integer{rep1=-(\rangex1)}
#endif

#if defined TARGET_optique1
\integer{rep=\f < 0 ? 1:2}
#include "lang.inc"
\statement{
  \name_instruction \embed{reply 1}:
<div class="wimscenter">\draw{600,200}{\dessin}</div>
}
\answer{\name_answertext ?}{\rep;\question}{type=click}
#endif

#if defined TARGET_optique2
\text{rep=\coula issametext \couleur1 and \a<0 ? 1}
\text{rep=\coula issametext \couleur2 and \a1<0 ? 4}
\text{rep=\coula issametext \couleur1 and \a>0 ? 2}
\text{rep=\coula issametext \couleur2 and \a1>0 ? 3}
#include "lang.inc"
\statement{\name_instruction
<ul><li>\embed{reply 1,1}</li>
<li>\embed{reply 1,2}</li>
<li>\embed{reply 1,3}</li>
<li>\embed{reply 1,4}</li>
</ul>
<div class="wimscenter">\draw{600,200}{\dessin}</div>
}
\answer{\name_answertext}{\rep;\question}{type=radio}
#endif

#if defined TARGET_optique3
\text{rep=\f<0 and \a<\f ? 2}
\text{rep=\f<0 and \a<0 and \a> \f ? 3}
\text{rep=\f<0 and \a>0 ? 1}
\text{rep=\f>0 and \a>\f ? 4}
\text{rep=\f>0 and \a>0 and \a<\f ? 1}
\text{rep=\f>0 and \a<0 ? 3}
#include "lang.inc"
\statement{\name_instruction
<ul><li>\embed{reply 1,1}</li>
<li>\embed{reply 1,2}</li>
<li>\embed{reply 1,3}</li>
<li>\embed{reply 1,4}</li>
</ul>
<div class="wimscenter">\draw{600,200}{\dessin}</div>
}
\answer{\name_answertext}{\rep;\question}{type=radio}
#endif
#if defined TARGET_optique3cv || defined TARGET_optique3cv2
\real{taillex=600}
\real{tailley=200}
\text{question=randitem(image,image inverse)}
\text{Point=\question issametext image ? randitem(A,B):randitem(A',B')}
\text{des_quest=\question issametext image ?
  text \couleur1,\a+0.1,0,large, A
  text \couleur1, \a+0.1,\yB,large, B
  linewidth 4
  segment \a,0,\a,\yB,\couleur1
:
  text \couleur2, \a1+0.1,0,large, A'
  text \couleur2,\a1+0.1,\yB1,large, B'
  linewidth 4
  segment \a1,0,\a1,\yB1,\couleur2
}
\text{pointy=\Point issametext A or \Point issametext A' ? 0}
\text{pointy=\Point issametext B ? \yB1}
\text{pointy=\Point issametext B' ? \yB}
\text{pointx=\question issametext image ? \a1 : \a}
\text{P=slib(draw/convpixel \pointx,\pointy,\taillex,\tailley,\rangex1,\rangex2,\rangey1,\rangey2,0,pixels)}
\real{Px=\P[1]}
\real{Py=\P[2]}
\text{des_rep=disk \pointx,\pointy, 10,blue}
\text{A=draw(\taillex,\tailley
\dessin
\des_quest
)}
#  if defined TARGET_optique3cv2
\text{pointy2=\Point issametext B or \Point issametext B' ? 0}
\text{pointy2=\Point issametext A ? \yB1}
\text{pointy2=\Point issametext A' ? \yB}
\text{PP=slib(draw/convpixel \pointx,\pointy2,\taillex,\tailley,\rangex1,\rangex2,\rangey1,\rangey2,0,pixels)}
\text{Point2=A isin \Point ? B:A}
\text{Point2=' isin \Point ? \Point2 '}
\text{rep=\P, \PP}
\css{<style type="text/css">
.jxgbox {margin-left:auto;margin-right:auto;}
.jsxgraph_button {text-align:center;}
</style>}
#include "lang.inc"
\statement{\name_instruction \(\Point \Point2).
\embed{reply1,\taillex x \tailley}
}
\answer{}{\A;vector,\rep}{type=jsxgraphcurve}
#  endif
#  if defined TARGET_optique3cv
#include "lang.inc"
\statement{\name_instruction \(\Point).
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\A;point,\P}{type=coord}
\feedback{1=1}{
<div class="wimscenter">
\draw{600,200}{
  \dessin
  \dessin1
  \dessin2
  text \couleur1,\a+0.1,0,large, A
  text \couleur2,\a1+0.1,\yB1,large, B'
  text \couleur1, \a+0.1,\yB,large, B
  text \couleur2, \a1+0.1,0,large, A'
  linewidth 4
  segment \a,0,\a,\yB,\couleur1
  segment \a1,0,\a1,\yB1, \couleur2
\des_rep
}
</div>}
# endif
#endif
#if defined TARGET_foyer
#include "lang.inc"
\statement{\name_instruction?
<div class="wimscenter">\draw{600,200}{\dessin}</div>
<div class="wims_instruction">\name_warning</div>
}
\answer{\name_answertext}{-(\f)}{type=numeric}
#endif
#if defined TARGET_foyercalcul
#include "lang.inc"
\statement{\name_instruction
\(A B\) \name_length \( \ayB \ cm), \(A'B'\) \name_length \(\ayB1 \ cm), \(A A'\) \name_length \( \aa \ cm).
\name_instruction2
<div class="wimscenter">\draw{600,200}{\dessin}</div>
}
\answer{\(\overline{O A})}{\a}{type=numeric}
\answer{\(\overline{O A'})}{\a1}{type=numeric}
\answer{\name_answertext}{-\f}{type=numeric}
\feedback{1=1}{<div class="wimscenter">
\draw{600,200}{
  \dessin
  \dessin1
  \dessin2
}
</div>}
#endif
#if defined TARGET_foyercv
\real{taillex=600}
\real{tailley=200}
\text{question=randitem(objet, image)}
\text{pointy=0}
\text{pointx=\question issametext objet ? \f : -\f}
\text{P=slib(draw/convpixel \pointx,\pointy,\taillex,\tailley,\rangex1,\rangex2,\rangey1,\rangey2,0,pixels)}
\real{Px=\P[1]}
\real{Py=\P[2]}
\text{des_rep=disk \pointx,\pointy, 10,blue}
\text{A=draw(\taillex,\tailley
\dessin
\dessin1
)}
#include "lang.inc"
\statement{\name_instruction
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\A;point,\Px,\Py}{type=coord}
\feedback{1=1}{
<div class="wimscenter">
\draw{600,200}{
  \dessin
  \dessin1
  \dessin2
  \des_rep
}
</div>}
#endif
#if defined TARGET_optique4
\integer{rep1=-(\rangex1)}
\steps{reply1
  reply2}
#include "lang.inc"
\statement{\name_instruction
  \if{\step<=1}{\name_instruction1: \embed{r1,4}
<div class="wimscenter">
\draw{600,200}{
  \dessin
  text black,\rangex1+0.2,-0.2,medium,O
  vline \rangex1,0,black
  text black, \rangex1+1, \rangey2/5,medium, 1
}
</div>}
\if{\step>=2}{\name_instruction2: \embed{r2,4}
<div class="wimscenter">
\draw{600,200}{
  \dessin
  linewidth 1
  hline black, 0,0
  \dessin1
  }
</div>
}
<div class="wims_instruction">\name_warning</div>
}
\answer{\name_answertext[1]}{\rep1}{type=numeric}
\answer{\name_answertext[2]}{-\f}{type=numeric}
\feedback{1=1}{
<div class="wimscenter">
\draw{600,200}{
  \dessin
  \dessin1
  \dessin2
}
</div>}
#endif
#if defined TARGET_optique2cv
\real{taillex=600}
\real{tailley=200}
\real{ynouv= \yB > 0 ? (\yB+1+ \rangey2)/2 : ( \rangey1 + \yB-1)/2}
\function{eqnouv= \ynouv+ (\yB1-\ynouv)/(\a1)* x}
Point de l'axe des x =
\real{pointx= -(\ynouv)*(\a1)/ (\yB1-\ynouv)}
\text{pointy = 0}
\text{P=slib(draw/convpixel \pointx,\pointy,\taillex,\tailley,\rangex1,\rangex2,\rangey1,\rangey2,0,pixels)}
\real{Px=\P[1]}
\real{Py=\P[2]}
\text{A=draw(\taillex,\tailley
\dessin
\dessin1
linewidth 1
segment \a, \yB, 0,\ynouv, brown)}
\text{des_rep=disk \pointx,\pointy, 10,blue}
#include "lang.inc"
\statement{\name_instruction
<div class="wimscenter">\embed{reply1}</div>
\name_instruction2
}
\answer{}{\A;point,\Px,\Py}{type=coord}
\feedback{1=1}{
<div class="wimscenter">
\draw{600,200}{
  \dessin
  \dessin1
  \dessin2
  \des_rep
  linewidth 1
  segment \a, \yB, 0,\ynouv, brown
  trange \rangex1,\rangex2
  plot  brown, \eqnouv
}
</div>}
#endif
