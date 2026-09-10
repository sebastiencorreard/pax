target=injsurj
#define GGG E2 -
\title{GGG Injectivité, surjectivité}
\description{exercice de type QCM sur les propriétés des fonctions entre deux ensembles finis.}
\observation{}
\keywords{set_theory,maps}
\language{fr}
\range{-30..30}
\author{Bernadette, Perrin-Riou}
\email{bernadette.m.riou@orange.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "common.inc"
#include "lang_injsurj_fr.inc"
\if{\lang=it}{
#include "lang_injsurj_it.inc"
}
\if{\lang=es}{
#include "lang_injsurj_es.inc"
}
\integer{r=randitem(1,2,3)}
\text{listess=<, >, =}
\text{ss=item(\r,\listess)}

\integer{h=random(1,2,3,4)}

\text{cas= item(\h,\listecas)}

\text{choix= \inj,\bij,\surj,\aut}
\matrix{solution= \inj,\inj,\surj&#44\bij,\surj&#44\bij
\surj,\surj, \inj&#44\bij,\inj&#44\bij
\surj&#44\inj&#44\bij, \surj&#44\inj&#44\bij,\aut,\aut
}
\matrix{solu= row(\r, \solution)}
\text{sol1= item(\h,\solu)}
\text{sol=wims(replace &#44 by , in \sol1)}

\statement{\instruction
card \(E) \(\ss) card \(F). \cas
\embed{choice 1 }.
<div class="wims_instruction">
\warning
</div>}

\choice{}{ \sol}{\aut,\choix}
