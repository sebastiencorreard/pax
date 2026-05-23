target=distance1 distance2
\keywords{distance}

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{l=shuffle(A,B,C,E,F)}
\text{A=\l[1]}
\text{B=\l[2]}
\text{C=\l[3]}


\text{enonce=wims(replace internal AAAA by \A in \name_enonce)}
\text{good=wims(replace internal AAAA by \A in \name_good)}
\text{bad=wims(replace internal AAAA by \A in \name_bad)}
\text{question=wims(replace internal AAAA by \A in \name_question)}
\statement{
(d) \question
<p>\enonce? </p>
}

\choice{}{\good}{\bad}
