\text{aim=wims(replace internal XXXX by \lim1 in \name_aim)}
\text{aim=wims(replace internal YYYY by \lim2 in \aim)}
\text{prelim=wims(replace internal NNNN by 4 in \name_prelim)}

\steps{reply1,reply2
reply3,reply4
reply5,reply6
reply7,reply8
}

\statement{<i>\prelim</i>
<div class="wims_question">
<p>\name_enonce[1] \(f : x \mapsto \f\) \name_enonce[2] \ensdef.
</p><p>\aim</p>
</div>
\if{\step=1}{
1. \name_question1[1] \( x \mapsto \u\) \name_question1[2] \ensdef.
  \name_question1[3] \lim1 \name_and2 \lim2.
<div class="wimscenter"><label for="reply1">\(\displaystyle\lim_{\tolim1} \u =\)</label>
\embed{reply1,5} <label for="reply2">\name_and
\(\displaystyle \lim_{\tolim2} \u =\) </label>\embed{reply2,5}</div>
}
\if{\step>1}{
1. \if{\step=2}
    {\if{\sc_reply1=1 and \sc_reply2=1 }
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad"> \name_youranswer[2;].</span>}}
<span class="oef_indgood">\name_youranswer[3;] \lim1 \name_and2 \lim2 \name_are</span>:
<p class="wimscenter">\(\displaystyle \lim_{\tolim1} \u = \sol1\) \name_and \(\displaystyle \lim_{\tolim2} \u = \sol2\)</p>
}
\if{\step=2}{
2. \name_question2 \(\v\) \name_at \lim1 \name_and2 \lim2 :
<div class="wimscenter">
  <label for="reply3">\(\displaystyle \lim_{\tolim1} \v\) =</label> \embed{reply3,8} \name_and <label for="reply4">\(\displaystyle \lim_{\tolim2} \v\) =</label> \embed{reply4,8}</div>
}
\if{\step>2}
{2. \if{\step=3}
    {\if{\sc_reply3=1 and \sc_reply4=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad"> \name_youranswer[2;].</span>}
}
<span class="oef_indgood">\name_youranswer4 \lim1 \name_and2 \lim2 \name_are :</span>
<p class="wimscenter">\(\displaystyle \lim_{\tolim1} \v = \sol3\) \name_and
\(\displaystyle \lim_{\tolim2} \v = \sol4\)</p>
}
\if{\step=3}{
3.<label for="reply5"> \name_deduc \lim1 \name_by</label> \embed{reply5}:
<div class="wimscenter">
<label for="reply6">\(\displaystyle \lim_{\tolim1} \f =\)</label> \embed{reply6,5}</div>
}
\if{\step>3}{
  3. \if{\step=4}
    {\if{\sc_reply5=1 and \sc_reply6=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad"> \name_youranswer[2;].</span>}
}
<span class="oef_indgood">\name_deduc[1], \name_andby \sol5, \name_deduc2</span>
<p class="wimscenter">\(\displaystyle \lim_{\tolim1} \f = \sol6\)</p>
}
\if{\step=4}{
4. <label for="reply7">\name_deduc \lim2 \name_by</label> \embed{reply7} :
<div class="wimscenter"><label for="reply8">\(\displaystyle \lim_{\tolim2} \f=\)</label> \embed{reply8,5}</div>
}
<div class="wims_instruction">\name_inst</div>
}
\answer{\name_answer \(u\) \name_at \lim1}{\rep1}{type=raw}{option=nospace,nonstop}
\answer{\name_answer \(u\) \name_at \lim2}{\rep2}{type=raw}{option=nospace,nonstop}
\answer{\name_answer \fct(\tk x) \name_at \lim1}{\rep3}{type=raw}{option=nospace,nonstop}
\answer{\name_answer \fct(\tk x) \name_at \lim2}{\rep4}{type=raw}{option=nospace,nonstop}

\answer{\name_answer \(f\) \name_at \lim1 \name_answer2}{\rep5;\name_choice}{type=select}{option=nonstop}
\answer{\name_answer \(f\) \name_at \lim1 }{\rep6}{type=raw}{option=nospace,nonstop}
\answer{\name_answer \(f\) \name_at \lim1 \name_answer2}{\rep7;\name_choice}{type=select}{option=nonstop}
\answer{\name_answer \(f\) \name_at \lim2 }{\rep8}{type=raw}{option=nospace}
