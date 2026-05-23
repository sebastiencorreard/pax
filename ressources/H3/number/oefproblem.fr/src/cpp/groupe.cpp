target=groupe1 groupe2

#include "lang_titles.inc"
#include "lang.inc"

\integer{nbcnt=items(\name_object1)}

\text{nb=randint(1..\nbcnt)}
\text{object1=\name_object1[\nb]}
\text{object2=\name_object2[\nb]}
\text{object=\name_object[\nb]}

\text{p=randitem(5,7,11,13)}
\text{p=randint(5..10)}
\integer{m1=\p*randint(6..20)}
\integer{m2=\p*randint(6..20)}
\text{p=pari(gcd(\m1,\m2))}

\text{enonce=wims(replace internal XXXX by \m1 in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \m2 in \enonce)}
\text{enonce=wims(replace internal OOOO by \object1 in \enonce)}
\text{enonce=wims(replace internal UUUU by \object2 in \enonce)}
\text{question2=wims(replace internal OOOO by \object1 in \name_question2)}
\text{question2=wims(replace internal MMMM by \object in \question2)}
\text{answer=wims(replace internal OOOO by \object1 in \name_answer)}
\text{answer=wims(replace internal MMMM by \object in \answer)}

\text{rep1=\p}
#if defined TARGET_groupe1
\integer{rep2=(\m1+\m2)/\p}
#endif
#if defined TARGET_groupe2
\integer{rep2=\m1/\p}
#endif
\statement{
\enonce
<ol><li>\name_question1?
</li>
<li>\question2?
</li>
</ol>
}
\answer{\answer[1]}{\rep1}{type=numeric}
\answer{\answer[2]}{\rep2}{type=numeric}
