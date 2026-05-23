target=vitesse12

\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
\computeanswer{no}
\format{html}
\precision{100}
#include "lang.inc"
\integer{h=randint(7..11)}
\integer{hr=randint(\h+1..\h+4)}
\integer{t1=randint(5..58)}
\integer{v1=randint(45..100)}
\integer{t2=randint(5..58)}
\integer{v2=randint(45..100)}
\integer{t3=randint(5..58)}
\integer{v3=randint(45..100)}

\real{d1=ceil(\v1*\t1/60*100)/100}
\real{d2=ceil(\v2*\t2/60*100)/100}
\real{d3=ceil(\v3*\t3/60*100)/100}
\real{d=ceil((\d1+\d2+\d3)*100)/100}
\real{tmin=\t1+\t2+\t3}

conversion de l'heure exprimée en minutes, en heure/minute
\integer{t=floor(\tmin/60)}
\integer{th=floor(\t)}
\integer{tm=\tmin-60*\th}
\integer{tha=\th+\h}

\real{v=ceil((\d/(\tmin/60))*100)/100}

\text{rep=\hr>\h+\t?item(1,\liste):item(2,\liste)}

\text{liste1=\name_list[1] \t1 min \name_list[2] \v1 \name_hkm[3], \name_list[1] \t1
 min \name_list[3] \d1 km, \name_list[1] \d1 km \name_list[2] \v1 \name_hkm[3]}
\text{liste2=\name_list[1] \t2 min \name_list[2] \v2 \name_hkm[3], \name_list[1] \t2
 min \name_list[3] \d2 km, \name_list[1] \d2 km \name_list[2] \v2 \name_hkm[3]}
\text{liste3=\name_list[1] \t3 min \name_list[2] \v3 \name_hkm[3], \name_list[1] \t3
 min \name_list[3] \d3 km, \name_list[1] \d3 km \name_list[2] \v3 \name_hkm[3]}
\text{portion1=randitem(\liste1)}
\text{portion2=randitem(\liste2)}
\text{portion3=randitem(\liste3)}

\steps{reply1
reply2
reply3
choice1}
\text{name_question=wims(replace internal XXXX by \d in \name_question)}
\text{name_question=wims(replace internal YYYY by \th \name_hkm[1] \tm min in \name_question)}
\text{name_question=wims(replace internal ZZZZ by \hr in \name_question)}

\statement{
\name_enonce[1] \h h 00 \name_enonce[2] \portion1,
\name_enonce[3] \portion2, \name_enonce[4] \portion3.
\if{\step=1}{<p>\name_question[1]?</p> }
\if{\step>=2}{<p>\name_question[2].</p>}
\if{\step=2}{<p>\name_question[3]?</p>}
\if{\step>=3}{<p>\name_question[4]</p>}
\if{\step=3}{<p>\name_question[5]?</p>}
\if{\step>=4}{<p>\name_question[6] \v \name_hkm[3].</p>}
\if{\step=4}{<div>\name_question[7] \hr \name_hkm[1] 00. \name_question[8]?
\embed{choice1}</div>}
<div class="wims_instruction">\name_instruction1
  <span class="tt">3 km, 5 km/h, 1 h 32 min </span> (\name_instruction2).
</div>
}
\hint{
  \if{\step=1}{\name_hint1: \(d=v*t)}
  \if{\step=2}{name_hint2.}
}
\answer{\name_answer[1]}{\d km}{type=units}
\answer{\name_answer[2]}{\th h \tm min}{type=units}
\answer{\name_answer[3]}{\v km/h}{type=units}
\choice{}{\rep}{\liste}
\feedback{\step>=4 and \choice1 notsametext \rep}{
\name_feed[1] \th \name_hkm[1] \tm min. \name_feed[2] \tha \name_hkm[1] \tm min,
  \name_feed[3]\if{\hr>=\h+\t}{\name_feed[4]}{\name_feed[5]} \name_feed[6]}
