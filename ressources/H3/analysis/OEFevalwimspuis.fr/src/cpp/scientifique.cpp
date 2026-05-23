target=scientifique2,scientifique3,scientifique4,scientifique5
#define TITRE Notation scientifique
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

#if defined TARGET_scientifique2
 \title{TITRE 2}
 \integer{enonce=randint(1000..99999)}
 \integer{nb=wims(charcnt \enonce)}
 \integer{exp=\nb-1}
 \real{dec=\enonce/10^(\exp)}
#endif

#if defined TARGET_scientifique3
 \title{TITRE 3}
 \integer{enonce=randint(1000..99999)}
 \integer{nb=wims(charcnt \enonce)}
 \integer{ch=randint(1..2)}
 \real{enonce=\enonce/10^(\ch)}
 \integer{exp=\nb-1-\ch}
 \real{dec=\enonce/10^(\exp)}
#endif

#if defined TARGET_scientifique4
 \title{TITRE 4}
 \integer{enonce=randint(1111..99999)}
 \integer{p=randitem(1,-1)*randint(2..7)}
 \integer{ch=randint(1..2)}
 \real{don=\enonce/10^(\ch)}
 \integer{nb=floor(\don)}
 \integer{nb=wims(charcnt \nb)}
 \text{enonce=\don \times 10^{\p}}
 \integer{exp=\nb-1}
 \real{dec=\don/10^(\exp)}
 \integer{exp=\exp+\p}
#endif

#if defined TARGET_scientifique5
 \title{TITRE 5}
 \integer{enonce=randint(0..9)*100+randint(1..9)*10+randint(1..9)}
 \integer{p=randitem(1,-1)*randint(2..7)}
 \integer{ch=randint(1..2)+3}
 \real{don=\enonce/10^(\ch)}
 \text{nb=wims(text select char 0 in \don)}
 \integer{nb=wims(charcnt \nb)}
 \text{enonce=\don \times 10^{\p}}
 \integer{exp=\nb}
 \real{dec=\don*10^(\exp)}
 \integer{exp=-(\exp)+\p}
#endif


\statement{
Donner l'écriture scientifique du nombre suivant :
<div class="wimscenter">\(\enonce =) \embed{r1,15} \(\times 10)<sup>\embed{r2,3}</sup></div>}

\answer{Partie décimale}{\dec}{type=numexp}
\answer{Exposant}{\exp}{type=numexp}
