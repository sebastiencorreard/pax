target=conj

\title{共轭}
#include "header.inc"
\text{propsname=公式}
\text{z12=shuffle(z_1,z_2)}
\text{z1=item(1,\z12)}
\text{z2=item(2,\z12)}
\text{z3=z3}
\text{i=random(i,-i)}
\text{in=\i issametext i?-i:i}
\integer{n=random(1..5)*random(1,-1)}
\integer{nn=-\n}
\integer{pos=random(2..8)}
\text{cj=\overline}
\text{dot=\cdot}
\text{good=shuffle(
 \(\cj{\z1+\z2} = \cj{\z1} + \cj{\z2}),
 \(\cj{\z1\dot \z2} = \cj{\z1} \dot \cj{\z2}),
 \(\cj{\z1}\dot \z2 = \z2\dot \cj{\z1}),
 \(\cj{\left(1/\z1\right)} = 1/\cj{\z1}),
 \(\cj{\i} = \in), \(\cj{\n} = \n),
 \(\cj{\i\dot \z1} = \in\dot \cj{\z1}),
 \(\cj{\z1 + i \z2} = \cj{\z1} - i\cj{\z2}),
 \(\cj{\z1 + i} = \cj{\z1} - i),
 \(\cj{\z1 - i} = \cj{\z1} + i),
 \(\cj{\left(\i/\z1\right)} = \in/\cj{\z1}),
 \(\cj{\left(\z1/\z2\right)} = \cj{\z1}/\cj{\z2}),
 \(\cj{\z1 + \pos} = \cj{\z1} + \pos),
 \(\cj{\z1 - \pos} = \cj{\z1} - \pos),
)}
\text{bad=shuffle(
 \(\cj{\z1+\z2} = \cj{\z1} - \cj{\z2}),
 \(\cj{\z1+\z2} = \cj{\z1} + \z2),
 \(\cj{\z1\dot \z2} = \cj{\z1}\dot \z2),
 \(\cj{\z1}\dot \z2 = \cj{\z2}\dot \z1),
 \(\cj{\left(1/\z1\right)} = -1/\cj{\z1}),
 \(\cj{\i} = \i), \(\cj{\n} = \nn),
 \(\cj{\i\dot \z1} = \i\dot \cj{\z1}),
 \(\cj{\i\dot \z1} = \in\dot \z1),
 \(\cj{\z1 + i \z2} = \cj{\z1} - i \z2),
 \(\cj{\z1 + i \z2} = \cj{\z1} + i\cj{\z2}),
 \(\cj{\z1 + i} = \cj{\z1} + i),
 \(\cj{\z1 + i} = \cj{\z1} + 1),
 \(\cj{\left(\i/\z1\right)} = \i/\cj{\z1}),
 \(\cj{\z1}/\z2 = \z1/\cj{\z2}),
 \(\cj{\z1}/\z2 = -\z1/\cj{\z2}),
 \(\cj{\z1}/\z2 = i\dot \z1/\cj{\z2}),
 \(\cj{\z1 + \pos} = \cj{\z1} - \pos),
 \(\cj{\z1 - \pos} = \cj{\z1} + \pos),
)}

#include "goodbad4.inc"

\statement{设 \(z1,z2,z3) 是复数.
#include "goodbadlist4.inc"
}

\reply{\cond\propsname是}{\ans;1,2,3,4}{type=checkbox}
