target=imagec1,imagec2,imagec3,imagec4,imagec5,antecedentc1,antecedentc2,antecedentc3,antecedentc4,antecedentc5
#include "author.inc"
\precision{100}
#if defined TARGET_imagec1 || defined TARGET_antecedentc1
# define NUM 1
#endif
#if defined TARGET_imagec2 || defined TARGET_antecedentc2
# define NUM 2
#endif
#if defined TARGET_imagec3 || defined TARGET_antecedentc3
# define NUM 3
#endif
#if defined TARGET_imagec4 || defined TARGET_antecedentc4
# define NUM 4
#endif
#if defined TARGET_imagec5 || defined TARGET_antecedentc5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}

#if defined TARGET_imagec1
 \text{v=wims(values v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \text{formule=\v[1]*x+\v[2]}
 \text{rep=evalue(\formule,x=\v[3])}
 \text{question=Calculer \(\f(\v[3])\)}
 \text{reponse=\(\f(\v[3])\)=}
#endif
#if defined TARGET_imagec2
 \text{v=wims(values v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \text{formule=-\v[1]*x+\v[2]}
 \text{rep=evalue(\formule,x=-\v[3])}
 \text{question=Calculer l'image de -\v[3] par \(\f\)}
 \text{reponse=\(\f(-\v[3])\)=}
#endif
#if defined TARGET_imagec3
 \text{v=wims(values v,-v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \text{formule=\v[1]*x+\v[2]}
 \text{nb=simplify(\v[3]/\v[4])}
 \text{rep=evalue(\formule,x=\nb)}
 \text{question=Calculer l'image de \nb par \(\f\)}
 \text{reponse=\(\f(\nb) = )}
#endif
#if defined TARGET_imagec4
 \text{v=wims(values v for v=2 to 10)}
 \text{v=shuffle(\v)}
 \text{formule=\v[1]/\v[5]*x-\v[2]}
 \text{nb=simplify(\v[3]/\v[4])}
 \text{rep=evalue(\formule,x=\nb)}
 \text{question=Calculer l'image de \nb par \(\f\)}
 \text{reponse=\(\f(\nb) = )}
#endif
#if defined TARGET_imagec5
 \text{v=wims(values v for v=2 to 10)}
 \text{v=shuffle(\v)}
 \text{formule=sqrt(\v[1])*x-\v[2]}
 \integer{nb=\v[1]*\v[2]^2}
 \text{rep=evalue(\formule,x=sqrt(\nb))}
 \text{question=Calculer l'image de \(\sqrt{\nb}) par \(\f\)}
 \text{reponse=\(\f(\sqrt{\nb}) = )}
#endif
#if defined TARGET_antecedentc1
 \text{v=wims(values v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \text{formule=\v[1]*x+\v[2]}
 \text{rep=0}
 \text{img=simplify(evalue(\formule,x=0))}
#endif
#if defined TARGET_antecedentc2
 \text{v=wims(values v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \text{formule=\v[1]*x+\v[2]}
 \text{rep=\v[3]}
 \text{img=simplify(evalue(\formule,x=\v[3]))}
#endif
#if defined TARGET_antecedentc3
 \text{v=wims(values v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \text{formule=-\v[1]*x+\v[2]}
 \text{rep=-\v[3]}
 \text{img=simplify(evalue(\formule,x=-\v[3]))}
#endif
#if defined TARGET_antecedentc4
 \text{v=wims(values v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \text{formule=-\v[1]*x+\v[2]}
 \text{rep=simplify(-\v[3]/\v[4])}
 \text{img=simplify(evalue(\formule,x=\rep))}
 \text{img=texmath(\img)}
#endif
#if defined TARGET_antecedentc5
 \text{v=randint(2..15)}
 \text{a=randitem(2,3,5,6,7,11)}
 \text{formule=sqrt(\a)*x+\v}
 \text{rep=sqrt(\a)}
 \text{img=simplify(evalue(\formule,x=\rep))}
 \text{img=texmath(\img)}
#endif
#if defined TARGET_antecedentc1 || defined TARGET_antecedentc2 || defined TARGET_antecedentc3 || defined TARGET_antecedentc4 || defined TARGET_antecedentc5
 \text{question=Calculer le nombre qui a pour image \(\img) par \(\f\)}
 \text{reponse=Le nombre qui a pour image \(\img\) par \(\f\) est }
#endif
\text{formule=texmath(\formule)}
\text{rep=simplify(\rep)}
\text{enonce=Soit \(\f\) la fonction affine définie par}
\statement{
\enonce \(\f : x \mapsto \formule\).<br>
\question ?
<p><b>Votre réponse :</b></p>
<label for="reply1">\reponse</label> \embed{r1}.
#if defined TARGET_antecedentc5
<div class="wims_instruction">Taper <span class="tt">sqrt(2)</span>
pour \(\sqrt{2}\)</div>
#endif
}
#if defined TARGET_antecedentc5
\reply{réponse}{\rep}{type=algexp}
#else
\reply{réponse}{\rep}{type=numexp}
#endif
