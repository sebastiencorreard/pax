target=oefhoraire1 oefhoraire2 oefhoraire3
#define TITRE Horaires
#if defined TARGET_oefhoraire1
#define NUM 1
#endif
#if defined TARGET_oefhoraire2
#define NUM 2
#endif
#if defined TARGET_oefhoraire3
#define NUM 3
#endif
\title{TITRE NUM}
\text{name_depl=avion,train,voiture}
\text{name_unit=semaine,jour,heure,minute,seconde}
\text{name_units=semaines,jours,heures,minutes,secondes}

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
\text{depl=randitem(\name_depl)}
\text{unit=\name_unit}
\text{units=\name_units}
\text{abr=\name_unit[1],j,h,min,s}
\text{conv=7,24,60,60}
\text{sign=+}
\integer{ch=3}

\integer{a1=randint(7..20)}
\integer{b1=randint(2..59)}
\integer{a2=randint(1..22-\a1)}
\integer{b2=randint(61-\b1..59)}

\integer{r=\a1+\a2}
\integer{s=\b1+\b2}
\integer{t=floor(\s/\conv[\ch])}
\integer{s=\s-\t*\conv[\ch]}
\integer{r=\r+\t}
#if defined TARGET_oefhoraire1
\text{rep=\r \abr[\ch] \s \abr[\ch+1]}
\text{name_stat=fait un voyage en,
  part à,
  Son voyage dure,
  Quelle est son heure d'arrivée}
\text{var=\a1,\b1,\a2,\b2}
#endif
#if defined TARGET_oefhoraire2
\text{rep=\a1 \abr[\ch] \b1 \abr[\ch+1]}
\text{name_stat=fait un voyage en,
  arrive à,
  Son voyage a duré,
  Quelle était son heure de départ}
\text{var=\r,\s,\a2,\b2}
#endif
#if defined TARGET_oefhoraire3
\text{rep=\a2 \abr[\ch] \b2 \abr[\ch+1]}
\text{name_stat=fait un voyage en,
  part à,
  \sa[\k] arrive,
  Quelle est la durée de son voyage}
\text{var=\a1,\b1,\r,\s}
#endif

\statement{\nom \name_stat[1] \depl :
<ul>
<li>\sa[\k] \name_stat[2] \var[1] \abr[\ch] \var[2] \abr[\ch+1]. </li>
<li>\name_stat[3] \var[3] \abr[\ch] \var[4] \abr[\ch+1].</li>
</ul>
<div class="spacer">\name_stat[4] ? \embed{r1,20}</div>

<div class="wims_instruction">
<ul><li>Rappel des unités :
h : heure ; min : minute ; s : seconde.
</li><li>Exemple pour le format de réponse : 11 h 4 min; 1 h 45 min</li>
</ul>
</div>}
\answer{}{\rep}{type=raw}{option=nocase,nospace}
