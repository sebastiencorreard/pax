target=oefvocabfract3 oefvocabfract4
#define TITRE Vocabulaire
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

\integer{f=randint(1..3)}
\if{\f<3}{
\integer{d2=random(2,4,5,8,10,16)}
\integer{d1=randint(1..9)}
\if{\d1=\d2}{\integer{d1=\d1+1}}
}
{\integer{d2=randint(2..9)}
\integer{d1=randint(2..9)}
\if{\d1=\d2}{\integer{d2=\d2+1}}
\integer{d1=\d2*\d1}}
\real{q=\d1/\d2}
\text{mot=numérateur,dénominateur,quotient}
\text{nomb=\d1,\d2,\q}

#if defined TARGET_oefvocabfract3
\title{TITRE 3}
\text{a=shuffle(3)}
\text{enonc1=Le \mot[\a[1]] de la fraction est le nombre }
\text{rep1=\nomb[\a[1]]}
\text{enonc2=Le \mot[\a[2]] de la fraction est le nombre }
\text{rep2=\nomb[\a[2]]}
\text{enonc3=Le \mot[\a[3]] de la fraction est le nombre }
\text{rep3=\nomb[\a[3]]}
\integer{large=5}
#endif

#if defined TARGET_oefvocabfract4
\title{TITRE 4}
\text{a=shuffle(3)}
\text{enonc1=Pour la fraction, le nombre \nomb[\a[1]] se nomme le }
\text{rep1=\mot[\a[1]]}
\text{enonc2=le nombre \nomb[\a[2]] se nomme le }
\text{rep2=\mot[\a[2]]}
\text{enonc3=le nombre \nomb[\a[3]] se nomme le }
\text{rep3=\mot[\a[3]]}
\integer{large=12}
#endif

\statement{Nous avons le calcul suivant :
<div class="wimscenter"> \(\frac{\d1}{\d2} = \q) </div>
<ul>
<li>\enonc1 \embed{r1,\large}.</li>
<li>\enonc2 \embed{r2,\large}.</li>
<li>\enonc3 \embed{r3,\large}.</li>
</ul>}

\answer{}{\rep1}
\answer{}{\rep2}
\answer{}{\rep3}
