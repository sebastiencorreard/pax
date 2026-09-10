target=bw
#include "author.inc"
#include "lang_titles.inc"

\integer{black=random(6..20)}
\integer{white=random(6..20)}
\integer{total=\black+\white}

#include "lang.inc"

\integer{type=random(1..3)}
\text{balls=item(\type,\name_balls)}
\real{sol=item(\type,2*\black*\white/(\total*(\total-1)),
		\black*(\black-1)/(\total*(\total-1)),
		\white*(\white-1)/(\total*(\total-1)))}

\statement{\name_statement \balls\name_space?}

\answer{\name_answer}{\sol}
