target=arg

\title{辐角}
#include "header.inc"
\text{propsname=公式}
\text{z12=shuffle(z1,z2)}
\text{z1=item(1,\z12)}
\text{z2=item(2,\z12)}
\text{z3=z3}
\text{c1=randint(1..5)}
\text{i1=randint(1..5)*i}
\text{ri=randint(2..9)}
\text{a0=random(0,2*pi,-2*pi)}
\text{a1=random(pi,-pi)}
\text{ai=random(pi/2,-3*pi/2)}
\text{aj=random(-pi/2,3*pi/2)}
\text{mod=&nbsp;&nbsp;&nbsp;(mod \(2*pi))}
\text{equiv=\(\equiv)}
\text{good=shuffle(
 \(Arg(z1*z2)) \equiv \(Arg(z1) + Arg(z2)) \mod,
 \(Arg(z1/z2)) \equiv \(Arg(z1) - Arg(z2)) \mod,
 \(Arg(1/z1)) \equiv \(-Arg(z1)) \mod,
 \(Arg(conj(z1))) \equiv \(-Arg(z1)) \mod,
 \(Arg(conj(z1))) \equiv \(Arg(1/z1)) \mod,
 \(Arg(\c1)) \equiv \(\a0) \mod,
 \(Arg(-\c1)) \equiv \(\a1) \mod,
 \(Arg(\i1)) \equiv \(\ai) \mod,
 \(Arg(-\i1)) \equiv \(\aj) \mod,
 \(Arg(|z1|)) \equiv \(\a0) \mod,
 \(Arg(z1^2)) \equiv \(2*Arg(z1)) \mod,
 \(Arg(-z1)) \equiv \(Arg(z1) random(+,-) pi) \mod,
 \(Arg(i*z1)) \equiv \(Arg(z1) random(+ pi/2, - 3*pi/2)) \mod,
 \(Arg(z1/i)) \equiv \(Arg(z1) random(- pi/2, + 3*pi/2)) \mod,
 \(Arg(\ri*z1)) \equiv \(Arg(z1)) \mod,
 \(Arg(-\ri*z1)) \equiv \(Arg(z1) random(+,-) pi) \mod,
)}
\text{bad=shuffle(
 \(Arg(0)) \equiv 0 \mod,
 \(Arg(z1*z2)) \equiv \(Arg(z1) * Arg(z2)) \mod,
 \(Arg(z1/z2)) \equiv \(Arg(z1) / Arg(z2)) \mod,
 \(Arg(1/z1)) \equiv \(1/Arg(z1)) \mod,
 \(Arg(z1+z2)) \equiv \(Arg(z1) + Arg(z2)) \mod,
 \(Arg(z1-z2)) \equiv \(Arg(z1) - Arg(z2)) \mod,
 \(Arg(-z1)) \equiv \(-Arg(z1)) \mod,
 \(Arg(conj(z1))) \equiv \(conj(Arg(z1))) \mod,
 \(Arg(\c1) = \a0), \(Arg(-\c1) = \a1), 
 \(Arg(\i1) = \ai), \(Arg(-\i1) = \aj),
 \(Arg(\c1)) \equiv \(\c1) \mod,
 \(Arg(-\c1)) \equiv \(random(,-)random(2,4,6)*pi) \mod,
 \(Arg(-\c1)) \equiv \(random(\ai,\aj)) \mod,
 \(Arg(\i1)) \equiv \(random(\aj,\aj,pi/4,-pi/4,\a1)) \mod,
 \(Arg(-\i1)) \equiv \(random(\ai,\ai,-pi/4,pi/4,\a1)) \mod,
 \(Arg(|z1|)) \equiv \(|Arg(z1)|) \mod,
 \(Arg(z1^2)) \equiv \(Arg(z1)^2) \mod,
 \(Arg(i*z1)) \equiv \(Arg(z1) random(- pi/2, + 3*pi/2, + pi/4, - pi/4, +3*pi/4, -3*pi/4, +pi, -pi)) \mod,
 \(Arg(z1/i)) \equiv \(Arg(z1) random(+ pi/2, - 3*pi/2, + pi/4, - pi/4, +3*pi/4, -3*pi/4, +pi, -pi)) \mod,
 \(Arg(\ri*z1)) \equiv \(\ri*Arg(z1)) \mod,
 \(Arg(-\ri*z1)) \equiv \(-Arg(z1)) \mod,
 \(Arg(-\ri*z1)) \equiv \(-\ri*Arg(z1)) \mod,
)}

#include "goodbad4.inc"

\statement{设 \(z1,z2) 是两个非零复数.
#include "goodbadlist4.inc"
}

\reply{\cond\propsname是}{\ans;1,2,3,4}{type=checkbox}
