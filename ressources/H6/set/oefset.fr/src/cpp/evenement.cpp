target=evenement
#define GGG D3 -
\title{GGG Evénements et ensembles}
\description{exercice comportant trois questions sur la description ensembliste d'un événement.}
\observation{L'événement est formé à partir d'au plus 3 ensembles.}
\keywords{set_theory,events}
\language{fr}
\author{Sophie, Lemaire}
\email{Sophie.Lemaire@math.u-psud.fr}
\computeanswer{no}
\format{html}
#include "common.inc"
#include "css.inc"
\integer{c=randint(1..3)}
\text{l1=A,B,C}
\text{l2=B,C,A}
\text{l3=C,A,B}
\text{ens1=item(\c,\l1)}
\text{ens2=item(\c, \l2)}
\text{ens3=item(\c, \l3)}
\integer{u=randint(1,2)}

#include "lang_evenement_fr.inc"
\if{\lang=it}{
#include "lang_evenement_it.inc"
}
\if{\lang=es}{
#include "lang_evenement_es.inc"
}
\text{listens=\(A\cup B \cup C\), \(\ens1\), \(\ens1\cap \ens2^c \cap \ens3^c\),\((A\cap B)\cup (A\cap C)\cup (B\cap C)\), \(\ens1\cap \ens2),\(\ens1\cup \ens2),\(\ens1\cap \ens2\cap \ens3^c),\(A\cap B \cap C)}
\text{listens2=\(A^c\cap B^c \cap C^c\), \(\ens1^c\), \(\ens1^c\cup \ens2 \cup \ens3), \((A^c\cap B^c)\cup (A^c\cap C^c)\cup (B^c\cap C^c)\),\(\ens1^c\cup \ens2^c), \(\ens1^c\cap \ens2^c),\(\ens1^c\cup \ens2^c\cup \ens3), \(A^c\cup B^c\cup C^c)}
\text{lisnum=1,2,3,4,5,6,7,8}
\text{choix=slib(data/random 4, \lisnum)}
\integer{num=slib(data/random 1, \choix)}
\text{choixc=slib(data/random 4, \lisnum)}
\text{choixc=\num,\choixc}
\text{choixc=wims(listuniq \choixc)}
\text{choixc=shuffle(\choixc)}
\integer{posit=position(\num,\choix)}
\integer{positc=position(\num,\choixc)}
\integer{nb=items(\choixc)}
\if{\u=1}{
\text{quest=item(\num,\evnt)}
\text{choix1=item(1,\choix)}
\text{choix1c=item(1,\choixc)}
\text{listrep=item(\choix1,\listens)}
\text{listrepc=item(\choix1c,\listens2)}
\text{listevc=item(\choix1c,\evnt2)}
\for{i=2 to 4}{
  \text{choix1=item(\i,\choix)}
  \text{choix1c=item(\i,\choixc)}
  \text{listrep=\listrep,item(\choix1,\listens)}
  \text{listrepc=\listrepc,item(\choix1c,\listens2)}
  \text{listevc=\listevc,item(\choix1c,\evnt2)}
  }
\if{\nb=5}{
  \text{choix1c=item(5,\choixc)}
  \text{listrepc=\listrepc,item(\choix1c,\listens2)}
  \text{listevc=\listevc,item(\choix1c,\evnt2)}
  }
}
{
\text{quest=item(\num,\evnt2)}
\text{choix1=item(1,\choix)}
\text{choix1c=item(1,\choixc)}
\text{listrep=item(\choix1,\listens2)}
\text{listrepc=item(\choix1c,\listens)}
\text{listevc=item(\choix1c,\evnt)}

\for{i=2 to 4}{
  \text{choix1=item(\i,\choix)}
  \text{choix1c=item(\i,\choixc)}
  \text{listrep=\listrep,item(\choix1,\listens2)}
  \text{listrepc=\listrepc,item(\choix1c,\listens)}
  \text{listevc=\listevc,item(\choix1c,\evnt)}
  }
\if{\nb=5}{
  \text{choix1c=item(5,\choixc)}
  \text{listrepc=\listrepc,item(\choix1c,\listens)}
  \text{listevc=\listevc,item(\choix1c,\evnt)}
  }
}
\text{ev=item(\posit,\listrep)}
\text{evc=item(\positc,\listevc)}
\text{cnt = items(\listrep)}
\text{cntc = items(\listevc)}
\text{cntcc = items(\listrepc)}
\text{mix = shuffle(\cntcc)}
\text{listrepc = \listrepc[\mix]}
\text{positrepc = position(\positc,\mix)}
\text{NB=wims(record 1 of notations.\lang)}
\text{instruction=wims(record 3  of notations.\lang) wims(record 4  of notations.\lang)}
\text{instruction=\instruction wims(record 5  of notations.\lang)}
\steps{reply1
reply2
reply3}
\statement{\instruction
<div class="wims_question">
<ol><li>
\name_question[1;]?
<div class="color1 center bold">\quest</div>
\if{\step=1}{
 <ul>
  \for{h = 1 to \cnt}{<li>\embed{reply1, \h}</li>}
 </ul>
</li>
}
\if{\step>1}{
<div class="oef_indgood">\name_question[2;] \ev.</div></li><li>
\name_question[3;] \(F^c\) ?}
\if{\step=2}{
 <ul>
  \for{k = 1 to \cntc}{<li>\embed{reply2, \k}</li>}
 </ul>
</li>
}
\if{\step>2}{
<div class="oef_indgood">\name_question[4;]
  <div class="color1 center bold">\evc</div>
</div></li>
<li>\name_question[5;] \(F^c\) ?
 <ul>
 \for{k = 1 to \cntcc}{<li>\embed{reply3, \k}</li>}
 </ul>
 </li>}
</ol>
</div>}
\help{\NB}
\answer{\label[1] \(F\) : }{\posit;\listrep}{type=radio}
\answer{\label[2] \(F^c\) : }{\positc;\listevc}{type=radio}
\answer{\label[1] \(F^c\) : }{\positrepc;\listrepc}{type=radio}
