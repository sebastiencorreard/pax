target=rg
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{black=random(8..20)}
\integer{white=random(8..20)}
\integer{total=\black+\white}
\integer{extract=random(3..7)}
\integer{eblack=random(1..\extract-1)}
\integer{ewhite=\extract-\eblack}
\real{sol=binomial(\black,\eblack)*binomial(\white,\ewhite)/binomial(\total,\extract)}

\statement{\name_statement[1] \black \name_statement[2] \white \name_statement[3] \extract
  \name_statement[4], \name_statement2 \eblack \if{\eblack=1}{\name_color[1]}{\name_color[2]}
 \name_and \ewhite \if{\ewhite=1}{\name_color[3]&nbsp;?}{\name_color[4]&nbsp;?}
}

\answer{\name_answer}{\sol}
