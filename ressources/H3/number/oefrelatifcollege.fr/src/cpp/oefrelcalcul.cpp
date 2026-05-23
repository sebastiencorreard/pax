target=oefrelcaladd oefrelcalsoust oefrelcalmult

\langage{fr}
\author{Jean-Luc, Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}
\precision{1000000}

\text{sign=-,+}
\text{s1=randint(1,2)}
\text{s2=randint(1,2)}
\text{ecrsg=&#150;,+}

#if defined TARGET_oefrelcaladd
\title{Addition de relatifs}
\integer{nb1=randint(1..49)}
\integer{nb2=randint(1..49)}
\if{\nb1=\nb2}{\integer{nb2=\nb1+randint(1..9)}}
\text{op1=+}
\real{res=\sign[\s1]\nb1+\sign[\s2]\nb2}
#endif

#if defined TARGET_oefrelcalsoust
\title{Différence de relatifs}
\integer{nb1=randint(1..49)}
\integer{nb2=randint(1..49)}
\if{\nb1=\nb2}{\integer{nb2=\nb1+randint(1..9)}}
\text{op1=&#150;}
\real{res=\sign[\s1]\nb1-\sign[\s2]\nb2}
#endif

#if defined TARGET_oefrelcalmult
\title{Multiplication de relatifs}
\integer{nb1=randint(1..49)}
\integer{nb2=randint(1..49)}
\if{\nb1=\nb2}{\integer{nb2=\nb1+randint(1..9)}}
\text{op1=\(times)}
\real{res=\sign[\s1]\nb1*\sign[\s2]\nb2}
#endif

\statement{<p>Donner le résultat du calcul suivant :</p>
<div class="wimscenter">
 ( \ecrsg[\s1] \nb1 ) \op1 ( \ecrsg[\s2] \nb2 )
=
\embed{r1}
</div>
}

\answer{}{\res}{type=numeric}
