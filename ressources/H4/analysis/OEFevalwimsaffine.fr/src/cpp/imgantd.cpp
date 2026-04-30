target=imgant1,imgant2,imgant3,imgant4,imgant5,coefficient1,coefficient2,coefficient3,coefficient4,coefficient5
\precision{100}
#if defined TARGET_imgant1 || defined TARGET_coefficient1
# define NUM 1
#endif
#if defined TARGET_imgant2 || defined TARGET_coefficient2
# define NUM 2
#endif
#if defined TARGET_imgant3 || defined TARGET_coefficient3
# define NUM 3
#endif
#if defined TARGET_imgant4 || defined TARGET_coefficient4
# define NUM 4
#endif
#if defined TARGET_imgant5 || defined TARGET_coefficient5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}

#if defined TARGET_imgant1
 \text{v=wims(values v,-v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \integer{rep=\a*\b}
 \text{enonce=Soit \(\f\) la fonction linéaire définie par \(\f : x \mapsto \a x)}
 \text{question=Calculer \(\f(\b)\)}
 \text{reponse=\(\f(\b)\)=}
#endif
#if defined TARGET_imgant2
 \text{v=wims(values v,-v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \integer{rep=\a*\b}
 \text{enonce=Soit \(\f\) la fonction linéaire définie par \(\f : x \mapsto \a x)}
 \text{question=Quelle est l'image de \b par \(\f\)}
 \text{reponse=L'image de \b par \(\f\) est}
#endif
#if defined TARGET_imgant3
 \text{v=wims(values v,-v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{rep=\v[2]}
 \integer{b=\a*\rep}
 \text{enonce=Soit \(\f\) la fonction linéaire définie par \(\f : x \mapsto \a x)}
 \text{question=Quel nombre a pour image \b par \(\f\)}
 \text{reponse=Le nombre qui a pour image \b par \(\f\) est }
#endif
#if defined TARGET_imgant4
 \text{v=wims(values v,-v for v=2 to 15)}
 \integer{g=gcd(\v[1],\v[2])}
 \if{\g!=1}{
  \text{a=randitem(7/5,5/7,1/2,3/4,7/8,1/5,2/3)}
 }{
  \text{a=\v[1]/\v[2]}
 }
 \integer{g=gcd(\v[3],\v[4])}
 \if{\g!=1}{
  \text{b=7/3}
 }{
  \text{b=\v[3]/\v[4]}
 }
 \text{rep=simplify(\a*\b)}
 \text{a=texmath(\a)}
 \text{b=texmath(\b)}
 \text{enonce=Soit \(\f\) la fonction linéaire définie par \(\f : x \mapsto \a x)}
 \text{question=Calculer \(\f(\b))}
 \text{reponse=\(\f(\b)=)}
#endif
#if defined TARGET_imgant5
 \text{v=wims(values v,-v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \integer{c=\v[3]}
 \text{rep=simplify(\b/\a*\c)}
 \text{enonce=Soit \(\f\) la fonction linéaire telle que \(\f(\a)=\b)}
 \text{question=Quelle est l'image de \c par \(\f\)}
 \text{reponse=\(\f(\c)\)=}
#endif
#if defined TARGET_coefficient1
 \text{v=wims(values v,-v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{rep=\v[2]}
 \integer{b=\a*\rep}
 \text{enonce=Soit \(\f\) une fonction linéaire. On sait que \(\f(\a)=\b)}
 \text{question=Quel est le coefficient de la fonction \(\f\)}
 \text{reponse=Le coefficient de \(\f\) est}
#endif
#if defined TARGET_coefficient2
 \text{v=wims(values v,-v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{rep=\v[2]}
 \integer{b=\a*\rep}
 \text{enonce=Soit \(\f\) une fonction linéaire. On sait que l'image de \a par \(\f\) est \b}
 \text{question=Quel est le coefficient de la fonction \(\f\)}
 \text{reponse=Le coefficient de \(\f\) est}
#endif
#if defined TARGET_coefficient3
 \text{v=wims(values v,-v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{rep=\v[2]}
 \integer{b=\a*\rep}
 \text{enonce=Soit \(\f\) une fonction linéaire. On sait que le nombre qui a pour image \b par \(\f\) est \a}
 \text{question=Quel est le coefficient de la fonction \(\f\)}
 \text{reponse=Le coefficient de \(\f\) est}
#endif
#if defined TARGET_coefficient4
\text{rep=randitem(1/2,3/2,1/3,4/3,5/3,2/3,4/5,5/4,2/5,6/7,11/7,3/7,9/4)}
 \integer{c=randitem(1,2,3,5,9,10,11)}
 \text{v=wims(replace internal / by , in \rep)}
 \integer{b=\v[1]*\c}
 \integer{a=\v[2]*\c}
 \text{enonce=Soit \(\f\) une fonction linéaire. On sait que \(\f(\a)=\b)}
 \text{question=Quel est le coefficient de la fonction \(\f\)}
 \text{reponse=Le coefficient de \(\f\) est}
#endif
#if defined TARGET_coefficient5
 \text{v=wims(values v,-v for v=2 to 15)}
 \integer{g=gcd(\v[1],\v[2])}
 \if{\g!=1}{
  \text{a=randitem(7/5,5/7,1/2,3/4,7/8,1/5,2/3)}
 }{
  \text{a=\v[1]/\v[2]}
 }
 \integer{g=gcd(\v[3],\v[4])}
 \if{\g!=1}{
  \text{b=7/3}
 }{
  \text{b=\v[3]/\v[4]}
 }
 \text{rep=simplify(\b/(\a))}
 \text{a=texmath(\a)}
 \text{b=texmath(\b)}
 \text{tmp=randitem(\(\f(\a)=\b),l'image de \(\a) par \(\f\) est \(\b),le nombre qui a pour image \(\b) par \(\f\) est \(\a))}
 \text{enonce=Soit \(\f\) une fonction linéaire. On sait que \tmp}
 \text{question=Quel est le coefficient de la fonction \(\f\)}
 \text{reponse=Le coefficient de \(\f\) est}
#endif

\statement{
\enonce.<p>
\question?
</p>
<b>Votre réponse :</b>
<div class="wimscenter">
<label for="reply1">\reponse</label> \embed{r1}.
</div>}

\reply{réponse}{\rep}{type=numexp}
