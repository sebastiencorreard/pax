target=indic
#define GGG A4 -
\title{GGG Fonctions indicatrices}
\description{il s'agit de trouver comment les opérations sur deux ensembles se traduisent en des opérations sur les fonctions indicatrices de ces ensembles.}
\observation{Les questions portent sur les 4 opérations de base : union, intersection, passage au complémentaire et produit cartésien.}
\keywords{set_theory}
\language{fr}
\range{-5..5}
\author{Bernadette, Perrin-Riou; Sophie, Lemaire}
\email{bernadette.m.riou@orange.fr;sophie.lemaire@universite-paris-saclay.fr}
\computeanswer{no}
\format{html}
#include "common.inc"
#include "lang_indic_fr.inc"
\if{\lang=it}{
#include "lang_indic_it.inc"
}
\if{\lang=es}{
#include "lang_indic_es.inc"
}
\integer{s=random(1,2)}
\integer{t=random(1,2)}
\integer{choix=random(1,2,3)}
\text{k=item(\choix,\cup,\cap,\times)}
\text{a1= \s=1? a: (1-a)}
\text{b1= \t=1? b: (1-b)}
\text{rep1= \choix=1? \a1 + \b1 - \a1*\b1}
\text{rep1= \choix=2? \a1*\b1}
\text{rep1= \choix=3? \a1*\b1}
\text{notat=\choix=3 ? \name_choix[1;]:\name_choix[2;]}

\if{\t=1}{
  \text{enonce= \s=1? A \k B: A^c \k B}
  }{
  \text{enonce= \s=1? A \k B^c: A^c \k B^c}
  }
\text{sol=wims(replace internal a by \(1_A(x)\) in \rep1)}
\if{\choix=3}{
  \text{y=y}\text{point=(x,y)}
  \text{sol=wims(replace internal b by \(1_B(y)\) in \sol)}
  }{
  \text{y=x}
  \text{point=x}
  \text{sol=wims(replace internal b by \(1_B(x)\) in \sol)}
  }
\text{sol=wims(replace internal * by in \sol)}
\text{NB=wims(record 1 of notations.\lang)}
\statement{\notat.
\instruction[1;]
\(\enonce\) \instruction[2;] \(\point\), \instruction[3;]
\(a = 1_A(x)), \(b = 1_B(\y)).
<div class="wimscenter">
           \(1_{\enonce}(\point)\) = \embed{reply 1, 30}
</div>
}
\answer{}{\rep1}{type=function}
\help{<ul><li>\NB</li>
<li>
\name_help
</li></ul>}
\feedback{1=1}{
<div class="wimscenter">\(1_{\enonce}(\point)) = \sol.</div>}
