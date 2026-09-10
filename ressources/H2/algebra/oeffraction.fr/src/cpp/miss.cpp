target=missden missnum missdeninv missnuminv missdensum missnumsum

#include "header.inc"

#define MISSING

#include "lang_titles.inc"

#include "lang.inc"

#if defined TARGET_missden
 \text{name_missing=\name_denominator}
 \text{fill=random(2,4)}
#endif
#if defined TARGET_missnum
 \text{name_missing=\name_numerator}
 \text{fill=random(1,3)}
#endif
#if defined TARGET_missdeninv
# define INVERSE 1
 \text{name_missing=\name_denominator}
 \text{fill=random(2,4)}
 \text{op=&times;}
#endif
#if defined TARGET_missnuminv
# define INVERSE 1
 \text{name_missing=\name_numerator}
 \text{fill=random(1,3)}
 \text{op=&times;}
#endif
#if defined TARGET_missdensum
# define INVERSE 1
 \text{name_missing=\name_denominator}
 \text{fill=random(2,4)}
 \text{op=+}
#endif
#if defined TARGET_missnumsum
# define INVERSE 1
 \text{name_missing=\name_numerator}
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
\text{hr=<hr style="height:2px;background-color:black" />}
\text{fw=wims(nospace 60 px)}
\text{big1=<span class="bold" style="font-size:30px;">}
\text{big2=</span>}
\text{size=2}

\statement{\name_statement[1] \name_missing \name_statement[2]

<table class="wimsnoborder wimscenter">
<tr>
<td>\big1
\if{\fill=1}{\embed{reply 1,\size}}{\f1[1]}\big2</td>
#ifdef INVERSE
<td rowspan="3">\big1\op\big2</td>
<td>\big1
\if{\fill=3}{\embed{reply 1,\size}}{\f2[1]}\big2</td>
<td rowspan="3">\big1 = 1\big2</td>
</tr><tr>
<td style="width:\fw">\hr</td>
<td style="width:\fw">\hr</td>
</tr><tr>
<td>\big1
\if{\fill=2}{\embed{reply 1,\size}}{\f1[2]}\big2</td>
<td>\big1
\if{\fill=4}{\embed{reply 1,\size}}{\f2[2]}\big2</td>
#else
<td rowspan="3">\big1 = \big2</td>
<td>\big1
\if{\fill=3}{\embed{reply 1,\size}}{\f2[1]}\big2</td>
</tr><tr>
<td style="width:\fw">\hr</td>
<td style="width:\fw">\hr</td>
</tr><tr>
<td>\big1
\if{\fill=2}{\embed{reply 1,\size}}{\f1[2]}\big2</td>
<td>\big1
\if{\fill=4}{\embed{reply 1,\size}}{\f2[2]}\big2</td>
#endif /* INVERSE */
</tr></table>
}

\answer{\name_the \name_missing}{\rep}{type=numeric}

