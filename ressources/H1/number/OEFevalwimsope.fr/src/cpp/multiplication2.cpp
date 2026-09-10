target=oefmultiplication2
#include "author.inc"
#define NUM 2
#include "lang_titles.inc"
#include "lang.inc"

\text{ch1=shuffle(9)}
\text{ch1=item(3..5,\ch1)}
\integer{ch22=randint(3..9)}
\integer{ch21=randint(2..9)}
\text{ch2=\ch22,\ch21}
\integer{nb1=\ch1[3]\ch1[2]\ch1[1]}
\integer{nbi1=\nb1*\ch21}
\integer{nbi2=\nb1*\ch22}
\integer{res=\nbi1+\nbi2*10}

\text{rep=}
\text{chif=}
\for{i=1 to 4}
{\text{chif=wims(char \i to \i of \nbi1)}
\if{\chif=}{}
          {\text{rep=wims(append item \chif to \rep)}}}
\integer{l1=items(\rep)}
\if{\l1=3}{\text{rep=0,\rep}}

\if{\nbi2<1000}{\text{rep=wims(append item 0 to \rep)}}
\text{chif=}
\for{i=1 to 4}{\text{chif=wims(char \i to \i of \nbi2)}
\if{\chif=}{}{\text{rep=wims(append item \chif to \rep)}}}

\if{\res<10000}{\text{rep=wims(append item 0 to \rep)}}
\text{chif=}
\for{i=1 to 5}{\text{chif=wims(char \i to \i of \res)}
  \if{\chif=}{}{\text{rep=wims(append item \chif to \rep)}}}


\text{sg= X}
\integer{ltr=6}
\text{size=25x35x1}

\statement{\name_enonce:
<table class="wimscenter wimsnoborder">
 <tr>
  <td></td><td></td>
  \for{a=1 to 4}{<td><span class="larger">\ch1[5-\a]</span></td>}
 </tr><tr>
 <td>\sg</td><td></td><td></td><td></td>
  \for{a=1 to 2}{<td><span class="larger">\ch2[\a]</span></td>}
 </tr><tr>
  <td colspan="\ltr"><hr></td>
 </tr><tr>
<td></td><td></td>
\for{b=1 to 4}{
<td>\embed{r\b,\size}</td>}
</tr><tr>
<td></td>
\for{b=5 to 8}{
<td>\embed{r\b,\size}</td>}<td></td>
</tr><tr>
<td colspan="\ltr"><hr></td></tr>
<tr>
<td></td>
 \for{b=9 to 13}{
<td> \embed{r\b,\size}</td>}
 </tr>
</table>
<div class="wims_instruction">\name_warning</div>
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
