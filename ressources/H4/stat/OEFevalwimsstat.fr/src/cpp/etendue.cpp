target=etendue1 etendue2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_etendue1
 \integer{nb=2*randint(3..6)+1}
 \text{val=slib(stat/random \nb,60,90,Z)}
#endif
#if defined TARGET_etendue2
 \integer{nb=2*randint(3..6)}
 \text{val=slib(stat/random \nb,-10,30,Z)}
#endif
#if defined TARGET_etendue3old
 \integer{nb=2*randint(3..6)}
 \text{val=slib(stat/random \nb,-10,30,Z)}
#endif
\real{rep=slib(stat/range [\val])}
\text{valeurs=wims(replace internal , by &nbsp; ; &nbsp; in \val)}
\statement{\name_enonce:
<div class="wimscenter">\valeurs </div>}

\answer{\name_head[2]}{\rep}{numexp}
