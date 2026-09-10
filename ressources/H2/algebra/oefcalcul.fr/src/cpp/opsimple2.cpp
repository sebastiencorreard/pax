target=opsimple2
#define NUM 2
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\precision{10000}

\integer{a1=random(6,7,8,9,10,11,12,13,14,15,16,18,20,24,25,30,50)}
\integer{a2=random(6,7,8,9,10,11,12,13,14,15,16,18,20,24,25,30,50)}
\integer{s1=random(-1,1)}
\integer{s2=random(-1,1)}

\integer{x1=\s1 * \a1}
\integer{x2=\s2 * \a2}
\integer{y=\x1 * \x2}
\integer{opeitem=random(3,4)}

\text{x1aff= \opeitem=3? \x1 : \y}
\text{x2aff= \s2=-1? (\x2) : \x2}
\text{operuleitem=5}

\text{opeaff=item(\opeitem,+,-,x,:)}

\integer{res= \opeitem=3? \y : \x1}
\integer{ressign=evalue(\res / abs(\res))}
\text{ressignaff= \ressign=-1? - : +}

\text{opename=item(\opeitem, \openames)}

\text{operule=item(\operuleitem, \operules)}

\steps{choice 1
choice 2, choice 3
choice 4, reply 1
}

\statement{
\name_statement[1]: <p>\x1aff \opeaff \x2aff.</p>
\if{\step<=1}{\name_statement[2] \embed{choice 1}.}

\if{\step=2}{\name_statement[3], \embed{choice 2}
<div>\name_statement[4]? \embed{choice 3}.</div>}

\if{\step=3}{\name_statement[5], \name_statement[6] \embed{choice 4}.
<div>\name_statement[7]: \embed{reply 1,3}.</div>}
}

\choice{}{\opename}{\openames}
\choice{}{\operule}{\operules}
\choice{}{\ressignaff}{+,-}
\choice{}{\opename}{\openames}
\answer{}{\res}{type=numeric}
