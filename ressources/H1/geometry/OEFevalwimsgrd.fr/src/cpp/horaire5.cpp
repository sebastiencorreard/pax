target=oefhoraire5
#define TITRE Horaires
#if defined TARGET_oefhoraire5
#define NUM 5
#endif
\title{TITRE NUM}

\langage{fr}
\author{Jean-Luc, Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}
\precision{100000}
\keywords{time}
\integer{k=randint(1..2)}
\text{sx=boy,girl}
\text{sa=Il,Elle}
\text{nom=slib(lang/fname fr,\sx[\k])}
\text{mois=janvier,février,mars,avril,mai,juin,juillet,août,septembre,octobre,novembre,décembre}
\text{jour=lundi,mardi,mercredi,jeudi,vendredi,samedi,dimanche}

\text{name_unit=semaine,jour,heure,minute,seconde}
\text{name_units=semaines,jours,heures,minutes,secondes}

\text{name_depl=bateau}
\text{unit=\name_unit}
\text{units=\name_units}
\text{abr=semaine,j,h,min,s}
\text{depl=randitem(\name_depl)}
\integer{jj=randint(1..7)}
\integer{md=randint(1..12)}
\integer{jd=randint(1..19)}
\integer{jl=randint(2..7)}

\text{conv=7,24,60,60}
\integer{ch=3}

\integer{a1=randint(7..20)}
\integer{b1=randint(2..59)}
\integer{a2=randint(1..23)}
\integer{b2=randint(10..59)}

\integer{r=\a1+\a2}
\integer{s=\b1+\b2}
\integer{t=floor(\s/\conv[\ch])}
\integer{s=\s-\t*\conv[\ch]}
\integer{r=\r+\t}

\integer{jja=\jj+\jl}
\integer{ja=\jd+\jl}

\if{\r>23}{\integer{jja=\jja+1}
  \integer{ja=\ja+1}
  \integer{r=\r-24}}

\if{\jja>7}{\integer{jja=\jja-floor(\jja/7)*7}}

\text{rep1=\jour[\jj] \jd \mois[\md]}
\text{rep2=\a1 \abr[\ch] \b1 \abr[\ch+1]}

\statement{\nom fait un voyage en \depl :
<ul>
<li>\sa[\k] arrive le \jour[\jja] \ja \mois[\md] à \r \abr[\ch] \s \abr[\ch+1]. </li>
<li>Son voyage a duré \jl jours \a2 \abr[\ch] \b2 \abr[\ch+1].</li>
</ul>
<p>Quelles étaient sa date et son heure de départ ?</p>
<ul>
<li>date : \embed{r1,20} <i>Exemple pour le format de réponse: lundi 12 janvier</i></li>
<li>heure : \embed{r2,20} <i>Exemple pour le format de réponse: 11 h 4 min; 1 h 45 min</i>.
</li>
</ul>
}

\answer{}{\rep1}{type=raw}{option=nocase,nospace}
\answer{}{\rep2}{type=raw}{option=nocase,nospace}
