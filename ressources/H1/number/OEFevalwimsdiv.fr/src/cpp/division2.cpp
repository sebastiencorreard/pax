target=oefdivision4 oefdivision5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"

\text{size=20x35x1}

#if defined TARGET_oefdivision4
\integer{d2=1}
\integer{d1=randint(2..9)}
\integer{d=\d2\d1}
\integer{r=randint(1..\d-1)}
\integer{test=\d-24}
\if{\test>0}{\integer{q3=randint(1..2)}}{\integer{q3=randint(1..3)}}
\integer{q2=randint(0..9)}
\integer{q1=randint(1..9)}
\integer{q=\q3\q2\q1}
\text{ordre=4}
\text{lquot=\q3,\q2,\q1}
\integer{q1plus=\q1+1}
\integer{q2plus=\q2+1}
\integer{q3plus=\q3+1}
\text{lquotplus=\q3plus,\q2plus,\q1plus}
#endif
#if defined TARGET_oefdivision5
\integer{q3=randint(1..4)}
\integer{q2=randint(0..9)}
\integer{q1=randint(1..9)}
\integer{q=\q3\q2\q1}
\integer{d=floor(9999/\q)-1}
\integer{d2=floor(\d/10)}
\integer{d1=\d-\d2*10}
\integer{r=randint(1..\d-1)}
\text{ordre=4}
\text{lquot=\q3,\q2,\q1}
\integer{q1plus=\q1+1}
\integer{q2plus=\q2+1}
\integer{q3plus=\q3+1}
\text{lquotplus=\q3plus,\q2plus,\q1plus}
#endif
\integer{test=\confparm2 notsametext jamais ? \d-\confparm2+1}
\text{mul=wims(values \d*x for x=1 to 10)}
\text{divi=1,2,3,4,5,6,7,8,9,10}
\integer{dd=\q*\d+\r}
\text{sgn=-}
\text{ldd=}
\for{i=1 to \ordre}{
  \text{chif=wims(char \i to \i of \dd)}
  \text{ldd=wims(append item \ldd to \chif)}}
\integer{m=\d*\q3}
\text{lprod=\m}
\text{rep=}
\for{i=1 to 2}{
  \text{chif=wims(char \i to \i of \m)}
  \text{rep=wims(append item \chif to \rep)}}
\text{rep=\rep,\q3,\q2,\q1}
\integer{rest=\ldd[4]\ldd[3]-\m}
\text{lrest=\rest}
\integer{test=10-\rest}
\if{\test>0}{
  \integer{l=1}
  \text{\rep=\rep,0}}{\integer{l=2}}
\for{i=1 to \l}{
  \text{chif=wims(char \i to \i of \rest)}
  \if{chif=}{}{\text{rep=wims(append item \chif to \rep)}}}
\text{rep=\rep,\ldd[2]}
\integer{m=\d*\q2}
\integer{test=10-\m}
\if{\test>0}{\integer{l=1} \text{rep=\rep,0,0}
            }
            {\integer{test=100-\m}
             \if{\test>0}{\integer{l=2}
                          \text{rep=\rep,0}
                         }
                         {\integer{l=3}}
           }
\text{lprod=\lprod,\m}
\for{i=1 to \l}{\text{chif=wims(char \i to \i of \m)}
\text{rep=wims(append item \chif to \rep)}}
\integer{rest=\rep[6]\rep[7]\rep[8]-\m}
\text{lrest=\lrest,\rest}
\integer{test=10-\rest}
\if{\test>0}{
  \integer{l=1}
  \text{\rep=\rep,0}}{\integer{l=2}}
\for{i=1 to \l}{
  \text{chif=wims(char \i to \i of \rest)}
  \if{chif=}{}{\text{rep=wims(append item \chif to \rep)}}}
\text{rep=\rep,\ldd[1]}
\integer{m=\d*\q1}
\text{lprod=\lprod,\m}
\integer{test=10-\m}
\if{\test>0}{\integer{l=1}
             \text{rep=\rep,0,0}
             }{\integer{test=100-\m}
             \if{\test>0}{\integer{l=2}
                          \text{rep=\rep,0}
                         }{\integer{l=3}}
              }
\for{i=1 to \l}{\text{chif=wims(char \i to \i of \m)}
\text{rep=wims(append item \chif to \rep)}}
\integer{test=10-\r}
\if{\test>0}{\integer{l=1}
             \text{\rep=\rep,0}
            }{\integer{l=2}}
\for{i=1 to \l}{
  \text{chif=wims(char \i to \i of \r)}
  \if{chif=}{}{\text{rep=wims(append item \chif to \rep)}}}
