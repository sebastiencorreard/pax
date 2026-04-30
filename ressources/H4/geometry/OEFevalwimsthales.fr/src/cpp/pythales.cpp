target=pythales1,pythales2,pythales3,pythales4,pythales5

#define TITRE Confusion Pythagore Thalès
\email{fguerima@free.fr}
\author{Fabrice,Guerimand}
#if defined TARGET_pythales1
# define NUM 1
#endif
#if defined TARGET_pythales2
# define NUM 2
#endif
#if defined TARGET_pythales3
# define NUM 3
#endif
#if defined TARGET_pythales4
# define NUM 4
#endif
#if defined TARGET_pythales5
# define NUM 5
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

#if defined TARGET_pythales1
 \text{dessin=segment 20,20,180,130,black
segment 20,20,50,180,black
segment 180,130,50,180,green
segment 31,78,78,60,green
segment 84,35,50,180,black
segment 84,35,20,20,black
text black,10,10,medium,\A
text black,190,135,medium,\B
text black,35,185,medium,\C
text black,21,78,medium,\E
text black,93,55,medium,\D
text black,90,30,medium,\F}
 \text{comp=Les deux droites vertes sont parallèles.}
 \text{good=2}
#endif

#if defined TARGET_pythales2
 \text{dessin=segment 20,20,180,130,black
segment 20,20,50,180,black
segment 180,130,50,180,black
segment 31,78,78,60,black
segment 84,35,50,180,black
segment 84,35,20,20,black
segment 82,41,75,40,red
segment 75,40,76,33,red
text black,10,10,medium,\A
text black,190,135,medium,\B
text black,35,185,medium,\C
text black,21,78,medium,\E
text black,93,55,medium,\D
text black,90,30,medium,\F}
 \text{comp=}
 \text{good=1}
#endif

#if defined TARGET_pythales3
 \text{dessin=linewidth=2
triangle 19,49,110,164,176,112,black
segment 110,164,90,77,black
segment 106,159,112,154,red
segment 112,154,116,159,red}
 \text{comp=}
 \text{good=1}
#endif

#if defined TARGET_pythales4
 \text{dessin=linewidth 2
triangle 140,15,22,114,80,182,black
segment 110,98,81,64,black
segment 30,108,36,115,red
segment 36,115,29,122,red
segment 48,88,52,92,green
segment 109,37,113,42,green
circle 95,140,10,green
circle 125,56,10,green}
 \text{comp=}
 \text{good=4}
#endif

#if defined TARGET_pythales5
 \text{dessin=circle 97,97,178,black
triangle 42.8,168.1,185.2,86.5,151,25.7,black
text black,102,94,medium,O
segment 110,200,85,0,black}
 \text{comp=Le centre du cercle est O.}
 \text{good=1}
#endif

\text{image=draw(200,200
\dessin)}

\text{liste=Le théorème de Pythagore,Le théorème de Thalès,Ni le théorème de Thalès ni celui de Pythagore,Le théorème de Pythagore ou le théorème de Thalès}
\text{Good=item(\good,\liste)}

\statement{
\if{\comp notsametext }{
<ul class="wims_nopuce">
 <li>\comp</li><li>
 }
  Sur la figure ci-contre, quel théorème pourrait-on utiliser ?

\if{\comp notsametext }{
  </li>
</ul>
}
<div class="wimscenter"><img src="\image" alt=""></div>}

\choice{Réponse}{\Good}{\liste}
