target=multipli

#include "author.inc"
#include "lang_title.inc"
#include "lang.inc"
\text{ch1=shuffle(9)}
\text{ch1=item(2..5,\ch1)}
\integer{ch23=randint(1..4)}
\integer{ch22=randint(3..8)}
\integer{ch21=randint(4..9)}
\text{ch2=\ch23,\ch22,\ch21}
\integer{nb1=\ch1[4]\ch1[3]\ch1[2]\ch1[1]}
\integer{nbi1=\nb1*\ch21}
\integer{nbi2=\nb1*\ch22}
\integer{nbi3=\nb1*\ch23}
\integer{res=\nbi1+\nbi2*10+\nbi3*100}
\text{rep=}
\text{chif=}
\for{i=1 to 5}
{\text{chif=wims(char \i to \i of \nbi1)}
\if{\chif=}{}
          {\text{rep=wims(append item \chif to \rep)}}}
\integer{l1=items(\rep)}
\text{chif=}
\for{i=1 to 5}
{\text{chif=wims(char \i to \i of \nbi2)}
\if{\chif=}{}
          {\text{rep=wims(append item \chif to \rep)}}}
\integer{l2=items(\rep)}
\text{chif=}
\for{i=1 to 5}
{\text{chif=wims(char \i to \i of \nbi3)}
\if{\chif=}{}
          {\text{rep=wims(append item \chif to \rep)}}}
\integer{l3=items(\rep)}
\text{chif=}
\for{i=1 to 7}
{\text{chif=wims(char \i to \i of \res)}
\if{\chif=}{}
          {\text{rep=wims(append item \chif to \rep)}}}
\integer{lr=items(\rep)}

\for{i=\lr+1 to 22}
          {\text{rep=wims(append item 0 to \rep)}}

\text{sg= X}
\integer{ltr=15}
\text{size=25x35x1}
\integer{c=\l2-\l1}
\integer{d=\l3-\l2}
\integer{e=\lr-\l3}
\statement{
\name_enonce:
<div class="wims_instruction">\name_inst</div>
<table class="wimscenter wimsnoborder">
 <tr>
  <td></td><td></td><td></td><td></td>
  \for{a=1 to 4}{<td><span class="larger">\ch1[5-\a]</span></td>}
 </tr>
 <tr>
 <td>\sg</td><td></td><td></td><td></td><td></td>
  \for{a=1 to 3}{<td><span class="larger">\ch2[\a]</span></td>}
 </tr>
 <tr>
  <td colspan="\ltr"><hr></td>
 </tr>
 <tr>
<td></td><td></td><td></td>
\if{\l1=4}{<td></td>}
\for{b=1 to \l1}{
<td> \embed{r\b,\size}</td>}
</tr>
<tr>
<td></td><td></td>
\if{\c=4}{<td></td>}
\for{b=\l1+1 to \l2}{
<td> \embed{r\b,\size}</td>}
\if{\lr<22}{<td> \embed{r22,\size}</td>}
</tr>
<tr>
<td></td>
\if{\d=4}{<td></td>}
\for{b=\l2+1 to \l3}{
<td> \embed{r\b,\size}</td>}
\if{\lr<21}{<td> \embed{r21,\size}</td>}
\if{\lr<20}{<td> \embed{r20,\size}</td>}
</tr>
<tr><td colspan="\ltr"><hr></td></tr>
<tr>
<td></td>
\if{\lr<19}{<td> \embed{r19,\size}</td>}
{\if{\e=6}{<td></td>}}
 \for{b=\l3+1 to \lr}{
<td>\embed{r\b,\size}</td>}
 </tr>
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
\answer{}{\rep[19];,0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[20];,0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[21];,0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[22];,0,1,2,3,4,5,6,7,8,9}{type=clickfill}
