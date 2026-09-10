target=arrondix arrondixguide arrondixrelie

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a=randint(0..999)}
\integer{b=randint(0..9999)}
\real{n=\a+\b/10000}
\integer{centi=floor(\b/100)-(floor(\b/1000))*10}
\text{nvirg=wims(replace internal . by , in \n)}
\real{valdef=\a+(floor(\b/1000))/10}
\real{valex=\valdef+0.1}
\text{nvaldef=wims(replace internal . by , in \valdef)}
\text{nvalex=wims(replace internal . by , in \valex)}
\if{\centi<5}{
  \integer{rep=1}
  \text{arrond=\nvaldef}}{
  \integer{rep=2}
  \text{arrond=\nvalex}
}
\text{narrond=wims(replace internal . by , in \arrond)}
\text{enonce=\name_enonce[1] \(\nvirg\).}
\text{dixiem=<b><span style="color:red">\name_precdix[2]</span></b>}
\text{centiem=<b><span style="color:blue">\name_precdix2[3]</span></b>}
\text{name_hint=wims(replace internal XXXX by \dixiem in \name_hint)}
\text{name_hint=wims(replace internal YYYY by \centiem in \name_hint)}

#if defined TARGET_arrondix
\statement{\enonce<br>
  \name_question:
  <br><label for="reply1">\name_statement0[1] \dixiem \name_statement0[2] \(\nvirg\)
  \name_statement0[3]</label> \embed{r1,3}.
}
\answer{\name_answer[2]}{\narrond}{type=raw}
#endif
#if defined TARGET_arrondixguide
\statement{
  \enonce \name_enonce[2] \dixiem.<br>
  \name_question:
  <ul><li>
  <label for="reply1">\name_statement[1;1] <span style="color:blue"><b>\centiem</b></span>
  \name_statement[1;2] \(\nvirg\) \name_statement[1;3]</label> \embed{r1,3},
  </li><li><label for="reply2">\name_statement[2;1] \dixiem \name_statement[2;2] \(\nvirg\)
  \name_statement[2;3] \dixiem</label> \embed{r2},
    <label for="reply3"> \name_statement[2;4]</label> \embed{r3,3}.
  </ul>}
\answer{\name_answer[1] \centiem}{\centi}{type=numexp}
\answer{}{\rep;\liste}{type=menu}
\answer{\name_answer[2]}{\narrond}{type=raw}
#endif
#if defined TARGET_arrondixguide
\feedback{(\rep=1 and \reply2 issametext \liste[2]) or (\rep=2 and \reply2 issametext \liste[1])}
{\name_feed}
#endif
#if defined TARGET_arrondix || defined TARGET_arrondixguide
\solution{\name_statement[1;1] \centiem \name_statement[1;2] \(\nvirg\) \name_statement[1;3] \(\centi\),
  \name_statement[2;1] \dixiem \name_statement[2;3] \dixiem \liste[\rep] : \(\narrond\).
  <p>\name_note \(\nvirg \approx \narrond.\)</p>}
#endif
#if defined TARGET_arrondixrelie
\integer{a=randint(0..9)*100+randint(0..9)*10}
\integer{b=randint(1..9)}
\text{rep=}
\text{reph=}
\for{i=1 to 4}{
  \integer{f=\b+\i}
  \real{n=(\a+\b+\i)/10}
  \text{rep=wims(append item \n to \rep)}
  \if{\f<>10}{\text{n=slib(numeration/ecriturenombre \n)}}
           {\text{n=slib(numeration/ecriturenombre \n).0}}
  text{n=wims(replace internal . by , in \n)}
  \text{reph=wims(append item \n to \reph)}
}
\real{nb1=\rep[2]-randint(501..999)/10000}
\text{nb1=slib(numeration/ecriturenombre \nb1)}
text{nb11=wims(replace internal . by , in \nb1)}
\real{nb2=\rep[2]-randint(1..499)/10000}
\text{nb2=slib(numeration/ecriturenombre \nb2)}
text{nb2=wims(replace internal . by , in \nb2)}
\real{nb3=\rep[4]-randint(501..999)/10000}
\text{nb3=slib(numeration/ecriturenombre \nb3)}
text{nb3=wims(replace internal . by , in \nb3)}
\real{nb4=\rep[4]-randint(1..499)/10000}
\text{nb4=slib(numeration/ecriturenombre \nb4)}
text{nb4=wims(replace internal . by , in \nb4)}
\text{list=\nb1 \name_list,\nb2 \name_list,\nb3 \name_list,\nb4 \name_list}
\statement{\name_question:
  <div class="wimscenter"> \embed{r1}</div>
}
\answer{}{\list;\reph}{type=correspond}
#endif
\help{\name_hint}
