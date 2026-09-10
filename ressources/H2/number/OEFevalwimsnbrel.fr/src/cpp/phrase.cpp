target=phrase1 phrase2 phrase3 phrase4 phrase5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{l=shuffle(2,3,4,5,6,7,8,9)}

#if defined TARGET_phrase1
\text{enonce=\name_enonce[1] \l[1] \name_enonce[2] \l[2].}
 \text{rep=\l[1]+(-\l[2])}
#endif
#if defined TARGET_phrase2
\text{enonce=\name_enonce[1] \l[1] \name_enonce[2] \l[2].}
\text{rep=-\l[1]-(-\l[2]),(-\l[1])-(-\l[2])}
#endif
#if defined TARGET_phrase3
 \text{enonce=\name_enonce[1] \l[1] \name_enonce[2] \l[2].}
 \text{rep=-(\l[1]+\l[2])}
#endif
#if defined TARGET_phrase4
 \text{enonce=\name_enonce[1] \l[1] \name_enonce[2] \l[2].}
 \text{rep=-\l[1]+(-\l[2]),(-\l[1])+(-\l[2])}
#endif
#if defined TARGET_phrase5
 \text{enonce=\name_enonce[1] \l[1] \name_enonce[2] \l[2] \name_enonce[3] \l[3].}
 \text{rep=\l[1]+\l[2]-(-\l[3])}
#endif

\text{A=randitem(A,B,C,D,E,F,G,H)}
\statement{\name_question[1] \A \name_question[2]:
<div class="wims_question">\A \enonce</div>
<div class="wims_instruction">\name_inst</div>
}

\answer{\A}{\rep}{type=litexp}
