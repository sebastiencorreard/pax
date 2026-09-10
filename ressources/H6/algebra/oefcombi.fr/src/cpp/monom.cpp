target=monom3 monom4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}
#if defined TARGET_monom3
\integer{type=randint(1..8)}
\integer{a=item(\type,2,2,2,3,3,4,5,5)}
\integer{b=item(\type,3,3,5,4,5,5,6,7)}
\integer{c=item(\type,5,7,7,5,7,7,7,8)}
\integer{degree=randint(4..15)}
\integer{sol=(\degree+2)*(\degree+1)/2}
\text{hint=wims(replace internal XXXX by \a, \b, \c in \name_hint)}
\text{hint=wims(replace internal YYYY by \(a+b+c=\degree\) in \hint)}
#endif
#if defined TARGET_monom4
\integer{type=randint(1..11)}
\integer{a=item(\type,2, 2,2, 2,3, 3,4, 4, 5,5, 5)}
\integer{b=item(\type,3, 3,5, 5,4, 5,5, 5, 6,7, 7)}
\integer{c=item(\type,5, 7,7, 7,5, 7,7, 9, 7,8, 9)}
\integer{d=item(\type,7,11,9,11,7,11,9,11,11,9,11)}
\integer{degree=randint(2..9)}
\integer{sol=(\degree+3)*(\degree+2)*(\degree+1)/6}
\text{hint1=wims(replace internal XXXX by \a, \b, \c, \d in \name_hint)}
\text{hint1=wims(replace internal YYYY by \(a+b+c+d=\degree\) in \hint1)}
#endif
\statement{\name_question[1]
#if defined TARGET_monom3
\(\a^a *\b^b *\c^c \)
#endif
#if defined TARGET_monom4
\(\a^a *\b^b *\c^c *\d^d \)
#endif
\name_question[2]
#if defined TARGET_monom3
\(a\), \(b\), \(c\)
#endif
#if defined TARGET_monom4
\(a), \(b\), \(c\), \(d\)
#endif
\name_question[3]
#if defined TARGET_monom3
\(a +b +c =\degree\)?
#endif
#if defined TARGET_monom4
\(a+b+c+d=\degree\)?
#endif
}

\hint{\hint1}
\answer{\name_answer}{\sol}
