target=mots
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{tot=random(6..10)}
\integer{adj=random(2..4)}
\text{lett=item(\adj,A,A B,A B C,A B C D)}
\integer{sol=factorial(\tot-\adj+1)*factorial(\adj)}
\text{question=wims(replace internal TTTT by \tot in \name_question)}
\text{question=wims(replace internal AAAA by \adj in \question)}
\text{question=wims(replace internal BBBB by \lett in \question)}
\statement{\question?}

\hint{\name_hint[1] \adj \name_hint[2] }
\answer{\name_answer}{\sol}
