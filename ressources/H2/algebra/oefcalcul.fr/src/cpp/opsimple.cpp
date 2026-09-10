target=opsimple
#define NUM 1
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\precision{10000}

\integer{a1=random(6..35)}
\integer{a2=random(6..35)}
\integer{s1=random(-1,1)}
\integer{s2=random(-1,1)}

\integer{x1=\s1 * \a1}
\integer{x2=\s2 * \a2}
\if{\x1=\x2}{\integer{x2=\s2 * (\a2 + 1)}}

\text{x2aff= \s2=-1? (\x2) : \x2}

\integer{opeitem=random(1,2)}
\text{ope=item(\opeitem, +,-)}
\text{opename=item(\opeitem, \openames)}

\integer{s2final= \opeitem=1? \s2 : -\s2}
\integer{opename2item= \s1=\s2final? 1:2}
\text{opename2=item(\opename2item, \openames)}
\if{\opename2item=1}{\integer{operuleitem= \s2=-1? 2:1}}
\if{\opename2item=2}{\integer{operuleitem= \s2=-1? 4:3}}

\integer{res=\x1 \ope \x2}
\integer{ressign=evalue(\res / abs(\res))}
\text{ressignaff= \ressign=-1? - : +}

\text{operule=item(\operuleitem, \operules)}

\steps{choice 1
choice 2, choice 3
choice 4, reply 1
}

\statement{
\name_statement[1]: <p>\x1 \ope \x2aff.</p>
\if{\step<=1}{\name_statement[2] \embed{choice 1}.}

\if{\step=2}{\name_statement[3], \embed{choice 2}
<div>\name_statement[4]? \embed{choice 3}.</div>}

\if{\step=3}{\name_statement[5], \name_statement[6] \embed{choice 4}.
<div><label for='reply1">\name_statement[7]:</label> \embed{reply 1,3}.</div>}
}

\choice{}{\opename}{\openames}
\choice{}{\operule}{\operules}
\choice{}{\ressignaff}{+,-}
\choice{}{\opename2}{\openames}
\answer{}{\res}{type=numeric}
