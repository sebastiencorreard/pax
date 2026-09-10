\text{tablehtml=<table class="wimscenter wimsborder">
<caption>Tableau des codons ARN</caption>
<tr>
<th rowspan="2">nucléotide 1</th>
<th colspan="4">nucléotide 2</th>
<th rowspan="2">nucléotide 3</th>
</tr><tr>
<th>U</th><th>C</th><th>A</th><th>G</th>
</tr>}
\text{tableau=,U,C,A,G}
\for{a in U,C,A,G}{
  \text{tablehtml=\tablehtml<tr><th rowspan="4">\a</th>}
  \for{c in U,C,A,G}{
    \text{tableau=\tableau
  \a,}
    \text{tablehtml=\tablehtml}
    \for{b in U,C,A,G}{
      \text{tableau=\tableau wims(lookup \a\b\c in codon2am),}
      \text{tablehtml=\tablehtml<td class="wims(lookup \a\b\c in codontype)">
      wims(lookup \a\b\c in codon2am)</td>}
    }
    \text{tableau=\tableau\c}
    \text{tablehtml=\tablehtml<th>\c</th></tr>}
  }
}
\text{tablehtml=\tablehtml</table>}

\matrix{legende=apolaire,Acide aminé apolaire
polaire,Acide aminé polaire
basique,Acide aminé basique
acide,Acide aminé acide
terminaison,Terminaison}
\text{tablehtml=\tablehtml<div>
  <p class="inline">Légende</p>
  <ul class="inline">}
\for{j=1 to 5}{
  \text{tablehtml=\tablehtml<li class="\legende[\j;1]">\legende[\j;2]</li>}
}
\text{tablehtml=\tablehtml</ul></div>}

\matrix{tableau=\tableau}
\text{tableauhtml=slib(text/matrixhtml [\tableau], wimsborder wimscenter,TH=[1;1,6] caption="Tableau des codons ARN")}
