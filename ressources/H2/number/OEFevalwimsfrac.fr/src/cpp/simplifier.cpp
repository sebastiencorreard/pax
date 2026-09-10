target=simplifier1 simplifier2 simplifier3 simplifier4 simplifier5
#define TITRE Réduction de fraction
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_simplifier1
 \title{TITRE 1}
 \text{ch=randint(1..5)}
 \text{list=\(\frac{1}{2}),\(\frac{1}{3}),\(\frac{2}{3}),\(\frac{3}{4}),\(\frac{1}{4})}
 \text{list2=1,2
1,3
2,3
3,4
1,4}
 \text{rep=item(\ch,\list)}
 \text{f=row(\ch,\list2)}
 \integer{a=randint(3..9)}
 \integer{b=\a*\f[1]}
 \integer{c=\a*\f[2]}
\statement{
Parmi les nombres ci-dessous lequel est égal à \(\frac{\b}{\c}) ?}
\choice{Réponse}{\rep}{\list}
#endif

#if defined TARGET_simplifier2
 \title{TITRE 2}
 \text{list=\(\frac{1}{2}),\(\frac{1}{3}),\(\frac{2}{3}),\(\frac{3}{4}),\(\frac{1}{4})}
 \text{list2=1,2
1,3
2,3
3,4
1,4}
 \text{ch=shuffle(1,2,3,4,5)}
 \text{left=}
 \text{right=}
 \for{k=1 to 4}{
  \text{tmp=row(\ch[\k],\list2)}
  \text{tmp2=item(\ch[\k],\list)}
  \text{right=wims(append item \tmp2 to \right)}
  \integer{r=randint(2..8)}
  \integer{b=\r*\tmp[1]}
  \integer{c=\r*\tmp[2]}
  \text{left=wims(append item \(\frac{\b}{\c}) to \left)}
 }
\statement{
Mettre en correspondance les fractions égales.
<div class="wimscenter">\embed{r1,60x100x100}</div>}
\answer{}{\left;\right}{type=correspond}
#endif

#if defined TARGET_simplifier3
 \title{TITRE 3}
 \text{list=\(\frac{1}{2}),\(\frac{1}{5}),\(\frac{2}{5}),\(\frac{3}{4}),\(\frac{1}{4})}
 \text{list2=1,2
1,5
2,5
3,4
1,4}
 \text{ch=shuffle(1,2,3,4,5)}
 \text{left=}
 \text{right=}
 \for{k=1 to 4}{
  \text{tmp=row(\ch[\k],\list2)}
  \text{tmp2=item(\ch[\k],\list)}
  \text{right=wims(append item \tmp2 to \right)}
  \integer{r=100/\tmp[2]}
  \integer{b=\r*\tmp[1]}
  \integer{c=\r*\tmp[2]}
  \text{left=wims(append item \(\frac{\b}{\c}) to \left)}
 }
\statement{
Mettre en correspondance les fractions égales.
<div class="wimscenter">\embed{r1,60x100x100}</div>}
\answer{}{\left;\right}{type=correspond}
#endif

#if defined TARGET_simplifier4
 \title{TITRE 4}
 \text{fr=randrow(1,2
7,5
2,5
3,4
7,4)}
 \integer{a=randint(2,5,10)}
 \integer{n=\fr[1]*\a}
 \integer{d=\fr[2]*\a}
 \statement{
Quelle est l'écriture simplifiée de la fraction \(\frac{\n}{\d}) ?}
 \answer{\(\frac{\n}{\d})}{\n/\d}{type=numexp}
#endif

#if defined TARGET_simplifier5
 \title{TITRE 5}
 \text{fr=randrow(1,2
7,5
2,5
3,4
7,4)}
 \integer{a=randint(4,9,6)}
 \integer{n=\fr[1]*\a}
 \integer{d=\fr[2]*\a}
 \statement{
Quelle est l'écriture simplifiée de la fraction \(\frac{\n}{\d}) ?}
\answer{\(\frac{\n}{\d})}{\fr[1]/\fr[2]}{type=numexp}

\solution{\(\frac{\n}{\d} = \frac{\fr[1]\times \a}{\fr[2] \times \a} = \frac{\fr[1]}{\fr[2]}).}

#endif
