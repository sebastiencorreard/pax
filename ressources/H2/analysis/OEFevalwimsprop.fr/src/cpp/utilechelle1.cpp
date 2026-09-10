target=utilechelle1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
 \text{bad=\name_bad}
 \integer{ch=randint(1..2)}
 \integer{p=randint(2..3)}
 \integer{l=randint(2..9)*10^\p}
 \text{e=\ch=1?\frac{1}{\l}:\frac{\l}{1}}
 \text{good=\bad[\ch]}
 \text{name=slib(lang/fname fr,boy)}

\statement{
\name \name_enonce \(\e).<p>
\name_question?</p> }
\choice{}{\good}{\bad}
