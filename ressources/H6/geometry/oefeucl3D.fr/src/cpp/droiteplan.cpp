target=droiteplan

\author{Bernadette, Perrin-Riou}
#include "author.inc"
#include "lang_title.inc"
\title{TITLE}
\title_en{TITLE_en}
\title_es{TITLE_es}
\title_ca{TITLE_ca}

\integer{a=randint(-10..10)}
\integer{b=randint(-10..10)}
\integer{c=randint(-10..10)}

\integer{u=randint(-10..10)}
\integer{v=randint(-10..10)}
\integer{w=randint(-10..10)}

\integer{u1=randint(-10..10)}
\integer{v1=randint(-10..10)}
\integer{w1=randint(-10..10)}
\integer{u= (\u1-(\u))^2+(\v1-(\v))^2+(\w1-(\w))^2=0 ? \u1+1}
\text{QR= \u1 - (\u) , \v1 - (\v) , \w1 - (\w)}
\text{QP= \a - (\u) , \b - (\v) , \c - (\w)}
\real{num= ((item(2,\QR))*(item(3,\QP))-(item(3,\QR))*(item(2,\QP)))^2
+((item(3,\QR))*(item(1,\QP))-(item(1,\QR))*(item(3,\QP)))^2
+((item(1,\QR))*(item(2,\QP))-(item(2,\QR))*(item(1,\QP)))^2
}
\real{sol=((\num)/((item(1,\QR))^2+(item(2,\QR))^2+(item(3,\QR))^2))^(1/2)}
#include "lang.inc"
\statement{
\name_instruction
\(Q) = (\u , \v , \w) \name_vocab[1;] \(R) = (\u1 , \v1 , \w1).
}

\answer{\name_vocab[2]}{\sol}{type=numeric}

\hint{\name_aide1
<div class="wimscenter">
\(\frac{||\vec{QR} \wedge \vec{QP}||}{||QR||}).
</div>
\name_aide2
}
