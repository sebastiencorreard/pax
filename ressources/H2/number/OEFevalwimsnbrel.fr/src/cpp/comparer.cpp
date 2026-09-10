target=comparer1 comparer2 comparer3 comparer4 comparer5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_comparer1
 \integer{a=randint(1..9)*10+randint(1..9)}
 \integer{d=randint(2..8)}
 \real{N1=\a+\d*0.1}
 \real{N2=\a+randint(1..\d-1)*0.1+randint(1..9)*0.01}
#endif
#if defined TARGET_comparer2
 \real{N1=randint(100..999)+randint(1..9)*0.1+randint(1..9)*0.01}
 \real{N2=randint(10..99)+randint(1..9)*0.1+randint(1..9)*0.01}
#endif
#if defined TARGET_comparer3
 \integer{a=randint(1..9)*10+randint(1..9)}
 \real{N1=-\a-randint(5..8)*0.1-randint(1..9)*0.01}
 \real{N2=-\a-randint(1..4)*0.1-randint(1..9)*0.01}
#endif
#if defined TARGET_comparer4
 \integer{a=randint(1..9)*10+randint(1..9)}
 \integer{d=randint(2..8)}
 \real{N1=-\a-\d*0.1}
 \real{N2=-\a-randint(1..\d-1)*0.1-randint(1..9)*0.01}
#endif
#if defined TARGET_comparer5
 \integer{a=randint(1..9)*10+randint(1..9)}
 \integer{d=randint(2..8)*10+randint(1..9)}
 \real{N1=\a+\d*0.01}
 \real{N2=\a+randint(1..\d-1)*0.01+randint(1..9)*0.001}
#endif

\integer{ch=randitem(1,2)}
\text{type=item(\ch,\name_type)}
\real{rep=\ch=1?min(\N1,\N2):max(\N1,\N2)}

\statement{\name_question[1] \type \name_question[2]
  \N1 \name_question[3] \N2?}

\choice{\name_answer \type}{\rep}{\N1,\N2}
