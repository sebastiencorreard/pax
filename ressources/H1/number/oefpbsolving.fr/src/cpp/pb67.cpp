target=resoudre_pb6 resoudre_pb7

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{g=randitem(1,2)}
\text{genre=girl}
\text{toto=slib(lang/fname fr,\genre)}
\text{enonce=wims(replace internal XXXX by \toto in \name_enonce)}
\text{question=wims(replace internal XXXX by \toto in \name_question)}
\text{question2=\name_question2}
\text{hrv=randint(9..15)}
\integer{mrv=randint(1..11)*5}
\text{mrv=\mrv<10?0\mrv}
\text{retard=randint(1..30)}
\text{s1=randint(5..15)}
\text{s2=randint(15..40)}
\integer{H1=\mrv+\hrv*60}
\integer{H2=\H1+\retard-(\s1+\s2)}
\text{h2=pari(divrem(\H2,60)~)}
\text{hdep=\h2[1]}
\text{mdep=\h2[2]}
\text{mdep=\mdep<10?0\mdep}
#if defined TARGET_resoudre_pb6
\text{data=\hdep,\mdep,\hrv,\mrv}
#endif
#if defined TARGET_resoudre_pb7
\text{data=\hrv,\mrv,\hdep,\mdep}
#endif
\statement{
\enonce[1;] \data[1] h \data[2] mn. \enonce[4;] \s1 mn \enonce[5;] \s2 mn.
\enonce[2;] \retard mn \enonce[3;]
\question?
<div class="wims_question">
<label for="reply1">\question2</label> \embed{r1,4} h \embed{r2,4} mn.
</div>}

\answer{H}{\data[3]}
\answer{mn}{\data[4]}
