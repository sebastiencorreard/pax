target=symax4 symcen4 rota4

#include "author.inc"
#include "lang_titles.inc"
#include "css.inc"

\text{image=transfo4.png}

#if defined TARGET_symax4
\text{axe=AC,BD,EG,HF}
\text{axe=shuffle(\axe)}
\if{\axe[1]=AC or \axe[1]=BD}{
\if{\axe[1]=AC}{\text{point=A,B,C,D,E,F,G,H,I,J,K,L,M}}
\if{\axe[1]=BD}{\text{point=B,C,D,A,F,G,H,E,J,K,L,I,M}}
\matrix{data=\point[1],\point[5],\point[9],\point[1],\point[8],\point[9],
\point[2],\point[5],\point[10],\point[4],\point[8],\point[12],
\point[5],\point[10],\point[13],\point[8],\point[12],\point[13],
\point[5],\point[9],\point[13],\point[8],\point[9],\point[13],
\point[2],\point[10],\point[6],\point[4],\point[12],\point[7],
\point[10],\point[13],\point[6],\point[12],\point[13],\point[7],
\point[6],\point[13],\point[11],\point[7],\point[13],\point[11],
\point[6],\point[11],\point[3],\point[7],\point[11],\point[3]}}
\if{\axe[1]=EG or \axe[1]=HF}{
\if{\axe[1]=EG}{\text{point=A,B,C,D,E,F,G,H,I,J,K,L,M}}
\if{\axe[1]=HF}{\text{point=B,C,D,A,F,G,H,E,J,K,L,I,M}}
\matrix{data=\point[1],\point[5],\point[9],\point[2],\point[5],\point[10],
\point[5],\point[9],\point[13],\point[5],\point[10],\point[13],
\point[1],\point[9],\point[8],\point[2],\point[10],\point[6],
\point[9],\point[13],\point[8],\point[10],\point[13],\point[6],
\point[13],\point[12],\point[8],\point[13],\point[11],\point[6],
\point[8],\point[12],\point[4],\point[6],\point[11],\point[3],
\point[13],\point[12],\point[7],\point[13],\point[11],\point[7],
\point[12],\point[4],\point[7],\point[11],\point[3],\point[7]}}
#endif

#if defined TARGET_symcen4
\text{point=A,B,C,D,E,F,G,H,I,J,K,L,M}
\matrix{data=\point[1],\point[5],\point[9],\point[3],\point[7],\point[11],
\point[5],\point[9],\point[13],\point[7],\point[11],\point[13],
\point[1],\point[9],\point[8],\point[3],\point[11],\point[6],
\point[9],\point[13],\point[8],\point[11],\point[13],\point[6],
\point[13],\point[12],\point[8],\point[13],\point[10],\point[6],
\point[8],\point[12],\point[4],\point[6],\point[10],\point[2],
\point[13],\point[12],\point[7],\point[13],\point[10],\point[5],
\point[12],\point[4],\point[7],\point[10],\point[2],\point[5]}
#endif
#if defined TARGET_symax4 || defined TARGET_symcen4
\text{k=randomrow(\data)}
\text{tri1=\k[1]\k[2]\k[3],\k[1]\k[3]\k[2],\k[2]\k[1]\k[3],\k[2]\k[3]\k[1],\k[3]\k[1]\k[2],\k[3]\k[2]\k[1]}
\text{tri2=\k[4]\k[5]\k[6],\k[4]\k[6]\k[5],\k[5]\k[4]\k[6],\k[5]\k[6]\k[4],\k[6]\k[4]\k[5],\k[6]\k[5]\k[4]}
\integer{choix=randint(2)}
\if{\choix=1}{\text{tri=\tri1[1]}}{\text{tri=\tri2[1]}}
#endif

#include "lang.inc"

