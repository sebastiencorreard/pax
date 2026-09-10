target=missden missnum missdeninv missnuminv missdensum missnumsum

#include "header.inc"
#define TIT Manjkajoèi
#if #TARGET (missden)
 \title{TIT imenovalec}
 \text{name=imenovalec}
 \text{fill=random(2,4)}
#endif
#if #TARGET (missnum)
 \title{TIT ¹tevec}
 \text{name=¹tevec}
 \text{fill=random(1,3)}
#endif
#if #TARGET (missdeninv)
# define INVERSE 1
 \title{TIT imenovalec (obrat)}
 \text{name=imenovalec}
 \text{fill=random(2,4)}
 \text{op=&times;}
#endif
#if #TARGET (missnuminv)
# define INVERSE 1
 \title{TIT ¹tevec (obrat)}
 \text{name=¹tevec}
 \text{fill=random(1,3)}
 \text{op=&times;}
#endif
#if #TARGET (missdensum)
# define INVERSE 1
 \title{TIT imenovalec (vsota)}
 \text{name=imenovalec}
 \text{fill=random(2,4)}
 \text{op=+}
#endif
#if #TARGET (missnumsum)
# define INVERSE 1
 \title{TIT ¹tevec (vsota)}
 \text{name=¹tevec}
 \text{fill=random(1,3)}
 \text{op=+}
#endif

\text{mulist=1,2,3,4,5,6,8,10}
#include "matrix.inc"
\text{data=randomrow(\all)}
\text{f1=wims(translate internal / to , in \data[1])}
\text{f2=wims(translate internal / to , in \data[2])}
#ifdef INVERSE
\if{\op issametext &times;}{
 \text{f2=\f2[2,1]}
}
\if{\op issametext +}{
 \integer{n1=min(\f1[1],\f1[2])}
 \integer{d1=max(\f1[1],\f1[2])}
 \integer{d2=max(\f2[1],\f2[2])}
 \integer{n2=(\d1-\n1)*\d2/\d1}
 \text{f1=\n1,\d1}
 \text{f2=\n2,\d2}
}
#endif
\text{rep=item(\fill,\f1,\f2)}
\text{hr=<HR noshade size=2>}
\text{fw=60}
\text{big1=<font size=+2>}
\text{big2=</font>}
\text{size=2}

\statement{V prazno polje vstavite ustrezno ¹tevilo,
da bo veljala enakost:

<p><center><table border=0>
<tr>
<td align=center>\big1
\if{\fill=1}{\embed{reply 1,\size}}{\f1[1]}\big2</td>
#ifdef INVERSE
<td align=center rowspan=3>\big1&nbsp;&nbsp;\op&nbsp;&nbsp;\big2</td>
<td align=center>\big1
\if{\fill=3}{\embed{reply 1,\size}}{\f2[1]}\big2</td>
<td align=center rowspan=3>\big1&nbsp;&nbsp;=&nbsp;&nbsp;1\big2</td>
</tr><tr>
<td align=center width=\fw>\hr</td>
<td align=center width=\fw>\hr</td>
</tr><tr>
<td align=center>\big1
\if{\fill=2}{\embed{reply 1,\size}}{\f1[2]}\big2</td>
<td align=center>\big1
\if{\fill=4}{\embed{reply 1,\size}}{\f2[2]}\big2</td>
#else
<td align=center rowspan=3>\big1&nbsp;&nbsp;=&nbsp;&nbsp;\big2</td>
<td align=center>\big1
\if{\fill=3}{\embed{reply 1,\size}}{\f2[1]}\big2</td>
</tr><tr>
<td align=center width=\fw>\hr</td>
<td align=center width=\fw>\hr</td>
</tr><tr>
<td align=center>\big1
\if{\fill=2}{\embed{reply 1,\size}}{\f1[2]}\big2</td>
<td align=center>\big1
\if{\fill=4}{\embed{reply 1,\size}}{\f2[2]}\big2</td>
#endif /* INVERSE */
</tr></table></center>
}

\answer{Iskano ¹tevilo}{\rep}{type=numeric}
