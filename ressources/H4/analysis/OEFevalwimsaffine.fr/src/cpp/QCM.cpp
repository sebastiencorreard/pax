target=pourcal1,pourcal2,pourcal3,pourcal4,pourcal5,vocabulaire1,vocabulaire2,vocabulaire3,vocabulaire4,vocabulaire5,relation1,relation2,relation3,relation4,relation5,reconnaitre1,reconnaitre2,reconnaitre3,reconnaitre4,reconnaitre5
#include "author.inc"
\precision{100}
#if defined TARGET_pourcal1 || defined TARGET_vocabulaire1 || defined TARGET_relation1 || defined TARGET_reconnaitre1
# define NUM 1
#endif
#if defined TARGET_pourcal2 || defined TARGET_vocabulaire2 || defined TARGET_relation2 || defined TARGET_reconnaitre2
# define NUM 2
#endif
#if defined TARGET_pourcal3 || defined TARGET_vocabulaire3 || defined TARGET_relation3 || defined TARGET_reconnaitre3
# define NUM 3
#endif
#if defined TARGET_pourcal4 || defined TARGET_vocabulaire4 || defined TARGET_relation4 || defined TARGET_reconnaitre4
# define NUM 4
#endif
#if defined TARGET_pourcal5 || defined TARGET_vocabulaire5 || defined TARGET_relation5 || defined TARGET_reconnaitre5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}
#if defined TARGET_pourcal1
 \integer{a=randint(20..50)}
 \integer{q=randitem(10,15,20,25,30,35,40)}
 \text{sg=randitem(-,+)}
 \real{b=(1\sg\q/100)*\a}
 \text{enonce=Un article passe de \(\a) euros à \(\b) euros. Parmi les affirmations suivantes laquelle est vraie}
 \real{p=abs(\a-\b)}
 \integer{r=\p/\b*10000}
 \real{r=\r/100}
 \text{bad=C'est une augmentation de \(\q \%),C'est une diminution de \(\q \%),C'est une augmention de \(\p \%),C'est une diminution de \(\p \%),C'est une diminution de \(\r \%),C'est une augmentation de \(\r \%)}
 \text{good=\a-\b<0?1:2}
#endif
#if defined TARGET_pourcal2
 \integer{som=randitem(25,20,40,50,200)}
 \integer{fi=randint(\som/3..2*\som/3)}
 \integer{ga=\som-\fi}
 \if{\ga=\fi}{
  \integer{fi=\fi-5}
  \integer{ga=\ga+5}
}
 \matrix{don=filles,\fi,\ga
  garçon,\ga,\fi}
 \text{don=randrow(\don)}
 \text{type=\don[1]}
 \text{x=\don[2]}
 \text{y=\don[3]}
 \text{enonce=Dans une piscine il y a \x filles et \y garçons. Quel est le pourcentage de \type}
 \real{p1=rint(1000*\fi/\som)/10}
 \real{p2=rint(1000*\ga/\fi)/10}
 \real{p3=rint(1000*\fi/\ga)/10}
 \real{p4=rint(1000*\ga/\som)/10}
 \text{bad=\(\p1 \%),\(\p2 \%),\(\p3 \%),\(\p4 \%)}
 \text{good=1}
#endif
#if defined TARGET_pourcal3
 \text{a=shuffle(10,15,20,25,30,35,40)}
 \integer{b=item(1,\a)}
 \integer{a=item(2,\a)}
\text{mois=janvier,février,mars,avril,mai,juin,juillet,septembre,octobre,novembre,décembre}
 \integer{i=randint(1..10)}
 \text{mois1=item(\i,\mois)}
 \text{mois2=item(\i+1,\mois)}
 \text{mois3=item(\i+2,\mois)}
 \text{nom=slib(lang/fname fr,boy)}
 \text{enonce=En \mois2, un magasin annonce une remise de \(\a \%) par rapport au mois précédent.<br>En \mois3, le même magasin annonce une nouvelle remise de \(\b \%).<br>Quel est le pourcentage de baisse des prix entre \mois1 et \mois2 dans ce magasin}
 \integer{p1=\a+\b}
 \integer{p2=max(\b-\a,\a-\b)}
 \real{p3=rint((1-(1-\a/100)*(1-\b/100))*1000)/10}
 \real{p4=rint(\a/\b*1000)/10}
 \real{p5=rint(\b/\a*1000)/10}
 \text{bad=\(\p1 \%),\(\p2 \%),\(\p3 \%),\(\p4 \%),\(\p5 \%)}
 \text{good=3}
