target=comparer1 comparer2 comparer3 comparer4 comparer5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_comparer3
 \text{name=slib(lang/fname fr,boy)}
 \integer{ch=randint(1..2)}
 \real{l1=randitem(1.25,1.5,1.75,2)}
 \real{l2=randitem(2.5,3,3.5,4)}
 \integer{l3=randint(3..7)*5}
 \text{gout=randitem(\name_gout)}
 \text{bad=\name_bad[1] \l1 \name_bad[2],\name_bad[1] \l2 \name_bad[2]}
 \text{type=\ch=1?\name_type[1]:\name_type[2]}
 \text{good=\bad[\ch]}
 \statement{<ul>
<li>\name \name_enonce1[1] \l1 \name_enonce1[2] \l2 \name_enonce1[3].</li>
<li>\name_enonce2[1], \name_enonce2[2] \l3 cl \name_enonce2[3] \gout.</li>
<li>\name_enonce3.</li>
</ul>
\name_question \type ?}
\choice{}{\good}{\bad}
#endif
#if defined TARGET_comparer5
 \integer{pour=randint(2..18)*5}
 \text{frac=randitem(1/2,1/3,2/3,1/4,3/4,1/5,2/5,3/5,4/5,1/10,3/10,7/10,9/10)}
 \text{name1=slib(lang/fname fr,boy)}
 \text{name2=slib(lang/fname fr,girl)}
 \text{bad=\name1,\name2,\name_bad}
 \text{good=\pour/100<\frac?\bad[2]:\bad[1]}
 \text{good=\pour/100=\frac?\bad[3]:\good}
 \statement{\name1 \name_and \name2 \name_enonce1
<ul><li>\name1 \name_say:
 <span style="font-style:italic">\name_enonce2[1] \pour % \name_enonce2[3].</span></li>
<li>\name2 \name_say:
<span style="font-style:italic">\name_enonce2[2] \(\frac) \name_enonce2[3].</span></li>
</ul>
\name_question?}

\choice{}{\good}{\bad}
#endif
#if defined TARGET_comparer4
\text{frac=shuffle(1/2,1/3,2/3,1/4,3/4,1/5,2/5,3/5,4/5,1/10,3/10,7/10,9/10)}
\text{bad=\name_bad[1],\name_bad[2]}
\statement{\name_enonce[1] \frac[1] \name_enonce[2] \frac[2].
 <p>\name_question?</p>}
\choice{}{\name_bad[3]}{\bad}
#endif
#if defined TARGET_comparer2
 \text{frac=shuffle(1/2,1/3,2/3,1/4,3/4,1/5,2/5,3/5,4/5,1/10,3/10,7/10,9/10)}
 \text{bad=\name_bad}
 \integer{ch=randint(1..2)}
 \text{type2=\ch=1?\name_type2[1]:\name_type2[2]}
 \if{\ch=1}{
  \text{good=\frac[1]<\frac[2]?\bad[2]:\bad[1]}
 }{
  \text{good=\frac[1]<\frac[2]?\bad[1]:\bad[2]}
 }
 \text{type=randitem(\name_type)}
 \statement{
\name_enonce1[1] \type \name_enonce1[2]
\name_enonce2[1] \frac[1] \type \name_enonce2[2] \frac[2].
<p>
\name_question[1] \type \name_question[2] \type2 ?
</p>}

\choice{}{\good}{\bad}
#endif
#if defined TARGET_comparer1
 \text{frac=wims(values v*5 for v=5 to 15)}
 \text{frac=shuffle(\frac)}
 \text{bad=\name_bad}
 \integer{ch=randint(1..2)}
 \text{type2=\ch=1?\name_type2[1]:\name_type2[2]}
 \if{\ch=1}{
  \text{good=\frac[1]<\frac[2]?\bad[2]:\bad[1]}
 }{
  \text{good=\frac[1]<\frac[2]?\bad[1]:\bad[2]}
 }
 \text{type=randitem(\name_type)}
 \statement{\name_enonce1<ul>
<li>\name_enonce2[1], \name_enonce2[3] \frac[1] % \name_enonce2[4] \type.</li>
<li>\name_enonce2[2], \name_enonce2[3] \frac[2] % \name_enonce2[4] \type.</li>
</ul>
\name_question[1] \type \name_question[2] \type2 ?}

\choice{}{\good}{\bad}
#endif
