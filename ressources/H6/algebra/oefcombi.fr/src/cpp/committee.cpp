target=committee

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{boys =random(5..9)}
\integer{girls=random(5..9)}
\integer{tot=\boys+\girls}
\integer{cboys=random(1..2)}
\integer{cgirls=random(1..2)}
\text{boy=\cboys=1?\name_gb[1]:\name_gbs[1]}
\text{girl=\cgirls=1?\name_gb[2]:\name_gbs[2]}
\integer{type=random(1..2)}
\integer{comite=\cboys+\cgirls+\type}
\integer{chboy=factorial(\boys)/(factorial(\cboys)*factorial(\boys-\cboys))}
\integer{chgirl=factorial(\girls)/(factorial(\cgirls)*factorial(\girls-\cgirls))}
\integer{chboy1=factorial(\boys)/(factorial(\cboys+1)*factorial(\boys-\cboys-1))}
\integer{chgirl1=factorial(\girls)/(factorial(\cgirls+1)*factorial(\girls-\cgirls-1))}
\integer{chboy2=factorial(\boys)/(factorial(\cboys+2)*factorial(\boys-\cboys-2))}
\integer{chgirl2=factorial(\girls)/(factorial(\cgirls+2)*factorial(\girls-\cgirls-2))}
\integer{sol=\type=1?\chboy*\chgirl1+\chboy1*\chgirl:
	\chboy*\chgirl2+\chboy1*\chgirl1+\chboy2*\chgirl}
\text{question=wims(replace internal XXXX by \boys in \name_question)}
\text{question=wims(replace internal YYYY by \girls in \question)}
\text{question=wims(replace internal CCCC by \comite in \question)}
\text{question=wims(replace internal BBBB by \cboys \boy in \question)}
\text{question=wims(replace internal GGGG by \cgirls \girl in \question)}

\statement{\question?}

\answer{\name_answer}{\sol}
