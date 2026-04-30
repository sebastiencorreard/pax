target=longtri1,longtri2,longtri3,longtri4,longtri5
#define TITRE Calcul de longueur
\email{fguerima@free.fr}
\author{Fabrice,Guerimand}
#if defined TARGET_longtri1
# define NUM A1
#endif
#if defined TARGET_longtri2
# define NUM A2
#endif
#if defined TARGET_longtri3
# define NUM A3
#endif
#if defined TARGET_longtri4
# define NUM A4
#endif
#if defined TARGET_longtri5
# define NUM A5
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

#if defined TARGET_longtri1
 \text{donnees=\(\A \B = \d1 \) ; \(\A \E = \n2\) ; \(\A \C = \d2 \)}
 \text{quest=\A \D}
 \text{rep=\n1}
#endif

#if defined TARGET_longtri2
 \text{donnees=\(\A \D = \n1 \) ; \(\D \E = \n2 \) ; \(\B \C = \d2 \)}
 \text{quest=\A \B}
 \text{rep=\d1}
#endif

#if defined TARGET_longtri3
 \text{donnees=\(\A \D = \n1 \) ; \(\A \B = \d1 \) ; \(\B \C = \d2 \)}
 \text{quest=\D \E}
 \text{rep=\n2}
#endif

#if defined TARGET_longtri4
 \integer{t=\d1-\n1}
 \text{donnees=\(\A \D = \n1 \) ; \(\D \B = \t \) ; \(\A \E = \n2 \)}
 \text{quest=\A \C}
 \integer{rep=\d2}
#endif

#if defined TARGET_longtri5
 \text{donnees=\(\A \E = \n1 \) ;\(\D \E = \n2 \) ;\(\B \C = \d2 \)}
 \text{quest=\E \C}
 \integer{rep=\d1-\n1}
#endif

\text{X=randrow(\D,\B,\E,\C
\E,\C,\D,\B)}

 \text{dessin=segment 20,20,180,130,black
segment 20,20,50,180,black
segment 180,130,50,180,red
segment 35,100,100,75,red
text black,10,10,medium,\A
text black,190,135,medium,\X[2]
text black,35,185,medium,\X[4]
text black,25,100,medium,\X[3]
text black,115,70,medium,\X[1]}
\text{image=draw(200,200
\dessin)}

\statement{
<ul class="wims_nopuce">
<li>
\(\A \B \C\) est un triangle.
</li><li>
\(\D\) et \(\E\) sont respectivement des points des côtés \([\A \B]\) et \([\A \C]\)
tels que les droites \((\D \E)\) et \((\B \C)\) soient parallèles.
</li><li>
  Sachant que :
<div class="wimscenter">\donnees</div>
  calculer \(\quest\).
</li></ul>
<div class="wimscenter"><img src="\image" alt=""></div>

<div class="wims_instruction">Le dessin n'est qu'indicatif,
  il n'est pas à l'échelle et ne respecte pas les proportions.
</div>

}

\answer{\(\quest\)}{\rep}{type=numexp}
