target=fracpour1 fracpour2 fracpour3 fracpour4 fracpour5
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
#define TITRE Ecriture fractionnaire et pourcentage

#if defined TARGET_fracpour1
 \title{TITRE 1}
 \integer{p=5*randint(7..15)}
 \statement{
\p % des élèves ont eu la moyenne au précédent contôle de mathématiques.
<p>
Quelle fraction des élèves a eu la moyenne ?
</p>
<div>
<b>Votre réponse</b> : \embed{r1,4}
</div>}
\answer{}{\p/100}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_fracpour2
 \title{TITRE 2}
 \integer{d=randitem(10,25,50,20)}
 \integer{n=randint(\d+1..2*\d-1)}
 \real{rep=\n/\d*100}
 \statement{
Quelle est l'écriture sous forme de pourcentage de la fraction \(\frac{\n}{\d}) ?
<div>
<b>Votre réponse</b> \embed{r1,4} %</div>}
\answer{}{\rep}{type=numexp}
#endif

#if defined TARGET_fracpour3
 \title{TITRE 3}
 \text{v=randrow(3/4,Les trois quarts
2/5,Les deux cinquièmes
1/5,Le cinquième
1/4,Le quart
1/2,La moitié
4/5,Les quatre cinquièmes)}
 \real{rep=\v[1]*100}
 \statement{
\v[2] des enfants ont un ordinateur chez eux.<p>
Quel pourcentage des enfants a un ordinateur ?</p>
<b>Votre réponse</b> \embed{r1,4} %}
\answer{}{\rep}{type=numexp}
#endif

#if defined TARGET_fracpour4
 \title{TITRE 4}
 \text{v=\(\frac{3}{4}),75 %
\(\frac{2}{5}),40 %
\(\frac{1}{5}),20 %
\(\frac{1}{4}),25 %
\(\frac{1}{2}),50 %
\(\frac{4}{5}),80 %}
 \text{ch=shuffle(1,2,3,4,5,6)}
 \text{left=}
 \text{right=}
 \for{k=1 to 4}{
  \text{tmp=row(\ch[\k],\v)}
  \text{left=wims(append item \tmp[1] to \left)}
  \text{right=wims(append item \tmp[2] to \right)}
}
 \statement{
Mettre en correspondance chaque fraction avec le pourcentage qu'elle représente.
<div class="wimscenter">\embed{r1,60x100x100}</div>}
\answer{}{\left;\right}{type=correspond}
#endif


#if defined TARGET_fracpour5
 \title{TITRE 5}

 \integer{a=randint(5..45)}
 \integer{b=randint(3..22)}
 \integer{c=randint(2..8)}
 \integer{d=randint(3..17)}
 \text{left=\(\frac{\a}{50}),\(\frac{\b}{25}),\(\frac{\c}{10}),\(\frac{\d}{20})}
 \text{right=simplify(2*\a) %,simplify(4*\b) %,simplify(10*\c) %,simplify(5*\d) %}
 \statement{
Mettre en correspondance chaque fraction avec le pourcentage qu'elle représente.
<div class="wimscenter">\embed{r1,60x100x100}</div>}
\answer{}{\left;\right}{type=correspond}
#endif
