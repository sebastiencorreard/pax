target=oefrelcalsomme  oefrelcalexp0  oefrelcalexp1 oefrelcalexp2

\langage{fr}
\author{Jean-Luc, Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}
\precision{1000000}

\text{sign=-,+}
\text{s1=randint(1,2)}
\text{s2=randint(1,2)}
\text{s3=randint(1,2)}

#if defined TARGET_oefrelcalsomme
\title{Somme algébrique}
\text{ecrsg=&#150;,+,&#177;}
\text{ops=\sign}
\integer{nb1=randint(1..29)}
\integer{nb2=randint(1..29)}
\integer{nb3=randint(1..19)}
\text{op1=randint(1,2)}
\text{op2=randint(1,2)}
\real{res=\sign[\s1]\nb1\ops[\op1]\sign[\s2]\nb2\ops[\op2]\sign[\s3]\nb3}
#endif

#if defined TARGET_oefrelcalexp0
\title{Expression numérique avec des petits relatifs}
\text{ecrsg=&#150;,+,\(times),&#177;}
\text{ops=-,+,*}
\integer{nb1=randint(1..7)}
\integer{nb2=randint(1..9)}
\integer{nb3=randint(1..5)}
\text{a=shuffle(2)}
\text{op1=\a[1]+1}
\text{op2=\a[2]+1}
\real{res=\sign[\s1]\nb1\ops[\op1]\sign[\s2]\nb2\ops[\op2]\sign[\s3]\nb3}
#endif

#if defined TARGET_oefrelcalexp1
\title{Expression numérique avec des relatifs 1}
\text{ecrsg=&#150;,+,\(times),&#177;}
\text{ops=-,+,*}
\integer{nb1=randint(1..19)}
\integer{nb2=randint(1..9)}
\integer{nb3=randint(1..19)}
\text{a=shuffle(2)}
\text{op1=\a[1]+1}
\text{op2=\a[2]+1}
\real{res=\sign[\s1]\nb1\ops[\op1]\sign[\s2]\nb2\ops[\op2]\sign[\s3]\nb3}
#endif

#if defined TARGET_oefrelcalexp2
\title{Expression numérique avec des relatifs 2}
\text{ecrsg=+,&#150;,\(times),&#177;}
\text{ops=+,-,*}
\integer{nb1=randint(1..19)}
\integer{nb2=randint(1..9)}
\integer{nb3=randint(1..19)}
\text{a=shuffle(2)}
\text{op1=\a[1]+1}
\text{op2=\a[2]+1}
\real{res=\sign[3-\s1]\nb1\ops[\op1]\sign[3-\s2]\nb2\ops[\op2]\sign[3-\s3]\nb3}
#endif


\statement{
<p>Donner le résultat du calcul suivant :</p>
<div class="wimscenter">
 ( \ecrsg[\s1] \nb1 ) \ecrsg[\op1] ( \ecrsg[\s2] \nb2 ) \ecrsg[\op2] ( \ecrsg[\s3] \nb3 )
=
\embed{r1}</div>
}

\answer{}{\res}{type=numeric}
