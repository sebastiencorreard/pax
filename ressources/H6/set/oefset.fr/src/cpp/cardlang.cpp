target=cardlang
#define GGG C4 -
\title{GGG Répartition d'élèves dans des options}
\description{exercice de dénombrement}
\observation{Les chiffres dans l'énoncé sont les seules données variables.}
\keywords{combinatorics,set_theory}
\language{fr}
\author{Bernadette, Perrin-Riou}
\email{bernadette.m.riou@orange.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "css.inc"
#include "common.inc"
\integer{A= random(100..200)}
\integer{Al= random(50..150)}
\integer{E= random(100..150)}
\integer{AAlE= random(5..20)}
\integer{AE= random(100..500)}
\integer{AAl= random(50..300)}

\integer{AlE= random(50..100)}

\integer{ptout= \A+\AE+\AAl+\AAlE+\E+\Al+\AlE}
\integer{rien=random(10..50)}
\integer{N= \rien+\ptout}
\integer{Ang= \A+\AE+\AAl+\AAlE}
\integer{Esp= \E+\AE+\AlE+\AAlE}
\integer{All= \Al+\AlE+\AAl+\AAlE}

\integer{aa= \AAl+\AAlE}
\integer{ae=\AE+\AAlE}
\integer{ale=\AlE+\AAlE}
#include "lang_cardlang_fr.inc"
\if{\lang=it}{
#include "lang_cardlang_it.inc"
}
\if{\lang=es}{
#include "lang_cardlang_es.inc"
}
\statement{<div class="color1">
\instruction</div>
<div class="wims_question">
<ol><li>
  \question[1;]
  \embed{reply1}
</li><li>
\question[2;]
 \embed{reply2}
</li></ol>
</div>}

\answer{\label[1;]}{\rien}
\answer{\label[2;]}{\AE}
