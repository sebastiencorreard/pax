target=arcarg

#include "xiao.inc"
\computeanswer{yes}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"

\matrix{data=arccos(x),-1/sqrt(1-x^2)
arcsin(x),1/sqrt(1-x^2)
arctan(x),1/(1+x^2)
argch(x),1/sqrt(x^2-1)
argsh(x),1/sqrt(x^2+1)
argth(x),1/(1-x^2)
sqrt(x^2+1),x/sqrt(x^2+1)
sqrt(x^2-1),x/sqrt(x^2-1)
sqrt(1-x^2),-x/sqrt(1-x^2)
ln(1+x^2),2x/(1+x^2)
ln(1-x^2),-2x/(1-x^2)
}

\integer{datacnt=rows(\data)}
\text{sh=shuffle(\datacnt)}
\matrix{data=\data[\sh[1..5];]}
\text{fn=wims(makelist \(x) for x in \data[;1])}
\text{der=wims(makelist \(x) for x in \data[;2])}

\statement{\name_enonce
<div class="wimscenter">
\embed{r1,60x120}
</div>
}

\answer{\name_answer}{\fn;\der}{type=correspond}
