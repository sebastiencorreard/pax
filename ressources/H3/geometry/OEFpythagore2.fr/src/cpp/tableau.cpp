target=tableau
\title{Tableau de valeurs}
\language{fr}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
\integer{ch=random(1..3)}

\text{list=wims(values v^2 for v=2 to 20)}
\integer{a=randitem(\list)}
\integer{b=random(2..100)}
\real{c=randint(100..1000)/10}
\real{d=randint(1000..10000)/100}
\text{e=simplify(randint(2..20)/randint(2..20))}
\text{list=\a,\b,\c,\d,\e}
\text{e=texmath(\e)}
\integer{chprec=randint(1..3)}
\text{listprec=dixième,centième,millième}
\integer{ch=random(1,2)}
\if{\ch=1}{
 \text{precision=item(\chprec,\listprec)}
 \text{precision= au \precision}
}{
 \real{precision=1/10^\chprec}
 \text{precision= à \precision}
}
\text{rep=}
\for{i=1 to 5}{
 \real{tmp=item(\i,\list)}
 \integer{tmp=sqrt(\tmp)*10^\chprec}
 \real{tmp=\tmp/10^\chprec}
 \text{rep=wims(append item \tmp to \rep)}
}

\statement{En utilisant votre calculatrice, complétez le tableau suivant.
<div class="wims_instruction">Les résultats seront donnés \precision près.</div>
<table class="wimscenter wimsborder">
  <tr>
    <td>\(x)</td>
    <td><label for="reply1">\a</label></td>
    <td><label for="reply2">\b</label></td>
    <td><label for="reply3">\c</label></td>
    <td><label for="reply4">\d</label></td>
    <td><label for="reply5">\(\e)</label></td>
  </tr><tr>
    <td>\(\sqrt{x})</td>
    <td>\embed{r1,7}</td>
    <td>\embed{r2,7}</td>
    <td>\embed{r3,7}</td>
    <td>\embed{r4,7}</td>
    <td>\embed{r5,7}</td>
  </tr>
</table>}

\reply{\(\sqrt{\a})}{\rep[1]}{type=numexp}
\reply{\(\sqrt{\b})}{\rep[2]}{type=numexp}
\reply{\(\sqrt{\c})}{\rep[3]}{type=numexp}
\reply{\(\sqrt{\d})}{\rep[4]}{type=numexp}
\reply{\(\sqrt{\e})}{\rep[5]}{type=numexp}
