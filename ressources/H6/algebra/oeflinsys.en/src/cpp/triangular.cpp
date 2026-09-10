target=triangular
#include "lang_titles.inc"
\language{fr}
\range{5..50}
\author{XIAO, Gang}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang.inc"
\integer{sign=random(1,2)}
\text{s1=\sign=1?:-}
\text{s2=\sign=1?-:+}
\integer{type=random(1..5)}
\text{r1  =item(\type,1,\n,    1,   \n \s2 1,0)}
\text{r2  =item(\type,1,\n \s2 1,2,   \n \s2 2,1)}
\text{r3  =item(\type,1,\n \s2 2,3,   \n \s2 3,2)}
\text{rn1 =item(\type,1,2,   \n \s2 1,1,     \n \s2 2)}
\text{rn  =item(\type,1,1,   \n,    0,     \n \s2 1)}
\text{rns=\s1 \rn}
\text{rns=\rn=0 ? 0: \rns}
\text{abs=item(\type,0,1,-1,1,-1)}
\integer{ans=\sign=1?\abs:-(\abs)}
\text{prov=\r1=0 ? 0:\s1\r1}
\statement{\name_question
<div class="wimscenter">\(\left\lbrace
\begin{array}{cccccc}
x_1&+x_2&+x_3&+...&+x_n&=&\prov
\\\
&x_2&+x_3&+...&+x_n&=&\s1\r2
\\\
&&&\vdots
\\\
&&&x_{n-1}&+ x_{n}&=&\s1\rn1\\\
&&&&x_{n}&=&\rns
\end{array}
\right .
\)
</div>
}

\answer{\(x_1\)}{\ans}
