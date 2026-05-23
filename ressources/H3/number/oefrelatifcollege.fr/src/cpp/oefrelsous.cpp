target=oefrelsous1 oefrelsous2 oefrelsous3 oefrelsous4 oefrelsous5
#define TITRE Soustraction des relatifs
\langage{fr}
\author{Jean-Luc, Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}
\text{sign1=random(+,-)}
\text{sign2=random(+,-)}
\if{\sign2=+}{\text{rep=-}}{\text{rep=+}}

#if defined TARGET_oefrelsous1
\title{TITRE 1}
\integer{nb1=randint(11..19)}
\integer{nb2=randint(4..9)}
#endif

#if defined TARGET_oefrelsous2
\title{TITRE 2}
\integer{nb1=randint(15..29)}
\integer{nb2=randint(16..49)}
#endif

#if defined TARGET_oefrelsous3
\title{TITRE 3}
\integer{nb1=randint(2..9)*10+randint(4..9)}
\integer{nb2=randint(97..99)}
#endif

#if defined TARGET_oefrelsous4
\title{TITRE 4}
\real{nb1=randint(1..7)*10+randint(2..9)}
\real{nb2=(randint(1..9)*10+randint(1..9))/10}
#endif

#if defined TARGET_oefrelsous5
\title{TITRE 5}
\integer{n=randint(1..2)}
\integer{m=randint(1..2)}
\if{\n=\m}{\integer{\m=\n+1}}
\real{nb1=(randint(1..7)*10+randint(2..9))/10^\n}
\real{nb2=(randint(1..9)*10+randint(1..9))/10^\m}
#endif

\real{res=\sign1\nb1-\sign2\nb2}
\statement{<p>Donnez le résultat de la soustraction :</p>
<div class="wimscenter">
 ( \sign1 \nb1 ) \(-) ( \sign2 \nb2 ) = ( \embed{r1,1} \nb1 ) + ( \embed{r2,1} \nb2 ) = \embed{r3,4}
</div>}

\answer{}{\sign1}{type=raw}
\answer{}{\rep}{type=raw}
\answer{}{\res}{type=numeric}
