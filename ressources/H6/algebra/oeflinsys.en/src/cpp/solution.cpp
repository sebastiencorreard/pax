target=solution
#include "xiao.inc"

#include "lang_titles.inc"
#include "lang.inc"
\integer{min=10}
\integer{max=200}
#include "3x3pos.inc"
\text{values=random(\min..\max),random(\min..\max),random(\min..\max)}
\real{tot=\values[1]+\values[2]+\values[3]}
\text{const=pari(([\values]*[\matrix]~)/\tot)}
\integer{c1=\const[1]}
\integer{c2=\const[2]}
\integer{c3=\const[3]}
\text{const=\c1,\c2,\c3}
\integer{tot=\tot}

\text{values=pari(([\const]*([\matrix]^-1)~)*\tot.0)}

\if{randitem(1,2) = 1}{
 \text{ion=\name_choix[1;1]}
 \text{dion=\name_choix[1;2]}
 \text{ions=shuffle(\name_choix[1;])}
}{
 \text{ion=\name_choix[2;1]}
 \text{dion=\name_choix[2;1]}
 \text{ions=shuffle(\name_choix[2;])}
}

\text{ABC=A,B,C}
\statement{\name_instruction

<table class="wimscenter wimsborder"><tr><th>\name_header[1]</th>
<th>\ions[1]</th><th>\ions[2]</th><th>\ions[3]</th></tr>
\for{m=1 to 3}{
 <tr><th>\name_header[2] \ABC[\m]</th>
 \for{n=1 to 3}{<td>\matrix[\n;\m]</td>}
 </tr>
}
</table>
\name_question[1] \tot \name_question[2] \const[1] \name_question[3]
\ions[1], \const[2] \name_question[3] \ions[2], \const[3] \name_question[3] \ions[3]
\name_question[4]?
}

\answer{Solution A en cL}{\values[1]}
\answer{Solution B en cL}{\values[2]}
\answer{Solution C en cL}{\values[3]}
