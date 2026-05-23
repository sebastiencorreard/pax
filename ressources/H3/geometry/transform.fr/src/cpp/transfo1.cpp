target=symax1 symcen1 rota1

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{liste=1,2,3,4,5,6,7,8}
\text{image=transfo1.png}

#if defined TARGET_symax1
\matrix{data=1,1,
2,8,
3,7,
4,6,
5,5,
6,4,
7,3,
8,2}
\text{K=randomrow(\data)}
\text{instruction=\name_instruction[1] \((DH)\) \name_instruction[2] }
\if{\K[1]=1 or \K[1]=5}{\text{sol=\name_onmeme}}
                       {\text{sol=\name_oncarre <span class="nowrap">\(\K[2]\).</span>}}
#endif

#if defined TARGET_symcen1
\matrix{data=1,5
2,6
3,7
4,8
5,1
6,2
7,3
8,4}
\text{K=randomrow(\data)}
\text{instruction=\name_instruction[1] \(O\) \name_instruction[2]}
#endif

#if defined TARGET_rota1
\integer{j=randint(2..8)}
\text{liste1=wims(makelist x for x=1 to \j-1)}
\text{liste2=wims(listcomplement \liste1 in \liste)}
\text{liste3=\liste2,\liste1}
\matrix{data=1,\liste3[1]
2,\liste3[2]
3,\liste3[3]
4,\liste3[4]
5,\liste3[5]
6,\liste3[6]
7,\liste3[7]
8,\liste3[8]}
\text{K=randomrow(\data)}
\text{liste4=wims(listcomplement \K[1] in \liste)}
\integer{dep=randomitem(\liste4)}
\text{dep=\dep,\data[\dep;2]}
\text{instruction=\name_instruction[1] \(\K[1]\) \name_instruction[2] \(O\) \name_instruction[3] \(\dep[1]\) \name_instruction[4] }
\integer{ecart=\dep[1]-\dep[2]}
\integer{absecart=abs(\ecart)}
\if{\ecart>0}{\text{sens=\name_sens_list[2]}}{\text{sens=\name_sens_list[1]}}
\if{\absecart>4 and \ecart>0}{\integer{absecart=8-\absecart}
                              \text{sens=\name_sens_list[1]}}
\if{\absecart>4 and \ecart<0}{\integer{absecart=8-\absecart}
                              \text{sens=\name_sens_list[2]}}
\if{\absecart=1}{\text{saut=\name_saut_list[1]}}{\text{saut=\name_saut_list[2]}}
#endif

#include "lang2.inc"

\statement{\name_statement
<p class="wimscenter"><img src="\imagedir/\image" alt="carrés"></p>
\instruction
#if defined TARGET_rota1
 <span class="nowrap">\(\dep[2]\) ?</span>
#endif
#if defined TARGET_symcen1 || defined TARGET_symax1
<span class="nowrap">\(\K[1]\) ?</span>
#endif
  \name_carre \embed{reply1}.
}
\answer{}{\K[2];\liste}{type=menu}

\solution{\name_solution}
