target=decomp
#include "author.inc"
#define NUM
#include "lang_titles.inc"
#include "lang.inc"

\text{a=9,12,15,16,18,20,21,24,25,27,28,30,32,35,36,40,42,
45,48,49,54,56,63,64,72,81}
\text{a=shuffle(\a)}
\integer{r1=\a[1]}
\integer{r2=\a[2]}
\integer{r3=\a[3]}
\integer{r4=\a[4]}

\statement{\name_enonce
<ul>
  <li>\r1 = \embed{r1,2} X  \embed{r2,2}</li>
  <li>\r2 = \embed{r3,2} X \embed{r4,2}</li>
  <li>\r3 = \embed{r5,2} X \embed{r6,2}</li>
  <li>\r4 = \embed{r7,2} X \embed{r8,2}</li>
</ul>
<div class="wims_instruction">\name_warning</div>}

\answer{}{\rep1}{type=auto}
\answer{}{\rep2}{type=auto}
\condition{\r1}{\rep1*\rep2=\r1 and \rep1<10 and \rep2<10}
\answer{}{\rep3}{type=auto}
\answer{}{\rep4}{type=auto}
\condition{\r2}{\rep3*\rep4=\r2 and \rep3<10 and \rep4<10}
\answer{}{\rep5}{type=auto}
\answer{}{\rep6}{type=auto}
\condition{\r3}{\rep5*\rep6=\r3 and \rep5<10 and \rep6<10}
\answer{}{\rep7}{type=auto}
\answer{}{\rep8}{type=auto}
\condition{\r4}{\rep7*\rep8=\r4 and \rep7<10 and \rep8<10}
