target=situation1,situation2,situation3,situation4,situation5
#define TITRE Propriété de Thalès
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
#if defined TARGET_situation1
# define NUM 1
#endif
#if defined TARGET_situation2
# define NUM 2
#endif
#if defined TARGET_situation3
# define NUM 3
#endif
#if defined TARGET_situation4
# define NUM 4
#endif
#if defined TARGET_situation5
# define NUM 5
#endif
\title{TITRE NUM}
#if defined TARGET_situation1
 \integer{y1=randint(67..100)}
 \integer{yv=randint(20..40)}
 \text{dessin=linewidth 2
parallel 20,\y1,180,\y1,0,\yv,2,green
segment 120,0,30,180,black
segment 80,0,170,180,black}
 \text{comp=Les deux droites vertes sont parallèles}
 \text{rep=Oui}
#endif

#if defined TARGET_situation2
 \integer{y1=randint(67..100)}
 \integer{yv=randint(20..40)}
 \text{dessin=linewidth 2
segment 0,120,180,30,black
segment 0,80,180,170,black
segment 120,0,30,180,black
segment 80,0,170,180,black}
 \text{comp=}
 \text{rep=Non}
#endif

#if defined TARGET_situation3
 \integer{y1=randint(30..60)}
 \integer{y2=randint(150..170)}
 \integer{x1=randint(20..60)}
 \integer{x2=randint(20..60)}
 \text{dessin=linewidth 2
segment 20,\y1,180,\y1,green
segment 20,\y2,180,\y2,green
segment 100-\x1,0,100+\x1,180,black
segment 100+\x2,0,100-\x2,180,black}
 \text{comp=Les deux droites vertes sont parallèles}
 \text{rep=Oui}
#endif

#if defined TARGET_situation4
 \integer{x1=randint(120..180)}
 \integer{y1=randint(20..60)}
 \integer{x2=randint(20..60)}
 \integer{y2=randint(120..180)}
 \integer{x3=randint(120..180)}
 \integer{y3=randint(120..180)}
 \text{dessin=linewidth 2
triangle \x1,\y1,\x2,\y2,\x3,\y3,black
segment (\x1+\x2)/2,(\y1+\y2)/2,(\x1+\x3)/2,(\y1+\y3)/2,black
segment (\x1+\x2)/2,(\y1+\y2)/2,\x3,\y3,black
segment \x2,\y2,(\x1+\x3)/2,(\y1+\y3)/2,black
circle (3*\x1+\x2)/4,(3*\y1+\y2)/4,10,green
circle (\x1+3*\x2)/4,(\y1+3*\y2)/4,10,green
segment (3*\x1+\x3)/4-4,(3*\y1+\y3)/4-2,(3*\x1+\x3)/4+4,(3*\y1+\y3)/4-2,green
segment (3*\x1+\x3)/4-4,(3*\y1+\y3)/4+2,(3*\x1+\x3)/4+4,(3*\y1+\y3)/4+2,green
segment (\x1+3*\x3)/4-4,(\y1+3*\y3)/4-2,(\x1+3*\x3)/4+4,(\y1+3*\y3)/4-2,green
segment (\x1+3*\x3)/4-4,(\y1+3*\y3)/4+2,(\x1+3*\x3)/4+4,(\y1+3*\y3)/4+2,green}
 \text{rep=Oui}
#endif
#if defined TARGET_situation5
 \integer{x1=randint(120..180)}
 \integer{y1=randint(-100..-60)}
 \integer{x2=randint(20..60)}
 \integer{y2=randint(160..180)}
 \integer{x3=randint(120..180)}
 \integer{y3=randint(160..180)}
 \integer{y5=randint(10..20)}
 \integer{y4=randint(120..130)}
 \text{dessin=linewidth 2
segment 0,\y4,200,\y4,green
segment 0,\y5,200,\y5,green
segment \x2,\y2,(2*\x1+3*\x2)/5,(2*\y1+3*\y2)/5,black
segment \x2,\y2,(3*\x1+2*\x3)/5,(3*\y1+2*\y3)/5,black
segment (2*\x1+3*\x2)/5,(2*\y1+3*\y2)/5,\x3,\y3,black
segment \x3,\y3,(3*\x1+2*\x3)/5,(3*\y1+2*\y3)/5,black}
 \text{comp=Les deux droites vertes sont parallèles}
 \text{rep=Non}
#endif

\text{image=draw(200,200
\dessin)}

\statement{
<ul class="wims_nopuce">
 <li>\comp</li>
 <li>
  Peut-on utiliser le théorème de Thalès dans la figure ci-contre ?
<div class="wimscenter"><img src="\image" alt=""></div>
 </li>
</ul>}

\choice{Réponse}{\rep}{Oui,Non}
