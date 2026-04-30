target=calcul1,calcul2,calcul3,calcul4,calcul5

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Calcul réfléchi
\text{A=randitem(A,B,C,D,V)}

#if defined TARGET_calcul1
 \title{TITRE 1}
 \integer{a=randint(1..6)}
 \integer{c=10+\a}
 \text{enonce=\c^2}
#endif

#if defined TARGET_calcul2
 \title{TITRE 2}
 \integer{a=randint(2..4)}
 \integer{b=randint(1..4)}
 \integer{c=\a*10+\b}
 \text{enonce=randitem(12,11)*\c}
#endif

#if defined TARGET_calcul3
 \title{TITRE 3}
 \integer{a=randint(1..5)}
 \integer{b=randitem(100,1000)}
 \integer{c=\a+\b}
 \integer{d=\b-\a}
 \text{enonce=\c * \d}
#endif

#if defined TARGET_calcul4
 \title{TITRE 4}
 \integer{a=randint(2..6)}
 \integer{b=100}
 \integer{c=\b-\a}
 \text{enonce=\c^2}
#endif

#if defined TARGET_calcul5
 \title{TITRE 5}
 \integer{a=randint(5..12)}
 \integer{b=100}
 \integer{c=\b-\a}
 \text{enonce=\c^2}
#endif

\text{affichage=texmath(\enonce)}
\integer{rep=\enonce}

\statement{
  Calculer l'expression suivante :
<div class="wimscenter">\(\A = \enonce)</div>
<div class="wims_instruction">Vous devez effectuer ce calcul sans calculette.</div>
<p>
<b>Votre réponse :</b>
</p>
<div class="wimscenter">
\(\A =) \embed{r1,20}.
</div>
}

\reply{réponse}{\rep}{type=numexp}
