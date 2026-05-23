target=Verbesirrgulie Verbesirrgulie2 Verbesirrgulie3 Verbesirrgulie4

#include "bpr.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\range{-30..30}
\computeanswer{yes}
\format{html}
\precision{10000}

\integer{u=1}
#if defined TARGET_Verbesirrgulie || defined TARGET_Verbesirrgulie3
#include "list1.inc"
#endif
#if defined TARGET_Verbesirrgulie2 || defined TARGET_Verbesirrgulie4
#include "list2.inc"
#endif
\integer{n= rows(\liste)}
\text{selec =item(1..\u,shuffle(\n))}
\text{selection= row(\selec,\liste)}
\text{possible=item(1..3,row(2,\table))}
#if defined TARGET_Verbesirrgulie || defined TARGET_Verbesirrgulie2
\integer{v=1}
\integer{w=2}
#endif
#if defined TARGET_Verbesirrgulie3 || defined TARGET_Verbesirrgulie4
\integer{v=randint(1,2,2,2,3,3,3)}
\integer{w=randint(1..3)}
#endif
\text{base1=item(\v,\selection)}
\text{file=transl_\lang}
\text{traduction=wims(lookup \selection[1] in \file)}
#if defined TARGET_Verbesirrgulie || defined TARGET_Verbesirrgulie2
\text{base2= item(\w,\selection)}
\text{base3= item(3,\selection)}
#endif
#if defined TARGET_Verbesirrgulie3 || defined TARGET_Verbesirrgulie4
\text{base2 = item(\w,\possible)}
\text{item1= item(1,\selection)}
\text{item2= item(2,\selection)}
\text{item3= item(3,\selection)}
\text{sol= item(\v, \possible)}
\text{sol1 = \base1 issametext item(1,\selection) and \v<>1 ? \sol, item(1, \possible): \sol}
\text{sol2 = \base1 issametext item(2,\selection) and \v<>2? \sol1, item(2, \possible): \sol1}
\text{sol3 = \base1 issametext item(3,\selection) and \v<>3 ? \sol2, item(3, \possible): \sol2}
\text{solu= item(\w, \selection)}
#endif
#if defined TARGET_Verbesirrgulie || defined TARGET_Verbesirrgulie2
\statement{
\name_enonce
<span style="color:green" class="bold">to \base1</span> :}
\answer{\name_answer[1] }{\base2}{type=nocase}
\answer{\name_answer[2] }{\base3}{type=nocase}
\feedback{1=1}{\name_feed[1] <span style="color:green" class="bold">to \base1</span>
 \name_feed[2] <span style="color:magenta" class="bold">\traduction</span> .}
#endif
#if defined TARGET_Verbesirrgulie3 || defined TARGET_Verbesirrgulie4
\statement{
\name_enonce[1;] <span style="color:green" class="bold">\base1</span>
\name_enonce[2;] (\name_enonce[3;] : \traduction) ?
\name_enonce[4;] \base2.
}

\choice{\name_answer}{\sol3}{\possible}
\answer{\base2 \name_is }{\solu}{type=nocase}
\feedback{, isin \sol3}{\name_feed \sol3}
#endif
