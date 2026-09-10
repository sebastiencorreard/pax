\text{prelim=wims(replace internal NNNN by 5 in \name_prelim)}
\steps{reply1,reply2
reply3
reply4
reply5
reply6}
\statement{
<i>\prelim</i>
<div class="wims_question">
<p>
\name_enonce \ensdef \name_by \(f(x) = \tf\).
</p><p>
\name_aim \(\texlim\) \natlim
</p></div>
\if{\step=1}{
1. \name_question1[1] \(\ff\) \name_question1[2]:
<div class="wimscenter"><label for="reply1">\(u(x)\) =</label> \embed{reply1,5}
  <label for="reply2">\name_and \(k\) = </label>\embed{reply2,5}</div>
}
\if{\step>1}{
<p>1. \if{\step=2}
    {\if{\sc_reply1=1 and \sc_reply2=1 }
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad"> \name_youranswer[2;].</span>}}
<span class="oef_indgood">\name_question1[1] \(\ff\) \name_question1[2]
\(u(x) = \u\) \name_and \(k = \k).</span></p>
}
\if{\step=2}{
2. \name_question2 \(\u\) \name_at \(\texlim\).
<div class="wimscenter">
  <label for="reply3">\(\displaystyle \lim_{\xtol} \u\) =</label> \embed{reply3,5}</div>
}
\if{\step>2}{
2. \if{\step=3}
    {\if{\sc_reply3=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad">\name_youranswer[2;].</span>}
}
<span class="oef_indgood">\name_youranswer[3;] \name_question2sol[1] \(u\) \name_at \xlim \name_question2sol[2]</span>:
<p class="wimscenter">\(\displaystyle \lim_{\xtol} u(x) = \lim_{\xtol} \u = \sol3\)</p>
}
\if{\step=3}{
3. \name_question3 \(\g\) \name_at \(\sol3\).
<div class="wimscenter">
  <label for="reply4">\(\displaystyle \lim_{\ttol} \g \) =</label> \embed{reply4,5}</div>
}

\if{\step>3}{
3. \if{\step=4}{
    \if{\sc_reply4=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad">\name_youranswer[2;].</span>}
}
<span class="oef_indgood">\name_deduc:</span>
<p class="wimscenter">\(\displaystyle \lim_{\ttol} \g = \sol4\)</p>
}
\if{\step=4}{
  4. \deduc2[1] \(t = u(x)\), \deduc2[2], \deduc2[3]:
<div class="wimscenter">
<label for="reply5">\(\displaystyle \lim_{\xtol} \ggx = \lim_{\xtol} \funct\) =</label> \embed{reply5,5}</div>
}
\if{\step>4}{
4. \if{\step=5}
    {\if{\sc_reply5=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad"> \name_youranswer[2;1], \name_youranswer[2;2].</span>}
}
<span class="oef_indgood">\name_question2sol[1] \(\gg\) \name_at \xlim \name_question2sol[2]</span>
<p class="wimscenter">
\(\displaystyle \lim_{\xtol}
  \ggx = \lim_{\xtol} \funct = \lim_{\ttol} \g = \sol5\).
</p>
}
\if{\step=5}{
5. \name_deduc4:
<div class="wimscenter"><label for="reply6">\(\displaystyle \lim_{\xtol} \f\) =</label> \embed{reply6,5}</div>
}
<div class="wims_instruction">\name_inst</div>
}

\answer{\name_answer2[1] u(x)}{\u}{type=formal}{option=nonstop}
\answer{\name_answer2[2] k}{\k}{type=numeric}{option=nonstop}
\answer{\name_answer u = }{\rep3}{type=raw}{option=nospace,nonstop}
\answer{\name_answer \(\g\) = }{\rep4}{type=raw}{option=nospace,nonstop}
\answer{\name_answer \(\gg\) = }{\rep5}{type=raw}{option=nospace,nonstop}
\answer{\name_answer \(f\) = }{\rep6}{type=raw}{option=nospace}
