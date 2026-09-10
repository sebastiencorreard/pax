target=tablemult

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\css{<style>
  .reponse {background-color: #ffcc99;
          color : black;
          margin: 2% 5%;
          padding: 2%;
  }
 </style>
 }

 \text{b = randitem(randint( 5..9), randint(11..14))}
 \text{tronque=shuffle(min(9,\b-1))}
 \integer{b2=\b/2}
 \text{tronque = \tronque[1..\b2]}
 \text{tronque =wims(sort numeric items  \tronque)}
 \text{n = randint (3..\b -1)}
 \text{z =}
\text{zn=wims(exec float_calc
obase=\b; ibase=10; \n)}
\text{zi=}

 \for{ i = 1 to \b-1}{
 \text{z= \z, wims(exec float_calc
obase=\b; ibase=10;\n*\i)}
\text{zi=\zi, wims(exec float_calc
obase=\b; ibase=10; \i)}
}
\text{zi=wims(nonempty items \zi)}
\text{z=wims(nonempty items \z)}

#include "lang.inc"

\statement{\name_statement
<table class="wimscenter">
\for{ j in \tronque} {
<tr><td>\zi[\j] \times \zn</td><td> = </td><td>\z[\j]</td></tr>}
</table>
}

\answer{\name_base}{\base}
\text{liste=}
\for{ k in \tronque}{
   \text{liste = \liste, wims(exec float_calc
obase=\base; ibase=10 ; \n*\k)}
}
\text{liste=wims(nonempty items \liste)}
\text{ listed=\z[\tronque]}
Ne marche pas à cause des lettres

\text{test=wims(listcomplement \listed in \liste)}
\text{position = position(\test[1],\liste)}
\text{erreur=items(\test)}
\condition{\name_condition}{\erreur=0}

\text{tronque2 = wims(sort numeric item \tronque,\base)}

\feedback{\erreur > 0 and \tronque2[-1] = \base}{
<div class="reponse">
  \name_feedback1
  \(b = \b\).

\name_feedback2[1] \base, \name_feedback2[2],
\tronque[\position] \times \n \name_feedback2[3] \liste[\position]
\name_feedback2[4] \(\listed[\position]\).
</div>
}

\feedback{\tronque2[-1] != \base}{
  <div class="reponse">\name_feedback3[1] \base, \name_feedback3[2] \base.
</div>}