\integer{rest=\rep[12]\rep[13]\rep[14]-\m}
\text{lrest=\lrest,\rest}
\text{lprodplus=\mul[\q3plus],\mul[\q2plus],\mul[\q1plus]}
\integer{ldivid1=\ldd[4]\ldd[3]}
\integer{ldivid2=\lrest[1]\ldd[2]}
\integer{ldivid3=\lrest[2]\ldd[1]}
\text{ldivid=\ldivid1,\ldivid2,\ldivid3}
\statement{
\name_question:
<div class="wims_instruction">\name_instruction</div>

<table class="divposee">
#if defined TARGET_oefdivision4
<tr>
  <td></td>
  <td>\ldd[4]</td>
  <td>\ldd[3]</td>
  <td>\ldd[2]</td>
  <td>\ldd[1]</td>
  <td class="vline-left bord-bas" aria-hidden="true">\d2</td>
  <td class="bord-bas" aria-hidden="true">\d1</td>
  <td class="bord-bas"></td> 
</tr>
<tr>
  <td class="bord-bas sgn-cell">\sgn</td>
  <td class="bord-bas">\embed{r1,\size}</td>
  <td class="bord-bas">\embed{r2,\size}</td>
  <td></td>
  <td></td>
  <td class="vline-left">\embed{r3,\size}</td>
  <td>\embed{r4,\size}</td>
  <td>\embed{r5,\size}</td>
</tr>
<tr>
  <td></td>
  <td>\embed{r6,\size}</td>
  <td>\embed{r7,\size}</td>
  <td>\embed{r8,\size}</td>
  <td class="vline-right"></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td class="bord-bas sgn-cell">\sgn</td>
  <td class="bord-bas">\embed{r9,\size}</td>
  <td class="bord-bas">\embed{r10,\size}</td>
  <td class="bord-bas">\embed{r11,\size}</td>
  <td class="vline-right"></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td></td>
  <td></td>
  <td>\embed{r12,\size}</td>
  <td>\embed{r13,\size}</td>
  <td class="vline-right">\embed{r14,\size}</td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td></td>
  <td class="bord-bas sgn-cell">\sgn</td>
  <td class="bord-bas">\embed{r15,\size}</td>
  <td class="bord-bas">\embed{r16,\size}</td>
  <td class="bord-bas vline-right">\embed{r17,\size}</td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td></td>
  <td></td>
  <td></td>
  <td>\embed{r18,\size}</td>
  <td class="vline-right">\embed{r19,\size}</td>
  <td></td>
  <td></td>
  <td></td>
</tr>
#endif
#if defined TARGET_oefdivision5
<tr>
  <td></td>
  <td>\ldd[4]</td>
  <td>\ldd[3]</td>
  <td>\ldd[2]</td>
  <td>\ldd[1]</td>
  <td class="vline-left bord-bas">\d2</td>
  <td class="bord-bas">\d1</td>
  <td class="bord-bas"></td>
</tr>
<tr>
  <td class="bord-bas sgn-cell">\sgn</td>
  <td class="bord-bas">\embed{r1,\size}</td>
  <td class="bord-bas">\embed{r2,\size}</td>
  <td></td>
  <td></td>
  <td class="vline-left top">\embed{r3,\size}</td>
  <td>\embed{r4,\size}</td>
  <td>\embed{r5,\size}</td>
</tr>
<tr>
  <td></td>
  <td>\embed{r6,\size}</td>
  <td>\embed{r7,\size}</td>
  <td>\embed{r8,\size}</td>
  <td class="vline-right"></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td class="bord-bas sgn-cell">\sgn</td>
  <td class="bord-bas">\embed{r9,\size}</td>
  <td class="bord-bas">\embed{r10,\size}</td>
  <td class="bord-bas">\embed{r11,\size}</td>
  <td class="vline-right"></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td></td>
  <td></td>
  <td>\embed{r12,\size}</td>
  <td>\embed{r13,\size}</td>
  <td class="vline-right">\embed{r14,\size}</td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td></td>
  <td class="bord-bas">\sgn</td>
  <td class="bord-bas">\embed{r15,\size}</td>
  <td class="bord-bas">\embed{r16,\size}</td>
  <td class="bord-bas vline-right">\embed{r17,\size}</td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td></td>
  <td></td>
  <td></td>
  <td>\embed{r18,\size}</td>
  <td class="vline-right">\embed{r19,\size}</td>
  <td></td>
  <td></td>
  <td></td>
</tr>
#endif
</table>
}

\answer{}{\rep[1];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[2];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[3];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[4];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[5];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[6];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[7];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[8];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[9];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[10];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[11];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[12];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[13];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[14];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[15];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[16];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[17];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[18];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[19];0,1,2,3,4,5,6,7,8,9}{type=clickfill}

