target=trianglesiso1 trianglesiso2 trianglesiso3 trianglesiso4 trianglesiso5
#define TITRE Triangles isométriques
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}

#include "isoqcm.inc"

#if defined TARGET_trianglesiso1
 \title{TITRE I}
 \integer{kk=random(1,1,1,1,2,2)}
 \if{\kk=1}
  {
   \text{data=randomrow(\isoVFquest)}
   \text{quest=\data[1]}
   \text{goodrep=\data[2]}
   \text{replist=Vrai,Faux}
  }
  {
 \integer{n=items(\isoquest)}
 \integer{ind=randint(1..\n)}
 \text{quest=\isoquest[\ind]}
 \text{replist=\isolstrep[\ind;]}
 \text{goodrep=\isogrep[\ind;]}
  }
\statement{
 Cocher la bonne réponse:
<div>
\quest
</div>
<ol>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
\if{\kk=2}
{
<li>\embed{reply1,3}</li>
}
</ol>
}
\answer{Bonne réponse;}{\goodrep;\replist}{type=radio}{option=shuffle}
#endif
#if defined TARGET_trianglesiso2
 \title{TITRE II}
\integer{k=random(1,2)}
\if{\k=1}{
 \text{dessin=
 xrange -12,12
 yrange -12,12
 circle 0,0,400,black
 polyline black,10,0,5,10*sqrt(3)/2,-5,10*sqrt(3)/2,-10,0,-5,-10*sqrt(3)/2,5,-10*sqrt(3)/2,10,0
 polyline black,10,0,-5,10*sqrt(3)/2,-5,-10*sqrt(3)/2,10,0
 polyline black,-10,0,5,10*sqrt(3)/2,5,-10*sqrt(3)/2,-10,0
 segment -10,0,10,0,black
 text black,11,0,medium,C
 text black,11/2,11*sqrt(3)/2,medium,B
 text black,-11/2,11*sqrt(3)/2,medium,A
 text black,-11,0,medium,F
 text black,-11/2,-11*sqrt(3)/2,medium,E
 text black,11/2,-11*sqrt(3)/2,medium,D
 text black,0,7,medium,H
 text black,0,-6,medium,K
 text black,-5.5,0,medium,I
 text black,5.2,0,medium,J
}
 \matrix{triangles=ABC,BCD,CDE,DEF,EFA,FAB
AFI,EFI,CBJ,CDJ
FAH,CBH,CDK,FEK}
 \matrix{numrep=1,2,3,4,5,6
7,8,9,10
11,12,13,14}
}
{
 \text{dessin=
 xrange -12,12
 yrange -12,12
 circle 0,0,400,black
 polyline black,10,0,10*cos(2*pi/5),10*sin(2*pi/5),10*cos(4*pi/5),10*sin(4*pi/5),10*cos(6*pi/5),10*sin(6*pi/5),10*cos(8*pi/5),10*sin(8*pi/5),10,0
 polyline black,10*cos(6*pi/5),10*sin(6*pi/5),10*cos(2*pi/5),10*sin(2*pi/5),10*cos(8*pi/5),10*sin(8*pi/5),10*cos(4*pi/5),10*sin(4*pi/5),10,0,10*cos(6*pi/5),10*sin(6*pi/5)
 text black,11,0,medium,A
 text black,11*cos(2*pi/5),11*sin(2*pi/5),medium,B
 text black,11*cos(4*pi/5),11*sin(4*pi/5),medium,C
 text black,11*cos(6*pi/5),11*sin(6*pi/5),medium,D
 text black,11*cos(8*pi/5),11*sin(8*pi/5),medium,E
 text black,-0.5,0,medium,O
 linewidth 5
 point black,0,0
}
 \matrix{triangles=ABC,BCD,CDE,DEA,EAB
ACD,BDE,CEA,DAB,EBC
OAB,OBC,OCD,ODE,OEA}
 \matrix{numrep=1,2,3,4,5
6,7,8,9,10
11,12,13,14,15}
}
 \integer{i=randint(1..3)}
 \text{data=row(\i,\triangles)}
 \text{cetriangle=randitem(\data)}
 \text{goodrep=row(\i,\numrep)}

\statement{<div class="float_right">\draw{480,480}{\dessin}</div>
 Cocher tous les triangles isométriques au triangle \cetriangle
<div class="wimscenter">
\embed{reply1}
</div>

}
\answer{Bonne réponse;}{\goodrep;\triangles[1;],\triangles[2;],\triangles[3;]}{type=checkbox}{option=shuffle}
#endif
#if defined TARGET_trianglesiso3
 \title{TITRE III}
