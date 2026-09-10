target=lenvec2
#include "author.inc"
#include "lang_titles.inc"

\precision{10000}
#include "lang.inc"

\integer{range=15}
\integer{a1=random(1..\range)*random(-1,1)}
\integer{b1=random(1..\range)*random(-1,1)}
\integer{c1=random(1..\range)*random(-1,1)}
\integer{l=random(3..\range)}
\real{ll=sqrt((\a1)^2+(\b1)^2+(\c1)^2)}
\integer{ss=random(1..floor(\l*\ll)-2)*random(-1,1)}
\real{lon=sqrt(\l^2-(\ss/\ll)^2)*\ll}

\statement{\name_enonce[1] \(u=(\a1,\b1,\c1)\) \name_enonce[2] \l.
  \name_enonce[3] \(\ss \), \name_enonce[4] \(u\wedge v)?
}

\answer{\name_answer}{\lon}

\hint{\name_hint}
