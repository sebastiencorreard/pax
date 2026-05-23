target=symax2 symcen2 rota2 rota2bis

#include "author.inc"
#include "lang_titles.inc"
#include "css.inc"

\text{image=transfo2.png}
\text{liste=wims(makelist x for x=1 to 20)}

#include "lang.inc"

#if defined TARGET_symax2
\matrix{data=1,6,
2,5,
3,4,
4,3,
5,2,
6,1,
7,10,
8,9,
9,8,
10,7,
11,16,
12,15,
13,14,
14,13,
15,12,
16,11,
17,20,
18,19,
19,18,
20,17}
\text{K=randomrow(\data)}
\text{instruction=\name_instruction[1] \(\K[1]\) \name_instruction[2] }
\text{action=\name_instruction[3] <span class="nowrap">\((d)\),</span>}
\text{nom=\name_instruction[4] \((d)\)}
#endif

#if defined TARGET_symcen2
\matrix{data=1,6,
2,7,
3,8,
4,9,
5,10,
6,1,
7,2,
8,3,
9,4,
10,5,
11,16,
12,17,
13,18,
14,19,
15,20,
16,11,
17,12,
18,13,
19,14,
20,15}
\text{K=randomrow(\data)}
\text{instruction=\name_instruction[1] \(\K[1]\) \name_instruction[2] }
\text{action=\name_instruction[3] <span class="nowrap">\(O\),</span>}
\text{nom=\name_instruction[4] \(O\)}
#endif

#if defined TARGET_rota2
\text{angle=36,72,108,144}
\integer{coef=randint(4)}
\integer{nangle=\angle[\coef]}
\integer{choix=randint(2)}
\integer{depart=randint(20)}
\text{list=1,2,3,4,5,6,7,8,9,10}
\text{List=11,12,13,14,15,16,17,18,19,20}
\text{list11=wims(makelist x for x=1 to \coef)}
\text{list12=wims(listcomplement \list11 in \list)}
\text{list13=\list12,\list11}
\text{List11=wims(makelist x for x=11 to 10+\coef)}
\text{List12=wims(listcomplement \List11 in \List)}
\text{List13=\List12,\List11}
\text{list21=wims(makelist x for x=1 to 10-\coef)}
\text{list22=wims(listcomplement \list21 in \list)}
\text{list23=\list22,\list21}
\text{List21=wims(makelist x for x=11 to 20-\coef)}
\text{List22=wims(listcomplement \List21 in \List)}
\text{List23=\List22,\List21}
\if{\choix=1}{\text{listdeca=\list13,\List13}
\text{goodrep=\listdeca[\depart]}
\text{listdecabad=\list23,\List23}
\text{badrep=\listdecabad[\depart]}}
\if{\choix=2}{\text{listdeca=\list23,\List23}
\text{goodrep=\listdeca[\depart]}
\text{listdecabad=\list13,\List13}
\text{badrep=\listdecabad[\depart]}}
\text{instruction=\name_instruction[1] \depart \name_instruction[2] \(O\), \name_instruction[3] \(\angle[\coef]^{\circ}\) \name_sens_list[\choix]&nbsp;?}
\if{\coef=1}{\text{saut=\name_saut_list[1]}}{\text{saut=\name_saut_list[2]}}
#endif

#if defined TARGET_rota2bis
\text{angle=36,72,108,144}
\integer{coef=randint(4)}
\integer{choix=randint(2)}
\integer{depart=randint(20)}
\text{list=1,2,3,4,5,6,7,8,9,10}
\text{List=11,12,13,14,15,16,17,18,19,20}
\if{\choix=1}{
\text{list1=wims(makelist x for x=1 to \coef)}
\text{list2=wims(listcomplement \list1 in \list)}
\text{list3=\list2,\list1}
\text{List1=wims(makelist x for x=11 to 10+\coef)}
\text{List2=wims(listcomplement \List1 in \List)}
\text{List3=\List2,\List1}
}
\if{\choix=2}{\text{list1=wims(makelist x for x=1 to 10-\coef)}
\text{list2=wims(listcomplement \list1 in \list)}
\text{list3=\list2,\list1}
\text{List1=wims(makelist x for x=11 to 20-\coef)}
\text{List2=wims(listcomplement \List1 in \List)}
\text{List3=\List2,\List1}}
\text{listdeca=\list3,\List3}
\integer{goodrep=\angle[\coef]}
\integer{badrep=360-\angle[\coef]}
\text{tgoodrep=\angle[\coef]°}
\text{tbadrep=\badrep°}
\text{lastchar=}
\text{instruction=\name_instruction[1] \(O\) \name_sens_list[\choix] \name_instruction[2] \depart \name_instruction[3] \listdeca[\depart]&nbsp;?
<div class="wims_instruction"><span style="color:red">\name_instruction[4].</span></div>}
\if{\coef=1}{\text{saut=\name_saut_list[1]}}{\text{saut=\name_saut_list[2]}}
#endif

#include "lang2.inc"

\statement{\name_statement <span class="nowrap">\(\widehat{AOB}=36^{\circ}\).</span>
<p class="wimscenter"><img src="\imagedir/\image" alt="motif"></p>
\instruction
#if defined TARGET_symax2
\name_transf <span class="nowrap">\((d)\) ?</span>
#endif
#if defined TARGET_symcen2
\name_transf <span class="nowrap">\(O\).</span>
#endif
}
#if defined TARGET_symax2 || defined TARGET_symcen2
\answer{\name_answer}{\K[2];\liste}{type=menu}
\solution{\name_solution1
<p>\name_conclusion: \name_solution2</p>}
#endif
#if defined TARGET_rota2
\answer{\name_answer}{\goodrep;\liste}{type=menu}
\feedback{\badrep=\reply1}{<div class="macss">\name_feedback</div>}
\solution{<span class="nowrap">\(\angle[\coef]^{\circ}=\coef \times 36^{\circ}\).</span>
\name_solution}
#endif
#if defined TARGET_rota2bis
\answer{\name_answer}{\rep}
\text{lastchar=wims(char -1 of \rep)}
\text{repsansunit=wims(replace internal ° by in \rep)}
\condition{\name_condition1?}{\repsansunit=\goodrep}{weight=10}
\condition{\name_condition2?}{\lastchar issametext °}{weight=1}
\feedback{\badrep=\repsansunit and \lastchar notsametext °}{<div class="macss">\name_feedback[1], \name_feedback[2] \depart \name_feedback[3] \listdeca[\depart] \name_feedback[4] \name_and \name_feedback[5].</div>}
\feedback{\badrep=\repsansunit and \lastchar issametext °}{<div class="macss">\name_feedback[1], \name_feedback[2] \depart \name_feedback[3] \listdeca[\depart] \name_feedback[4].</div>}
\feedback{\repsansunit<>\goodrep and \lastchar notsametext ° and \repsansunit<>\badrep}{<div class="macss">\name_feedback[1], \name_feedback[6].</div>}
\feedback{\repsansunit=\goodrep and \lastchar notsametext °}{<div class="macss">\name_feedback[1], \name_feedback[7].</div>}
\solution{\name_solution1.
<p class="nowrap">\(\coef \times 36^{\circ}=\goodrep^{\circ}\).</p>
\name_conclusion: \name_solution2</p>}
#endif
