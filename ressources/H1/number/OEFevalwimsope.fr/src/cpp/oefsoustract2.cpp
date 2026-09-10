target=oefsoustract2
#include "author.inc"
#define NUM 2
#include "lang_titles.inc"
#include "lang.inc"

\text{ch1=shuffle(9)}
\text{ch1=item(3..6,\ch1)}
\text{ch2=shuffle(9)}
\text{ch2=item(3..5,\ch2)}

\integer{nb1=\ch1[4]\ch1[3]\ch1[2]\ch1[1]}
\integer{nb2=\ch2[3]\ch2[2]\ch2[1]}

\integer{res=\nb1-\nb2}

\text{rep=}
\text{chif=}
\for{i=1 to 5}{
  \text{chif=wims(char \i to \i of \res)}
  \if{\chif=}{}{\text{rep=wims(append item \chif to \rep)}}
}

\text{sg= -}
\integer{ltr=6}
\text{size=25x35x1}

\statement{\name_enonce:
<div class="wims_instruction">\name_warning</div>
<table class="wimscenter wimsnoborder">
 <tr>
  <td></td>
  \for{a=1 to 4}{<td><span class="larger">\ch1[5-\a]</span></td>}
  <td></td>
 </tr><tr>
 <td>\sg</td><td></td>
\for{a=1 to 3}{<td><span class="larger">\ch2[4-\a]</span></td>}
  <td></td>
 </tr><tr>
  <td colspan="\ltr"><hr></td>
 </tr><tr>
 <td></td>
\for{b=1 to 5}{
  <td>\embed{r\b,\size}</td>}
</tr>
</table>
}

\answer{}{\rep[1];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[2];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[3];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\rep[4];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
