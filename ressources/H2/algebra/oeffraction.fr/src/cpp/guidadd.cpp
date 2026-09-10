target=guidadd

#include "header.inc"
\computeanswer{no}

#include "lang_titles.inc"  

#include "lang.inc"
  
\integer{den1=random(8,9,10,12,14,15,16)}
\integer{den2=random(randint(\den1/2+1..\den1-1),randint(\den1+1..2*\den1-1))}
\integer{num1=randint(2..1.5*\den1)}
\integer{num1=gcd(\num1,\den1)>1?\num1+1}
\integer{num2=randint(2..1.5*\den2)}
\integer{num2=gcd(\num2,\den2)>1?\num2+1}
\text{hr=<hr style="size:2px" />}
\text{new=}
\integer{test1=0}
\text{big1=<span style="font-size:30px;font-type:bold;">}
\text{big2=</span>}

\integer{cnt1=items(\name_list_method1)}
\text{sh1=shuffle(\cnt1)}
\integer{good1=position(1,\sh1)}
\text{method1=item(\sh1,\name_list_method1)}

\integer{cnt2=items(\name_list_method2)}
\text{sh2=shuffle(\cnt2)}
\integer{good2=position(1,\sh2)}
\text{method2=item(\sh2,\name_list_method2)}

\text{nstep=r1}
\nextstep{\nstep}

\statement{\name_statement1
<p class="wimscenter">
\(\num1/(\den1) + \num2/(\den2))
</p>

\if{\step=1}{
 \name_statement2 <ul>
 \for{k=1 to \cnt1}{ <li>\embed{r1,\k} </li>}
 </ul>
 \exit{}
}

\if{\step=2 or \test1<1}{
 \name_statement3
 <p>
 \name_statement4[1] \embed{r2} \name_statement4[2] \(\num1/(\den1)) \name_statement4[3] \embed{r3,3}, \name_statement4[4]
 </p>
 <table class="wimscenter wimsnoborder">
  <tr>
  <td>\num1</td><td rowspan="3">&nbsp;\big1=\big2&nbsp;</td>
  <td>\embed{r6,3}</td></tr>
  <tr><td>\hr</td><td>\hr</td></tr>
  <tr><td>\den1</td>
  <td>\embed{r7,3}</td></tr>
 </table>
 \name_statement4[1] \embed{r4} \name_statement4[2] \(\num2/(\den2)) \name_statement4[3] \embed{r5,3}, \name_statement4[4]
 <table class="wimscenter wimsnoborder">
  <tr>
  <td>\num2</td><td rowspan="3">&nbsp;\big1=\big2&nbsp;</td>
  <td>\embed{r8,3}</td></tr>
  <tr><td>\hr</td><td>\hr</td></tr>
  <tr><td>\den2</td>
  <td>\embed{r9,3}</td></tr>
 </table>
 \exit{}
}
 \name_statement5[1] \(\num1/(\den1) = \new[1]/(\new[2])) \name_and
 \(\num2/(\den2) = \new[3]/(\new[4])), \name_statement5[2]
 <p class="wimscenter">
  \(\new[1]/(\new[2]) + \new[3]/(\new[4])) .
 </p>
 \if{\step=3}{
  \name_statement6 <ul>
  \for{k=1 to \cnt2}{ <li>\embed{r10,\k} </li>}
  </ul>
  \exit{}
 }
 \name_statement7
	       
 <table class="wimscenter wimsnoborder">
 <tr><td>\num1</td>
 <td rowspan=3>&nbsp;&nbsp;\big1+\big2&nbsp;&nbsp;</td>
 <td>\num2</td>
 <td rowspan=3>&nbsp;&nbsp;&nbsp;\big1=\big2&nbsp;&nbsp;&nbsp;</td>
 <td>\new[1]</td>
 <td rowspan=3>&nbsp;&nbsp;\big1+\big2&nbsp;&nbsp;</td>
 <td>\new[3]</td>
 <td rowspan=3>&nbsp;&nbsp;&nbsp;\big1=\big2&nbsp;&nbsp;&nbsp;</td>
 <td>\embed{r11,4}</td></tr>
 <tr><td>\hr</td><td>\hr</td><td>\hrv<td>\hr</td><td>\hr</td></tr>
 <tr><td>\den1</td>
 <td>\den2</td>
 <td>\new[2]</td>
 <td>\new[4]</td>
 <td>\embed{r12,4}</td></tr>
 </table> 

}

\answer{\name_answer1 1}{\good1;\method1}{type=click}

\answer{\name_answer2 1}{3;\name_list_objects}{type=menu}
\answer{\name_answer3 1}{\m1}{type=number}
\answer{\name_answer2 2}{3;\name_list_objects}{type=menu}
\answer{\name_answer3 2}{\m2}{type=number}
\answer{\name_answer4 1}{\nn1}{type=number}
\answer{\name_answer5 1}{\nd1}{type=number}
\answer{\name_answer4 2}{\nn2}{type=number}
\answer{\name_answer5 2}{\nd2}{type=number}

\answer{\name_answer1 2}{\good2;\method2}{type=click}

\answer{\name_answer6}{\nsum}{type=number}
\answer{\name_answer7}{\dsum}{type=number}

\if{\step=2}{
 \text{nstep=r2,r3,r4,r5,r6,r7,r8,r9}
}

\text{test1=\test1<1 and \m1>0 and \m1=floor(\m1) and \m2>0 and \m2=floor(\m2)
    and \nn1=\num1*\m1 and \nd1=\den1*\m1
    and \nn2=\num2*\m2 and \nd2=\den2*\m2
    and \nd1=\nd2?1}
\if{\test1>0}{
 \text{new=\nn1,\nd1,\nn2,\nd2}
}

\condition{\name_condition1}{\test1>0}

\if{\step=3 and \test1>0}{
 \text{nstep=r10}
}

\if{\step=4}{
 \text{nstep=r11,r12}
}

\condition{\name_condition2}{\test1>0 and \nsum=\nn1+\nn2 and \dsum=\nd1}

\feedback{\step=1 and \reply1 notsametext ~\good1}{\name_feedback1}

\feedback{\step=2 and (\reply2 notsametext ~3 or \reply4 notsametext ~3)}{
 \name_feedback2}

\feedback{\step=3 and (\m1=0 or \m2=0)}{\name_feedback3}

\feedback{\step=3 and (\m1<0 or \m2<0)}{\name_feedback4}

\feedback{\step=3 and \m1>0 and \m2>0 and (\floor(\m1)!=\m1 or \floor(\m2)!=\m2)}{\name_feedback5}

\feedback{\step=3 and \nd1=\den1*\m1 and \nd2=\den2*\m2 and \nd1!=\nd2}{
 \name_feedback6}

\feedback{\step=3 and (\nd1!=\den1*\m1 or \nn1!=\num1*\m1 or
	\nd2!=\den2*\m2 or \nn2!=\num2*\m2)}{\name_feedback7}

\feedback{\step=3 and \reply10 notsametext ~\good2}{\name_feedback8}

