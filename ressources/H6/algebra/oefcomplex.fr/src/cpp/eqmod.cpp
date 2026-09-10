target=eqmod
\keywords{equations}
#include "common.inc"
#include "lang_title.inc"

\integer{a=random(1..20)*random(-1,1)}
\integer{b=random(2..20)*random(-1,1)}
\complex{z1=\a+\b*i}
\integer{type=random(1,2)}
\text{sign=item(\type,+,-)}
\text{s2=item(\type,,-)}
\real{im=\b}
\real{re=((\a)^2-(\b)^2)/(2*(\a))}
\complex{z=(\a>0 and \type=1) or (\a<0 and \type=2)?\re+(\im)*i:0+0*i}

#include "lang.inc"

\statement{\name_statement \(z\sign|z|=\z1).
<div class="wims_instruction">
\name_instruction[1] <span class="tt">0</span> \name_instruction[2].
</div>
}

\answer{\(z)}{\z}{type=complex}
\hint{\name_hint[1], \name_hint[2] \(z), \(\s2|z|),
\(\z1) \name_hint[3].}
