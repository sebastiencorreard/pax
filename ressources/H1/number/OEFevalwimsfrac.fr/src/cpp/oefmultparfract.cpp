target=oefmultparfract2 oefmultparfract3
#define TITRE Multiplier par une fraction
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

#if defined TARGET_oefmultparfract2
\title{TITRE 2}
\text{lt=shuffle(2,3,4,5,6,7,8,9)}
\integer{n1=\lt[1]}
\integer{d1=\lt[2]}
\integer{m=floor(99/\d1)}
\integer{m=randint(3..\m)}
\integer{nb=\m*\d1}
\integer{rep1=\m*\n1}
\text{enonc=Calculer et donner le résultat : }
#endif

#if defined TARGET_oefmultparfract3
\title{TITRE 3}
\text{lt=shuffle(2,3,4,5,6,7,8,9)}
\integer{n1=\lt[1]}
\integer{d1=\lt[2]}
\integer{m=floor(9999/\d1)}
\integer{m=randint(3..\m)}
\real{nb=\m*\d1/100}
\real{rep1=\m*\n1/100}
\text{enonc=Calculer et donner le résultat :}
#endif

\text{rep1=slib(numeration/ecriturenombre \rep1)}
\text{rep1=wims(translate . to , in \rep1)}

\statement{
\enonc
<div class="wimscenter">
\(\nb \times \frac{\n1}{\d1} \) = \embed{r1,5}
</div>
<div class="wims_instruction">Vous utiliserez la virgule comme séparateur décimal
et respecterez l'espace tous les trois chiffres et éviterez les zéros inutiles
</div>
}

\answer{}{\rep1}{type=raw}
