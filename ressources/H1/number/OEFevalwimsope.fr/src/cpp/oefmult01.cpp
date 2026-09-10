target=oefmult011 oefmult012 oefmult013 oefmult014 oefmult015
#include "author.inc"
\integer{p=randint(1..3)}
#if defined TARGET_oefmult011
# define NUM 1
\text{ch=randint(0..9),randint(1..9)}
\integer{n=randint(\p..3)}
\integer{nb=\ch[1]\ch[2]}
\integer{nb=\nb*10^\n}
#endif
#if defined TARGET_oefmult012
# define NUM 2
\text{ch=randint(1..9),randint(0..9)}
\integer{nb=\ch[1]\ch[2]}
\integer{n=randint(1..\p-1)}
\integer{nb=\nb*10^\n}
#endif
#if defined TARGET_oefmult013
# define NUM 3
\integer{n=randint(2..4)}
\text{ch=}
\for{i=1 to \n}{
  \text{ch1=randint(1..9)}
  \text{ch=wims(append item \ch1 to \ch)}
}
\integer{nb=\ch[1]\ch[2]\ch[3]\ch[4]}
#endif
#if defined TARGET_oefmult014
# define NUM 4
\integer{n=randint(1..3)}
\text{ch=randint(1..9)}
\for{i=1 to \n}{\text{ch=wims(append item 0 to \ch)}}
\text{ch1=randint(1..9)}
\text{ch=wims(append item \ch1 to \ch)}
\integer{nb=\ch[1]\ch[2]\ch[3]\ch[4]\ch[5]}
\integer{m=randint(1..\n+1)}
\text{nb=pari(1.*\nb/10^\m)}
#endif
#if defined TARGET_oefmult015
# define NUM 5
\text{ch=randint(0..9),randint(1..9)}
\integer{nb=\ch[1]\ch[2]}
\integer{m=randint(2..4-\p)}
\text{nb=pari(1.*\nb/10^\m)}
#endif
#include "lang_titles.inc"
#include "lang.inc"
\text{dix=pari(1.*10^-\p)}
\text{res=pari(1.*(\nb)*10^-\p)}
\statement{
\name_enonce:
<div class="wimscenter">
 \nb \(\times\) \dix = \embed{r1}
</div>}
\answer{\nb  x  \dix =}{\res}{type=numeric}
