target=oefconstpat2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ha=randint(20..75)}
\integer{la=randint(30..100-\ha)}
\integer{lo=randint(\la..270-2*\la)}

\integer{xo=(340-\lo-2*\ha)/2}
\integer{yo=150+\la+\ha}

\text{patron=draw(340,300
arrow2 0,20,340,20,10,black
text black,100,5,medium,Longueur de la feuille
arrow2 10,0,10,300,10,black
text black,15,280,medium,Hauteur de la feuille
rect \xo+\ha,\yo,\xo+\ha+\lo,\yo-\la,black
arrow2 \xo+\ha,\yo+10,\xo+\ha+\lo,\yo+10,10,black
text black,\xo+\ha+\lo/2,\yo+15,medium,a
rect \xo+\ha+\lo,\yo-\la,\xo+\ha,\yo-\la-\ha,black
arrow2 \xo+\ha+\lo+10,\yo-\la,\xo+\ha+\lo+10,\yo-\la-\ha,10,black
text black,\xo+\ha+\lo+20,\yo-\la-\ha/2-5,medium,c
rect \xo+\ha,\yo-\la-\ha,\xo,\yo-\ha-2*\la,black
arrow2 \xo+\ha-10,\yo,\xo+\ha-10,\yo-\la,10,black
text black,\xo+\ha-25,\yo-\la/2-5,medium,b
rect \xo+\ha,\yo-\la-\ha,\xo+\ha+\lo,\yo-\ha-2*\la,black
rect \xo+\ha+\lo,\yo-\ha-2*\la,\xo+2*\ha+\lo,\yo-\ha-\la,black
rect \xo+\ha+\lo,\yo-\ha-2*\la,\xo+\ha,\yo-2*\la-2*\ha,black
)}
\text{fig=<img src="\patron" alt="">}
\integer{rep2=(\ha+\la)*2}
\integer{rep1=\lo+\ha*2}

\statement{<div class="wims_columns">
 <div class="medium_size img_col">\fig</div>
 <div class="medium_size text_col">
Nous avons le patron d'un parallélépipède rectangle.
Nous avons les dimensions suivantes :
<ul><li>a = \lo mm
</li><li> b = \la mm
</li><li> c = \ha mm
</li></ul>
Nous ne faisons pas de languette pour le collage.
Trouver les dimensions minima de la feuille de papier :
<ul><li><label for="reply1">Longueur minimum de la feuille :</label> \embed{r1,5} mm
</li><li><label for="reply2">Hauteur minimum de la feuille :</label>\embed{r2,5} mm
</li></ul>
</div></div>
}

\answer{}{\rep1}{type=raw}
\answer{}{\rep2}{type=raw}
