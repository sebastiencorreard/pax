target=oeffairetabl1
#include "author.inc"

#if defined TARGET_oeffairetabl1
# define NUM 1
#endif
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\text{n=4}
\text{ss=100}
\for{i=1 to \n-1}{
\text{u=randint(8..20)}
\if{\i=1}{\text{s=\u}}{\text{s=\s,\u}}
\real{ss=\ss-\u}}
\text{s=\s,\ss}
\text{shu=shuffle(4)}
\text{listecouleur=red,skyblue,yellow,lightgreen}
\text{listefr=\name_header[1],\name_header[2],\name_header[3], \name_header[4]}
 \text{listealpha = A,B,C,D}
\text{pos=randint(1..\n)}
\text{couleur=item(item(\pos,\shu), \listefr)}
\text{alph=item(item(\pos,\shu), \listealpha)}
\integer{ind=randint(10..30)*100}
\real{rep= round(item(\pos,\s)/100*\ind)}
\text{dessin= ellipse 0,0,2,2,black
segment 0,0,1,0,black}
\text{anglet=0}
\text{pos=randint(1..\n)}
\if{\pos=1}{\text{donnee=\s[2],\s[3],\s[4]}}
\if{\pos=2}{\text{donnee=\s[1],\s[3],\s[4]}}
\if{\pos=3}{\text{donnee=\s[1],\s[2],\s[4]}}
\if{\pos=4}{\text{donnee=\s[1],\s[2],\s[3]}}
\for{i=1 to \n}{
\real{angle=item(\i,\s)*2*pi/100}
\real{point=\anglet+\angle/2}
\text{couleur=item(item(\i,\shu),\listecouleur)}
\text{alph=item(item(\i,\shu), \listealpha)}
\real{anglet=\anglet+\angle}
\text{dessin=\dessin
segment 0,0,cos(\anglet),sin(\anglet),black
fill cos(\point)/2,sin(\point)/2, \couleur
text black, 1.2*cos(\point),1.2*sin(\point),medium, \alph}
\if{\i = \pos}{}{\text{dessin=\dessin
text black, 2*cos(\point)/3,2*sin(\point)/3, medium, item(\i,\s)%
}}}

\text{couleur=item(item(\pos,\shu), \listefr)}
\text{alph=item(item(\pos,\shu), \listealpha)}

\real{rep1=item(position(1,\shu),\s)}
\real{rep2=item(position(2,\shu),\s)}
\real{rep3=item(position(3,\shu),\s)}
\real{rep4=item(position(4,\shu),\s)}
\statement{ \name_instruction:
<div class="wimscenter">
 \draw{200,200}
{xrange -1.5,1.5
yrange -1.5,1.5
\dessin}
</div>
\name_question:
<table class="wimscenter wimsborder table-scroll"><tr><th></th>
<th><label for="reply1">\name_header[1] (A)</label></th>
<th><label for="reply2">\name_header[2] (B)</label></th>
<th><label for="reply3">\name_header[3] (C)</label></th>
<th><label for="reply4">\name_header[4] (D)</label>
</th><th>\name_header[5]</th></tr>
<tr><th>\name_header[6]</th>
<td>\embed{reply 1, 5}</td>
<td>\embed{reply 2, 5}</td>
<td>\embed{reply 3, 5}</td>
<td>\embed{reply 4, 5}</td>
<td>100</td>
</tr></table>
}

\answer{\name_header[1]}{\rep1}{type=numeric}
\answer{\name_header[2]}{\rep2}{type=numeric}
\answer{\name_header[3]}{\rep3}{type=numeric}
\answer{\name_header[4]}{\rep4}{type=numeric}

#include "solution.inc"
\solution{\sol&nbsp;:\(100-(\donnee[1]+\donnee[2]+\donnee[3])=\s[\pos]\).}
