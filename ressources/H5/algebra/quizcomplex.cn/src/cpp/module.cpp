target=module

\title{模}
#include "header.inc"
\text{propsname=公式}
\text{z12=shuffle(z1,z2)}
\text{z1=item(1,\z12)}
\text{z2=item(2,\z12)}
\text{z3=z3}
\text{i=random(i,-i)}
\text{good=shuffle(
 \(abs(-\z1) = abs(\z1)),
 \(abs(-conj(\z1)) = abs(\z1)),
 \(abs(conj(\z1)) = abs(\z1)),
 \(abs(\z1*\z2) = abs(\z1)*abs(\z2)),
 \(abs(\z1*conj(\z2)) = abs(\z1)*abs(\z2)),
 \(abs(conj(\z1)*\z2) = abs(\z1)*abs(\z2)),
 \(abs(\z1/\z2) = abs(\z1)/abs(\z2)),
 \(abs(conj(\z1)/\z2) = abs(\z1)/abs(\z2)),
 \(abs(\z1/conj(\z2)) = abs(\z1)/abs(\z2)),
 \(abs(1/\z1) = 1/abs(\z1)),
 \(abs(-1/\z1) = 1/abs(\z1)),
 \(abs(1/conj(\z1)) = 1/abs(\z1)),
 \(abs(\z1+\z2) = abs(\z2+\z1)),
 \(abs(conj(\z1)+conj(\z2)) = abs(\z2+\z1)),
 \(abs(conj(\z1)-conj(\z2)) = abs(\z2-\z1)),
 \(abs(\i*\z1) = abs(\z1)),
 \(abs(\i/\z1) = 1/abs(\z1)),
 \(abs(\z1^2) = abs(\z1)^2),
 \(abs(\z1)^2 = \z1*conj(\z1)),
 \(\z1*conj(\z1) = abs(\z1)^2),
 \(abs(\z1*conj(\z1)) = \z1*conj(\z1)),
 \(abs(\z1*conj(\z1)) = abs(\z1)^2),
)}
\text{bad=shuffle(
 \(abs(-\z1) = -abs(\z1)),
 \(abs(-\z1) = 1/abs(\z1)),
 \(abs(conj(\z1)) = - abs(\z1)),
 \(abs(conj(\z1)) = 1/abs(\z1)),
 \(abs(1/conj(\z1)) = abs(\z1)),
 \(abs(\z1+\z2) = abs(\z1) + abs(\z2)),
 \(abs(\z1-\z2) = abs(\z1) - abs(\z2)),
 \(abs(\z1*\z2) = abs(\z1) + abs(\z2)),
 \(abs(\z1*conj(\z2)) = abs(\z1) / abs(\z2)),
 \(abs(conj(\z1)*\z2) = abs(\z2) / abs(\z1)),
 \(abs(\z1*conj(\z2)) = abs(\z1) - abs(\z2)),
 \(abs(conj(\z1)*\z2) = abs(\z2) - abs(\z1)),
 \(abs(\z1/\z2) = abs(\z1) - abs(\z2)),
 \(abs(1/\z1) = - abs(\z1)),
 \(abs(-1/\z1) = - abs(\z1)),
 \(abs(1/\z1) = - 1/abs(\z1)),
 \(abs(1/\z1) = abs(conj(\z1))),
 \(abs(\z1+conj(\z2)) = abs(\z1+\z2)),
 \(abs(conj(\z1)+\z2) = abs(\z1+\z2)),
 \(abs(\z1-conj(\z2)) = abs(\z1-\z2)),
 \(abs(conj(\z1)-\z2) = abs(\z1-\z2)),
 \(abs(\i*\z1) = \i*abs(\z1)),
 \(abs(\i+\z1) = \i+abs(\z1)),
 \(abs(\i/\z1) = \i/abs(\z1)),
 \(abs(\z1^2) = 2*abs(\z1)),
 \(abs(\z1)^2 = \z1^2),
)}

#include "goodbad4.inc"

\statement{设 \(z1,z2) 是两个复数.
#include "goodbadlist4.inc"
}

\reply{\cond\propsname是}{\ans;1,2,3,4}{type=checkbox}
