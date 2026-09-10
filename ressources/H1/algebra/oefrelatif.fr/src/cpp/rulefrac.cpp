target=rulefrac0 rulefrac rulefracirr rulefracrel rulefracrelirr
#include "lang_titles.inc"
#include "lang.inc"
#include "author.inc"
\integer{m=6}
#if defined TARGET_rulefrac || defined TARGET_rulefrac0
\integer{m1=0}
\integer{signe=1}
#endif
#if defined TARGET_rulefracirr
\integer{m1=0}
\integer{signe=1}
#endif
#if defined TARGET_rulefracrel
\integer{m1=-\m}
\integer{signe=randitem(-1,1)}
#endif
#if defined TARGET_rulefracrelirr
\integer{m1=-\m}
\integer{signe=randitem(-1,1)}
#endif
\computeanswer{no}
\precision{1000}

\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
  \integer{a=\i*1}
  \integer{s=\i}
  \text{dessin=\dessin
  text blue, \s,-1, medium,\a}
}
#if defined TARGET_rulefrac0
\text{den=randitem(2,5)}
#else
\text{den=randitem(2,4,5)}
#endif
\text{num=randint(1..10)}
\text{reste=pari(divrem(\num,\den)~[2])}
\while{\reste=0}{
  \integer{den =\den*\den}
  \text{reste=pari(divrem(\num,\den)~[2])}
}
\rational{a=\signe*\num/\den}
\text{nd=pari([numerator(\a),denominator(\a)])}

\text{dessin=
xrange \m1-0.1,\m+0.1
  yrange -2,2.2
  hline black,0,0
  arrow 2.5,0,\m,0,10,black
  parallel \m1,-0.8,\m1,0.4,1/2,0, 40, blue
  parallel \m1,-0.3,\m1,0.3,1/10,0, 200, blue
  parallel \m1,-0.8,\m1,0.6,1,0, 40, red
  \dessin
  arrow \a,2,\a,0, 8, black
}
\text{dessintikz=drawtikz(600,50
\dessin)}
\statement{\instruction
  <table class="wimscenter wimsnoborder">
  <tr><td>\embed{reply 1,6}</td></tr>
  <tr><td><hr></td></tr>
  <tr><td>\embed{reply 2,6}</td></tr>
  </table>
  <div class="wimscenter">\draw{600,50}{\dessin}
  </div>
  \if{\consigne!=}{
    <div class="wims_instruction">
    <span style="font-weight:bold;">\name_consigne</span>.
    \consigne
    </div>
  }
}
#if defined TARGET_rulefrac0 || defined TARGET_rulefrac
\answer{\name_numden[1]}{\nd1}{type=numeric}{option=noanalyzeprint}
\answer{\name_numden[2]}{\nd2}{type=numeric}{option=noanalyzeprint}
\text{test1=round(\reply1)=\reply1 ? 1:0}
\condition{Bonne réponse ?}{\test1=1 and \reply1/\reply2=\a}
\feedback{\reply1/\reply2!=\a or \test1=0}{\name_solution \(\frac{\nd[1]}{\nd[2]}\).}
#endif
#if defined TARGET_rulefracrel
\answer{\name_numden[1]}{\nd1}{type=numeric}{option=noanalyzeprint}
\answer{\name_numden[2]}{\nd2}{type=numeric}{option=noanalyzeprint}
\text{test1=round(\reply1)=\reply1 ? 1:0}
\condition{Bonne réponse ?}{\test1=1 and \reply1/\reply2=\a}
\feedback{\reply1/\reply2!=\a or \test1=0}{\name_option \(\frac{\nd[1]}{\nd[2]}\).}
#endif
#if defined TARGET_rulefracirr
\answer{\name_numden[1]}{\nd[1]}{type=numeric}
\answer{\name_numden[2]}{\nd[2]}{type=numeric}
\real{test1=\reply1/\reply2-\a}
\feedback{\test1=0 and \reply1<>\nd[1]}{\name_warning}
#endif
#if defined TARGET_rulefracrelirr
\answer{\name_numden[1]}{\nd[1]}{type=numeric}
\answer{\name_numden[2]}{\nd[2]}{type=numeric}
\real{test1=\reply1/\reply2-\a}
\feedback{\test1=0 and \reply1<>\nd[1]}{\name_warning}
#endif
\latex{
\begin{statement}
\instruction
\begin{center}
\dessintikz
\end{center}
\end{statement}
}
