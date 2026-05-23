#if defined TARGET_symax2 || defined TARGET_symcen2
\text{name_solution1=Par \action le motif \(\K[1]\) se superpose au motif <span class="nowrap">\(\K[2]\).</span>}
\text{name_solution2=Le symétrique par rapport \nom du motif \(\K[1]\) est le motif <span class="nowrap">\(\K[2]\).</span>}
#endif
#if defined TARGET_rota2
\text{name_solution=<p>Il y a \coef \saut à faire \name_sens_list[\choix] entre le motif de départ \depart et celui d'arrivée.<p>
On compte \coef \saut \name_sens_list[\choix] à partir du motif \depart. On obtient le motif \goodrep.
<p>\name_conclusion: L'image du motif \depart par la rotation de centre \(O\), d'angle \(\angle[\coef]^{\circ}\) \name_sens_list[\choix] est le motif \goodrep.</p>}
#endif
#if defined TARGET_rota2bis
\text{name_solution1=Il y a \coef \saut \name_sens_list[\choix] à faire entre le motif de départ \depart et le motif d'arrivée \listdeca[\depart]}
\text{name_solution2=L'angle de la rotation de centre \(O\) \name_sens_list[\choix] qui transforme le motif \depart en \listdeca[\depart] est <span class="nowrap">\(\goodrep^{\circ}\).</span>}
#endif
#if defined TARGET_symax1
\text{name_solution=Par pliage le long de la droite \((DH)\), le carré \(\K[1]\) se superpose \sol
<p>\name_conclusion: Le symétrique par rapport à la droite \((DH)\) du carré \(\K[1]\) est...le carré <span class="nowrap">\(\K[2]\).</span>}
#endif
#if defined TARGET_symcen1
\text{name_solution=Par demi-tour autour du point \(O\), le carré \(\K[1]\) se superpose au carré <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Le symétrique par rapport au point \(O\) du carré \(\K[1]\) est le carré <span class="nowrap">\(\K[2]\).</span>}
#endif
#if defined TARGET_rota1
\text{name_solution=Il y a \absecart \saut \sens pour aller du carré \dep[1] au carré \dep[2].
<p> On compte \absecart \saut, dans le même sens, à partir du carré <span class="nowrap">\(\K[1]\).</span> On obtient le carré <span class="nowrap">\(\K[2]\).</span></p>
La rotation de centre <span class="nowrap">\(O\),</span> qui transforme le carré \(\dep[1]\) en carré <span class="nowrap">\(\dep[2]\),</span> transforme le carré \(\K[1]\) en carré <span class="nowrap">\(\K[2]\).</span>}
#endif
#if defined TARGET_symax5
\text{name_solution=Par pliage le long de la droite <span class="nowrap">\((\axe)\),</span> le cerf-volant \(\K[1]\) se superpose au cerf-volant <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Par la symétrie d'axe <span class="nowrap">\((\axe)\),</span> l'image du cerf-volant \(\K[1]\) est le cerf-volant <span class="nowrap">\(\K[2]\).</span></p>}
#endif
#if defined TARGET_symcen5
\text{name_solution=Par demi-tour autour du point <span class="nowrap">\(J\),</span> le cerf-volant \(\K[1]\) se superpose au cerf-volant <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Par la symétrie de centre <span class="nowrap">\(J\),</span> l'image du cerf-volant \(\K[1]\) est le cerf-volant <span class="nowrap">\(\K[2]\).</span></p>}
#endif
#if defined TARGET_symax6
\text{name_solution=Par la symétrie d'axe <span class="nowrap">\((\axe)\),</span>
<p>le point \(\ptdep[1]\) a pour image le point <span class="nowrap">\(\ptar[1]\),</span></p>
<p>le point \(\ptdep[2]\) a pour image le point <span class="nowrap">\(\ptar[2]\),</span></p>
<p>donc l'image du segment \([\ptdep[1]\ptdep[2]]\) est le segment <span class="nowrap">\([\ptar[1]\ptar[2]]\).</span></p>}
#endif
#if defined TARGET_symcen6
\text{name_solution=Par la symétrie de centre O,
<p>le point \(\tdep[1]\) a pour image le point <span class="nowrap">\(\tar[1]\),</span></p>
le point \(\tdep[2]\) a pour image le point <span class="nowrap">\(\tar[2]\),</span>
<p>le point \(\tdep[3]\) a pour image le point <span class="nowrap">\(\tar[3]\),</span></p>
<p>le point \(\tdep[4]\) a pour image le point <span class="nowrap">\(\tar[4]\),</span></p>
<p>le symétrique du quadrilatère \(\K\) est le quadrilatère <span class="nowrap">\(\quadrep[1]\).</span></p>}
#endif
#if defined TARGET_rota6
\text{name_solution=Par la rotation de centre O qui transforme le triangle \(\A[2]\) en triangle <span class="nowrap">\(\A[3]\),</span>
<p>l'image du point \(\ptA[1]\) est <span class="nowrap">\(\t[1]\),</span></p>
<p>l'image du point \(\ptA[2]\) est <span class="nowrap">\(\t[2]\),</span></p>
<p>l'image du point \(\ptA[3]\) est <span class="nowrap">\(\t[3]\),</span></p>
donc l'image du triangle \(\A[1]\) est le triangle <span class="nowrap">\(\trirep[1]\).</span>}
#endif
#if defined TARGET_trans2
\text{name_solution=Le quadrilatère \(\pt[1]\pt[2]\quest[1;2]\quest[1;1]\) est un parallélogramme donc la translation,
qui transforme le point \(\pt[1]\) en le point \(\pt[2]\)
transforme également le point \(\quest[1;1]\) en le point <span class="nowrap">\(\quest[1;2]\).</span>
</p>
<p>Le quadrilatère \(\pt[1]\pt[2]\quest[2;2]\quest[2;1]\) est un parallélogramme donc la translation,
qui transforme le point \(\pt[1]\) en le point \(\pt[2]\) transforme également
le point \(\quest[2;1]\) en le point <span class="nowrap">\(\quest[2;2]\).</span></p>
Le quadrilatère \(\pt[1]\pt[2]\quest[3;2]\quest[3;1]\) est un parallélogramme donc la translation,
qui transforme le point \(\pt[1]\) en le point \(\pt[2]\) transforme également le point
\(\quest[3;1]\) en le point <span class="nowrap">\(\quest[3;2]\).</span></p>
<p>Le quadrilatère \(\pt[1]\pt[2]\quest[4;2]\quest[4;1]\) est un parallélogramme donc la translation,
qui transforme le point \(\pt[1]\) en le point \(\pt[2]\) transforme également le point \(\quest[4;1]\)
en le point <span class="nowrap">\(\quest[4;2]\).</span></p>}
#endif
#if defined TARGET_trans1 || defined TARGET_trans2 || defined TARGET_trans3im || defined TARGET_trans3ant || defined TARGET_trans7
\text{name_hint=Une translation est une transformation géométrique qui correspond à l'idée intuitive de « glissement » d'un objet,
sans rotation, ni retournement, ni déformation de cet objet.
<p>Par exemple, la figure bleue est l'image de la figure rouge par la translation qui transforme le point \(A\) en <span class="nowrap">\(A^{'}\).</span></p>
<div class="wimscenter"><img src="\imagedir/hinttrans2.png" alt="Translaté de cocotte"></div>
<p>L'image de \(A\) est \(A^{'}\), l'image de \(C\) est \(C^{'}\), l'image de \(H\) est \(H^{'}\).</p>
Les quadrilatères \(A A^{'}C^{'}C\) et \(A A^{'}H^{'}H\) sont des parallélogrammes.}
#endif
#if defined TARGET_associerapportsitu
\text{name_hint=On considère une homothétie de rapport \(k\) où \(k\) désigne un nombre non nul.
<ul>
  <li>Si \(k > 1\) alors l'homothétie est un agrandissement avec inversion de figures.</li>
  <li>Si \(0 < k < 1\) alors l'homothétie est une réduction sans inversion de figures.</li>
  <li>Si \(-1 < k < 0\) alors l'homothétie est une réduction avec inversion de figures.</li>
  <li>Si \(k< -1\) alors l'homothétie est un agrandissement avec inversion de figures.</li>
</ul>}
#endif
#if defined TARGET_symax3
\text{name_solution=Par pliage le long de la droite <span class="nowrap">\((\axe[1])\),</span> le motif \(\K[1]\) se superpose au motif <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Le symétrique du motif \(\K[1]\) par rapport à la droite \((\axe[1])\) est le motif <span class="nowrap">\(\K[2]\).</span></p>}
#endif

