target=racinen1 racinen2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_racinen1
\keywords{inequalities}
\text{lstsymb= <,>}
\integer{b1=randint(2..6)}
\integer{b2=randint(2..6)}
\integer{b2=\b2=\b1?\b1+randint(1,-1)}
\integer{n1=randint(2..8)}
\integer{n2=randint(2..8)}
\integer{n2=\n2=\n1?\n1+randint(1,-1)}
\text{data=\b1^(1/\n1),\b2^(1/\n2)
\b2*(\b1)^(1/\n1),\b1*(\b2)^(1/\n2)
}
\text{texdata=\b1^{\frac{1}{\n1}},\b2^{\frac{1}{\n2}}
\b2\displaystyle\sqrt[\n1]{\b1},\b1\displaystyle\sqrt[\n2]{\b2}
}
\integer{i=randint(1..rows(\data))}
\text{cedata=row(\i,\data)}
\text{cetex=row(\i,\texdata)}
\real{a=\cedata[1]}
\text{ta=\cetex[1]}
\real{b=\cedata[2]}
\text{tb=\cetex[2]}
\text{symb=\a<\b?<:>}
\statement{
  \name_enonce:
<div class="wimscenter">\(\ta) \embed{reply1,\size} \(\tb)</div>
}
\answer{comparaison}{\symb;\lstsymb}{type=clickfill}
#endif
#if defined TARGET_racinen2
\keywords{real_function,derivative}
\integer{n1=randint(2..5)}
\integer{n2=randint(2..5)}
\integer{n3=randint(2..5)}

\text{data=x\displaystyle\sqrt[\n2]{x},1+1/\n2
x^\n1\displaystyle\sqrt[\n2]{x},\n1+1/\n2
x\displaystyle\sqrt[\n2]{x^\n3},1+\n3/\n2
x^\n1\displaystyle\sqrt[\n2]{x^\n3},\n1+\n3/\n2
\displaystyle\frac{\sqrt[\n2]{x}}{x},-1+1/\n2
\displaystyle\frac{\sqrt[\n2]{x}}{x^\n1},-\n1+1/\n2
\displaystyle\frac{\sqrt[\n2]{x^\n3}}{x},-1+\n3/\n2
\displaystyle\frac{\sqrt[\n2]{x^\n3}}{x^\n1},-\n1+\n3/\n2
\displaystyle\frac{x}{\sqrt[\n2]{x}},1-1/\n2
\displaystyle\frac{x^\n1}{\sqrt[\n2]{x}},\n1-1/\n2
\displaystyle\frac{x}{\sqrt[\n2]{x^\n3}},1-\n3/\n2
\displaystyle\frac{x^\n1}{\sqrt[\n2]{x^\n3}},\n1-\n3/\n2
\frac{1}{x\displaystyle\sqrt[\n2]{x}},-1-1/\n2
\frac{1}{x^\n1\displaystyle\sqrt[\n2]{x}},-\n1-1/\n2
\frac{1}{x\displaystyle\sqrt[\n2]{x^\n3}},-1-\n3/\n2
\frac{1}{x^\n1\displaystyle\sqrt[\n2]{x^\n3}},-\n1-\n3/\n2}
\integer{i=randint(1..rows(\data))}
\text{cedata=row(\i,\data)}
\text{ft=\cedata[1]}
\rational{r=simplify(\cedata[2])}
\function{f=x^(\r)}
\rational{r1=simplify(\r-1)}
\statement{
  \name_enonce[1] \(x \in \rbrack 0; +\infty \lbrack\).
  \name_enonce[2] \(f(x)\) \name_enonce[3] "\(x^{\alpha}\)" \name_enonce[4] \(f'(x)\).

<div class="wimscenter"><label for="reply1">\(f(x)=\ft=x\)</label><sup>\embed{reply1,3}</sup></div>
<div class="wimscenter"><label for="reply2">\(f'(x)\)=</label>\embed{reply2,4}<label for="reply3">\(x\)</label><sup>\embed{reply3,4}</sup>
</div>
}
\answer{\name_answer[1]}{\r}{type=numexp}
\answer{\name_answer[2]}{\r}{type=numexp}
\answer{\name_answer[3]}{\r1}{type=numexp}
#endif
