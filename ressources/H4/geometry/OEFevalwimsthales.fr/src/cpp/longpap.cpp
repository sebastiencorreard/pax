target=longpap1,longpap2,longpap3,longpap4,longpap5
#define TITRE Calcul de longueur
\email{fguerima@free.fr}
\author{Fabrice,Guerimand}
#if defined TARGET_longpap1
# define NUM B1
#endif
#if defined TARGET_longpap2
# define NUM B2
#endif
#if defined TARGET_longpap3
# define NUM B3
#endif
#if defined TARGET_longpap4
# define NUM B4
#endif
#if defined TARGET_longpap5
# define NUM B5
#endif
\title{TITRE NUM}
\matrix{sommets=A,B,C,D,E,F
E,F,G,H,I,J
M,N,O,P,Q,R}
\text{sommet=randrow(\sommets)}
\text{sommet=shuffle(\sommet)}

\text{A=item(1,\sommet)}
\text{B=item(2,\sommet)}
\text{C=item(3,\sommet)}
\text{D=item(4,\sommet)}
\text{E=item(5,\sommet)}
\text{F=item(6,\sommet)}

\integer{den=randint(3..7)}
\integer{num=randint(1..\den-1)}
\text{v=wims(values v for v=15 to 49)}
\text{v=shuffle(\v)}
\integer{d1=\den*\v[1]}
\integer{n1=\num*\v[1]}
\integer{d2=\den*\v[2]}
\integer{n2=\num*\v[2]}

#if defined TARGET_longpap1
 \text{donnees=\(\A \B = \d1\) ; \(\A \E = \n2\) ; \(\A \C = \d2\)}
 \text{quest=\A \D}
 \text{rep=\n1}
#endif
#if defined TARGET_longpap2
 \text{donnees=\(\A \D = \n1\) ; \(\D \E = \n2\) ; \(\B \C = \d2\)}
 \text{quest=\A \B}
 \text{rep=\d1}
#endif
#if defined TARGET_longpap3
 \text{donnees=\(\A \D = \n1 \) ; \(\A \B = \d1\) ; \(\B \C = \d2\)}
 \text{quest=\D \E}
 \text{rep=\n2}
#endif
#if defined TARGET_longpap4
 \integer{t=\d1+\n1}
 \text{donnees=\(\A \D = \n1 \) ; \(\D \B = \t \) ; \(\A \E = \n2 \)}
 \text{quest=\A \C}
 \integer{rep=\d2}
#endif
#if defined TARGET_longpap5
 \text{donnees=\(\A \E = \n1 \) ; \(\D \E = \n2 \) ; \(\B \C = \d2 \)}
 \text{quest=\E \C}
 \integer{rep=\d1+\n1}
#endif

\text{X=randrow(\D,\B,\E,\C
\E,\C,\D,\B)}

 \text{dessin=segment 20,80,180,120,black
segment 90,30,110,170,black
segment 20,80,90,30,red
segment 180,120,110,170,red
text black,110,90,medium,\A
text black,5,70,medium,\X[2]
text black,100,25,medium,\X[4]
text black,95,170,medium,\X[3]
text black,185,120,medium,\X[1]}
\text{image=draw(200,200
\dessin)}

\statement{
<ul class="wims_nopuce">
 <li>
\((\B \D)\) et \((\E \C)\) sont deux droites sécantes en \(\A).
 </li><li>
  Les droites \((\D \E)\) et \((\B \C)\) sont parallèles.
</li><li>
  Sachant que :
<div class="wimscenter">\donnees</div>
calculer \(\quest\).
</li></ul>
<div class="wims_instruction">Le dessin n'est qu'indicatif,
  il n'est pas à l'échelle et ne respecte pas les proportions.
</div>

<div class="wimscenter"><img src="\image" alt=""></div>
}

\answer{\(\quest\)}{\rep}{type=numexp}
