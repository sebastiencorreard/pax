target = calcul fraction priorite calcdivers

\language{fr}
\range{-5..5}
\author{Rectorat de Nice}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}


#if defined TARGET_calcul
 \title{Calcul avec parenthèses}
 \text{val=shuffle(2,3,4,5,6,7,8)}
 \integer{b=randint(3..9)}
 \integer{a=randint(\b+1..20)}
\text{enonce=\val[1]-\val[2]-\val[3]*\val[4],\val[1]-\val[2]-\val[3]\times \val[4]
\val[1]-(\val[2]-\val[3]*\val[4]),\val[1]-(\val[2]-\val[3]\times \val[4])
\val[1]-(\a-\b)*\val[4],\val[1]-(\a-\b)\times \val[4]}
#endif

#if defined TARGET_calcdivers
 \title{Calcul divers}
 \text{enonce=2.25+6.75-5.5-2.5,2.25+6.75-5.5-2.5
450-11*10+4*2.5 ,450-11 \times 10+4\times 2.5
10+7/0.1-18/3+2.5,10+7:0.1-\frac{18}{3}+2.5}
 \text{compenonce=et écrire les résultats sous forme simplifiée}
#endif

#if defined TARGET_fraction
 \title{Calculer avec des fractions}
\integer{d=randitem(2,3,5)}
\integer{b=randitem(13,15)}
\integer{a=randitem(2,3,5,7,9)}
\integer{c=randitem(2,3)*\a}
\text{n=shuffle(2,5,7,11)}
\integer{e=\n[1]*\n[2]}
 \text{enonce=11/\a + 9/\c,\frac{11}{\a} + \frac{9}{\c}
\b/\d-4/\d*7/3,\frac{\b}{\d}-\frac{4}{\d} \times \frac{7}{3}
\e/\n[3] * \n[4]/\n[1],\frac{\e}{\n[3]} \times \frac{\n[4]}{\n[1]}}
 \text{compenonce=et écrire les résultats sous forme simplifiée}
#endif

#if defined TARGET_priorite
 \title{Priorités opératoires}
 \text{enonce=4-7-8,4-7-8
3-(14-3),3-(14-3)
(7.6-9.6)+(-10.75-2.25),(7.6-9.6)+(-10.75-2.25)}
#endif

\text{don=shuffle(1,2,3)}
\text{good=}
\text{affichage=}
\for{j=1 to 3}{
 \text{tmp=row(\don[\j],\enonce)}
 \text{donnees=item(1,\tmp)}
 \text{tmp=item(2,\tmp)}
 \text{affichage=wims(append item \tmp to \affichage)}
 \text{tmp=simplify(\donnees)}
 \text{good=wims(append item \tmp to \good)}
}

\statement{
Calculer les expressions suivantes \compenonce :
<ul>
<li>\(A = \affichage[1])
<div>\(A\) = \embed{r1,\size}</div>
</li><li>
 \(B = \affichage[2])
<div>\(B\) = \embed{r2,\size}</div>
</li><li>
 \(C = \affichage[3])
<div>\(C\) = \embed{r3,\size}</div>
</li>
</ul>}

\reply{Réponse}{\good[1]}{type=numexp}
\reply{Réponse}{\good[2]}{type=numexp}
\reply{Réponse}{\good[3]}{type=numexp}
