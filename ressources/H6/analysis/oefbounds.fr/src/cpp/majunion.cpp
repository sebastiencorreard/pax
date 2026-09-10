target=majunion

#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{o=random(1,2)}
\text{bounded=item(\o,\name_maj1)}
\text{bounder=item(\o,\name_maj1)}
\matrix{meth=a,\yes,\no
b,\yes,\no
item(\o,max,min)(a,b),\yes,\yes
item(\o,min,max)(a,b),\yes,\no
a+b,\no,\no
item(\o,|a|+|b|,-|a|-|b|),\yes,\yes
item(\o,-|a|-|b|,|a|+|b|),\no,\no
item(\o,|a+b|,-|a+b|),\yes,\no
item(\o,-|a+b|,|a+b|),\no,\no
}
\text{meth=randomrow(\meth)}
\text{rant=item(1,\meth)}
\text{good1=item(2,\meth)}
\text{good2=item(3,\meth)}
\statement{\name_enonce[1] \bounded \name_enonce[2]?
<ul><li>
I. \(A \cap B\) \name_isby[1] \bounded \name_isby[2] \(\rant\).
</li><li>
II. \(A \cup B\) \name_isby[1] \bounded \name_isby[2] \(\rant\).
</li>
</ul>}

\choice{I. \name_answer[1]}{\good1}{\yes,\no,\bad}
\choice{II. \name_answer[2]}{\good2}{\yes,\no,\bad}
