target= miseequation1 miseequation2 miseequation3 miseequation4 miseequation5
#include "author.inc"

\keywords{pbsolving}
#define TITRE Mettre en équation
#if defined TARGET_miseequation1
# define NUM 1
#endif
#if defined TARGET_miseequation2
# define NUM 2
#endif
#if defined TARGET_miseequation3
# define NUM 3
#endif
#if defined TARGET_miseequation4
# define NUM 4
#endif
#if defined TARGET_miseequation5
# define NUM 5
#endif
\title{TITRE NUM}
\text{name1=slib(lang/fname fr,boy)}
\text{name2=slib(lang/fname fr,girl)}
\text{name3=slib(lang/fname fr,girl)}
\text{name=shuffle(\name1,\name2,\name3)}
\text{name=wims(listuniq \name)}
\integer{nb=items(\name)}
\text{name=\nb<3?shuffle(Pierre,Paul,Olivier)}
\text{x=randitem(x,y,z)}

#if defined TARGET_miseequation1
 \integer{valx=randint(75..125)}
 \integer{dif1=randint(12..24)}
 \integer{dif2=randint(25..\valx-25)}
 \integer{total=3*\valx+\dif1-\dif2}
 \text{enonce=\name[1], \name[2] et \name[3] se sont partagés \total euros. \name[1] a pris \dif1 euros de plus que \name[2] et \name[3] en a \dif2 de moins que \name[2]. Combien chacun a-t-il pris &#63;}
 \text{question=Soit \(\x\) la quantité d'argent prise par \name[2]. Quelle équation doit vérifier \(\x\)}
#endif

#if defined TARGET_miseequation2
 \text{listnom=le quart,le tiers,le sixième,le cinquième}
 \text{listfrac=1/4,1/3,1/6,1/5}
 \text{lt=shuffle(1,2,3,4)}
 \text{part1=\listnom[\lt[1]]}
 \text{part2=\listnom[\lt[2]]}
 \text{tmp=simplify(1-\listfrac[\lt[1]]-\listfrac[\lt[2]])}
 \text{tmp2=wims(replace internal / by , in \tmp)}
 \text{tmp2=item(1,\tmp2)}
 \integer{quant=\tmp2*randint(2..5)}
 \integer{valx=\quant/(\tmp)}
 \text{enonce=\name[1], \name[2] et \name[3] se sont partagés des voitures. \name[1] en a pris \part1, \name[2] en a pris \part2 et \name[3] a pris le reste, c'est-à-dire \quant voitures. Combien y-avait-il de voitures au total &#63;}
 \text{question=Si on appelle \(\x\) le nombre total de voitures, quelle équation doit vérifier \(\x\)}
#endif
#if defined TARGET_miseequation3
 \text{listnom=au quart,au trois quarts,au tiers,au deux tiers,au cinquième, au deux cinquièmes, au trois cinquièmes}
 \text{listfrac=1/4,3/4,1/3,2/3,1/5,2/5,3/5}
 \text{lt=shuffle(1,2,3,4,5,6,7)}
 \text{part1=\listnom[\lt[1]]}
 \text{fr1=\listfrac[\lt[1]]}
 \text{tmp2=wims(replace internal / by , in \fr1)}
 \text{tmp2=item(1,\tmp2)}
 \integer{cont=\tmp2*randint(2..5)}
 \integer{valx=\cont/(\fr1)}
 \text{enonce=Un bidon contient \cont litres. Il est plein \part1. Quelle est la contenance totale de ce bidon &#63;}
 \text{question=Soit \(\x\) la contenance, en litre, du bidon. Quelle équation doit vérifier \(\x\)}
#endif
#if defined TARGET_miseequation4
 \integer{l=randint(5..15)}
 \integer{valx=randint(25..50)}
 \integer{peri=2*(\l+\valx)}
 \text{enonce=ABCD est un rectangle de largeur \l cm. Son périmètre mesure \peri cm. Quelle est sa longueur &#63;}
 \text{question=Soit \(\x\) la longueur, en cm, du rectangle. Quelle équation doit vérifier \(\x\)}
#endif
#if defined TARGET_miseequation5
 \text{place=6,8
3,4
5,7}
 \text{place=randrow(\place)}
 \integer{nbp=\place[1]}
 \integer{nbq=\place[2]}
 \integer{p=randint(4..8)}
 \integer{q=randint(9..15)}
 \integer{nbtot=\p*\nbp+\q*\nbq}
 \integer{nbtab=\p+\q}
 \integer{valx=\p}
 \text{enonce=Pour un mariage un restaurateur doit placer ses invités sur des tables de \nbp ou des tables de \nbq. Il a demandé à son garçon de salle de préparer les \nbtab tables. Cependant, le garçon ne se rappelle plus combien il faut de tables de \nbp places et de tables de \nbq places. Il se souvient seulement qu'il y a \nbtot invités en tout. Peut-on trouver le nombre de tables de chaque sorte &#63;}
 \text{question=Soit \(\x\) le nombre de tables de \nbp places. Quelle équation doit vérifier \(\x\)}
#endif

\statement{Voici un problème :
<p class="bold">\enonce</p>

<p>\question ?</p>
<div class="wimscenter">\embed{r1}</div>}

\answer{}{\rep}{type=auto}

\text{test=maxima(SOLVE(\rep,\x);)}
\text{test=wims(replace internal = by , in \test)}
\text{test=\test[2]}
\condition{Equation correcte}{\valx=\test}
