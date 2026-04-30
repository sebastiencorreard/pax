target=cplpremier1 cplpremier2 cplpremier3 cplpremier4 cplpremier5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{100}

#if defined TARGET_cplpremier1
 \text{ltpgcd=2,3,5,10,9,11}
 \text{val=2,3,5,7}
#endif
#if defined TARGET_cplpremier2
 \text{ltpgcd=2,3,5,10,9,11}
 \text{val=2,3,5,7,11,13}
#endif
#if defined TARGET_cplpremier3
 \text{ltpgcd=7,8,13,21,15,12}
 \text{val=2,3,5,7,11,13,17,19}
#endif
#if defined TARGET_cplpremier4
 \text{ltpgcd=7,8,13,21,23,29}
 \text{val=2,3,5,7,11,13,17,19}
#endif
#if defined TARGET_cplpremier5
 \text{val=2,3,5,7,11,13,17,19,23,29,31}
 \text{ltpgcd=\val}
#endif
\text{val=shuffle(\val)}
\text{ltpgcd=shuffle(\ltpgcd)}
\text{ltch=randrow(\couples)}
\text{ltch=shuffle(\ltch)}

#if defined TARGET_cplpremier1 || defined TARGET_cplpremier3
 \integer{a=item(1,\val)}
 \integer{b=item(2,\val)}
 \integer{ch=randint(0..1)}
 \if{\ch=1}{
  \integer{A=\ltpgcd[1]*\a}
  \integer{B=\ltpgcd[1]*\b}
 }{
  \integer{A=\ltpgcd[1]*\a}
  \integer{B=\ltpgcd[2]*\b}
 }
 \integer{g=gcd(\A,\B)}
 \text{good=\g=1?\name_yesno[1]:\name_yesno[2]}
\statement{
\A \name_question[1] \B \name_question[2] ?
<div class="spacer">
<b>\name_answer :</b>
\embed{c1,6}.
</div>
}
 \choice{PGCD}{\good}{\name_yesno}
#else
  \text{couples=1,1,0
0,0,1}
 \text{sol=}
 \integer{cpt=1}
 \text{enonce=}
 \for{i=1 to 3}{
  \integer{a=item(\i*2-1,\val)}
  \integer{b=item(\i*2,\val)}
  \integer{ch=item(\i,\ltch)}
  \if{\ch=1}{
   \integer{A=item(\cpt,\ltpgcd)*\a}
   \integer{B=item(\cpt,\ltpgcd)*\b}
   \integer{cpt=\cpt+1}
  }{
   \integer{A=item(\cpt,\ltpgcd)*\a}
   \integer{B=item(\cpt+1,\ltpgcd)*\b}
   \integer{cpt=\cpt+2}
  }
  \integer{g=gcd(\A,\B)}
  \text{tmp=(\A , \B)}
  \text{sol=\g=1?wims(append item \tmp to \sol)}
  \text{enonce=wims(append item \tmp to \enonce)}
 }
 \statement{
  \name_question
  <div class="spacer">
  <b>\name_answer :</b>
  <div class="wimscenter">\embed{r1, 100x50}</div>
</div>
}
 \reply{PGCD}{\rep;\enonce}{type=clickfill}
 \integer{nb3=items(\sol)}
 \text{tmplist=\rep,\sol}
 \text{tmplist=wims(listuniq \tmplist)}
 \integer{nb1=items(\tmplist)}
 \text{replt=wims(listuniq \rep)}
 \integer{nb2=items(\replt)}
 \condition{\name_cond}{\nb1=\nb3 and \nb2=\nb3}
#endif
