target=vitesse1 vitesse2 vitesse3 vitesse4 vitesse5
#include "author.inc"
#if defined TARGET_vitesse1
# define NUM 1
#endif
#if defined TARGET_vitesse2
# define NUM 2
#endif
#if defined TARGET_vitesse3
# define NUM 3
#endif
#if defined TARGET_vitesse4
# define NUM 4
#endif
#if defined TARGET_vitesse5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"
\text{name=slib(lang/fname fr,girl)}
\text{don=randrow(kilomètres,heures,km/h
  mètres,secondes,m/s)}
\text{unit=item(3,\don)}
\text{udist=item(1,\don)}
\text{utemps=item(2,\don)}
#if defined TARGET_vitesse1
 \integer{v1=randint(10..100)}
 \real{t1=randint(1..12)*0.25}
 \real{d1=\t1*\v1}
 \text{enonce=\name parcourt \d1 \udist en \t1 \utemps}
 \text{rep=\v1}
#endif
#if defined TARGET_vitesse2
 \integer{v1=randint(10..100)}
 \integer{t1a=randint(1..3)}
 \text{unit=km/h}
 \real{t1b=randitem(0.25,0.75,0.5)}
 \real{t1=\t1a+\t1b}
 \integer{aff=\t1b*60}
 \real{d1=\t1*\v1}
 \text{enonce=\name parcourt \d1 kilomètres en \t1a h \aff min}
 \real{rep=\v1}
#endif
#if defined TARGET_vitesse3
 \integer{v1=randint(10..100)}
 \integer{v2=randint(10..100)}
 \text{t=wims(values v*0.25 for v=2 to 12)}
 \text{t=shuffle(\t)}
 \real{t1=item(1,\t)}
 \real{t2=item(2,\t)}
 \real{d1=\t1*\v1}
 \real{d2=\t2*\v2}
 \text{enonce=\name parcourt \d1 \udist en \t1 \utemps puis \d2 \udist en \t2 \utemps}
 \integer{rep=(\d1+\d2)/(\t1+\t2)}
#endif
#if defined TARGET_vitesse4
 \text{v=wims(values v*2 for v=10 to 30)}
 \text{v=shuffle(\v)}
 \integer{v1=\v[1]}
 \integer{v2=\v[2]}
 \real{t=h isin \unit?randint(2..4):randint(25..55)}
 \real{d1=\t*\v1}
 \real{d2=\t*\v2}
 \text{enonce=\name se déplace à \v1 \unit pendant \t \utemps puis à la vitesse de \v2 \unit pendant la même durée}
 \integer{rep=(\d1+\d2)/(2*\t)}
#endif
#if defined TARGET_vitesse5
 \text{v=randint(7..15)}
 \text{t=randrow(1,4
2,5
2,7
1,3
3,8)}
 \text{t1=\t[1]}
 \text{t2=\t[2]}
 \integer{v1=\v*\t2}
 \integer{v2=\v*\t1}
 \text{unit=km/h}
 \real{d1=\t1*\v1}
 \real{d2=\t2*\v2}
 \text{enonce=\name va chez ses grands parents qui habitent à \d2 km de chez lui. A l'aller sa vitesse est de \v1 km/h et au retour elle est de \v2 km/h}
 \integer{rep=(\d1+\d2)/(\t1+\t2)}
#endif
\statement{
\enonce.
<p>
  Quelle est sa vitesse moyenne durant ce trajet&nbsp;?
</p>
<label for="reply1"><b>Votre réponse :</b></label> \embed{r1,5} \unit.
<div class="wims_instruction">Donner l'arrondi entier si nécessaire.</div>}

\answer{}{\rep}{type=numexp}
