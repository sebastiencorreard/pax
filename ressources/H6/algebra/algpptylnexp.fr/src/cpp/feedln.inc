  Voici une résolution détaillée de (I) : \(\ineq\) :
  <p>
#if defined TARGET_ineqln
  ln(\(\u)) existe si et seulement si
  \(\u > 0\), c'est-à-dire pour
  \(\x \symb1 \rep1\).
  </p><p>
  ln(\(\v)) existe à condition que \(\v > 0\),
  c'est-à-dire que \(\x \symb2 \rep2\).
  </p>
#endif
#if defined TARGET_ineqln1bis
  L'expression ln(\(\u)) est définie pour
  \({\utex > 0}), c'est-à-dire pour
  \(\x \symb1 \rep1\).
  </p><p>
  L'expression ln(\(\v)) est définie pour \({\vtex> 0}),
  c'est-à-dire \(\x \symb2 \rep2\).
#endif
  </p><p>
  Pour tout réel \(\x) vérifiant ces deux conditions, on peut ramener
  (I) à une inéquation du premier degré
  en appliquant la règle
  \(\ln(u) \symb \ln(v) \Longleftrightarrow u \symb v\),
  on obtient :
  </p><div class="wimscenter">
  (I) \(\Longleftrightarrow \utex \symb \vtex \Longleftrightarrow \m\x \symb \p
  \Longleftrightarrow \x \symb3 \rep3\).
</div>
Les réels \(\x\) solutions de (I) doivent donc vérifier les trois inégalités :
<div class="wimscenter">
  \(\x \symb1 \rep1\) et \(\x \symb2 \rep2\)
  et \(\x \symb3 \rep3\).
  </div>
  Chaque inégalité définit un intervalle,
  l'ensemble des solutions est l'intersection des
  trois intervalles.
#if defined TARGET_ineqln
<ul><li> \(\x \symb1 \rep1 \Longleftrightarrow \x \in I_1\) avec \(I_1\) = \def1
</li><li>\(\x \symb2 \rep2 \Longleftrightarrow \x \in I_2\) avec \(I_2\) = \def2
</li><li>\(\x \symb3 \rep3 \Longleftrightarrow \x \in I_3\) avec \(I_3\) = \def3
</li><li>\(\x\) solution de (I) si et seulement si \(\x\in I_1 \cap I_2 \cap I_3\).
</li></ul>
#endif
#if defined TARGET_ineqln1bis
<ul><li>\(\x\) vérifie la première inégalité si et seulement si
</li><li>\(\x\) appartient à \(I_1 =\) \def1, il vérifie la seconde
si et seulement s'il appartient à \(I_2 =\) \def2
et la troisième si et seulement s'il appartient à \(I_3 =\) \def3.
</li><li>L'ensemble des solutions est donc l'intersection des trois intervalles \( I_1 \cap I_2 \cap I_3\).
</li></ul>
#endif
