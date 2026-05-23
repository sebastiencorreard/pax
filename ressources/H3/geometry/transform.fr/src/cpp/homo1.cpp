target=homo1 homo3

#include "author.inc"
#include "lang_titles.inc"

#include "lang.inc"
  
#if defined TARGET_homo1
\text{image=homo1.png}
\matrix{liste=\name_figure \(F_1\),\name_homot \(-0.5)
\name_figure \(F_{2}\),\name_homot \(-0.3)
\name_figure \(F_{3}\),\name_homot \(0.3)
\name_figure \(F_{4}\),\name_homot \(0.5)}
\text{mix=shuffle(rows(\liste))}
\matrix{question=\liste[\mix[1..4];]}
\text{type1=correspond}
#endif

#if defined TARGET_homo3
\text{image=homo3.png}
\matrix{liste1=B,2
C,3
D,4
E,5}
\matrix{liste2=A,B,2
A,C,3
A,D,4
A,E,5
B,A,1/2
B,C,3/2
B,D,2
B,E,5/2
C,A,1/3
C,B,2/3
C,D,4/3
C,E,5/3
D,A,1/4
D,B,1/2
D,C,3/4
D,E,5/4
E,A,1/5
E,B,2/5
E,C,3/5
E,D,4/5}
\text{choix1=randomrow(\liste1)}
\text{choix2=randomrow(\liste2)}
\integer{num=pari(numerator(\choix2[3]))}
\integer{denum=pari(denominator(\choix2[3]))}
\text{listerep=A,B,C,D,E}
\for{i=1 to 5}{
                \if{\choix2[2]=\listerep[\i]}{\integer{good=\i}}
               }
\text{type1=numexp}
\text{type2=menu}
#endif

#include "lang2.inc"

\statement{
\name_statement1
<div class="wimscenter"><img src="\imagedir/\image" alt="\name_alt"></div>
#if defined TARGET_homo1
<p>\name_statement2</p>
<div class="wimscenter">\embed{reply1,40x100x200}</div>
#endif
#if defined TARGET_homo3
<div class="wims_instruction">\name_instruction</div>
<ol><li><label for="reply1"> \name_quest1[1]  \choix1[1] \name_quest1[2]? </label>\embed{reply1,5}</li>
<li>\name_quest2[1]  \(\choix2[3]\) \name_quest2[2]  \choix2[1]. \name_quest2[3]?\embed{reply2}</li>
</ol>
#endif
}
#if defined TARGET_homo1
\answer{}{\question[;1];\question[;2]}{type=\type1}{option=split}
#endif
#if defined TARGET_homo3
\answer{}{\choix1[2]}{type=\type1}
\answer{}{\good;\listerep}{type=\type2}
#endif
#if defined TARGET_homo3
\solution{\name_solution}
#endif
