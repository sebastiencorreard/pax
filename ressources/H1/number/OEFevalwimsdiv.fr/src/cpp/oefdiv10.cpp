target=oefdiv101 oefdiv102 oefdiv103 oefdiv104 oefdiv105

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"
#if defined TARGET_oefdiv101
\text{ch=randint(0..9),randint(1..9)}
\integer{p=randint(1..3)}
\integer{n=randint(\p..3)}
\integer{nb=\ch[1]\ch[2]}
\integer{nb=\nb*10^\n}
#endif
#if defined TARGET_oefdiv102
\text{ch=randint(1..9),randint(0..9)}
\integer{p=randint(1..3)}
\integer{nb=\ch[1]\ch[2]}
\integer{n=randint(1..\p-1)}
\integer{nb=\nb*10^\n}
#endif
#if defined TARGET_oefdiv103
\integer{p=randint(1..3)}
\integer{n=randint(2..4)}
\text{ch=}
\for{i=1 to \n}{\text{ch1=randint(1..9)}
  \text{ch=wims(append item \ch1 to \ch)}
}
\integer{nb=\ch[1]\ch[2]\ch[3]\ch[4]}
#endif
#if defined TARGET_oefdiv104
\integer{p=randint(1..3)}
\integer{n=randint(1..3)}
\text{ch=randint(1..9)}
\for{i=1 to \n}
{\text{ch=wims(append item 0 to \ch)}
}
\text{ch1=randint(1..9)}
\text{ch=wims(append item \ch1 to \ch)}
\integer{nb=\ch[1]\ch[2]\ch[3]\ch[4]\ch[5]}
\integer{m=randint(1..\n+1)}
\real{nb=\nb/10^\m}
#endif
#if defined TARGET_oefdiv105
\integer{p=randint(1..3)}
\text{ch=randint(0..9),randint(1..9)}
\integer{nb=\ch[1]\ch[2]}
\integer{m=randint(2..6-\p)}
\real{nb=\nb/10^\m}
#endif
\text{tnb=slib(numeration/ecriturenombre \nb,comma tex)}
\integer{dix=10^\p}
\text{tdix=slib(numeration/ecriturenombre \dix,tex)}
\real{res=\nb/\dix}
\text{reply_class=euler_quest_nobg}
\statement{
<div class="\reply_class">
  \name_question:
  <div class="wimscenter">
  <label for="reply1">\(\tnb \div \tdix =\)</label> \embed{r1}
  </div>
</div>
}
\answer{}{\repel}
\text{repel=wims(replace internal * by in \repel)}
\text{repel=wims(replace internal , by . in \repel)}
\real{repel=pari(\repel)}

\condition{\name_cond}{\repel issametext \res}
\if{\repel=\res}{\text{reply_class=euler_rep_good_nobg tick}}{\text{reply_class=euler_rep_bad_nobg cross"}}

