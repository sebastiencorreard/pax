target=calculette1 calculette2 calculette3 calculette4 calculette5
#define TITRE Utiliser sa calculatrice
#include "author.inc"

\text{p=shuffle(2,1,1,0,0,0,0)}
\integer{a=2^\p[1]*3^\p[2]*5^\p[3]*7^\p[4]*11^\p[5]*13^\p[6]*17^\p[7]}

#if defined TARGET_calculette1
 \title{TITRE 1}
 \text{calc=sqrt(\a)}
 \text{type=1}
#endif
#if defined TARGET_calculette2
 \title{TITRE 2}
 \text{calc=sqrt(\a)}
 \text{type=2}
#endif
#if defined TARGET_calculette3
 \title{TITRE 3}
 \text{calc=sqrt(\a)}
 \text{type=3}
#endif
#if defined TARGET_calculette4
 \title{TITRE 4}
 \real{a=(10*randint(100..1000)+randint(1..9))/10}
 \text{calc=sqrt(\a)}
 \text{type=1,2,3}
#endif
#if defined TARGET_calculette5
 \title{TITRE 5}
 \integer{a=randint(3..7)}
 \integer{b=randint(8..12)}
 \text{sg=randitem(-,+)}
 \integer{a2=\a^2}
 \integer{b2=\b^2}
 \text{calc=sqrt(\b2\sg\a2)}
 \text{type=1,2,3}
#endif

\integer{prec=random(1..3)}
\text{type=randitem(\type)}
\real{good=item(\type,rint(\calc*10^(\prec-1)),ceil(\calc*10^(\prec-1)),floor(\calc*10^(\prec-1)))}
\real{good=\good/10^(\prec-1)}

\text{listprec=à l'unité,au dixième,au centième}
\text{precision=item(\prec,\listprec)}
\text{ttype=item(\type,l'arrondi \precision,la valeur approchée \precision par excès,la valeur approchée \precision par défaut)}

\text{enonce=texmath(\calc)}

\statement{
  Utilisez votre calculatrice pour donner \ttype de :
<div class="wimscenter"> \(\enonce)</div>}

\answer{\(\enonce)}{\good}{type=numexp}