#endif
#if defined TARGET_pourcal4
 \integer{a=randitem(10,15,20,25,30,35,40)}
\text{mois=janvier,février,mars,avril,mai,juin,juillet,septembre,octobre,novembre,décembre}
 \integer{i=randint(1..10)}
 \text{mois1=item(\i,\mois)}
 \text{mois2=item(\i+1,\mois)}
 \text{mois3=item(\i+2,\mois)}
 \text{nom=slib(lang/fname fr,boy)}
 \text{objet=randitem(téléviseur,magnétoscope,ordinateur,vélo,jeu vidéo)}
 \text{enonce=\nom passe devant un magasin en \mois1 et voit le prix d'un \objet.<br>En \mois2, il repasse devant le même magasin et constate que le prix à augmenter de \(\a \%).<br>En \mois3, il constate que le prix à diminuer de \(\a \%) par rapport à \mois2.<br>Laquelle de ces affirmations est vraie}
 \text{bad=Le prix de cet article en \mois3 est plus élevé qu'en \mois1, Les prix de cet article en \mois3 et en \mois1 sont exactement les mêmes, Le prix de cet article en \mois3 est moins élevé qu'en \mois1}
 \text{good=3}
#endif
#if defined TARGET_pourcal5
 \integer{som=randitem(25,20,40,50)}
 \text{a=shuffle(5,10,15,20,25)}
 \integer{x=\a[1]}
 \integer{y=\a[2]}
 \integer{fi=randint(\som/3..2*\som/3)}
 \integer{ga=\som-\fi}
 \if{\ga=\fi}{
  \integer{fi=\fi-5}
  \integer{ga=\ga+5}
}
 \integer{som=20*\som}
 \integer{a=20*\fi}
 \integer{b=20*\ga}
 \text{enonce=Dans un groupe d'adolescent composé de \a filles et \b garçons, \(\x \%) des filles et \(\y \%) des garçons ont des lunettes. Quel est le pourcentage des enfants qui portent des lunettes}
 \real{p1=rint((\x+\y)/2)/10}
 \real{p2=\x+\y}
 \real{p3=max(\x-\y,\y-\x)}
 \real{p4=rint((\a*\x+\b*\y)/\som*10)/10}
 \text{bad=\(\p1 \%),\(\p2 \%),\(\p3 \%),\(\p4 \%)}
 \text{good=4}
#endif
!! exercice connaissance du vocavulaire sur les fonctions linéaires.

#if defined TARGET_vocabulaire1
 \text{v=wims(values v for v=2 to 10)}
 \text{v=shuffle(\v)}
 \integer{a=item(1,\v)}
 \integer{c=item(2,\v)}
 \integer{b=\a*\c}
 \text{f=randitem(f,g,h)}
 \text{enonce=Soit \(\f) une fonction linéaire telle que \(\f(\a)=\b). Parmi ces affirmations, laquelle est vraie}
 \text{bad=\b est l'image de \a par \f,\a est l'image de \b par \f,\a est le coefficient de \f,\b est le coefficient de \f}
 \text{good=1}
#endif
#if defined TARGET_vocabulaire2
 \text{v=wims(values v for v=2 to 10)}
 \text{v=shuffle(\v)}
 \integer{a=item(1,\v)}
 \integer{c=item(2,\v)}
 \integer{b=\a*\c}
 \text{f=randitem(f,g,h)}
 \text{enonce=Soit \(\f) une fonction linéaire telle que \(\f(\a)=\b). Parmi ces affirmations, laquelle est vraie}
 \text{bad=\a est le nombre qui a pour image \b par \f,\b est le nombre qui a pour image \a par \f,\a est le coefficient de \f,\b est le coefficient de \f}
 \text{good=1}
#endif
#if defined TARGET_vocabulaire3
 \text{v=wims(values v for v=2 to 10)}
 \text{v=shuffle(\v)}
 \integer{a=item(1,\v)}
 \integer{c=item(2,\v)}
 \integer{b=\a*\c}
 \text{f=randitem(f,g,h)}
 \text{enonce=Soit \(\f) la fonction linéaire \(\f : x \mapsto \a x). Parmi ces affirmations, laquelle est vraie}
 \text{bad=\a est le coefficient de \f,x est le coefficient de \f,\a est le nombre qui a pour image x par \(\f),x est le nombre qui a pour image \a par \(\f),x est l'image de \a par \f,\a est l'image de x par \f}
 \text{good=1}
#endif
#if defined TARGET_vocabulaire4
 \text{v=wims(values v for v=2 to 10)}
 \text{v=shuffle(\v)}
 \integer{a=item(1,\v)}
 \integer{c=item(2,\v)}
 \integer{b=\a*\c}
 \text{f=randitem(f,g,h)}
 \text{enonce=Soit \(\f) une fonction linéaire telle que \(\f(\a)=\b). Parmi ces affirmations, laquelle est vraie}
 \text{bad=\(\f(\a)) est l'image de \a par \f,\(\f(\a)) est l'image de \b par \f,\(\f(\b)) est l'image de \a par \f,\(\f(\b)) est l'image de \b par \f,\a est l'image de \b par \f}
 \text{good=1}
#endif
#if defined TARGET_vocabulaire5
 \text{v=wims(values v for v=2 to 10)}
 \text{v=shuffle(\v)}
 \integer{a=item(1,\v)}
 \integer{c=item(2,\v)}
 \integer{b=\a*\c}
 \text{f=randitem(f,g,h)}
 \text{enonce=Soit \(\f) une fonction linéaire telle que \(\f(\a)=\b). Parmi ces affirmations, laquelle est vraie}
 \text{bad=\a est le nombre qui a pour image \f(\a) par \f,\a est le nombre qui a pour image \f(\b) par \f,\b est le nombre qui a pour image \f(\b) par \f,\b est le nombre qui a pour image \f(\a) par \f,\b est le nombre qui a pour image \a par \f}
\text{good=1}
#endif
!! établir une relation de proportionnalité.
#if defined TARGET_relation1
 \integer{pour=randint(10..90)}
 \text{enonce=Augmenter une quantité de \pour % c'est la multiplier par}
 \real{a1=1+\pour/100}
 \real{a2=\pour+100}
 \real{a3=100-\pour}
 \real{a4=1-\pour/100}
\text{bad=\a1,0.\pour,\pour,\a2,\a3,\a4}
 \text{good=1}
#endif
#if defined TARGET_relation2
 \integer{pour=randint(10..90)}
 \text{enonce=Diminuer une quantité de \pour % c'est la multiplier par}
 \real{a1=1-\pour/100}
 \real{a2=\pour+100}
 \real{a3=100-\pour}
 \real{a4=1+\pour/100}
\text{bad=\a1,0.\pour,\pour,\a2,\a3,\a4}
 \text{good=1}
#endif
#if defined TARGET_relation3
 \real{pour=randint(200..900)/100}
 \text{enonce=Multiplier une quantité par \pour c'est l'augmenter de }
 \real{a1=(\pour-1)*100}
 \real{a2=\pour*100}
 \real{a3=(\pour+1)*100}
\text{bad=\a1 %,\pour %,\a2 %,\a3 %}
 \text{good=1}
#endif
#if defined TARGET_relation4
 \real{pour=randint(20..90)/100}
 \text{enonce=Multiplier une quantité par \pour c'est }
 \real{a1=(1-\pour)*100}
 \real{a2=\pour*100}
\text{bad=la diminuer de \a1 %,l'augmenter de \a1 %,la diminuer de \pour %,l'augmenter de \pour %,la diminuer de \a2 %,l'augmenter de \a2 %}
 \text{good=1}
#endif
#if defined TARGET_relation5
 \integer{a=randitem(2,4,5,8,10)}
 \real{pour=1/\a}
 \text{enonce=Diviser une quantité par \pour c'est }
 \real{a1=(\a-1)*100}
 \real{a2=\a*100}
 \real{a3=(\a+1)*100}
\text{bad=l'augmenter de \a1 %,la diminuer de \a1 %,l'augmenter de \a2 %,la diminuer de \a2 %,l'augmenter de \pour %,la diminuer de \pour %,l'augmenter de \a3 %,la diminuer de \a3 %}
 \text{good=1}
#endif
!! exercice reconnaître.
#if defined TARGET_reconnaitre1
 \text{v=wims(values v for v=2 to 20)}
 \text{v=shuffle(\v)}
 \integer{good=randitem(1,2)}
 \if{\good=1}{
  \integer{a=\v[1]}
  \integer{b=\v[2]}
 }{
  \integer{a=0}
  \integer{b=\v[2]}
 }
 \text{enonce=Soit \(\f\) une fonction telle que \(\f(\a)=\b). Cette fonction peut-elle être linéaire}
 \text{bad=Oui,Non}
#endif
#if defined TARGET_reconnaitre2
 \text{v=wims(values v for v=2 to 20)}
 \text{v=shuffle(\v)}
 \integer{a1=\v[1]}
 \integer{good=randint(1..2)}
 \if{\good=1}{
  \integer{a2=\v[1]}
 }{
  \integer{a2=\v[2]}
 }
 \integer{n1=\v[3]}
 \integer{n2=\v[4]}
 \integer{i1=\n1*\a1}
 \integer{i2=\n2*\a2}
 \text{enonce=Soit \(\f\) une fonction telle que \(\f(\n1)=\i1) et \(\f(\n2)=\i2). Cette fonction peut-elle être linéaire}
 \text{bad=Oui,Non}
#endif
#if defined TARGET_reconnaitre3
\text{v=wims(values v for v=2 to 20)}
 \text{v=shuffle(\v)}
 \integer{good=randitem(1,2)}
 \if{\good=1}{
  \text{a=\v[1],\v[1],\v[1]}
 }{
  \matrix{a=\v[1],\v[2],\v[3]
\v[1],\v[2],\v[2]}
  \text{a=randrow(\a)}
  \text{a=shuffle(\a)}
 }
 \text{n=\v[4],\v[5],\v[6]}
\text{i=simplify(\n[1]*\a[1]),simplify(\n[2]*\a[2]),simplify(\n[3]*\a[3])}
 \text{enonce=Soit \(\f\) une fonction dont certaines valeurs ont été portées dans le tableau ci-dessous :
 <table class="wimscenter wimsborder"><tr><th>x</th><td>\n[1]</td><td>\n[2]</td><td>\n[3]</td></tr>
 <tr><th>\f(x)</th><td>\i[1]</td><td>\i[2]</td><td>\i[3]</td></tr></table>
 Cette fonction peut-elle être linéaire}
 \text{bad=Oui,Non}
#endif
#if defined TARGET_reconnaitre4
 \text{v=wims(values v for v=2 to 20)}
 \text{v=shuffle(\v)}
 \integer{good=randitem(1,2)}
 \if{\good=1}{
  \text{form=randitem(\v[1]x,\frac{\v[1]}{\v[2]}x,\sqrt{2}x,\pi x)}
 }{
  \text{form=randitem(\v[1]x+\v[2],\v[1]x+\pi,\cos(x),\sqrt{x},\x^2,\v[1]x^2)}
 }
 \text{enonce=Soit \(\f\) une fonction dont la formule est donnée par \(\f(x)=\form). Cette fonction est-elle linéaire}
 \text{bad=Oui,Non}
#endif
#if defined TARGET_reconnaitre5
 \text{v=wims(values v for v=3 to 6)}
 \text{v=shuffle(\v)}
 \integer{good=randitem(1,2)}
 \if{\good=1}{
  \integer{a=randint(1..9)*randitem(1,-1)}
  \text{donnees=\a*x}
 }{
  \text{donnees=randitem(\v[1]/10*x^2,\v[3]*x+\v[2])}
 }
\text{dessin=slib(draw/repere 400,400,0,-10,10,-10,10,1,1,black,grey)}
\text{dessin=wims(line 3 to -1 of \dessin)}
\text{figure=draw(400,400
\dessin
range -10,10,-10,10
plot blue,\donnees
text black,9.5,-0.3,medium,X
text black,-1.5,10,medium,\f(X)
text black,0.9,-0.3,medium,1
text black,-0.5,1.5,medium,1)}
 \text{enonce=Soit \(\f\) une fonction dont la représentation graphique est donnée ci-dessous.<div class="wimscenter"><img src="\figure" alt=""></div>Cette fonction est-elle linéaire}
 \text{bad=Oui,Non}
 #endif
!! gestionnaire de l'exercice.

\text{lettres=A,B,C,D,E,F,G,H}
\text{good=item(\good,\bad)}
\text{bad=shuffle(\bad)}
\text{po=positionof(\good,\bad)}
\text{reponse=<ul>}
\integer{nb=items(\bad)}
\for{i=1 to \nb}{
 \text{reponse=\reponse<li><b>\lettres[\i]</b> : \bad[\i]</li>}
}
\text{reponse=\reponse</ul>}
\text{Good=item(\po,\lettres)}
\text{Bad=wims(item 1 to \nb of \lettres)}
\statement{
\enonce ? <br>
\reponse
<p><b>Votre réponse :</b></p>
  <label for="reply1">Ma réponse est</label> : \embed{r1}.
}
choice{réponse}{\Good}{\Bad}
\answer{réponse}{\po;\Bad}{type=menu}
