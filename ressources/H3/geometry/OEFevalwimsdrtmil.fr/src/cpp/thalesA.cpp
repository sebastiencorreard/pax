target=thalesA3 thalesA4

#include "author.inc"
#define TITRE Triangles et proportionnalité
#if defined TARGET_thalesA3
# define NUM A3
#endif
#if defined TARGET_thalesA4
# define NUM A4
#endif
\title{TITRE NUM}
#if defined TARGET_thalesA3
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
#if defined TARGET_thalesA4
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
\text{name_enonce=Peut-on utiliser la propriété d'égalité des rapports dans la figure ci-contre&nbsp;}
\text{name_choix=Oui,Non}
\text{image=draw(200,200
\dessin)}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
 <div class="medium_size text_col">
 \comp
<p>\name_enonce?</p>
 </div>
</div>
}
\choice{Réponse}{\rep}{\name_choix}
