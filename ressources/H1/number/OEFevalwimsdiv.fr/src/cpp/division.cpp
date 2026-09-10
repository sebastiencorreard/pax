target=oefdivision1 oefdivision2 oefdivision3

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"

\text{size=25x35x1}

#if defined TARGET_oefdivision3 
\integer{d2=1}
\integer{d1=randint(2..5)}
\integer{d=\d2\d1}
#endif
#if defined TARGET_oefdivision1
\integer{d=randint(2..5)}
#endif
#if defined TARGET_oefdivision2
\integer{q1=randint(2..9)}
\integer{d=randint(6..9)}
#endif
\integer{r=randint(1..\d-1)}
#if defined TARGET_oefdivision1
\integer{q1=randint(2..9)}
\integer{q2=randint(7-\d..9)}
#endif
#if defined TARGET_oefdivision2
\integer{q2=randint(2..9)}
#endif
#if defined TARGET_oefdivision3
\integer{q1=randint(2..9)}
\integer{q2=randint(2..10-\d1)}
\if{\d1=2 and \q2=8}{\integer{q1=2}}
\if{\d1=3 and \q2=7}{\integer{q1=randint(2..5)}}
#endif
\text{lquot=\q2,\q1}
\integer{q2plus=\q2+1}
\integer{q1plus=\q1+1}
\text{lquotplus=\q2plus,\q1plus}
\integer{testconf=\confparm2 notsametext jamais ? \d-\confparm2+1}
\text{mul=wims(values \d*x for x=1 to 10)}
\text{divi=1,2,3,4,5,6,7,8,9,10}
\integer{q=\q2\q1}
\text{ordre=3}
\integer{dd=\q*\d+\r}
\text{sgn=-}
\text{ldd=}
\for{i=1 to \ordre}{
  \text{chif=wims(char \i to \i of \dd)}
  \text{ldd=wims(append item \ldd to \chif)}}
\integer{m=\d*\q2}
\text{lprod=\m}
\text{rep=}
\integer{test=10-\m}
\if{\test>0}{
  \integer{l=1}
  \text{\rep=\rep,0}}{\integer{l=2}}
\for{i=1 to 2}{
  \text{chif=wims(char \i to \i of \m)}
  \text{rep=wims(append item \chif to \rep)}}
\text{rep=\rep,\q2,\q1}
\integer{rest=\ldd[3]\ldd[2]-\m}
\text{lrest=\rest}
\integer{test=10-\rest}
\if{\test>0}{
  \integer{l=1}
  \text{\rep=\rep,0}}{\integer{l=2}}
\for{i=1 to \l}{
  \text{chif=wims(char \i to \i of \rest)}
  \if{chif=}{}{\text{rep=wims(append item \chif to \rep)}}}
#if defined TARGET_oefdivision1 || defined TARGET_oefdivision2 || defined TARGET_oefdivision3
\text{rep=\rep,\ldd[1]}
\integer{m=\d*\q1}
#endif
\text{lprod=\lprod,\m}
#if defined TARGET_oefdivision1 || defined TARGET_oefdivision2
\integer{test=10-\m}
\if{\test>0}{
  \integer{l=1}
  \text{rep=\rep,0}}{
    \integer{l=2}}
#endif
#if defined TARGET_oefdivision3
\integer{test=10-\m}
\if{\test>0}{\integer{l=1}
             \text{rep=\rep,0,0}}
            {
              \integer{test=100-\m}
              \if{\test>0}{\integer{l=2}
                           \text{rep=\rep,0}
                           }
                           {\integer{l=3}}
            }
#endif
\for{i=1 to \l}{\text{chif=wims(char \i to \i of \m)}
\text{rep=wims(append item \chif to \rep)}}
#if defined TARGET_oefdivision1 || defined TARGET_oefdivision2
\integer{rest=\rep[6]\rep[7]-\m}
\text{lprodplus=\mul[\q2plus],\mul[\q1plus]}
#endif
#if defined TARGET_oefdivision3
\integer{rest=\rep[5]\rep[6]\rep[7]-\m}
\text{lprodplus=\mul[\q2plus],\mul[\q1plus]}
#endif


\text{lrest=\lrest,\rest}
\integer{test=10-\rest}
\if{\test>0}{
  \integer{l=1}
  \text{\rep=\rep,0}}{\integer{l=2}}
\for{i=1 to \l}{
  \text{chif=wims(char \i to \i of \rest)}
  \if{chif=}{}{\text{rep=wims(append item \chif to \rep)}}}

\integer{ldivid1=\ldd[3]\ldd[2]}
\integer{ldivid2=\lrest[1]\ldd[1]}
\text{ldivid=\ldivid1,\ldivid2}

\statement{
\name_question:
<div class="wims_instruction">\name_instruction</div>

<table class="divposee">
#if defined TARGET_oefdivision1 || defined TARGET_oefdivision2 || defined TARGET_oefdivision3 
<tr>
  <td></td>
  <td>\ldd[3]</td>
  <td>\ldd[2]</td>
  <td>\ldd[1]</td> 
#if defined TARGET_oefdivision1 || defined TARGET_oefdivision2
    <td class="vline-left bord-bas" aria-hidden="true">\d</td>
    <td class="bord-bas "></td>
#endif
#if defined TARGET_oefdivision3
    <td class="vline-left bord-bas" aria-hidden="true">\d2</td>
    <td class="bord-bas" aria-hidden="true">\d1</td> 
#endif
</tr> 
<tr>
  <td class="bord-bas sgn-cell">\sgn</td>
  <td class="bord-bas">\embed{r1,\size}</td>
  <td class="bord-bas">\embed{r2,\size}</td>
  <td></td>
  <td class="vline-left">\embed{r3,\size}</td>
  <td>\embed{r4,\size}</td>
</tr>
<tr>
  <td></td>
  <td>\embed{r5,\size}</td>
  <td>\embed{r6,\size}</td>
  <td class="vline-right">\embed{r7,\size}</td>
  <td></td>
  <td></td>
</tr>
#endif 
#if defined TARGET_oefdivision1 || defined TARGET_oefdivision2
<tr>
  <td class="bord-bas sgn-cell">\sgn</td>
  <td class="bord-bas"></td>
  <td class="bord-bas">\embed{r8,\size}</td>
  <td class="bord-bas vline-right">\embed{r9,\size}</td>
  <td></td>
  <td></td>
</tr>
#endif
#if defined TARGET_oefdivision3
<tr>
   <td class="bord-bas sgn-cell">\sgn</td>
   <td class="bord-bas">\embed{r8,\size}</td>
   <td class="bord-bas">\embed{r9,\size}</td>
   <td class="bord-bas vline-right">\embed{r10,\size}</td>
   <td></td>
   <td></td>
</tr>
#endif
#if defined TARGET_oefdivision1 || defined TARGET_oefdivision2
<tr>
  <td></td>
  <td></td>
  <td>\embed{r10,\size}</td>
  <td class="vline-right">\embed{r11,\size}</td>
  <td></td>
  <td></td>
</tr>
#endif
#if defined TARGET_oefdivision3
<tr>
  <td></td>
  <td></td>
  <td>\embed{r11,\size}</td>
  <td class="vline-right">\embed{r12,\size}</td>
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

#if defined TARGET_oefdivision3
\answer{}{\rep[12];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
#endif
