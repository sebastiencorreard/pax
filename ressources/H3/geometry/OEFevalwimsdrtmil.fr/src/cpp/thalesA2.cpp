target=thalesA2

#include "author.inc"
#define TITRE Triangles et proportionnalité
#if defined TARGET_thalesA2
# define NUM A2
#endif
\title{TITRE NUM}

\integer{y1=randint(67..100)}
\integer{yv=randint(20..40)}
\text{dessin=linewidth 2
parallel 20,\y1,180,\y1,0,\yv,2,green
segment 120,0,30,180,black
segment 80,0,170,180,black}
\text{comp=Les deux droites vertes sont parallèles}
\text{rep=Oui}
\text{image=draw(200,200
\dessin)}
\statement{<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
 <div class="medium_size text_col">
 \comp
<p>
Peut-on utiliser la propriété d'égalité des rapports dans la figure ci-contre ?
</p>
 </div>
</div>
}
\choice{Réponse}{\rep}{Oui,Non}
