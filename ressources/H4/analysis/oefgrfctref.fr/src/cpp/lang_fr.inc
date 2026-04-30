#if defined TARGET_grtrigo1 || defined TARGET_assgrsqrt || defined TARGET_assgrhyper || defined TARGET_assgrtrigo1 || defined TARGET_assgrtrigo2 || defined TARGET_assgrcarre || defined TARGET_assgrcube || defined TARGET_assgrfctref || defined TARGET_assgrfctref2
\text{name_enonce=Dans le plan muni d'un repère orthonormé \((O,i,j)\),
  associez son graphe à chacune des fonctions ci-dessous}
\text{name_answer=Correspondance graphe/fonction}
#endif
#if defined TARGET_chgrhyper || defined TARGET_chgrsqrt || defined TARGET_chgrcarre || defined TARGET_chgrcube || defined TARGET_chgrtrigo1 || defined TARGET_chgrtrigo2
\text{name_enonce=Dans le plan muni d'un repère orthonormé \((O,I,J)\), on considère la fonction
  réelle \(f) définie sur l'intervalle \(\ [-2,2]\) par
  XXXX. Indiquez dans la liste ci-dessous la courbe représentative de \(f).}
# if defined TARGET_chgrcarre
\text{name_sol=L'expression de \( f(x) \) est donnée sous forme canonique :
  \(f(x)=a\left(x-\alpha\right)^2+\beta\)<br>
  Rappel (propriétés) :
  <ul>
  <li>La droite d'équation \(x=\alpha\) est l'axe de symétrie de la parapole qui représente \(f\);
  <li>Si \(a>0\), la fonction \(f\) admet pour minimum \(\beta\), et il est atteint en \(x=\alpha\);
  <li>Si \(a<0\), la fonction \(f\) admet pour maximum \(\beta\), et il est atteint en \(x=\alpha\).
  </ul>
}
# endif
#endif
\text{name_graph=Graphe}
