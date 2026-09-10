target=oefsoustract3 oefsoustract4 oefsoustract5
#include "author.inc"

#if defined TARGET_oefsoustract3
#define NUM 3
\integer{v1=1}
\integer{v2=1}
#endif
#if defined TARGET_oefsoustract4
#define NUM 4
\integer{v1=2}
\integer{v2=1}
#endif
#if defined TARGET_oefsoustract5
#define NUM 5
\integer{v1=1}
\integer{v2=2}
#endif
#include "lang_titles.inc"
#include "lang.inc"
\if{\v2=2}{\text{ch1=randint(1..9),randint(0..5),randint(3..9)}}
   {\text{ch1=randint(1..9),randint(0..5),randint(3..9),randint(3..9)}}

\if{\v1=2}{\text{ch2=randint(2..9),randint(3..9),randint(1..\ch1[4]-1)}}
{\text{ch2=randint(2..9),randint(3..9),randint(1..9)}}

\integer{nb1=\ch1[4]\ch1[3]\ch1[2]\ch1[1]}
\integer{nb2=\ch2[3]\ch2[2]\ch2[1]}

\integer{res=(\nb1*10^\v2-\nb2*10^\v1)/10}
\integer{k=4-\v1-\v2}

\text{rep=}
\text{chif=}
\for{i=1 to \k}
{\text{chif=wims(char \i to \i of \res)}
\if{\chif=}{}
          {\text{rep=wims(append item \chif to \rep)}}}

\text{chif=}
\integer{i=\k+1}
\text{chif=wims(char \i to \i of \res)}
\text{rep=wims(append item \chif&#44; to \rep)}

\text{chif=}
\for{i= \k+2 to 4}
{\text{chif=wims(char \i to \i of \res)}
\if{\chif=}{}
          {\text{rep=wims(append item \chif to \rep)}}}

\text{sg= -}
\integer{ltr=max(max(\v1+4,\v2+4),\v1+\v2+3)}
\text{row1=wims(makelist <td></td> for x= 5+\v1 to \ltr)}
\text{row2=wims(makelist <td></td> for x= 5+\v2 to \ltr)}
\text{row3=wims(makelist <td></td> for x= \v1+\v2+4 to \ltr)}
\text{row1=wims(items2words \row1)}
\text{row2=wims(items2words \row2)}
\text{row3=wims(items2words \row3)}
\text{size=25x35x1}
\text{alllist=0,1,2,3,4,5,6,7,8,9,0&#44;,1&#44;,2&#44;,3&#44;,4&#44;,5&#44;,6&#44;,7&#44;,8&#44;,9&#44;}
\statement{\name_enonce:
<div class="wims_instruction">\name_warning</div>
<table class="wimscenter wimsnoborder">
 <tr>
  \for{a=1 to \v1}{<td></td>}
  \for{a=1 to 3-\v1}{<td><span class="larger">\ch1[5-\a]</span></td>}
 \for{a=4-\v1 to 4-\v1}{<td><span class="larger">\(\ch1[5-\a],)</span></td>}
\for{a=5-\v1 to 4}{<td><span class="larger">\ch1[5-\a]</span></td>}
\row1
</tr><tr>
 <td>\sg</td>
\for{a=1 to \v2}{<td></td>}
\for{a=1 to 2-\v2}{<td><span class="larger">\ch2[4-\a]</span></td>}
\for{a=3-\v2 to 3-\v2}{<td><span class="larger">\(\ch2[4-\a],)</span></td>}
\for{a=4-\v2 to 3}{<td><span class="larger">\ch2[4-\a]</span></td>}
 \row2</tr><tr>
  <td colspan="\ltr"><hr></td>
 </tr><tr>
\for{a=1 to \v1+\v2-1}{<td></td>}
\for{b=1 to 4}{
<td>\embed{r\b,\size}</td>}
\row3
</tr>
</table>
}

\answer{}{\rep[1];\alllist}{type=clickfill}
\answer{}{\rep[2];\alllist}{type=clickfill}
\answer{}{\rep[3];\alllist}{type=clickfill}
\answer{}{\rep[4];\alllist}{type=clickfill}
