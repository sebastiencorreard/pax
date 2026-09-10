target=negationLN

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\range{-10..10}
\text{monaide=wims(record 11 of \glossaire)}
\help{\monaide}

\integer{a=random(1..4)}
\integer{cas=\a<3?1:2}
\integer{u=random(1..7)}

\text{sujets=\cas==2?\name_subjects}
\text{verbes=\cas==2?\name_verbs}
\text{nonverbes=\cas==2?\name_nonverbs}

\text{suj=\cas==2?item(2*\u-1, \sujets)}
\text{sujs=\cas==2?item(2*\u,\sujets)}
\text{verb=\cas==2?item(2*\u-1, \verbes)}
\text{verbs=\cas==2?item(2*\u, \verbes)}
\text{nonverb=\cas==2?item(2*\u-1, \nonverbes)}
\text{nonverbs=\cas==2?item(2*\u, \nonverbes)}
\text{adj=\cas==2?item(\u,\name_adj)}
\text{nonadj=\cas==2?item(\u,\name_nonadj)}

\text{Alist=\cas==1?\name_Alist}
\text{Blist= \cas==1?\name_Blist}
\text{nonAlist=\cas==1?\name_nonAlist}
\text{nonBlist=\cas==1?\name_nonBlist}

\text{A=\cas==1?item(\u,\Alist)}
\text{B=\cas==1?item(\u,\Blist)}
\text{nonA=\cas==1?item(\u,\nonAlist)}
\text{nonB=\cas==1?item(\u,\nonBlist)}

\text{Tous=\u<6?\Tous1:\Tous2}
\text{prop=item(\a,\A \name_et \B,\A \name_ou \B,\Ilexiste \suj \qui \verb, \Tous \sujs \verbs )}

\text{neg=\a==1?\nonA \name_ou \nonB}
\text{neg=\a==2?\nonA \name_et \nonB}

\text{ass=\a==1?
\A \name_ou \nonB,
\nonA \name_ou \B,
\nonA \name_et \nonB
}

\text{ass=\a==2?
\A \name_et \nonB,
\nonA \name_et \B,
\nonA \name_ou \nonB
}

\text{neg=(\a==3)?randitem(\Aucun \suj \nest \adj, \Tous \sujs \nonverbs)}

\text{ass=(\a==3)?
\Tous \sujs \verbs,
\Aucun \suj \nest \nonadj,
\Ilexiste \suj \qui \nonverb,
\Certains \sujs \verbs,
\Certains \sujs \nonverbs
}

\text{neg=(\a==4)?randitem(\Ilexiste \suj \qui \nonverb, \Certains \sujs \nonverbs)}

\text{ass=(\a==4)?
\Certains \sujs \verbs,
\Ilexiste \suj \qui \verb,
\Aucun \suj \nest \adj,
\Aucun \suj \nest \nonadj,
\Tous \sujs \nonverbs
}

\text{choix=shuffle(\ass)}

\statement{<div class="wims_question">
<p>\name_statement1</p>
<div class="wimscenter"> <span class="fraseA">\(P) : " \prop "</span></div>
<p>\name_statement2</p>
</div>
}

\choice{\name_question}{\neg}{\choix}

\feedback{\a==4 and (\choice1 issametext \Aucun \suj \nest \nonadj)}
{<b>\Remarque</b>
\name_remark1 "\Aucun \suj \nest \nonadj" \name_remark2 "\prop" \name_remark3.}
