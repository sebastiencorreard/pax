target=entier rationnel decimal puissance1 puissance2

#include "author.inc"
#include "lang_titles.inc"
\precision{10000}

\integer{ch=random(1..3)}

#if defined TARGET_entier
\text{size=50x50x1}
\text{B=shuffle(1,2,3,5,6,7,10,11)}
\text{B=item(1,\B),item(2,\B),item(3,\B)}
\text{A=wims(values (x)^2 for x in \B)}
\text{C=wims(values (x)^4 for x in \B)}
\text{plus=}
\for{x in \B}{\text{plus=wims(append item \(\sqrt{\x}) to \plus)}}
\if{\B[\ch]<>1}{
\text{C=wims(replace item number \ch by \(\A[\ch]) in \C)}
\text{A=wims(replace item number \ch by \(\B[\ch]) in \A)}
\text{B=wims(replace item number \ch by \(\sqrt{\B[\ch]}) in \B)}}
#endif
#if defined TARGET_rationnel
\text{size=50x70x1}
\text{fraction=1/2,2/3,1/3,1/5,2/5,3/5,1/6,5/6,1/7,2/7,3/7,5/7}
\text{list=shuffle(\fraction)}
\text{list=item(1,\fraction),item(2,\fraction),item(3,\fraction)}
\text{A=}
\text{B=}
\text{C=}
\text{plus=}
\for{x=1 to 3}{
\text{FT=wims(replace internal / by , in \list[\x])}
\integer{num=\FT[1]^2}
\integer{den=\FT[2]^2}
\integer{num2=\num^2}
\integer{den2=\den^2}
\if{\x=\ch}{
\text{tmp=\sqrt{\frac{\FT[1]}{\FT[2]}}}
\text{tmp=\FT[1]=1?\frac{1}{\sqrt{\FT[2]}},\tmp:\tmp}
\text{tmp=randitem(\tmp)}
\text{B=wims(append item \(\tmp) to \B)}
\text{A=wims(append item \(\frac{\FT[1]}{\FT[2]}) to \A)}
\text{C=wims(append item \(\frac{\num}{\den}) to \C)}
}{
\text{B=wims(append item \(\frac{\FT[1]}{\FT[2]}) to \B)}
\text{A=wims(append item \(\frac{\num}{\den}) to \A)}
\text{C=wims(append item \(\frac{\num2}{\den2}) to \C)}
\text{plus=wims(append item \(\sqrt{\frac{\FT[1]}{\FT[2]}}) to \plus)}
}
}
#endif
#if defined TARGET_decimal
\text{size=50x75x1}
\text{B=shuffle(0.1,0.2,0.3,0.5,0.6,0.7,1.1,1.2,1.3)}
\text{B=item(1,\B),item(2,\B),item(3,\B)}
\text{A=wims(values (x)^2 for x in \B)}
\text{C=wims(values (x)^4 for x in \B)}
\text{plus=}
\for{x in \B}{\text{plus=wims(append item \(\sqrt{\x}) to \plus)}}
\if{\B[\ch]<>1}{
\text{C=wims(replace item number \ch by \(\A[\ch]) in \C)}
\text{A=wims(replace item number \ch by \(\B[\ch]) in \A)}
\text{B=wims(replace item number \ch by \(\sqrt{\B[\ch]}) in \B)}}
#endif

#if defined TARGET_puissance1  || defined TARGET_puissance2
# if defined TARGET_puissance1
\text{nombre=10,10,10}
# else
\text{nombre=randint(2,3,5,6,7),randint(2,3,5,6,7),randint(2,3,5,6,7)}
# endif
\text{size=60x50x1}
\text{puis=shuffle(-2,-3,-4,-5,-6,2,3,4,5,6)}
\text{puis=2,4,6}
\text{puis=item(1,\puis),item(2,\puis),item(3,\puis)}
\text{A=}
\text{B=}
\text{C=}
\text{plus=}
\for{x=1 to 3}{
   \integer{tmp=\puis[\x]/2}
   \if{\tmp notitemof \puis}{
   \text{plus=wims(append item \(\sqrt{\nombre[\x]^{\puis[\x]}}) to \plus)}}
   \text{B=wims(append item \(\nombre[\x]^{\puis[\x]}) to \B)}
   \integer{tmp=2*\puis[\x]}
   \text{A=wims(append item \(\nombre[\x]^{\tmp}) to \A)}
   \integer{tmp=2*\tmp}
   \text{C=wims(append item \(\nombre[\x]^{\tmp}) to \C)}
}
#endif

\statement{Compléter le tableau à l'aide des réponses proposées.
<table class="wimsborder wimscenter">
  <tr>
    <td>\(x)</td>
    <td>\A[1]</td>
    <td>\embed{reply 1,\size}</td>
    <td>\embed{reply 2,\size}</td>
  </tr><tr>
    <td>\(\sqrt{x})</td>
    <td>\embed{reply 3,\size}</td>
    <td>\B[2]</td>
    <td>\embed{reply 4,\size}</td>
  </tr><tr>
    <td>\(x^2)</td>
    <td>\embed{reply 5,\size}</td>
    <td>\embed{reply 6,\size}</td>
    <td>\C[3]</td>
  </tr>
</table>}

\reply{x2}{\A[2]|\A,\B,\C,\plus}{type=clickfill}
\reply{x3}{\A[3]|\A,\B,\C,\plus}{type=clickfill}
\reply{\(\sqrt{x1})}{\B[1]|\A,\B,\C,\plus}{type=clickfill}
\reply{\(\sqrt{x3})}{\B[3]|\A,\B,\C,\plus}{type=clickfill}
\reply{\(x1^2)}{\C[1]|\A,\B,\C,\plus}{type=clickfill}
\reply{\(x2^2)}{\C[2]|\A,\B,\C,\plus}{type=clickfill}
