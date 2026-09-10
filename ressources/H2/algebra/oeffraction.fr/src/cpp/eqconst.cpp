target=eqconst4 eqconst5 eqconst6 eqconst8 eqconst10

#include "header.inc"

#define EQCONST

#if defined TARGET_eqconst4
# define CNT 4
#endif
#if defined TARGET_eqconst5
# define CNT 5
#endif
#if defined TARGET_eqconst6
# define CNT 6
#endif
#if defined TARGET_eqconst8
# define CNT 8
#endif
#if defined TARGET_eqconst10
# define CNT 10
#endif

#include "lang_titles.inc"

\integer{cnt=CNT}

\text{mulist=1,2,3,4,5,6,8,10}
#include "matrix.inc"
\text{data=randomrow(\all)}
\text{f1=wims(translate internal / to , in \data[1])}
\text{f2=wims(translate internal / to , in \data[2])}
\text{all=wims(translate internal / to , in \all)}
\text{all=wims(lines2items wims(rows2lines \all))}
\text{all=wims(listuniq \all)}
\text{all=wims(listcomplement \f1,\f2 in \all)}
\text{hr=<hr style="height:2px;background-color:black" />}
\text{big1=<span>}
\text{big2=</span>}
\text{fw=wims(nospace 60 px)}
\if{\cnt>4}{
 \text{all=,item(1..\cnt-4,shuffle(\all))}
 \text{all=wims(replace internal , by \big2,\big1 in \big1\all\big2)}
}{
 \text{all=}
}
\text{size=50x40x1}

#include "lang.inc"

\statement{\name_statement
<table class="wimscenter wimsnoborder">
<tr>
<td>\embed{reply 1,\size}</td>
<td rowspan="3">\big1=\big2</td>
<td>\embed{reply 3,\size}</td>
</tr><tr>
<td style="width:\fw">\hr</td>
<td style="width:\fw">\hr</td>
</tr><tr>
<td>\embed{reply 2,\size}</td>
<td>\embed{reply 4,\size}</td>
</tr></table>
}

\answer{\name_numerator 1}{\r1;\big1\f1[1]\big2 \all}{type=dragfill}
\answer{\name_denominator 1}{\r2;\big1\f1[2]\big2}{type=dragfill}
\answer{\name_numerator 2}{\r3;\big1\f2[1]\big2}{type=dragfill}
\answer{\name_denominator 2}{\r4;\big1\f2[2]\big2}{type=dragfill}

\text{rr=wims(replace internal \big1 by in \r1,\r2,\r3,\r4)}
\text{rr=wims(replace internal \big2 by in \rr)}
\integer{text=\rr[1]*\rr[4]-\rr[2]*\rr[3]}

\condition{\(\rr[1]/(\rr[2]) = \rr[3]/(\rr[4]))}
{? notin \rr and \rr[1]*\rr[2]*\rr[3]*\rr[4]>0 and \text issametext 0}