#if defined TARGET_rota4
\integer{choix=randint(2)}
\if{\choix=1}{\text{sens=\name_sense[2]}}{\text{sens=\name_sense[1]}}
\text{point=A,B,C,D,E,F,G,H,I,J,K,L,M}
\matrix{datatri=\point[1],\point[5],\point[9]
\point[5],\point[9],\point[13]
\point[1],\point[9],\point[8]
\point[9],\point[13],\point[8]
\point[13],\point[12],\point[8]
\point[8],\point[12],\point[4]
\point[13],\point[12],\point[7]
\point[12],\point[4],\point[7]
\point[11],\point[3],\point[7]
\point[11],\point[7],\point[13]
\point[6],\point[11],\point[3]
\point[6],\point[13],\point[11]
\point[6],\point[13],\point[10]
\point[6],\point[10],\point[2]
\point[5],\point[10],\point[13]
\point[2],\point[10],\point[5]}
\matrix{datapt=\point[1],\point[4],\point[2]
\point[2],\point[1],\point[3]
\point[3],\point[2],\point[4]
\point[4],\point[3],\point[1]
\point[5],\point[8],\point[6]
\point[6],\point[5],\point[7]
\point[7],\point[6],\point[8]
\point[8],\point[7],\point[5]
\point[9],\point[12],\point[10]
\point[10],\point[9],\point[11]
\point[11],\point[10],\point[12]
\point[12],\point[11],\point[9]
\point[13],\point[13],\point[13]}
\integer{ch=randint(16)}
\text{tridep=\datatri[\ch;1]\datatri[\ch;2]\datatri[\ch;3]}
\if{\choix=1}{\for{j=1 to 13}{\if{\datatri[\ch;1] issamecase \datapt[\j;1]}{\text{trirep1=\datapt[\j;2]}
                                                                            \text{tribad1=\datapt[\j;3]}}
                              \if{\datatri[\ch;2] issamecase \datapt[\j;1]}{\text{trirep2=\datapt[\j;2]}
                                                                            \text{tribad2=\datapt[\j;3]}}
                              \if{\datatri[\ch;3] issamecase \datapt[\j;1]}{\text{trirep3=\datapt[\j;2]}
                                                                            \text{tribad3=\datapt[\j;3]}}
                             }
             }{\for{j=1 to 13}{\if{\datatri[\ch;1] issamecase \datapt[\j;1]}{\text{trirep1=\datapt[\j;3]}
                                                                            \text{tribad1=\datapt[\j;2]}}
                              \if{\datatri[\ch;2] issamecase \datapt[\j;1]}{\text{trirep2=\datapt[\j;3]}
                                                                            \text{tribad2=\datapt[\j;2]}}
                              \if{\datatri[\ch;3] issamecase \datapt[\j;1]}{\text{trirep3=\datapt[\j;3]}
                                                                            \text{tribad3=\datapt[\j;2]}}
                              }
               }
\text{tri1=\trirep1\trirep2\trirep3,\trirep1\trirep3\trirep2,\trirep3\trirep2\trirep1,\trirep2\trirep1\trirep3,\trirep2\trirep3\trirep1,\trirep3\trirep1\trirep2}
\text{tri2=\tribad1\tribad2\tribad3,\tribad1\tribad3\tribad2,\tribad3\tribad2\tribad1,\tribad2\tribad1\tribad3,\tribad2\tribad3\tribad1,\tribad3\tribad1\tribad2}
#endif

#include "lang2.inc"

\statement{\name_statement1.
<p class="wimscenter"><img src="\imagedir/\image" alt="\name_alt"></p>
#if defined TARGET_symcen4
\name_statement2[1] \(\tri[1]\tri[2]\tri[3]\) \name_statement2[2] <span class="nowrap">\(M\) ?</span>
#endif
#if defined TARGET_symax4
\name_statement2[1] \(\tri[1]\tri[2]\tri[3]\) \name_statement2[2] <span class="nowrap">\((\axe[1])\) ?</span>
#endif
#if defined TARGET_rota4
<label for="reply1">\name_statement2[1] \(\tridep\) \name_statement2[2] \(M\) \name_statement2[3] \(90^{\circ}\) \name_statement2[4] \sens&nbsp;?</label> \embed{reply1,5}
#endif
}
#if defined TARGET_symax4 || defined TARGET_symcen4
\answer{\name_answer}{\rep1}{type=auto}
\condition{}{(\choix=1 and \rep1 isitemof \tri2) or (\choix=2 and \rep1 isitemof \tri1)}
#endif

#if defined TARGET_rota4
\answer{}{\rep1}{type=case}
\condition{}{(\choix=1 and \rep1 isitemof \tri1) or (\choix=2 and \rep1 isitemof \tri1)}
\feedback{(\choix=1 and \rep1 isitemof \tri2) or (\choix=2 and \rep1 isitemof \tri2)}{<span class="macss">\name_feedback.</span>}
#endif
#if defined TARGET_symax4 || defined TARGET_symcen4
\solution{\name_solution
\if{\choix=1}{\name_solution1}
              {\name_solution2}
}
#endif
#if defined TARGET_rota4
\solution{\name_solution}
#endif