\integer{a=random(4..20)}
\text{lstquest=l'hypoténuse a pour longueur \a cm.,1
AB=\a cm.,2
\(\hat{A})=45°,2
AB=\a cm et \(\hat{A})=45°,2
AB=\a cm et \(\hat{B})=45°,2
AB=\a cm et \(\hat{C})=45°,1
AB=\a cm et \(\hat{A})=90°,1
AB=\a cm et \(\hat{B})=90°,1
AB=\a cm et \(\hat{C})=90°,1
}
 \integer{i=randint(1..9)}
 \text{data=row(\i,\lstquest)}
 \text{quest=\(ABC) est rectangle isocèle et \data[1]}
 \text{goodrep=\data[2]}
#endif

#if defined TARGET_trianglesiso4
 \title{TITRE IV}
\integer{a=random(4..20)}
\integer{c=\a+random(4..10)}
\integer{b=random(15..70)}
\text{lstquest=en \(A) et l'hypoténuse a pour longueur \a cm,2
en \(A) et \(AB=\a) cm,2
en \(B) et \(\hat{A})=\b°,2
en \(B)&#44; \(AB=\a) cm et \(\hat{A})=\b°,1
en \(C)&#44; \(AB=\a) cm et \(\hat{B})=\b°,1
en \(A)&#44; \(AB=\a) cm et \(AC=\c) cm,1
en \(B)&#44; \(AB=\a) cm et \(AC=\c) cm,1
&#44; \(AB=\a) cm et \(AC=\c) cm,2
}
 \integer{i=randint(1..8)}
 \text{data=row(\i,\lstquest)}
 \text{quest=\(ABC) est rectangle  \data[1]}
 \text{goodrep=\data[2]}
#endif
#if defined TARGET_trianglesiso5
 \title{TITRE V}
\integer{a=random(4..20)}
\integer{b=random(4..20)}
\integer{c=\b>\a?random(\b-\a..\b+\a):random(\a-\b..\a+\b)}
\integer{t=random(10..140)}
\integer{s=random(5..160-\t)}
\integer{u=180-\s-\t}

\text{lstquest=AB=\a &#44;  BC=\b  et CA=\c,1
AB=\a &#44; BC=\b et \(\hat{B})=\t,1
AC=\a &#44; BC=\b et \(\hat{C})=\t,1
AB=\a &#44; AC=\b et \(\hat{A})=\t,1
AC=\a &#44; \(\hat{C})=\t et \(\hat{A})=\s,1
AB=\a &#44; \(\hat{B})=\t et \(\hat{A})=\s,1
BC=\a &#44; \(\hat{B})=\t et \(\hat{C})=\s,1
\(\hat{A})=\u &#44; \(\hat{B})=\t et \(\hat{C})=\s,2
AB=\a &#44; \(\hat{C})=\t et \(\hat{A})=\s,1
BC=\a &#44; \(\hat{C})=\t et \(\hat{A})=\s,1
AC=\a &#44; \(\hat{B})=\t et \(\hat{A})=\s,1
BC=\a &#44; \(\hat{B})=\t et \(\hat{A})=\s,1
AC=\a &#44; \(\hat{B})=\t et \(\hat{C})=\s,1
AB=\a &#44; \(\hat{B})=\t et \(\hat{C})=\s,1
AB=\a &#44; BC=\b et \(\hat{A})=\t,2
AB=\a &#44; BC=\b et \(\hat{C})=\t,2
AC=\a &#44; BC=\b et \(\hat{B})=\t,2
AC=\a &#44; BC=\b et \(\hat{A})=\t,2
AB=\a &#44; AC=\b et \(\hat{B})=\t,2
AB=\a &#44; AC=\b et \(\hat{C})=\t,2
}
 \integer{i=randint(1..20)}
 \text{data=row(\i,\lstquest)}
 \text{quest=\data[1]}
 \text{goodrep=\data[2]}

#endif

#if (defined TARGET_trianglesiso5  || defined TARGET_trianglesiso4  || defined TARGET_trianglesiso3 )
\statement{
Alexandra et Xavier doivent dessiner, sans se consulter, un triangle \(ABC) vérifiant:
<div class="wimscenter">\quest.</div>
Les deux triangles qu'ils tracent sont-ils nécessairement isométriques?
}
\answer{Isométriques?}{\goodrep;Oui,Non}{type=radio}
#endif