#if defined TARGET_symcen3
\text{name_solution=Par demi-tour autour du point <span class="nowrap">\(G\),</span> le motif \(\K[1]\) se superpose au motif <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Le symétrique du motif \(\K[1]\) par rapport au point \(G\) est le motif <span class="nowrap">\(\K[2]\).</span></p>}
#endif
#if defined TARGET_trans3im
\text{name_solution=Le point \(\D\) est l'image du point \(\C\) par la translation qui transforme \don[11].
<p>Cela signifie que le quadrilatère \(\para\) est un parallélogramme.</p>
On place ainsi le point \(\D\) de sorte que \(\para\) soit un parallélogramme.}
#endif
#if defined TARGET_trans3ant
\text{name_solution=Le point \(\C\) est l'antécédent du point \(\D\) par la translation qui transforme \don[11] signifie que le point \(\D) est l'image du point \(\C\) par cette même translation.
<p>Ainsi le quadrilatère \(\para\) est un parallélogramme.</p>
On place le point \(\C\) de sorte que \(\para\) soit un parallélogramme.}
#endif
#if defined TARGET_symax4
\text{name_solution=Rappel&nbsp;: Si un point est situé sur l'axe de la symétrie alors il est son propre symétrique.
<p>Par pliage le long de la droite <span class="nowrap">\((\axe[1])\),</span></p>}
\text{name_solution1=le point \(\k[1]\) se superpose au point <span class="nowrap">\(\k[4]\),</span>
              <p>le point \(\k[2]\) se superpose au point <span class="nowrap">\(\k[5]\),</span></p>
              le point \(\k[3]\) se superpose au point <span class="nowrap">\(\k[6]\),</span>
              <p>donc, par la symétrie d'axe <span class="nowrap">\((\axe[1])\),</span> l'image du triangle \(\k[1]\k[2]\k[3]\) est <span class="nowrap">\(\k[4]\k[5]\k[6]\).</span></p>}
