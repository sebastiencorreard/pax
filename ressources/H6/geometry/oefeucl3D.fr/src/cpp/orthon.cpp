target=orthon

\author{Bernadette, Perrin-Riou}
#include "author.inc"
#include "lang_title.inc"
\title{TITLE}
\title_en{TITLE_en}
\title_es{TITLE_es}
\title_ca{TITLE_ca}

\text{v1=random(randint(1..2), randint(-2..-1)),random(randint(1..2), randint(-2..-1)),random(randint(1..2), randint(-2..-1))}
\text{v2=randint(-2..2),0,randint(-2..2)}
\text{v2=\v2
randint(-2..2),randint(-2..2),0}
\text{v2=\v2
0,randint(-2..2),randint(-2..2)}
\text{v2=randomrow(\v2)}

\steps{reply1, reply2,reply3
reply4,reply5,reply6}

#include "lang.inc"

\statement{\name_instruction1

\if{\step=1}{\name_instruction2
<div class="wimscenter">
\( F^\perp= \{(x , y , z) \in \RR^3, <(x , y , z) , f> = 0 \;  \mathrm{ \name_instruction[1;] } \;  f \in F\})
</div>}

\if{\step=2}{\name_instruction[2;] \(v_1 = (\rep1)), \(v_2 = (\rep2)),
 \(v_3 = (\rep3)).}
}

\answer{\name_instruction[3;] \(v_1)}{\rep1}{type=vector}
\answer{\name_instruction[4;] \(v_2)}{\rep2}{type=vector}
\answer{\name_instruction[5;]}{\rep3}{type=vector}
\answer{\name_instruction[6;] \(v_1)}{\rep4}{type=numeric}
\answer{\name_instruction[6;] \(v_2)}{\rep5}{type=numeric}
\answer{\name_instruction[6;] \(v_3)}{\rep6}{type=numeric}
\text{S=pari( print(matrank([\rep1;\rep2])))}
\text{S1=pari(print(matrank([\rep1;\v1;\v2])))}
\text{S2=pari(print(matrank([\rep2;\v1;\v2])))}
\real{S3=(item(1,\rep1))*(item(1,\rep2))+(item(2,\rep1))*(item(2,\rep2))+(item(3,\rep1))*(item(3,\rep2))}
\condition{\name_instruction[7;]}{\S=2}
\condition{\(v_1) \name_instruction[8;] F}{\S1=2}
\condition{\(v_2) \name_instruction[8;] F}{\S2=2}
\condition{\name_instruction[9;]}{\S3=0}
\real{S0=(item(1,\rep3))^2+(item(2,\rep3))^2+(item(3,\rep3))^2}
\real{N3=(\S0)^(1/2)}
\real{N1=((item(1,\rep1))^2+(item(2,\rep1))^2+(item(3,\rep1))^2)^(1/2)}
\real{N2=((item(1,\rep2))^2+(item(2,\rep2))^2+(item(3,\rep2))^2)^(1/2)}

\real{S4=(item(1,\v1))*(item(1,\rep3))+(item(2,\v1))*(item(2,\rep3))+(item(3,\v1))*(item(3,\rep3))}
\real{S5=(item(1,\v2))*(item(1,\rep3))+(item(2,\v2))*(item(2,\rep3))+(item(3,\v2))*(item(3,\rep3))}
\condition{\name_instruction[10;]}
{\S4=0 and \S5=0 and \S0<>0}
\condition{\name_instruction[6;] \(v_1)=\rep4}{\N1=\rep4}
\condition{\name_instruction[6;] \(v_2)=\rep5}{\N2=\rep5}
\condition{\name_instruction[6;] \(v_3) =\rep6}{\N3=\rep6}
