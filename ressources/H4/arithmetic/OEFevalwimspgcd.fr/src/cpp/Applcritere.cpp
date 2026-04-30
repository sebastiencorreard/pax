target=Applcritere1 Applcritere2 Applcritere3 Applcritere4 Applcritere5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_Applcritere1
 \integer{div=2}
 \text{autres=3,5,7,9}
#endif
#if defined TARGET_Applcritere2
 \integer{div=3}
 \text{autres=2,4,5,7,8}
#endif
#if defined TARGET_Applcritere3
 \integer{div=5}
 \text{autres=2,3,4,6,7,8,9}
#endif
#if defined TARGET_Applcritere4
 \integer{div=9}
 \text{autres=2,3,4,5,6,7,8}
#endif
#if defined TARGET_Applcritere5
 \integer{div=4}
 \text{autres=3,2,6,7,9}
#endif

\precision{100}

\text{val=wims(values v for v=5 to 35)}
\text{val=shuffle(\val)}
\text{A=}
\text{sol=}
\text{autres=shuffle(\autres)}
\text{mult=\div,\div,item(1,\autres),item(2,\autres)}
\for{i=1 to 4}{
 \integer{tmp=item(\i,\val)*item(\i,\mult)}
 \text{A=wims(append item \tmp to \A)}
 \integer{test=\tmp/\div}
 \integer{tst=\test*\div}
 \if{\tst=\tmp}{
  \text{sol=wims(append item \tmp to \sol)}
 }
}
\text{A=shuffle(\A)}
\statement{
   \name_question \div ?
<div class="wimscenter"> \A[1] ; \A[2] ; \A[3] ; \A[4] </div>

<br class="spacer">
<b>\name_answer:</b>
  \name_question2[1] \div \name_question2[2] \embed{r1,100x50}.
}
\answer{\name_num}{\rep;\A}{type=clickfill}

\integer{nb3=items(\sol)}
\text{tmplist=\rep,\sol}
\text{tmplist=wims(listuniq \tmplist)}
\integer{nb1=items(\tmplist)}
\text{replt=wims(listuniq \rep)}
\integer{nb2=items(\replt)}
\condition{\name_cond}{\nb1=\nb3 and \nb2=\nb3}

\solution{\name_sol[1] \div \name_sol[2]: \sol .}
