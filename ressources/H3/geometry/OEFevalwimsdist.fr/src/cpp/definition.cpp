target=definition1 definition2 definition3 definition4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{l=shuffle(A,B,C,D,E,F)}
\text{A=\l[1]}
\text{B=\l[2]}
\text{C=\l[3]}

#if defined TARGET_definition1
  \text{enonce=\name_enonce [\A\B]}
 \text{good=1,2}
#endif
#if defined TARGET_definition2
 \text{enonce=\name_enonce \A}
 \text{good=3}
#endif
#if defined TARGET_definition3
  \text{enonce=\name_enonce \A}
 \text{good=4}
#endif
#if defined TARGET_definition4
 \text{enonce=\name_enonce \A}
 \text{good=5}
#endif
\text{bad=wims(replace internal AAAA by \A in \name_bad)}
\text{bad=wims(replace internal BBBB by \B in \bad)}
\text{bad=wims(replace internal CCCC by \C in \bad)}

\statement{
\(\A\B\C\) \name_question \enonce ?
<ul>
\for{k=1 to 5}{
 <li>\embed{r1,\k}</li>
}
</ul>}

\answer{}{\good;\bad}{type=checkbox}{option=shuffle,split}
