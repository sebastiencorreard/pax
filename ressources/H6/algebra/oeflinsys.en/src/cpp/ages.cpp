target=ages
\author{XIAO, Gang}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\range{-5..5}
\precision{1000}
#include "lang_titles.inc"
#include "lang.inc"

\text{names=slib(lang/fname \lang,boy,3)}
\integer{min=19}
\integer{max=89}
\text{values=shuffle(\max-\min+1)}
\text{values=\values[1,2,3]}
\text{values=wims(values x+\min for x in \values)}
\integer{mininx=\values[1] < \values[2] ? 1:2}
\integer{mininx=\values[\mininx] > \values[3] ? 3}
\integer{maxinx=\values[1] > \values[2] ? 1:2}
\integer{maxinx=\values[\maxinx] < \values[3] ? 3}
\integer{midinx=6-\mininx-\maxinx}
\integer{sum=\values[1]+\values[2]+\values[3]}
\integer{big=randint(120..150)}

\text{lessmin=wims(nonempty item wims(replace item number \mininx by in 1,2,3))}
\text{lessmax=wims(nonempty item wims(replace item number \maxinx by in 1,2,3))}
\text{lessmid=wims(nonempty item wims(replace item number \midinx by in 1,2,3))}

\integer{diff=abs(\values[\midinx]-\values[\lessmid[1]])}
\text{discover=randitem(\name_discover)}
\text{n2=\names[\lessmid[1]]}
\if{\values[\midinx] > \values[\lessmid[1]]}{
 \text{plusmoins=randitem(\name_plusmoins1)}
}{
 \text{plusmoins=randitem(\name_plusmoins2)}
}
\text{plusmoins=wims(replace internal XXXXX by \diff in \plusmoins)}
\text{plusmoins=wims(replace internal YYYYY by \n2 in \plusmoins)}

\if{randitem(1,2)=1}{
 \text{mean1=\name_mean[1]}
 \real{age1=(\sum-\values[\mininx]*3)/2}
}{
 \text{mean1=\name_mean[2]}
 \real{age1=(\sum-\values[\mininx]*3)}
}

\if{\randitem(1,2)=1}{
 \real{age2=(\sum-\values[\maxinx]*3)/2+\big}
 \text{t3=\name_question[1] \names[\maxinx] \name_question[2] \big ans, \name_mean[1]
  \name_question[3] \names[\lessmax[1]] \name_question[4] \names[\lessmax[2]]
   \name_question[5] \age2.}
}{
 \real{age2=(\sum-\values[\maxinx]*3)+\big*2}
 \text{t3=\name_question[1] \names[\maxinx] \name_question[2] \big \name_question[3], \name_mean[2]
  \name_question[4] \names[\lessmax[1]] \name_question[5] \names[\lessmax[2]]
   \name_question[6] \age2.}
}
\int{asum=\sum}

\text{order=shuffle(3)}
\text{party=randitem(\name_party)}
\statement{\name_instruction \party.
<ul><li>\name_instruction1[1] \asum.
</li><li>\names[\midinx] \discover \plusmoins.
</li><li>
\name_instruction1[2] \names[\mininx] \name_instruction1[3],
  \mean1 \name_question[4] \names[\lessmin[1]] \name_question[5]
  \names[\lessmin[2]] \name_instruction1[4] \age1.
</li>
<li>\t3</li></ul>
\name_instruction1[5]?
}

\answer{\name_age \names[\order[1]]}{\values[\order[1]]}
\answer{\name_age \names[\order[2]]}{\values[\order[2]]}
\answer{\name_age \names[\order[3]]}{\values[\order[3]]}
