target=angcalc1,angcalc2,angcalc3,angcalc4,angcalc5

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Calcul d'angle
\text{x=randitem(A,B,C,D)}
\text{x=\widehat{\x}}

#if defined TARGET_angcalc1
 \title{TITRE 1}
 \integer{ch=randint(1..2)}
 \text{form=item(\ch,arccos(x),arcsin(x))}
 \text{tform=item(\ch,\cos(\x),\sin(\x))}
 \real{re=randint(30..70)/100}
#endif

#if defined TARGET_angcalc2
 \title{TITRE 2}
 \text{form=arctan(x)}
 \text{tform=\tan(\x)}
 \real{re=randint(130..1000)/100}
#endif

#if defined TARGET_angcalc3
 \title{TITRE 3}
 \integer{ch=randint(1..2)}
 \text{form=item(\ch,arccos(x),arcsin(x))}
 \text{tform=item(\ch,\cos(\x),\sin(\x))}
 \text{re=randint(2..9)}
 \text{re=\re/randint(\re+1...\re+9)}
#endif

#if defined TARGET_angcalc4
 \title{TITRE 4}
 \text{form=arctan(x)}
 \text{tform=\tan(\x)}
 \real{re=simplify(randint(2..15)/randint(2..15))}
#endif

#if defined TARGET_angcalc5
 \title{TITRE 5}
 \integer{ch=randint(1..2)}
 \text{form=item(\ch,arccos(x),arcsin(x),arctan(x))}
 \text{tform=item(\ch,\cos(\x),\sin(\x),\tan(x))}
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \text{re=randint(2..7)/(\v[1]+\v[2])}
#endif

\text{angle=wims(replace internal x by \re in \form)}
\integer{ch=randint(0..2)}
\text{arr=item(\ch+1,au degré,au dixième de degré,au centième de degré)}
\real{rep=\angle/pi*180}
\real{rep=rint(\rep*10^\ch)/10^\ch}
\text{are=texmath(\re)}

\statement{
Utiliser la calculatrice et donner l'arrondi \arr de la mesure de l'angle aigu
\(\x) vérifiant :
<div class="wimscenter">
 \(\tform = \are )
</div>
<b>Réponse :</b><br>
 <label for="reply1">\(\x \simeq \)</label> \embed{r1,5} °.}

\answer{\(\x)}{\rep}{type=numexp}
