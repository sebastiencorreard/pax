target=correquat1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\text{size=50x200x75}

\integer{nombre=4}

\text{nx=x}
\text{x=shuffle(19)}
\integer{a=randint(3..11)}

\integer{c1=randint(\a*\x[1]..200)}
\integer{b1=\c1-\a*\x[1]}
\text{eq1= \a \nx + \b1 = \c1}

\integer{c2=\a*randint(\x[2]+1..21)}
\integer{b2=\c2/\a-\x[2]}
\text{eq2= \a (\nx + \b2) = \c2}

\integer{c3=randint(2..\a-1)}
\integer{b3=randint(1..19)}
\integer{d3=\x[3]*(\a-\c3)+\b3}
\text{eq3= \a \nx + \b3 = \c3 \nx + \d3}

\integer{c4=randint(2..\a-1)}
\integer{b4=randint(1..9)}
\integer{d4=\x[4]*(\a-\c4)+\a*\b4}
\text{eq4= \a (\nx + \b4) = \c4 \nx + \d4}

\text{eq=\(\eq1\),\(\eq2\),\(\eq3\),\(\eq4\)}
\text{rep=item(1..4,\x)}

\statement{\name_enonce[1] \(\nx\) \name_enonce[2]
<div class="wimscenter">
\embed{reply 1,\size}
</div>
}
\answer{}{\eq;\rep}{type=correspond}
