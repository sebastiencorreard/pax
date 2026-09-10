target=qcm1

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{choix=randitem(1,2)}
\text{question=\name_question \name_choix[\choix]}
\text{cnt=rows(\data)}
\text{N=shuffle(\cnt)}
\text{nb=5}
\text{N=\N[1..\nb]}
\text{rep=}
\for{j=1 to 5}{
  \text{rep=\data[\N[\j];2]==\choix? wims(append item \j to \rep)}
}
\statement{
<div class="wims_question">\question?</div>}
\answer{}{\rep;\data[\N;1]}{type=checkbox}

\feedback{1=1}{
\if{\choix=1}{\name_feed1}{\name_feed2}
}
