target=compderiv

#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\integer{ra=random(1..4)}
\text{cos1=item(\ra,cos,sin,cos,sin)}
\text{cos2=item(\ra,cos,cos,sin,sin)}
\real{add=item(\ra,0,0,pi/2,pi/2)}
\text{bad=\name_ouinon}
\integer{t=random(1..19)}
\integer{s=\t+2}
\integer{sign=random(-1,1)}
\integer{a=\sign<0?-\s:\t}
\integer{b=\sign<0?-\t:\s}
\integer{f1=floor((\a+\add)/pi)}
\integer{f2=floor((\b+\add)/pi)}
\text{good=\f1=\f2?\name_ouinon[1]:\name_ouinon[2]}

\statement{\name_enonce[1] \(f(x) = arc\cos1(\cos2(x))\) \name_enonce[2] [\a,\b]?}

\choice{\name_answer}{\good}{\bad}
