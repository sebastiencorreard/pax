#if defined TARGET_oefcompltabl1
\text{sol=\(\lig11+\lig12=\totl1\)
<p>\(\totl2-\lig21=\lig22\)}
#endif
#if defined TARGET_oefcompltabl2
\text{sol=\(\lig11+\lig12=\totl1\)
<p>\(\lig21+\lig22=\totl2\)</p>
<p>\(\lig11+\lig21=\totc1\)</p>
<p>\(\lig12+\lig22=\totc2\)</p>
<p>\(\totc1+\totc2=\tott\) ou \(\totl1+\totl2=\tott\)</p>}
#endif
#if defined TARGET_oefcompltabl3
\text{sol=\(\totl1-\lig11=\lig12\)
<p>\(\tott-\totc2=\totc1\)</p>
<p>\(\totc1-\lig11=\lig21\)</p>
<p>\(\totc2-\lig12=\lig22\)</p>
<p>\(\lig21+\lig22=\totl2\) ou \(\tott-\totl1=\totl2\)</p>
}
#endif
#if defined TARGET_oefcompltabl4
\text{sol=\(\totc2-\lig22=\lig12\)
<p>\(\totl1-(\lig11+\lig12+\lig14)=\lig13\)</p>
<p>\(\totc1-\lig11=\lig21\)</p>
<p>\(\totc4-\lig14=\lig24\)</p>
<p>\(\lig21+\lig22+\lig23+\lig24=\totl2\)</p>
<p>\(\lig13+\lig23=\totc3\)</p>
<p>\(\totl1+\totl2=\tott\) ou \(\totc1+\totc2+\totc3+\totc4=\tott\)</p>
}
#endif
#if defined TARGET_oeffairetabl1
\text{sol=Pourcentage de \listefr[\shu[\pos]]}
#endif
#if defined TARGET_oeffairetabl3
\text{sol=<p>Le nombre total de personnes est \(\efft\).</p>}
#endif
#if defined TARGET_oefgraph4
\text{eleves=élèves,ont}
\text{eleve=élève,a}
\text{consi=élèves ont une note inférieure à 10.}
\text{conss=élèves ont une note supérieure à 10.}
\text{name_other=Les autres élèves ont plus de 10.,Les autres élèves ont moins de 10.}
\if{\a=1}{
  \integer{n=0}
  \if{\effs[1]<2}{
    \text{phrase=\(\effs[1]\) \eleve[1] \eleve[2] 0}
  }{
    \text{phrase=\(\effs[1]\) \eleves[1] \eleves[2] 0}
  }
  \for{k=2 to 3}{
    \integer{n=\n+4}
    \if{\effs[\k]<2}{
      \text{phrase=\phrase, \(\effs[\k]\) \eleve[1] \eleve[2] \n}
    }{
      \text{phrase=\phrase, \(\effs[\k]\) \eleves[1] \eleves[2] \n}
    }
  }
}{
  \integer{n=12}
  \if{\effs[4]<2}{
    \text{phrase=\(\effs[4]\) \eleve[1] \eleve[2] 12}
  }{
    \text{phrase=\(\effs[4]\) \eleves[1] \eleves[2] 12}
  }
  \for{k=5 to 6}{
    \integer{n=\n+4}
    \if{\effs[\k]<2}{
      \text{phrase=\phrase, \(\effs[\k]\) \eleve[1] \eleve[2] \n}
    }{
      \text{phrase=\phrase, \(\effs[\k]\) \eleves[1] \eleves[2] \n}
    }
  }
}
\if{\a=1}{
  \text{\sol= \phrase. \name_other[\a]
  <p>\(\effs[1]+\effs[2]+\effs[3]=\rep\)</p> \(\rep\) \consi}
}{
  \text{\sol=\phrase. \name_other[\a]
  <p>\(\effs[4]+\effs[5]+\effs[6]=\rep\)</p>
  \(\rep\) \conss}
}
#endif
#if defined TARGET_oefliretabl1
\text{enonc1sol=\sex[floor((\b+1)/2)] \qual[\b] en \niv[\a[1]]}
\text{enonc2sol=\sex[floor((\d+1)/2)] \qual[\d] en \niv[\a[2]]}
\text{sol=On lit directement la réponse dans le tableau&nbsp;: il y a <mark class="yellow">\(\rp1\)</mark> \enonc1sol.
<p>On lit directement la réponse dans le tableau&nbsp;: il y a <mark class="PaleGreen">\(\rp2\)</mark> \enonc2sol.</p>}
#endif
#if defined TARGET_oefliretabl2
\text{enonc1sol=élèves en \niv[\a[1]]}
\text{enonc2sol=élèves en \niv[\a[2]]}
\text{sol=On lit directement la réponse dans le tableau&nbsp;: il y a <mark class="yellow">\(\rp1\)</mark> \enonc1sol.
<p>On lit directement la réponse dans le tableau&nbsp;: il y a <mark class="PaleGreen">\(\rp2\)</mark> \enonc2sol.</p>}
#endif
#if defined TARGET_oefliretabl3
\text{sol=On lit directement dans le tableau&nbsp;: il y a <mark class="yellow">\(\rp1\)</mark> \sex[floor((\a[1]+1)/2)] \qual[\a[1]].
<p>On lit directement dans le tableau&nbsp;: il y a <mark class="PaleGreen">\(\rp2\)</mark> \sex[floor((\a[2]+1)/2)] \qual[\a[2]].</p>}
#endif
#if defined TARGET_oefliretabl4
\text{sol=On calcule le nombre de \sex[\b] en \niv[\a]&nbsp;: \(\val[\b*2-1;\a[1]]+\val[\b*2;\a[1]]=\rp1\).
<p>Il y a <mark class="yellow">\(\rp1\)</mark> \sex[\b] en \niv[\a].
<p>On lit directement la réponse dans le tableau&nbsp;: il y a <mark class="PaleGreen">\(\rp2\)</mark> élèves dans le collège.</p>}
#endif
#if defined TARGET_oefliretabl5
\text{sol=On calcule le nombre de \qual[\b] en \niv[\a[1]]&nbsp;: \(\val[\b;\a[1]]+\val[\b+2;\a[1]]=\rp1\).
<p>Il y a <mark class="yellow">\(\rp1\)</mark> \qual[\b] en \niv[\a[1]].</p>
On calcule le nombre de \qual[\b] en \niv[\a[2]]&nbsp;: \(\val[\b;\a[2]]+\val[\b+2;\a[2]]=\rp2\).
<p>Il y a <mark class="PaleGreen">\(\rp2\)</mark> \qual[\b] en \niv[\a[2]].</p>}
#endif
#if defined TARGET_oefutitabl1
\text{sol=Le nombre d'élèves en \niv[\b] est \(\totc[\b]\).}
#endif
#if defined TARGET_oefutitabl2
\integer{aux=floor((\b+1)/2)}
\text{sol=<p>Le nombre de \sex[\aux] \qual[\b] est \(\totl[\b]\).</p>}
#endif
#if defined TARGET_oefutitabl3
\if{\b=1}{\text{calculrep=\val[1;1]+\val[1;2]+\val[1;3]+\val[1;4]+\val[2;1]+\val[2;2]+\val[2;3]+\val[2;4]}}
{\text{calculrep=\val[3;1]+\val[3;2]+\val[3;3]+\val[3;4]+\val[4;1]+\val[4;2]+\val[4;3]+\val[4;4]}}
\text{sol=\(\calculrep=\rp1\)
<p>Le nombre de \sex[\b] est \(\rp1\).</p>}
#endif
#if defined TARGET_oefutitabl4
\if{\b=1}{\text{calculrep=\val[1;1]+\val[1;2]+\val[1;3]+\val[1;4]+\val[3;1]+\val[3;2]+\val[3;3]+\val[3;4]}}
{\text{calculrep=\val[2;1]+\val[2;2]+\val[2;3]+\val[2;4]+\val[4;1]+\val[4;2]+\val[4;3]+\val[4;4]}}
\text{sol=\(\calculrep=\rp1\)
<p>Il y a \(\rp1\) \qual[\b] au collège.}
#endif
#if defined TARGET_oefutitabl5
\text{sol=On effectue la somme de tous les nombres situés dans le tableau.
<p>Il y a \(\rp1\) élèves dans le collège.</p>}
#endif

#if defined TARGET_oefutigraph1
\integer{n=0}
\if{\effs[1]<2}{\text{phrase=\(\effs[1]\) élève a 0}}{\text{phrase=\(\effs[1]\) élèves ont 0}}
\for{k=2 to 5}{\integer{n=\n+4}
  \if{\effs[\k]<2}{\text{phrase=\phrase, \(\effs[\k]\) élève a \n}}{\text{phrase=\phrase, \(\effs[\k]\) élèves ont \n}}}
\if{\effs[6]<2}{\text{phrase=\phrase, \(\effs[6]\) élève a 20.}}{\text{phrase=\phrase, \(\effs[6]\) élèves ont 20.}}
\text{sol=\phrase
<p>\(\effs[1]+\effs[2]+\effs[3]+\effs[4]+\effs[5]+\effs[6]=\rp\)</p>
Il y a \(\rp\) élèves dans la classe.}
#endif
#if defined TARGET_oefutigraph5
\text{sol=On calcule \(\s[\a] \percent\) de \(\n\).
<p>\(\frac{\s[\a]}{100} \times \n = \frac{\s[\a] \times \n}{100}=\rp\)</p>
\(\rp\) élèves préfèrent le \listefr[\a].}
#endif
