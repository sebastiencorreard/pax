target=pourcentangle
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}

\text{n=randint(4..6)}
\text{ss=100}
\for{i=1 to \n-1}{
 \text{u=randint(8..20)}
 \if{\i=1}{\text{s=\u}}{\text{s=\s,\u}}
 \real{ss=\ss-\u}}
 \text{s=\s,\ss}
 \text{shu=shuffle(6)}
 \text{listecouleur=red,skyblue,orange,grey,green,purple}
 \text{listefr=rouge, bleu,orange,gris, vert, violet}
 \text{listealpha = A,B,C,D,E,F}
 \text{pos=randint(1..\n)}
 \text{alph=item(item(\pos,\shu), \listealpha)}
 \text{couleur=item(item(\pos,\shu), \listefr)}
 \integer{ind=randint(10..30)*100}
 \real{rep= round(item(\pos,\s)/100*\ind)}
 \text{dessin= ellipse 0,0,2,2,black
segment 0,0,1,0,black}
 \text{anglet=0}
 \text{pos=randint(1..\n)}
 \for{i=1 to \n}{
 \real{angle=item(\i,\s)*2*pi/100}
 \real{point=\anglet+\angle/2}
 \text{couleur=item(item(\i,\shu),\listecouleur)}
 \text{alph=item(item(\i,\shu), \listealpha)}
 \real{anglet=\anglet+\angle}
 \text{dessin=\dessin
segment 0,0,cos(\anglet),sin(\anglet),black
fill cos(\point)/2,sin(\point)/2, \couleur
text black, 1.2*cos(\point),1.2*sin(\point),medium, \alph
}
\if{\i = \pos}{}{\text{dessin=\dessin
text black, 2*cos(\point)/3,2*sin(\point)/3, medium, item(\i,\s)%
}}}

\text{couleur=item(item(\pos,\shu), \listefr)}
\text{alph=item(item(\pos,\shu), \listealpha)}
\integer{ind=randint(10..30)*100}
\real{rep= round(item(\pos,\s)/100*360)}

\statement{\name_enonce[1] \n \name_enonce[2] \ind \name_enonce[3]:
<div class="wimscenter">
 \draw{200,200}
{xrange -1.5,1.5
yrange -1.5,1.5
\dessin}
</div>
\name_question \couleur (\alph) ?
<div class="wims_instruction">
\name_inst
</div>}

\answer{\name_answer}{\rep}{type=numeric}