\text{name_solution2=le point \(\k[4]\) se superpose au point <span class="nowrap">\(\k[1]\),</span>
              <p>le point \(\k[5]\) se superpose au point <span class="nowrap">\(\k[2]\),</span></p>
              le point \(\k[6]\) se superpose au point <span class="nowrap">\(\k[3]\),</span>
              <p>donc, par la symétrie d'axe <span class="nowrap">\((\axe[1])\),</span> l'image du triangle \(\k[4]\k[5]\k[6]\)
              est <span class="nowrap">\(\k[1]\k[2]\k[3]\).</span></p>}
#endif

#if defined TARGET_symcen4
\text{name_solution=Par symétrie de centre <span class="nowrap">\(M\),</span>}
\text{name_solution1=<p>l'image du point \(\k[1]\) est le point <span class="nowrap">\(\k[4]\),</span></p>
              <p>l'image du point \(\k[2]\) est le point <span class="nowrap">\(\k[5]\),</span></p>
              <p>l'image du point \(\k[3]\) est le point <span class="nowrap">\(\k[6]\),</span></p>
              donc l'image du triangle \(\k[1]\k[2]\k[3]\) est <span class="nowrap">\(\k[4]\k[5]\k[6]\).</span>}
\text{name_solution2=<p>l'image du point \(\k[4]\) est le point <span class="nowrap">\(\k[1]\),</span></p>
              <p>l'image du point \(\k[5]\) est le point <span class="nowrap">\(\k[2]\),</span></p>
              <p>l'image du point \(\k[6]\) est le point <span class="nowrap">\(\k[3]\),</span></p>
              donc l'image du triangle \(\k[4]\k[5]\k[6]\) est <span class="nowrap">\(\k[1]\k[2]\k[3]\).</span>}
#endif
#if defined TARGET_rota4
\text{name_solution=Par la rotation de centre \(M\) et d'angle \(90^{\circ}\) dans le sens \sens,
<p>l'image de \(\datatri[\ch;1]\) est <span class="nowrap">\(\trirep1\),</span></p>
<p>l'image de \(\datatri[\ch;2]\) est <span class="nowrap">\(\trirep2\),</span></p>
<p>l'image de \(\datatri[\ch;3]\) est \(\trirep3\)</p>
donc l'image du triangle \(\tridep\) est <span class="nowrap">\(\tri1[1]\).</span>}
#endif
#if defined TARGET_homo3
\text{name_solution=1. Il n'y a pas inversion de figures, le rapport cherché est positif.
<p>De plus, \(O\choix1[1]=\choix1[2]\times OA\) donc le rapport de l'homothétie de centre \(O\) qui permet de passer de la figure \(A\) à la figure \(\choix1[1]\) vaut <span class="nowrap">\(\choix1[2]\).</span></p>
<p>2. \(\frac{\num}{\denum} \times O\choix2[1]=O\choix2[2]\) donc l'homothétie de centre O et de rapport \(\frac{\num}{\denum}\) permet de passer de la figure \(\choix2[1]\) à la figure <span class="nowrap">\(\choix2[2]\).</span></p>}
#endif