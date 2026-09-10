\target=oefconstpat4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ha=randint(35..75)}
\integer{la=randint(45..105)}
\integer{lo=randint(\ha..380-2*\ha)}

\text{mes=\lo,\la,\ha}
\text{nm=shuffle(a,b,c)}

\integer{mes1=item(position(a,\nm),\mes)}
\integer{mes2=item(position(b,\nm),\mes)}
\integer{mes3=item(position(c,\nm),\mes)}

\integer{xo=(-\lo-2*\ha)/2}
\integer{yo=\la+\la-50}
\text{tr=rect,}
\matrix{vide=2,1,1,1,\la,\ha
1,2,1,1,\ha,\lo
1,1,2,1,\la,\ha
1,1,1,2,\la,\lo}
\integer{ch=randint(1..4)}
\text{ch=row(\ch,\vide)}
\if{\ch[5]>\ch[6]}{
  \integer{long=\ch[5]}
  \integer{larg=\ch[6]}}
{\integer{long=\ch[6]}
  \integer{larg=\ch[5]}}
\text{patron=xrange -210,210
yrange -200,200
\tr[\ch[1]] \xo+\ha,\yo-\la-\ha,\xo,\yo-\ha-2*\la,black
\tr[\ch[2]] \xo+\ha+\lo,\yo-\ha-2*\la,\xo+\ha,\yo-2*\la-2*\ha,black
\tr[\ch[3]] \xo+\ha+\lo,\yo-\ha-2*\la,\xo+2*\ha+\lo,\yo-\ha-\la,black
\tr[\ch[4]] \xo+\ha,\yo,\xo+\ha+\lo,\yo-\la,black

rect \xo+\ha+\lo,\yo-\la,\xo+\ha,\yo-\la-\ha,black
filledrect \xo+\ha,\yo-\la-\ha,\xo+\ha+\lo,\yo-\ha-2*\la,yellow
rect \xo+\ha,\yo-\la-\ha,\xo+\ha+\lo,\yo-\ha-2*\la,black
arrow2 \xo+\ha,\yo+10-\ha-\la,\xo+\ha+\lo,\yo+10-\ha-\la,10,black
text black,\xo+\ha+\lo/2,\yo+30-\ha-\la,medium,\nm[1]
arrow2 \xo+\ha-10,\yo-\la,\xo+\ha-10,\yo-\la-\ha,10,black
text black,\xo+\ha-25,\yo-\la-\ha/2,medium,\nm[3]
arrow2 \xo+\ha+10,\yo-\ha-\la,\xo+\ha+10,\yo-\ha-2*\la,10,black
text black,\xo+\ha+15,\yo-\ha-\la*1.4,medium,\nm[2]
}

\text{pat1=draw(420,400
\patron
)}
\text{pat2=draw(420,400
rotate 90
\patron
)}
\text{pat3=draw(420,400
rotate 270
\patron
)}

\text{patron=\pat1,\pat2,\pat3}
\integer{a=randint(1..3)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\patron[\a]" alt=""></div>
 <div class="medium_size text_col">
Une face a été oubliée dans le dessin d'un patron de parallélépipède rectangle.
Nous avons les dimensions suivantes :
<ul><li>a = \mes1 mm
</li><li>b= \mes2 mm
</li><li>c = \mes3 mm.
</li></ul>
<p>Quelles sont les dimensions de la face oubliée :</p>
<ul><li><label for="reply1">Longueur :</label>
\embed{r1,3} mm</li>
<li><label for="reply2">largeur :</label> \embed{r2,3} mm
</li></ul>
</div></div>
}

\answer{}{\long}{type=raw}
\answer{}{\larg}{type=raw}
