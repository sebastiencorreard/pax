target=module

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{z12=shuffle(z_1,z_2)}
\text{z1=item(1,\z12)}
\text{z2=item(2,\z12)}
\text{z3=z_3}
\text{i=randitem(i,-i)}
\text{good=shuffle(
 abs(-\z1) = abs(\z1),
 abs(-conj(\z1)) = abs(\z1),
 abs(conj(\z1)) = abs(\z1),
 abs(\z1 \z2) = abs(\z1) abs(\z2),
 abs(\z1 conj(\z2)) = abs(\z1) abs(\z2),
 abs(conj(\z1) \z2) = abs(\z1) abs(\z2),
 abs(\z1/\z2) = abs(\z1)/abs(\z2),
 abs(conj(\z1)/\z2) = abs(\z1)/abs(\z2),
 abs(\z1/conj(\z2)) = abs(\z1)/abs(\z2),
 abs(1/\z1) = 1/abs(\z1),
 abs(-1/\z1) = 1/abs(\z1),
 abs(1/conj(\z1)) = 1/abs(\z1),
 abs(\z1 + \z2) = abs(\z2 + \z1),
 abs(conj(\z1) + conj(\z2)) = abs(\z2 + \z1),
 abs(conj(\z1) - conj(\z2)) = abs(\z2 - \z1),
 abs(\i \z1) = abs(\z1),
 abs(\i/\z1) = 1/abs(\z1),
 abs(\z1^2) = abs(\z1)^2,
 abs(\z1)^2 = \z1 conj(\z1),
 \z1 conj(\z1) = abs(\z1)^2,
 abs(\z1 conj(\z1)) = \z1 conj(\z1),
 abs(\z1 conj(\z1)) = abs(\z1)^2,
)}
\text{bad=shuffle(
 abs(-\z1) = -abs(\z1),
 abs(-\z1) = 1/abs(\z1),
 abs(conj(\z1)) = - abs(\z1),
 abs(conj(\z1)) = 1/abs(\z1),
 abs(1/conj(\z1)) = abs(\z1),
 abs(\z1+\z2) = abs(\z1) + abs(\z2),
 abs(\z1-\z2) = abs(\z1) - abs(\z2),
 abs(\z1 \z2) = abs(\z1) + abs(\z2),
 abs(\z1 conj(\z2)) = abs(\z1) / abs(\z2),
 abs(conj(\z1) \z2) = abs(\z2) / abs(\z1),
 abs(\z1 conj(\z2)) = abs(\z1) - abs(\z2),
 abs(conj(\z1) \z2) = abs(\z2) - abs(\z1),
 abs(\z1/\z2) = abs(\z1) - abs(\z2),
 abs(1/\z1) = - abs(\z1),
 abs(-1/\z1) = - abs(\z1),
 abs(1/\z1) = - 1/abs(\z1),
 abs(1/\z1) = abs(conj(\z1)),
 abs(\z1 + conj(\z2)) = abs(\z1 + \z2),
 abs(conj(\z1) + \z2)  =  abs(\z1+\z2),
 abs(\z1-conj(\z2)) = abs(\z1-\z2),
 abs(conj(\z1) - \z2) = abs(\z1 - \z2),
 abs(\i * \z1) = \i * abs(\z1),
 abs(\i+\z1) = \i + abs(\z1),
 abs(\i/\z1) = \i/abs(\z1),
 abs(\z1^2) = 2 abs(\z1),
 abs(\z1)^2 = \z1^2,
)}

#include "goodbad4.inc"

\statement{\name_instruction
#include "goodbadlist4.inc"
}

\reply{\name_answer[1] \cond \propsname \name_answer[2]}{\ans;1,2,3,4}{type=checkbox}

\latex{
\begin{statement}
\name_instruction
#include "goodbadlist4latex.inc"
\end{statement}
}
