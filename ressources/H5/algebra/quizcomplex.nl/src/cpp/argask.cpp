target=argask
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\computeanswer{no}
\precision{1000}

\integer{a=random(-20..20)}
\integer{b=random(2..20)*random(-1,1)}
\text{B=\b>=0?+\b:\b}
\real{mod=sqrt((\a)^2+(\b)^2)}
\real{ar=\b>0?pi/2:-pi/2}
\real{at=\a=0?\ar:arctan(\b/(\a))}
\real{Arg=\a<0?\at+pi:\at}

\statement{\name_instruction \(z=\a\B i).}

\answer{\(|z|)}{\mod}
\answer{arg(z)}{\arg}
\condition{\arg \name_feed \(z)}
	{abs((\arg-\Arg)/(2*pi)-round((\arg-\Arg)/(2*pi)))<0.0001}
