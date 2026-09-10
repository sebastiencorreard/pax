target=division

#include "author.inc"
#include "lang_title.inc"
#include "lang.inc"
\text{size=25x35x1}
\integer{d2=randint(1..2)}
\integer{d1=randint(3..9)}
\integer{d=\d2\d1}
\integer{r=randint(1..\d-1)}
\if{\d>24}{\integer{q3=randint(1..2)}}{\integer{q3=randint(1..3)}}
\integer{q2=randint(0..9)}
\integer{q1=randint(1..9)}
\integer{q=\q3\q2\q1}
\integer{dd=\q*\d+\r}
\text{sgn=-}

\text{ldd=}
\for{i=1 to 4}
   {\text{chif=wims(char \i to \i of \dd)}
    \text{ldd=wims(append item \ldd to \chif)}}

\integer{m=\d*\q3}

\text{rep=}
\for{i=1 to 2}
{\text{chif=wims(char \i to \i of \m)}
\text{rep=wims(append item \chif to \rep)}}

\text{rep=\rep,\q3,\q2,\q1}

\integer{rest=\ldd[4]\ldd[3]-\m}
\if{\rest<10}
   {\integer{l=1}
     \text{\rep=\rep,0}}{\integer{l=2}}

\for{i=1 to \l}
   {\text{chif=wims(char \i to \i of \rest)}
       \if{chif=}{}{\text{rep=wims(append item \chif to \rep)}}}
\text{rep=\rep,\ldd[2]}

\integer{m=\d*\q2}
\if{\m<10}{\integer{l=1} \text{rep=\rep,0,0}}
   {\if{\m<100}{
     \integer{l=2}
        \text{rep=\rep,0}}{\integer{l=3}}}
\for{i=1 to \l}
{\text{chif=wims(char \i to \i of \m)}
\text{rep=wims(append item \chif to \rep)}}

\integer{rest=\rep[6]\rep[7]\rep[8]-\m}
\if{\rest<10}
   {\integer{l=1}
     \text{\rep=\rep,0}}{\integer{l=2}}

\for{i=1 to \l}
   {\text{chif=wims(char \i to \i of \rest)}
       \if{chif=}{}{\text{rep=wims(append item \chif to \rep)}}}

\text{rep=\rep,\ldd[1]}

\integer{m=\d*\q1}
\if{\m<10}{\integer{l=1} \text{rep=\rep,0,0}}
   {\if{\m<100}{
     \integer{l=2}
        \text{rep=\rep,0}}{\integer{l=3}}}
\for{i=1 to \l}
{\text{chif=wims(char \i to \i of \m)}
\text{rep=wims(append item \chif to \rep)}}

\if{\r<10}
   {\integer{l=1}
     \text{\rep=\rep,0}}{\integer{l=2}}

\for{i=1 to \l}
   {\text{chif=wims(char \i to \i of \r)}
       \if{chif=}{}{\text{rep=wims(append item \chif to \rep)}}}
\statement{
\name_enonce:
<div class="wims_instruction">\name_inst</div>
<table class="wimscenter wimsnoborder">
<tr><td></td>
\for{a=1 to 4}
{<td><span class="larger">\ldd[5-\a]</span></td>}
<td></td>
<td colspan="1" rowspan="12"
style="width:1px; height:200px; background-color:rgb(0, 0, 0);">
</td>
<td></td>
<td><span class="larger">\d2</span></td>
<td><span class="larger">\d1</span></td></tr>
<tr>
\for{a=1 to 6}{<td></td>}
<td colspan="4" rowspan="1"
style="width:100px; height:1px; background-color:rgb(0, 0, 0);">
</td></tr>
<tr><td>\sgn</td><td>\embed{r1,\size}</td><td>\embed{r2,\size}</td>
\for{a=1 to 4}{<td></td>}
<td>\embed{r3,\size}</td>
<td>\embed{r4,\size}</td>
<td>\embed{r5,\size}</td></tr>
<tr><td></td><td colspan="2" rowspan="1"
style="width:60px; height:1px; background-color:rgb(0, 0, 0);"></td></tr>
<tr><td></td>
<td>\embed{r6,\size}</td><td>\embed{r7,\size}</td><td>\embed{r8,\size}</td>
</tr>
<tr><td>\sgn</td><td>\embed{r9,\size}</td><td>\embed{r10,\size}</td><td>\embed{r11,\size}</td></tr>
<tr><td></td><td colspan="3" rowspan="1"
style="width:80px; height:1px; background-color:rgb(0, 0, 0);"></td></tr>
<tr><td></td><td></td><td>\embed{r12,\size}</td><td>\embed{r13,\size}</td>
<td>\embed{r14,\size}</td>
</tr>
<tr><td></td><td>\sgn</td>
<td>\embed{r15,\size}</td><td>\embed{r16,\size}</td><td>\embed{r17,\size}</td>
</tr>
<tr><td></td><td></td><td colspan="3" rowspan="1"
style="width:80px; height:1px; background-color:rgb(0, 0, 0);"></td></tr>
<tr><td></td><td></td>
<td></td><td>\embed{r18,\size}</td><td>\embed{r19,\size}</td>
</tr></table>}

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
