target=ecritensemb
#define GGG D1 -
\title{GGG Ecriture ensembliste d'événements}
\description{exercice sur l'écriture d'événements simples à l'aide des notations ensemblistes.}
\observation{La question porte sur un événement choisi parmi 9 différents constitué à partir d'au plus deux ensembles.}
\keywords{set_theory,events}
\language{fr}
\author{Sophie, Lemaire}
\email{sophie.lemaire@universite-paris-saclay.fr}
#include "css.inc"
#include "common.inc"
\computeanswer{no}
\format{html}
\integer{c=randint(1..2)}
\text{l1=A,B}
\text{l2=B,A}
\text{ens1=item(\c,\l1)}
\text{ens2=item(\c, \l2)}
\integer{u=randint(1,2)}
\text{symb=\(A\) ,\(B\) ,\(A^c\) ,\(B^c\) ,\(\cup\),\(\cap\)}
#include "lang_ecritensemb_fr.inc"
\if{\lang=it}{
#include "lang_ecritensemb_it.inc"
}
\if{\lang=es}{
#include "lang_ecritensemb_es.inc"
}
\matrix{listens=\name_listens[1;], \(\ens1\)|\(\ens1\),\(\cup\),\(\ens1\)|\(\ens1\),\(\cap\),\(\ens1\)
\name_listens[2;],\(\ens1^c\)| \(\ens1^c\),\(\cap\),\(\ens1^c\) | \(\ens1^c\),\(\cup\),\(\ens1^c\)
\name_listens[3;],\(A\), \(\cup\),\(B\) | \(B\),\(\cup\),\(A\)
\name_listens[4;],\(\ens1\),\(\cap\),\(\ens2^c\) |\(\ens2^c\),\(\cap\),\(\ens1\)
\name_listens[5;], \(\ens1\),\(\cap\),\(\ens2\)|\(\ens2\),\(\cap\),\(\ens1\)
\name_listens[6;],\(A^c\),\(\cap\),\(B^c\)|\(B^c\),\(\cap\),\(A^c\)
\name_listens[7;], \(\ens1^c\),\(\cup\),\(\ens2\) | \(\ens2\),\(\cup\),\(\ens1^c\)
\name_listens[8;],\(\ens1^c\),\(\cup\),\(\ens2^c\)|\(\ens2^c\),\(\cup\),\(\ens1^c\)
\name_listens[9;],\(\ens1^c\),\(\cap\),\(\ens2^c\) | \(\ens2^c\),\(\cap\),\(\ens1^c\)}

\integer{ligne=randint(1..9)}
\text{question = \listens[\ligne;] }
\integer{ cnt = items(\question)}
\text{enonce = \question[1]}
\text{choix=\question[2..\cnt]}
\text{NB=wims(record 1 of notations.\lang)}
\text{notation1=wims(record 3 of notations.\lang)}
\text{notation2=wims(record 5 of notations.\lang)}

\steps{reply1}
\statement{ \notation1 \instruction \notation2
<div class="wims_question">
<p>\name_question? </p>
<div class="center color1">\enonce</div>
<div class="wimscenter">\(F\) = \embed{reply1,50x30x3}.</div>
</div>}

\answer{Ensemble \(F\) : }{\choix;\symb}{type=clickfill}
\text{rep=wims(replace internal \(\cap\) by and in \reply1)}
\text{rep=wims(replace internal \(\cup\) by or in \rep)}
\text{rep=wims(replace internal , by in \rep)}

\feedback{\ligne=1 and ((\reply1 issametext \(\ens1\),\(\cap\),\(\ens1\))
or (\reply1 issametext \(\ens1\),\(\cup\),\(\ens1\)))}{
\name_feedback
\(\ens1\)}
\feedback{\ligne=2 and ((\reply1 issametext \(\ens1^c\),\(\cap\),\(\ens1^c\))
or (\reply1 issametext \(\ens1^c\),\(\cup\),\(\ens1^c\)))}{
\name_feedback \(\ens1^c\)
}
\help{\NB}
