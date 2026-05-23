target=symax6 symcen6 rota6

#include "author.inc"
#include "lang_titles.inc"
#include "css.inc"

\text{image=transfo6.png}

#include "lang.inc"
  
#if defined TARGET_symax6
\text{axe=random(CF,AD,BE)}
\integer{nb=randint(10)}
\if{\axe=CF}{\text{listsegdep=AB,BC,CD,DE,EF,FA,OA,OB,OD,OE}
             \text{listsegar=ED,CD,CB,BA,AF,FE,OE,OD,OB,OA}
            }
\if{\axe=AD}{\text{listsegdep=AB,BC,CD,DE,EF,FA,OB,OC,OE,OF}
             \text{listsegar=AF,FE,ED,DC,CB,BA,OF,OE,OC,OB}
            }
\if{\axe=BE}{\text{listsegdep=AB,BC,CD,DE,EF,FA,OA,OC,OD,OF}
            \text{listsegar=CB,BA,AF,FE,ED,DC,OC,OA,OF,OD}
            }
\text{ptdep=wims(text expand \listsegdep[\nb] using 01)}
\text{ptdep=wims(words2items \ptdep)}
\text{segdep=\ptdep[1]\ptdep[2],\ptdep[2]\ptdep[1]}
\text{csegdep=[\ptdep[1]\ptdep[2]],[\ptdep[2]\ptdep[1]]}
\text{ptar=wims(text expand \listsegar[\nb] using 01)}
\text{ptar=wims(words2items \ptar)}
\text{segdar=\ptar[1]\ptar[2],\ptar[2]\ptar[1]}
\text{csegdar=[\ptar[1]\ptar[2]],[\ptar[2]\ptar[1]]}
\text{instruction=\name_instruction[1] \(\csegdep[1]\) \name_instruction[2]}
#endif

#if defined TARGET_symcen6
\text{data=shuffle(ABOF,ABCO,CDEO,EDOF)}
\text{K=\data[1]}
\if{\K=ABOF}{\text{quadrep=DEOC,DCOE,EOCD,EDCO,OCDE,OEDC,CDEO,COED}}
\if{\K=ABCO}{\text{quadrep=DEFO,DOEF,EFOD,EDOF,FODE,FEDO,ODEF,OFED}}
\if{\K=CDEO}{\text{quadrep=FABO,FOBA,ABOF,AFOB,BOFA,BAFO,OFAB,OBAF}}
\if{\K=EDOF}{\text{quadrep=BAOC,BCOA,AOCB,ABCO,OCBA,OABC,CBAO,COAB}}
\text{tdep=wims(text expand \K using 01)}
\text{tdep=wims(words2items \tdep)}
\text{tar=wims(text expand \quadrep[1] using 01)}
\text{tar=wims(words2items \tar)}
\text{instruction=\name_instruction[1] \(O\) \name_instruction[2] }
#endif

#if defined TARGET_rota6
\text{tri=ABO,FAO,EFO,DEO,CDO,BCO}
\text{A=slib(data/random 3,item, \tri)}
\integer{pos1=position(\A[1],\tri)}
\integer{pos2=position(\A[2],\tri)}
\integer{pos3=position(\A[3],\tri)}
\text{ptA=wims(text expand \A using 01)}
\text{ptA=wims(words2items \ptA)}
\integer{j=\pos1+\pos3-\pos2}
\integer{k=pari(lift(Mod(\j,6)))}
\if{\k=0}{\integer{k=6}}
\text{trirep=\tri[\k]}
\text{t=wims(text expand \trirep using 01)}
\text{t=wims(words2items \t)}
\text{trirep=\t[1]\t[2]\t[3],\t[1]\t[3]\t[2],\t[2]\t[1]\t[3],\t[2]\t[3]\t[1],\t[3]\t[1]\t[2],\t[3]\t[2]\t[1]}
\text{instruction=\name_instruction[1] \(\A[1]\) \name_instruction[2] \(\A[2]\) \name_instruction[3] }
#endif

#include "lang2.inc"

\statement{\name_statement
<p class="wimscenter"><img src="\imagedir/\image" alt="hexagone"></p>
\instruction
#if defined TARGET_symax6
 <span class="nowrap">\((\axe)\) ?</span>
<p><label for="reply1">\name_label[1] \((\axe)\), \name_label[2] \([\ptdep[1]\ptdep[2]]\) \name_label[3]</label> [\embed{reply1,5}].</p>
#endif
#if defined TARGET_symcen6
<span class="nowrap">\(\K\) ?</span>
#endif
#if defined TARGET_rota6
<span class="nowrap">\(\A[3]\) ?</span>
#endif
}
#if defined TARGET_symax6
\answer{}{\ptar[1]\ptar[2]|\ptar[2]\ptar[1]}{type=case}
#endif
#if defined TARGET_symcen6
\answer{\name_answer}{\rep}{type=auto}
\condition{\rep isitemof \quadrep}
#endif
#if defined TARGET_rota6
\answer{\name_answer}{\rep}
\condition{\rep isitemof \trirep}
#endif
\solution{\name_solution}
