target=ppower11 ppower12 ppower13
\author{Bernadette, Perrin-Riou}
#include "lang_titles.inc"
#include "lang.inc"
\text{nb=\confparm1 iswordof 1 2 3 4 5? \confparm1:3}
\text{AC=wims(makelist x for x=2 to 5)}
\text{A=shuffle(\AC)}
\text{A=\A[1..\nb]}
\text{C=shuffle(\AC)}
\text{D=shuffle(\AC)}
\text{B=wims(makelist 2 for x=1 to \nb)}
#if defined TARGET_ppower11
\observation{nombres inférieurs à 9, puissance 2, avec addition}
\text{H=wims(makelist + for x=1 to \nb)}
#endif
#if defined TARGET_ppower12
\observation{nombres inférieurs à 9, puissance 2, avec soustraction}
\text{H=wims(makelist - for x=1 to \nb)}
#endif
#if defined TARGET_ppower13
\observation{nombres inférieurs à 9, puissance 2,avec addition ou soustraction}
\text{H=wims(makelist + for x=1 to \nb),wims(makelist - for x=1 to \nb)}
\text{H=shuffle(\H)}
\text{H=\H[1..\nb]}
#endif
\text{H1=wims(replace internal + by +1 in \H)}
\text{H1=wims(replace internal - by -1 in \H1)}

\text{N1=pari(A=[\A]; B=[\B]; C=[\C];D=[\D];H=[\H1];)}
\text{N1=pari(vector(\nb,i, C[i] + (H[i])* D[i]*A[i]^B[i]))}
\text{N2=pari(vector(\nb,i,(C[i] + (H[i])* D[i])*A[i]^B[i]))}
\text{N3=pari(vector(\nb,i, C[i] + (H[i])*(D[i]*A[i])^B[i]))}

\text{STEP=wims(makelist r x for x=1 to 3*\nb)}
\text{label=wims(makelist x for x=1 to 3*\nb)}
\steps{\STEP}
\statement{
\name_statement:
<ul>
\for{j=1 to \nb}{
<li>
 <ul class="inline"><li class="spacer">
<label for="reply\label[3*(\j-1)+1]">\(\C[\j] \H[\j] \D[\j]*\A[\j]^\B[\j] \)</label> = \embed{\STEP[3*(\j-1)+1],5}
</li><li>
<label for="reply\label[3*(\j-1)+2]">\((\C[\j] \H[\j] \D[\j])*\A[\j]^\B[\j] \)</label> = \embed{\STEP[3*(\j-1)+2],5}
</li><li>
<label for="reply\label[3*(\j-1)+3]">\(\C[\j] \H[\j] (\D[\j]*\A[\j])^\B[\j]\)</label> = \embed{\STEP[3*(\j-1)+3],5}
</li></ul>
</li>
}
</ul>
}

\answer{}{\N1[1]}{type=numexp}
\answer{}{\N2[1]}{type=numexp}
\answer{}{\N3[1]}{type=numexp}
\answer{}{\N1[2]}{type=numexp}
\answer{}{\N2[2]}{type=numexp}
\answer{}{\N3[2]}{type=numexp}
\answer{}{\N1[3]}{type=numexp}
\answer{}{\N2[3]}{type=numexp}
\answer{}{\N3[3]}{type=numexp}
\answer{}{\N1[4]}{type=numexp}
\answer{}{\N2[4]}{type=numexp}
\answer{}{\N3[4]}{type=numexp}
\answer{}{\N1[5]}{type=numexp}
\answer{}{\N2[5]}{type=numexp}
\answer{}{\N3[5]}{type=numexp}
