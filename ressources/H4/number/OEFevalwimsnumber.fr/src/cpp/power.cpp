target=power1 power2 power3 power4 power5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}

#if defined TARGET_power1
 \title{Calcul avec des puissances I}
\text{tverb=Multiplier}
\integer{a=randint(4..9)}
\integer{b=randint(4..9)}
\integer{c=randint(11..16)}
\integer{d=\c-randint(3..5)}
\text{A=\a \times 10^{\c}}
\text{B=-\b \times 10^{-\d}}
\text{taction=\(\text{Multiplier}\; \A\; \text{par}\; \B)}
\real{sol=-\a*\b*10^(\c-\d)}
\real{precis=10^(\c-\d)}

#endif
#if defined TARGET_power2
 \title{ Calcul avec des puissances II}
\text{tverb=Diviser}
\integer{k=randint(4,6,7,8,9)}
\integer{a=\k*randint(9..15)}
\integer{b=\k*randint(2,4,5,8)}
\integer{c=randint(11..16)}
\integer{d=\c+randint(1,2)*randint(1,-1)}
\text{A=\a \times 10^{\c}}
\text{B=\b \times 10^{\d}}
\text{taction=\(\text{Diviser}\;\; \A \;\text{par}\;\; \B)}
\text{trep=en tronquant au centième}
\real{u=(\a*10^\c)/(\b*10^(\d))*100}
\integer{v=floor(\u)}
\real{sol=\v/100}
\integer{precis=10^(\c-\d)}
#endif

#if defined TARGET_power3
 \title{ Calcul avec des puissances III}
\text{tverb=Ajouter}
\integer{a=randint(11..50)}
\integer{b=randint(13..60)}
\integer{c=randint(2..4)}
\integer{d=randint(1..3)}
\text{A=\a \times 10^{\c}}
\text{B=\b \times 10^{-\d}}
\text{taction=\(\text{Ajouter}\; \A \; \text{et}\; \B)}
\real{sol=(\a*10^\c)+(\b*10^(-\d))}
\real{precis=10^(\c+\d)}
#endif

#if defined TARGET_power4
 \title{ Calcul avec des puissances IV}
\text{tverb=Retrancher}
\integer{a=randint(11..50)}
\integer{b=randint(13..60)}
\integer{c=randint(1..3)}
\integer{d=\c-4}
\text{A=\a \times 10^{\c}}
\text{B=\b \times 10^{\d}}
\text{taction=\(\text{Effectuer}\; \A - \B)}
\real{sol=(\a*10^\c)-(\b*10^(\d))}
\integer{precis=10^(\c)}

#endif

#if defined TARGET_power5
 \title{ Calcul avec des puissances V}
\text{tverb=Elever au carré}
\integer{a=randint(2..9)}
\integer{b=randint(2..8)}
\integer{c=\a>3?randint(1,2):randint(1..2)}
\integer{c2=2*\c}
\integer{d=\c2<6?randint(1,2):1}
\text{A=(\a \times 10^{\c})^2}
\text{B=\b \times 10^{-\d}}
\text{taction=\(\text{Effectuer}\; \A + \B)}
\real{sol=(\a*10^\c)^2+(\b*10^(-\d))}
\integer{precis=10^(2*\c)}
#endif

\precision{100000000}
\statement{<div class="warning">A faire sans calculatrice!</div>
<b>\tverb</b> :
<div class="wimscenter">\taction</div>
  Écrire la réponse sous forme décimale \trep.
<div class="wimscenter"><label for="reply1">Votre solution</label>:\embed{reply1}
</div>
}
\answer{}{\sol}{type=numeric}
