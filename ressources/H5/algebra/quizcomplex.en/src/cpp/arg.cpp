target=arg

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{z12=shuffle(z_1,z_2)}
\text{z1=item(1,\z12)}
\text{z2=item(2,\z12)}
\text{z3=z_3}
\text{c1=randint(1..5)}
\text{i1=randint(1..5)}
\text{i1=\i1=1 ? i:\i1 i}
\text{ri=randint(2..9)}
\text{a0=random(0,2 \pi,-2 \pi)}
\text{a1=random(\pi,-\pi)}
\text{ai=random(\pi/2,-3 \pi/2)}
\text{aj=random(-\pi/2,3 \pi/2)}
\text{mod=\mod 2\pi}
\text{equiv=\equiv}
\text{good=shuffle(
 Arg(z_1 z_2) \equiv Arg(z_1) + Arg(z_2) \mod,
 Arg(z_1/z_2)\equiv Arg(z_1) - Arg(z_2) \mod,
 Arg(1/z_1) \equiv -Arg(z_1) \mod,
 Arg(\bar{z_1}) \equiv -Arg(z_1) \mod,
 Arg(\overline{z_1}) \equiv Arg(1/z_1) \mod,
 Arg(\c1) \equiv \a0 \mod,
 Arg(-\c1) \equiv \a1 \mod,
 Arg(\i1) \equiv \ai \mod,
 Arg(-\i1) \equiv \aj \mod,
 Arg(|z_1|) \equiv \a0 \mod,
 Arg(z_1^2) \equiv 2 Arg(z_1) \mod,
 Arg(-z_1) \equiv Arg(z_1) random(+,-) \pi \mod,
 Arg(i z_1) \equiv Arg(z_1) random(+ \pi/2, - 3 \pi/2) \mod,
 Arg(z_1/i) \equiv Arg(z_1) random(- \pi/2, + 3 \pi/2) \mod,
 Arg(\ri z_1) \equiv Arg(z_1) \mod,
 Arg(-\ri z_1)\equiv Arg(z_1) random(+,-) \pi \mod,
)}
\text{bad=shuffle(
 Arg(0) \equiv 0 \mod,
 Arg(z_1 z_2) \equiv Arg(z_1) Arg(z_2) \mod,
 Arg(z_1/z_2)\equiv Arg(z_1) / Arg(z_2) \mod,
 Arg(1/z_1)\equiv 1/Arg(z_1) \mod,
 Arg(z_1+z_2)\equiv Arg(z_1) + Arg(z_2)\mod,
 Arg(z_1-z_2)\equiv Arg(z_1) - Arg(z_2)\mod,
 Arg(-z_1)\equiv -Arg(z_1)\mod,
 Arg(\overline{z_1})\equiv \overline{Arg(z_1)}\mod,
 Arg(\c1) = \a0, Arg(-\c1) = \a1,
 Arg(\i1) = \ai, Arg(-\i1) = \aj,
 Arg(\c1)\equiv \c1\mod,
 Arg(-\c1)\equiv random(,-)random(2,4,6) \pi\mod,
 Arg(-\c1)\equiv random(\ai,\aj)\mod,
 Arg(\i1)\equiv random(\aj,\aj,\pi/4,-\pi/4,\a1)\mod,
 Arg(-\i1)\equiv random(\ai,\ai,-\pi/4,\pi/4,\a1)\mod,
 Arg(|z_1|)\equiv |Arg(z_1)|\mod,
 Arg(z_1^2)\equiv Arg(z_1)^2\mod,
 Arg(i z_1)\equiv Arg(z_1) random(- \pi/2, + 3 \pi/2, + \pi/4, - \pi/4, +3 \pi/4, -3 \pi/4, +\pi, -\pi)\mod,
 Arg(z_1/i)\equiv Arg(z_1) random(+ \pi/2, - 3 \pi/2, + \pi/4, - \pi/4, +3 \pi/4, -3 \pi/4, +\pi, -\pi)\mod,
 Arg(\ri z_1)\equiv \ri Arg(z_1)\mod,
 Arg(-\ri z_1)\equiv -Arg(z_1)\mod,
 Arg(-\ri z_1)\equiv -\ri Arg(z_1)\mod,
)}

#include "goodbad4.inc"

\statement{\name_instruction
#include "goodbadlist4.inc"
}

\reply{\name_answer[1] \cond \propsname \name_answer[2]}{\ans;1,2,3,4}{type=checkbox}

\latex{\begin{statement}
\name_instruction
#include "goodbadlist4latex.inc"
\end{statement}
}
