target=Trianglequilat
\keywords{complex_plane}
#include "common.inc"
#include "lang_title.inc"

\integer{a=random(0..9)}
\integer{b=random(0..9)}
\integer{c=random(1..9)}
\integer{d=random(1..9)}
\integer{cc=\c-\a}
\integer{dd=\d-\b}
\real{r= \a+(\cc-\dd*3^(1/2))/2}
\real{r1= \a+(\cc+\dd*3^(1/2))/2}
\real{j= \b+ (\cc*3^(1/2)+\dd)/2}
\real{j1= \b+ (-\cc*3^(1/2)+\dd)/2}
\complex{z= \a+\b*i}
\complex{z1= \c+\d*i}

#include "lang.inc"

\statement{\name_statement[1] \(\z) \name_and \(\z1),
\name_statement[2].}

\hint{\name_hint}
\answer{\(Re(z))}{\rep}{type=default}
\answer{\(Im(z))}{\ima}{type=default}

\condition{\(z=\rep+\ima *i)}{(\rep=\r and \ima=\j) or (\ima=\j1 and \rep=\r1)}
