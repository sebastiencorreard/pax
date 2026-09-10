target=imfunc
#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\text{bo=\name_choix[1]}
\text{mino=\name_choix[2]}
\text{majo=\name_choix[3]}
\text{no=\name_choix[4]}
\integer{o=random(1,2,3)}
\text{direct=item(\o,\mino,\majo,\bo)}
\text{reverse=item(\o,\majo,\mino,\bo)}
\text{strong=item(\o,\no,\no,\bo)}
\integer{dir=random(1,2)}
\matrix{data=\name_data[1], \no, \no
\name_data[2], \strong, \no
\name_data[3], \strong, \strong
\name_data[4], \strong, \no
\name_data[5], \bo, \no
\name_data[6], \direct, \no
\name_data[7], \bo, \no
\name_data[8], \direct, \direct
\name_data[9], \reverse, \no
\name_data[10], \bo, \no
\name_data[11], \reverse, \reverse
\name_data[12], \no, \no
\name_data[13], \direct, \no
\name_data[14], \reverse, \no
\name_data[15], \no, \no
\name_data[16], \no, \no
\name_data[17], \bo, \no
\name_data[18], \bo, \no
\name_data[19], \no, \no
\name_data[20], \direct, \no
\name_data[21], \reverse, \no
}
\text{data=randomrow(\data)}
\text{cond=item(1,\data)}
\text{dimage=item(2,\data)}
\text{rimage=item(3,\data)}

\statement{\name_enonce[1] \(f: \RR \rightarrow \RR\) \name_enonce[2] \cond
\name_enonce[3] \direct
\name_enonce[4] \(\displaystyle{\RR}\). \name_enonce[5] \(B=f(A)\) \name_enonce[6]
  \(C=f^{-1}(A)\) \name_enonce[7] \(A\).
<p>\name_question?</p>
<div class="wims_instruction">\name_instruction</div>
}

\choice{\(B\) \name_is }{\dimage}{\bo,\mino,\majo,\no,}
\choice{\(C\) \name_is }{\rimage}{\bo,\mino,\majo,\no,}
