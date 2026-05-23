target=correspondance1 correspondance2
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\text{size=40x220x220}
\integer{confparm1=\confparm1=?2}

\text{value=wims(values v for v=1 to 10)}
\text{value=shuffle(\value)}
#if defined TARGET_correspondance1
\integer{b=\value[1]}
\integer{d=\value[2]}
\text{x=random(x,y)}
\matrix{lt=0,0,0,0
0,1,0,1
0,1,0,0
0,0,0,1}
#endif
#if defined TARGET_correspondance2
\integer{a=\value[1]}
\integer{b=\value[2]}
\integer{c=\value[3]}
\integer{d=\value[4]}
\text{x=random(x,y,z,a,b)}
\matrix{lt=0,0,1,0
1,0,0,0
0,1,0,0
0,0,0,1}
#endif

\text{col1=}
\text{col2=}
\for{i=1 to 4}{
  \text{s=row(\i,\lt)}
#if defined TARGET_correspondance1
  \text{fact=(\x^\confparm1+(-1)^(\s[2])*\b)*(\x+(-1)^(\s[4])*\d)}
#endif
#if defined TARGET_correspondance2
  \text{fact=((-1)^(\s[1])*\a*\x^\confparm1+(-1)^(\s[2])*\b)*((-1)^(\s[3])*\c*\x+(-1)^(\s[4])*\d)}
#endif
  \text{fact=simplify(\fact)}
  \text{dev=maxima(expand(\fact))}
  \text{dev=texmath(\dev)}
  \text{dev=\(\dev)}
  \text{fact=texmath(\fact)}
  \text{fact=\(\fact)}
  \text{col1=wims(append item \fact to \col1)}
  \text{col2=wims(append item \dev to \col2)}
}
\statement{
  \name_enonce
  <div class="wimscenter">
  \embed{r1,\size}
  </div>
}
\answer{}{\col1;\col2}{type=correspond}
