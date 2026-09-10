target=calcul
#define NUM
#include "author.inc"
#include "lang_titles.inc"
\precision{10000}
\text{a=randint(1..10)}
\text{b=randint(2..10)}
\text{c=randint(3..10)}
#include "lang.inc"
\text{tous=\(\quad \a + \b \times \c\quad ;\),
\(\quad (\a + \b) \times \c\quad ;\),
\(\quad \a \times\b + \c\quad ;\),
\(\quad \a \times (\b+ \c)\quad ;\),
\(\quad \a + \frac{\b}{\c}\quad ;\),
\(\quad \frac{\a + \b}{\c}\quad ;\),
\(\quad \frac{\a}{\b+\c}\quad ;\),
\(\quad \frac{\a }{\b} +\c\quad ;\)
}

\matrix{data=\tous[1], \tous[2]| \tous[2],\tous[1]
\tous[2]
\tous[1]
\tous[3], \tous[4]| \tous[4],\tous[3]
\tous[4]
\tous[5],\tous[6]|\tous[6],\tous[5]
\tous[5]
\tous[7]
\tous[8],\tous[7]|\tous[7],\tous[8]
\tous[6]
\tous[8]
}

\text{choix=random(1,2)}
\text{u=\choix=1 ? randint(1..5):5+randint(1..6)}
\text{qu1=item(\u,\data1)}
\text{rep1=row(\u,\data)}
\text{mauvais=\choix=1?\tous[1..4]:\tous[5..8]}
\statement{<p>\name_statement[1] \qu1. \name_statement[2]?</p>
<div class="wims_instruction">\name_instruction</div>
 <div class="wimscenter">\embed{reply1,100x80}</div>
}

\answer{}{\rep1;\mauvais}{type=compose}
