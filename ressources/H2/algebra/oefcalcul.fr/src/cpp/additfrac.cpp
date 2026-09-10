target=additfrac0 additfrac

#if defined TARGET_additfrac0
# define NUM (1)
#endif
#if defined TARGET_additfrac
# define NUM (2)
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\text{si=random(+,-)}
\text{additio=\si=+? \name_oper[1]: \name_oper[2]}
#if defined TARGET_additfrac0
\integer{a=randint(3,5,9,11)}
\integer{b=randint(2,4,7,8)}
\integer{c=randint(2,4,8,14,7)}
\integer{d=randint(5,11,3,9)}
#endif
#if defined TARGET_additfrac
\integer{a=randint(3,7,5,15,9,11)}
\integer{b=randint(2,4,7,8,13)}
\integer{c=randint(2,4,8,14,7)}
\integer{d=randint(5,11,3,9,25,15)}
#endif

\integer{ad=\a*(\d)}
\integer{bd=\b*(\d)}
\integer{bc=\b*(\c)}
\integer{sol= \ad \si\bc}
\text{num=pari(numerator(\sol/\bd))}
\text{den=pari(denominator(\sol/\bd))}

\steps{reply1,reply2,reply3,reply4
reply5,reply6,reply7,reply8
reply9
reply10, reply11}
\statement{<p>\name_effect \additio:
\(\frac{\a}{\b}\si \frac{\c}{\d}\).
</p>

\if{\step<=1}{<p>\name_statement[1;]:</p>
<table class="wimscenter"><tr><td></td><td>\a \times \embed{reply 1,3}</td><td></td>
<td>\c \times \embed{reply 3,3}</td>
</tr><tr><td>\(\frac{\a}{\b}\si \frac{\c}{\d}\)= </td>
<td><hr></td><td>&nbsp;&nbsp;\si &nbsp;&nbsp;</td><td><hr></td></tr>
<tr><td></td><td>\b \times \embed{reply 2,3}</td><td></td>
<td>\d \times \embed{reply 4,3}</td></tr>
</table>}

\if{\step=2}{\name_statement[2;]:
<table class="wimscenter"> <tr><td></td><td>\embed{reply 5,3}</td><td></td>
<td> \embed{reply 7,3}</td>
</tr>
<tr><td>\(\frac{\a}{\b}\si \frac{\c}{\d}= \frac{\a\times \d}{\b\times \d}\si
\frac{\c\times \b}{\d\times \b}=\) </td>
<td><hr></td><td> &nbsp;&nbsp;\si &nbsp;&nbsp; </td><td><hr></td></tr>
<tr><td></td><td> \embed{reply 6,3}</td><td></td>
<td>\embed{reply 8,3}</td></tr>
</table>
}

\if{\step=3}{\name_statement[3;]
<table class="wimscenter"> <tr><td></td><td> \embed{reply 9,3}</td>
</tr>
<tr><td>\(\frac{\a}{\b}\si \frac{\c}{\d}= \frac{\a\times \d}{\b\times \d}\si
\frac{\c\times \b}{\d\times \b}=\frac{\ad}{\bd}\si
\frac{\bc}{\bd}=\) </td><td><hr></td>
</tr>
<tr><td></td><td>\bd</td></tr>
</table>}
\if{\step>=4}{\name_statement[4;]:
<table class="wimscenter"><tr><td> </td><td>
\embed{reply 10,3}</td></tr>
<tr><td>\(\frac{\a}{\b}\si \frac{\c}{\d}= \frac{\sol}{\bd}=\)</td><td><hr>
</td>
</tr>
<tr><td></td><td> \embed{reply 11,3}</td></tr>
</table>
}}
\answer{}{\d}{type=numeric}
\answer{}{\d}{type=numeric}
\answer{}{\b}{type=numeric}
\answer{}{\b}{type=numeric}
\answer{}{\ad}{type=numeric}

\answer{}{\bd}{type=numeric}
\answer{}{\bc}{type=numeric}
\answer{}{\bd}{type=numeric}
\answer{}{\sol}{type=numeric}
\answer{}{\num}{type=numeric}
\answer{}{\den}{type=numeric}
\feedback{1=1}{\name_feed,
<div class="wimscenter">\(\frac{\a}{\b}\si \frac{\c}{\d}=\frac{\num}{\den}.\)</div>}
