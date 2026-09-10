target=argask

#include "common.inc"
#include "lang_titles.inc"

\integer{a=random(-20..20)}
\integer{b=random(2..20)*random(-1,1)}
\complex{z=\a+\b*i}
\real{mod=sqrt((\a)^2+(\b)^2)}
\real{ar=\b>0?pi/2:-pi/2}
\real{at=\a=0?\ar:arctan(\b/(\a))}
\real{Arg=\a<0?\at+pi:\at}

#include "lang.inc"

\statement{\name_statement \(\z\).}

\answer{\(|z|\)}{\mod}{type=numeric}
\answer{\(Arg(z)\)}{\arg}{type=numeric}
\condition{\arg \name_condition \(z\)}
	{abs((\arg-\Arg)/(2*pi)-round((\arg-\Arg)/(2*pi)))<0.0001}

