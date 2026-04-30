target=mediane1 mediane2 mediane3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_mediane1
 \integer{nb=2*randint(3..6)+1}
 \text{val=slib(stat/random \nb,100,200,Z)}
 \text{val=wims(sort numeric item \val)}
#endif
#if defined TARGET_mediane2
 \integer{nb=2*randint(3..6)+1}
 \text{val=slib(stat/random \nb,60,90,Z)}
#endif
#if defined TARGET_mediane3
 \integer{nb=2*randint(3..6)}
 \text{val=slib(stat/random \nb,-10,30,Z)}
#endif

\real{rep=slib(stat/median [\val])}
\text{valeurs=wims(replace internal , by &nbsp;;&nbsp; in \val)}
\statement{\name_enonce:
  <div class="wimscenter">\valeurs</div>}

\answer{\name_head[2]}{\rep}{numexp}
