target= oefremplacer2 oefremplacer3
#define TITRE Remplacer dans
#if defined TARGET_oefremplacer2
   \title{TITRE (a+b)²}
   \text{signe=+}
#endif

#if defined TARGET_oefremplacer3
   \title{TITRE (a-b)² #}
   \text{signe=-}
#endif

\language{fr}
\range{-5..5}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@gmail.com}
\computeanswer{no}
\format{html}
\precision{10000}


\integer{confparm1=\confparm1}
\integer{confparm2=\confparm2}
\integer{confparm2=\confparm2= or NaN isin \confparm2?2}
\integer{confparm1=NaN isin \confparm1 or \confparm1=?1}
\integer{confparm3=\confparm3=?1}

#include "valeurs.inc"

\real{n=item(1,\valeurs)}

\text{a=random(1,1)*randint(2..15)}
\text{a=simplify(\a)}
\text{b=randint(2..15)}
\text{x=random(x,y)}
\real{rr=8*-3^0}

\text{lt=wims(values v for v=0 to \confparm1)}
\text{lt=shuffle(\lt)}
\integer{p1=item(1,\lt)}
\integer{p2=item(2,\lt)}

\text{m1=\a*\x^\p1}
\real{r1=\a*(\n)^\p1}
\text{m1=simplify(\m1)}
\text{rep1=texmath(\m1)}

\text{m2=\b*\x^\p2}
\real{r2=\b*(\n)^\p2}
\text{m2=simplify(\m2)}
\text{rep2=texmath(\m2)}

\if{\signe=+}{\real{r=(\r1 + \r2)^2}}{\real{r=(\r1 - \r2)^2}}
\text{rep=(\m1 \signe \m2)^2}

\text{rep8=slib(commutesom \rep,\x)}
\text{repf=texmath(item(6,\rep8))}

\statement{
Calculer l'expression E = \(\repf) avec la valeur \x = \n.
<div class="wimscenter">
Pour \x = \n , nous avons E =\embed{r1,10}.</div>
<p>
Calculer l'expression F = \(\rep) avec la valeur \x = \n.
</p>
<div class="wimscenter">
Pour \x = \n , nous avons F =\embed{r2,10}.
</div>
}

\answer{}{\r}{type=numeric}
\answer{}{\r}{type=numeric}
