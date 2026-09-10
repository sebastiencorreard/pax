target=Troisentiers Quatreentiers Quatreentier2 Quatreentier3 sixentiers
\language{fr}
\range{-5..5}
\author{XIAO,Gang}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\precision{1000000}
#include "lang_titles.inc"
#if defined TARGET_Troisentiers
\integer{N=3}
\integer{a=random(-499..499)}
\integer{b=random(-499..499)}
\integer{c=random(-499..499)}
\integer{m1=\a+\b}
\integer{m2=\b+\c}
\integer{m3=\c+\a}
\integer{ra=2*\a}
\integer{rb=2*\b}
\integer{rc=2*\c}
\text{list=\(a\), \(b\), \(c\)}
#endif
#if defined TARGET_Quatreentiers
\integer{N=4}
\integer{a=random(-333..333)}
\integer{b=random(-333..333)}
\integer{c=random(-333..333)}
\integer{d=random(-333..333)}
\integer{m1=\a+\b+\c}
\integer{m2=\b+\c+\d}
\integer{m3=\c+\d+\a}
\integer{m4=\d+\a+\b}
\integer{ra=\a*3}
\integer{rb=\b*3}
\integer{rc=\c*3}
\integer{rd=\d*3}
\text{list= \(a\), \(b\), \(c\), \(d\)}
#endif
#if defined TARGET_Quatreentier2
\integer{N=4}
\integer{m1=random(-499..499)}
\integer{m2=random(-499..499)}
\integer{m3=random(-499..499)}
\integer{m4=\m1+(\m3)-(\m2)}
\text{list= \(a\), \(b\), \(c\), \(d\)}
#endif
#if defined TARGET_Quatreentier3

\integer{N=4}
\integer{a1=random(-99..99)}
\integer{a2=random(-99..99)}
\integer{a3=random(-99..99)}
\integer{a4=random(-99..99)}
\integer{m1=\a1+(\a2)}
\integer{m2=\a2+(\a3)}
\integer{m3=\a3+(\a4)}
\integer{m4=\a4+(\a1)}
\text{list= \(a\), \(b\), \(c\), \(d\)}
#endif
#if defined TARGET_sixentiers

\integer{N=6}
\text{a1=\(a_1\)}
\text{a2=\(a_2\)}
\text{a3=\(a_3\)}
\text{a4=\(a_4\)}
\text{a5=\(a_5\)}
\text{a6=\(a_6\)}
\integer{m1=random(-199..199)}
\integer{m2=random(-199..199)}
\integer{m3=random(-199..199)}
\integer{m4=random(-199..199)}
\integer{m5=random(-199..199)}
\integer{m6=\m1+(\m3)+(\m5)-(\m2)-(\m4)}
\text{list= \(a_1\), \(a_2\), \(a_3\), \(a_4\),\(a_5\), \(a_6\)}
#endif

#include "lang.inc"

#if defined TARGET_Troisentiers
\statement{\name_instruction[1] \list \name_instruction[2]:
<ul>
<li>\name_mean[1] \(a\) \name_mean[2] \(b\) \name_mean[3] \m1.
</li><li>\name_mean[1] \(b\) \name_mean[2] \(c\) \name_mean[3] \m2.
</li><li>\name_mean[1] \(c\) \name_mean[2] \(a\) \name_mean[3] \m3.
</li></ul>
\name_question?}

\answer{\(a\)}{\ra}
\answer{\(b\)}{\rb}
\answer{\(c\)}{\rc}
#endif
#if defined TARGET_Quatreentiers
\statement{\name_instruction[1] \list \name_instruction[2]:
<ul>
<li>\name_mean[1] \(a\), \(b\) \name_mean[2] \(c\) \name_mean[3] \m1.
</li><li>\name_mean[1] de \(b\), \(c\) \name_mean[2] \(d\) \name_mean[3] \m2.
</li><li>\name_mean[1] \(c\), \(d\) \name_mean[2] \(a\) \name_mean[3] \m3.
</li><li>\name_mean[1] \(d\), \(a\) \name_mean[2] \(b\) \name_mean[3] \m4.
</li></ul>
\name_question?}

\answer{\(a\)}{\ra}
\answer{\(b\)}{\rb}
\answer{\(c\)}{\rc}
\answer{\(d\)}{\rd}

#endif

#if defined TARGET_Quatreentier2
\statement{\name_instruction[1] \list \name_instruction[2]
<ul>
<li>\name_mean[1] \(a\) \name_mean[2] \(b\) \name_mean[3] \m1.
</li><li>\name_mean[1] \(b\) \name_mean[2] \(c\) \name_mean[3] \m2.
</li><li>\name_mean[1] \(c\) \name_mean[2] \(d\) \name_mean[3] \m3.
</li></ul>
\name_question \(d\) \name_mean[2] \(a\)&nbsp;?}

\answer{\((d+a)/2\)}{\m4}
\hint{\name_hint?
<div class="wimscenter">
\(\left\lbrace\begin{array}{ccccc}
 0.5a&+&0.5b&=&\m1\\\
0.5a&+&0.5c&=&\m2\\\
0.5c&+&0.5d&=&\m3\\\
0.5c&+&0.5a&=&t\\\
\end{array}\right.\)
</div>
}
#endif
#if defined TARGET_Quatreentier3
\statement{\name_instruction[1] \list \name_instruction[2]
<ul><li>\name_mean[1] \(a\) \name_mean[2] \(b) \name_mean[3] \m1.
</li><li>\name_mean[1] \(b) \name_mean[2] \(c) \name_mean[3] \m2.
</li><li>\name_mean[1] \(c) \name_mean[2] \(d) \name_mean[3] \m3.
</li><li>\name_mean[1] \(d) \name_mean[2] \(a) \name_mean[3] \m4.
</li></ul>
\name_question?}

\answer{a}{\aa}
\answer{b}{\ab}
\answer{c}{\ac}
\answer{d}{\ad}
\condition{(a+b)/2=\m1}{floor(\aa)+floor(\ab)=2*\m1}
\condition{(\b+\c)/2=\m2}{floor(\ab)+floor(\ac)=2*\m2}
\condition{(c+d)/2=\m3}{floor(\ac)+floor(\ad)=2*\m3}
\condition{(d+a)/2=\m4}{floor(\ad)+floor(\aa)=2*\m4}
#endif
#if defined TARGET_sixentiers
\statement{\name_instruction[1] \list \name_instruction[2]:
<ul><li>\name_mean[1] \a1 \name_mean[2] \a2 \name_mean[3] \m1.
</li><li>\name_mean[1] \a2 \name_mean[2] \a3 \name_mean[3] \m2.
</li><li>\name_mean[1] \a3 \name_mean[2] \a4 \name_mean[3] \m3.
</li><li>\name_mean[1] \a4 \name_mean[2] \a5 \name_mean[3] \m4.
</li><li>\name_mean[1] \a5 \name_mean[2] \a6 \name_mean[3] \m5.
</li></ul>
\name_question \(a_1\) \name_mean[2] \(a_6\)?}

\answer{(a_1+a_6)/2}{\m6}
#endif
