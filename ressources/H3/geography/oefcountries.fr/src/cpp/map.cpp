target=mapeu mapas mapaf mapam mapoc mapall mapbig
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
#if defined TARGET_mapeu
# include "eu.inc"
#endif
#if defined TARGET_mapas
# include "as.inc"
#endif
#if defined TARGET_mapaf
# include "af.inc"
#endif
#if defined TARGET_mapam
# include "am.inc"
#endif
#if defined TARGET_mapoc
# include "oc.inc"
#endif
#if defined TARGET_mapall
# include "all.inc"
#endif
#if defined TARGET_mapbig
# include "big.inc"
#endif
#if defined TARGET_mapall  || defined TARGET_mapbig
 \text{continents=\af,\am,\as,\eu,\oc}
# define ALLORBIG 1
#endif

\precision{10000}

\text{code1=randomrow(\data)}
\text{listpays=wims(nospace PP _fr)}
\if{\lang=en}{
  \text{listpays=wims(nospace PP _en)}
}
\text{code=item(1,\code1)}
\text{pays=wims(lookup \code in data/\listpays)}
\text{pays=\pays[1]}
#ifdef ALLORBIG
 \text{cont=item(2,\code1)}
#endif
\text{names=
#include "pays.inc"
}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
\img{scripts/data/maps/\code.jpg}{class="spacer wimscenter"}
</div>
 <div class="medium_size text_col">
  <label for="reply1">\name_instruction[1] \continent ?</label>
#ifdef ALLORBIG
 \embed{reply 1,18}
 <div>
  \name_instruction[2]
 \embed{choice 1}
 </div>
#else
 \embed{reply 1,18}
#endif
</div></div>
}

\answer{\name_answer[1]}{\pays;\names}{type=atext}
#ifdef ALLORBIG
\choice{\name_answer[2]}{\cont}{\continents}
#endif
