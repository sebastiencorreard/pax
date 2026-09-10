#if defined TARGET_trigo
\text{name_instruction=Calculer les réels \(\expr) et \( \expr2) sachant que
\(\sincosx(x) = \a), que \(\sincosy(y) = \b),
que \(x) est compris entre \(\ux) et \(\vx) et que
\(y) est compris entre \(\uy) et \(\vy).}
\text{name_feed1=Votre réponse est vraiment impossible,
  elle doit être comprise entre -1 et 1.}
\text{name_feed2=Voici les points \(A), \(B), \(C), \(D) de représentation complexe}
\text{name_feed3=En <span style="color:red">rouge</span>,vous voyez la droite sur laquelle vous
  prétendez que se trouve}
\text{name_feed4=En <span style="color:magenta">magenta</span>,
  vous voyez la droite sur laquelle vous prétendez que se trouve}
#endif
#if defined TARGET_trigo3
\text{name_instruction=Trouver toutes les solutions de l'équation,
qui se trouvent dans l'intervalle ,en les mettant dans l'ordre croissant.}
\text{name_solution=Solutions}
\text{name_hint=Voici la courbe de la fonction, sur l'intervalle}
\text{name_feed=Une au moins de vos réponses n'est pas dans l'intervalle demandé.}
#endif
#if defined TARGET_trigo2
\text{name_instruction=Soit l'équation }
\text{name_instruction1=Combien a-t-elle de solutions dans l'intervalle}
\text{name_instruction2=Les \nombre solutions dans l'intervalle [0 , \(2*pi)] sont
  de la forme}
\matrix{name_instruction21=avec \(k) parcourant l'ensemble
  ou de la forme
  avec \(k) parcourant l'ensemble}
\matrix{name_inst=Écrire \(k) sous la forme d'un rationnel si cela en est un.
  Vous devez ainsi donner toutes les solutions une et une seule fois.}
\text{name_cond=L'ensemble des solutions est le bon}
\text{name_answer=Nombre}
#endif
#if defined TARGET_trigo1
\text{name_instruction=Combien l'équation,a-t-elle de solutions dans l'intervalle}
\text{name_answer=Nombre de solutions}
#endif
#if defined TARGET_planim
\text{name_instruction=Un planimètre est formé de deux barres de même longueur
  1 liées par une articulation.  L'extrémité orange \(O)  de l'une
  est fixée tandis que la deuxième extrémité rouge \(M) de l'autre
  est libre de se déplacer et munie d'une pointe&nbsp;}
\text{name_question1=Si le point \(M) est de coordonnées}
\text{name_question2=calculer les coordonnées
  du point d'articulation bleu \(N).
  Calculer l'angle \(\theta_1) que fait la branche partant de \(O) avec l'axe
  \(O x) et l'angle \(\theta_2) que fait la deuxième branche avec la première.
}
\text{name_inst=On mesurera \(\theta_1) entre 0 et \(2 \pi) et \(\theta_2) entre
 \(0) et \(\ \pi) (en radians).}
\text{name_hint=Passer dans le plan complexe.}
#endif
#if defined TARGET_phase
\text{name_instruction=Mettre la fonction,sous la forme,avec}
\text{name_hint=Que vaut la partie réelle de }
\text{name_cond=Vous avez trouvé}
\text{name_feed=est le module du nombre complexe \(a - i*b) et \(u) son argument. Ici,}
#endif
#if defined TARGET_compose
\text{name_instruction=Trouvez l'amplitude \(A > 0) et la phase \(p) de la fonction
  trigonométrique}
\text{name_instruction2=de sorte que}
\text{name_condition=La réponse est bonne}
\text{name_answer=L'amplitude,La phase \(p) (entre 0 et \(2*pi))}
#endif
#if defined TARGET_decomp1 || defined TARGET_decomp2
\text{name_instruction=Trouvez les valeurs de \(a) et \(b) telles que}
#endif
