target=flageu flagas flagaf flagam flagoc flagall flagbig
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_flageu
# include "eu.inc"
#endif
#if defined TARGET_flagas
# include "as.inc"
#endif
#if defined TARGET_flagaf
# include "af.inc"
#endif
#if defined TARGET_flagam
# include "am.inc"
#endif
#if defined TARGET_flagoc
# include "oc.inc"
#endif
#if defined TARGET_flagall
# include "all.inc"
#endif
#if defined TARGET_flagbig
# include "big.inc"
#endif
#include "author.inc"

\text{code=randomrow(\data)}
\text{listpays=wims(nospace PP _fr)}
\if{\lang=en}{
  \text{listpays=wims(nospace PP _en)}
}
\text{pays=wims(lookup \code in data/\listpays)}
\integer{n=rows(\data)}
\text{sh=item(1..5,shuffle(\n))}
\matrix{data=row(\sh,\data)}
\text{data=wims(translate internal | to , in \data)}
\text{flags=column(1,\data)}
\text{countries=}
\for{j=1 to 5}{
  \text{pays=wims(lookup \data[\j;1] in data/\listpays)}
  \matrix{countries=\countries
  \pays}
}
\text{countries=wims(translate internal | to , in \countries)}
\text{countries=\countries[;1]}
\text{countries=wims(replace internal ; by , in \countries[1;])}
\text{flagb=}
\for{i=1 to 5}{
  \text{flag=item(\i,\flags)}
  \text{flag=wims(rename gifs/flags/\flag-lgflag.gif)}
  \text{flagb=wims(append item \flag to \flagb)}
}
\text{flags=wims(nospace \flags)}
\text{imgleft=<img style="height:46px" src="}
\text{imgright=" alt="">}

\text{flagb=wims(replace internal , by \imgright,\imgleft in
	\imgleft\flagb\imgright)}
\text{data=\flagb ; \countries}

\statement{
\name_instruction:
<div class="wimscenter">\embed{reply 1,80x120x150}</div>
}

\answer{\name_answer}{\data}{type=correspond}
