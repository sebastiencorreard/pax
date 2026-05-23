target=resoudre1 resoudre2 resoudre3 resoudre4 resoudre5
#include "author.inc"
#define TITRE Résoudre
#if defined TARGET_resoudre1
# define NUM 1
#endif
#if defined TARGET_resoudre2
# define NUM 2
#endif
#if defined TARGET_resoudre3
# define NUM 3
#endif
#if defined TARGET_resoudre4
# define NUM 4
#endif
#if defined TARGET_resoudre5
# define NUM 5
#endif
\title{TITRE NUM}

 \text{name1=slib(lang/fname fr,boy)}
 \text{name2=slib(lang/fname fr,boy)}
 \text{name3=slib(lang/fname fr,boy)}
 \text{name=shuffle(\name1,\name2,\name3)}
 \text{name=wims(listuniq \name)}
 \integer{nb=items(\name)}
 \text{name=\nb<3?shuffle(Pierre,Paul,Olivier)}
\text{x=randitem(x,y,z)}
#if defined TARGET_resoudre1
 \integer{rep=randint(10..20)}
 \integer{nb1=randint(5..15)}
 \integer{nb2=randint(5..12)}
 \integer{nb3=randint(5..15)}
 \integer{tot=\nb1+\rep-\nb2+\nb3}
 \text{enonce=Dans un bus \nb1 personnes montent. A l'arrêt suivant, \nb2 personnes descendent et \nb3 montent. Le bus arrive ensuite au terminal et \tot personnes descendent.}
 \text{question=Combien y-avait-il de personnes dans le bus au départ}
#endif
#if defined TARGET_resoudre2
 \integer{a=randint(10..20)}
 \integer{b=randint(31..50)}
 \integer{c=randint(10..20)}
 \integer{d=\c+randint(20..40)}
 \text{dessin=draw(220,170
dsegment 50,10,50,100,black
dsegment 100,10,100,50,black
dsegment 140,30,140,150,black
dsegment 200,10,200,50,black
dsegment 10,50,100,50,black
dsegment 10,100,50,100,black
dsegment 10,150,50,150,black
segment 50,15,200,15,black
segment 140,35,200,35,black
ftriangle 50,15,55,12,55,18,black
ftriangle 140,35,145,32,145,38,black
ftriangle 100,15,105,12,105,18,black
ftriangle 100,15,95,12,95,18,black
ftriangle 200,15,195,12,195,18,black
ftriangle 200,35,195,32,195,38,black
polygon black,100,50,200,50,200,150,50,150,50,100
segment 25,50,25,150,black
ftriangle 25,50,22,55,28,55,black
ftriangle 25,100,22,105,28,105,black
ftriangle 25,100,22,95,28,95,black
ftriangle 25,150,22,145,28,145,black
text black,170,24,medium,\x
text black,28,125,medium,\a
text black,28,75,medium,\b
text black,70,2,medium,\c
text black,135,2,medium,\d)}

 \integer{rep=randint(10..20)}
 \integer{nb1=randint(5..15)}
 \integer{nb2=randint(5..12)}
 \integer{nb3=randint(5..15)}
 \integer{tot=\nb1+\rep-\nb2+\nb3}
 \text{enonce=\name1 et \name2 doivent se partager le terrain ci-dessous
 (<i>Les mesures sont en mètres.</i>):
 <div class="wimscenter"><img src="\dessin" alt=""></div>
}
 \text{question=Quelle doit être la mesure de \x pour que le partage soit équitable}
 \text{comp=m}
 \text{rep=simplify((\d*(\a+\b)+\c*(2*\a+\b)/2)/(2*\a+2*\b))}
#endif
#if defined TARGET_resoudre3
 \integer{rep=randint(10..17)}
 \text{t=shuffle(2,3,4)}
 \integer{nb1=\t[1]}
 \integer{nb2=\t[2]}
 \integer{tot=3*\rep+\nb1-\nb2}
 \text{enonce=\name[1] a \nb1 ans de plus que son frère \name[2] et \name[3] a \nb2 ans de moins que \name[2]. La somme de leurs âges est l'âge de leur mère qui est de \tot ans.}
 \text{question=Quel est l'âge de \name[2]}
 \text{comp=ans}
#endif
#if defined TARGET_resoudre4
 \text{t=shuffle(4,6,8)}
 \integer{v1=10*randint(5..10)}
 \integer{v2=\v1+10*randint(2,4)}
 \text{fr1=simplify(\v2/(\v2-\v1))}
 \text{tmp2=wims(replace internal / by , in \fr1)}
 \integer{t=items(\tmp2)}
 \text{tmp2=\t=1?1:item(2,\tmp2)}
 \integer{h=2*randint(1..3)}
 \text{enonce=\name[1] a roulé à \v1 Km/h. S'il avait roulé à \v2 Km/h, il aurait mis \h heures de moins pour effectuer son trajet.}
 \text{question=Combien de temps \name[1] a-t-il mis pour terminer son parcours}
 \text{comp=heures}
 \integer{rep=\h*\fr1}
#endif
#if defined TARGET_resoudre5
 \text{a=randitem(2,3)}
 \text{b=randitem(4,5)}
 \text{lt=,double,triple,quadruple,quintuple}
 \text{aa=\lt[\a]}
 \text{ab=\lt[\b]}
 \integer{n1=randint(5..20)}
 \integer{t=6-(\n1-floor(\n1/6))}
 \integer{n2=\t+6*randint(10..20)}
 \text{rep=simplify((\n1+\n2)/(\b-\a))}
 \text{enonce=En ajoutant \n1 au \aa d'un nombre, \name[1] trouve le même résultat qu'en retranchant \n2 au \ab de ce nombre.}
 \text{question=Quel est ce nombre}
#endif

\statement{
\enonce
<div>
\question ?
</div>
<label for="reply1"><b>Votre réponse :</b></label> \embed{r1,8} \comp.}

\answer{}{\rep}{type=numexp}{options=noreduction}
