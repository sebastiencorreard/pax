target=CORequ3 CORequ4 CORequ5
#include "author.inc"
#if defined TARGET_CORequ3
# define NUM 4
#endif
#if defined TARGET_CORequ4
# define NUM 5
#endif
#if defined TARGET_CORequ5
# define NUM 6
#endif

#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}

\text{size=50x150x100}
\integer{nombre=NUM}

#include "valeurs.inc"

\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}
\text{x=randitem(x,y,a,b)}

\if{\confparm1>=5}{
 \integer{ai=100*\a}
 \integer{bi=100*\b}
}{
 \text{ai=\a}
 \text{bi=\b}
}
\text{donnees=\a*\x+\b=0;#;-(\bi)/(\ai),\a*\x-\b=0;#;(\bi)/(\ai),\b*\x+\a=0;#;-(\ai)/(\bi),\b*\x-\a=0;#;(\ai)/(\bi),\x+\b=\a;#;(\a)-(\b),\x-\b=\a;#;(\a)+(\b)}

\text{donnees=shuffle(\donnees)}
\text{donnees=wims(item 1 to \nombre of \donnees)}
\matrix{donnees=wims(items2lines \donnees)}
\matrix{donnees=wims(replace internal ;#; by , in \donnees)}
\text{nb=column(1,\donnees)}
\text{ra=column(2,\donnees)}

\text{tmp1=}
\text{tmp2=}
\for{i=1 to \nombre}{
  \text{tmp=item(\i,\ra)}
  \if{\confparm1>4}{
    \text{tmp=wims(replace internal / by , in \tmp)}
    \text{tmp3=items(\tmp)}
    \if{\tmp3=2}{
      \integer{tmp3=item(1,\tmp)*100}
      \integer{tmp4=item(2,\tmp)*100}
      \text{tmp=\tmp3/\tmp4}
    }
  }
  \text{tmp=simplify(\tmp)}
  \text{tmp=texmath(\tmp)}
  \text{tmp1=wims(append item \(\tmp\) to \tmp1)}
  \text{tmp=item(\i,\nb)}
  \text{tmp=texmath(\tmp)}
  \text{tmp2=wims(append item \(\tmp\) to \tmp2)}
}
\text{ra=\tmp1}
\text{nb=\tmp2}

\statement{\name_question[1] \(\x\) \name_question[2]
<div class="wimscenter">
\embed{reply 1,\size}
</div>
}

\reply{\name_answer}{\nb;\ra}{type=correspond}
