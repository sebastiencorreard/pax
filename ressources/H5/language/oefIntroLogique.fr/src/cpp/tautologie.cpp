target=tautologie

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\range{-10..10}
\text{monaide=wims(record 6  of \glossaire)}
\help{\monaide}

\integer{a=random(1..18)}
\text{A=item(\a,\Alist)}
\text{nonA=item(\a,\nonAlist)}
\text{B=item(\a,\Blist)}
\text{nonB=item(\a,\nonBlist)}

\text{si=\a<6?\si1:\si2}

\text{tau=\si \A \alors  \A,
\si \A \alors  \A \name_ou \B,
\si \A \alors \si2 \B \alors  \A,
\si \A \name_et \si \B \alors \A,
\A \name_ou \B \name_ou (\nonA \name_et \nonB),
\A \name_ou \nonA,
\A \name_ou \B \name_ou \nonA,
\si \nonA \alors \A \name_ou \nonA,
\si \nonA \name_et \si \A \alors \B,
\si \A \name_et \si2 \B \alors \A \name_ou \B,
\si \A \alors \B \name_ou \si2 \B \alors \A,
\si \A \alors \B \name_ou \si2 \nonA \alors \B
}

/** les 12 premières  sont tautologiques , les 11 suivantes non **/
\text{ass=\tau,
\A \name_ou \B,
\A \name_et \B,
\si \A \alors \B,
\A \name_et \nonA,
\si \A \alors \nonA,
\si \A \alors \nonA \name_ou \B,
\si \A \alors \A \name_et \B,
\si \nonA \alors \A \name_ou  \B,
\si \A \name_ou \si \B \alors \A et \B,
\si \nonA \name_ou \si \A \alors  \B,
\si \A \alors \B \name_et \si \B \alors \A
}

\text{typ=
\(A \rightarrow A),
\(A \rightarrow A \ou B),
\(A \rightarrow (B \rightarrow A)),
\(A \et B \rightarrow  A),
\(A \ou B \ou (\not{A} \et \not{B})),
\(A \ou \not{A}),
\(A \ou B \ou \not{A}),
\(\not{A} \rightarrow A \ou \not{A}),
\(\not{A} \et A \rightarrow  B),
\(A \et B \rightarrow A \ou B),
\(A \rightarrow B \ou B \rightarrow A),
\(A \rightarrow B \ou \not{A} \rightarrow B),
\(A \ou B),
\(A \et B),
\(A \rightarrow B),
\(A \et \not{A}),
\(A \rightarrow \not{A}),
\(A \rightarrow \not{A} \ou B),
\(A \rightarrow A \et B),
\(\not{A} \rightarrow A \ou  B),
\(A \ou B \rightarrow A \et B),
\(\not{A} \ou A \rightarrow B),
\(A \rightarrow B \et B \rightarrow A)
}

\integer{ind=random(1..23)}
\text{P=item(\ind,\ass)}
\text{typP=item(\ind,\typ)}
\text{shtyp=shuffle(\typ)}

\text{choix=item(1,\shtyp),item(2,\shtyp),item(3,\shtyp),
item(4,\shtyp),item(5,\shtyp)}
\text{liste=
(\typP isitemof \choix)?shuffle(\choix):shuffle(\typP,\choix)}

\integer{rep1=position(\typP,\liste)}
\integer{rep2=\ind<13?1:2}
\integer{test=(\typP isitemof \choix)?\oui:\non}

\integer{numliste=items(\liste)}

\statement{<div class="wims_question">

<p>\Soient \(A) : <span class="fraseC">" \A "</span>
\name_et
\(B) : <span class="fraseB">" \B "</span>. </p>
<p>\name_statement1 \(P) \name_statement2\spacebeforecolon:</p>
<div class="wimscenter"><span class="fraseA"> \(P) : " \P "</span></div>
<p>\name_question1 \(P)\spacebeforecolon?</p>
<div class="wimscenter">
<ul class="inline">
\for{k=1 to \numliste}{
<li class="unbreakable">\embed{r1,\k}</li>
}
</ul>
</div>
<div> \(P) \name_question2\spacebeforecolon? \embed{reply2}</div>
</div>
}

\answer{Type formule}{\rep1;\liste}{type=checkbox}
\answer{Tautologie?}{\rep2;\oui,\non}{type=checkbox}
\hint{\name_hint}
