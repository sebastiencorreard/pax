target=critere1 critere2 critere3 critere4 critere5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_critere1
 \integer{div=2}
 \text{ltchi=\(0, 2, 4, 6\) ou 8}
 \integer{ph=1}
#endif
#if defined TARGET_critere2
 \integer{div=3}
 \text{ltchi=\(3,6) ou 9}
 \integer{ph=2}
#endif

#if defined TARGET_critere3
 \integer{div=5}
 \text{ltchi=0 ou 5}
 \integer{ph=1}
#endif

#if defined TARGET_critere4
 \integer{div=9}
 \text{ltchi=9}
 \integer{ph=2}
#endif

#if defined TARGET_critere5
 \integer{div=4}
 \text{ltchi=\(0,4\) ou 8}
 \integer{ph=0}
#endif
\precision{100}

\text{phrases=wims(replace internal XXXX by \ltchi in \name_phrases)}
\text{phrases=wims(replace internal YYYY by \div in \phrases)}
\text{phrase2=wims(replace internal YYYY by \div in \name_phrase2)}
\text{good=\ph!=0?item(\ph,\phrases):
  \phrase2}
\statement{
  \name_question[1] \div \name_question[2]:}

\choice{\name_answer}{\good}{\phrases}
