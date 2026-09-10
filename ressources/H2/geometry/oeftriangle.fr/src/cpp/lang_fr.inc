#if defined TARGET_centers
\text{always=toujours à l'intérieur}
\text{depend=parfois à l'extérieur}
\text{never =toujours à l'extérieur}
\matrix{data=
  médiatrices des côtés, le centre du cercle circonscrit, \depend, médiatrices, centre circonscrit
  hauteurs, l'orthocentre, \depend
  bissectrices intérieures des angles, le centre du cercle inscrit, \always, bissectrices , centre inscrit
  médianes, le centre de gravité, \always, , centre de gravité
}
\text{bad=triangle angle côtés périmètre sommet point intersection droite}
\matrix{name_instruction=Complétez le texte&nbsp;
  Le point d'intersection des trois
  d'un triangle est
  de ce triangle, qui est
  du triangle}
#endif
#if defined TARGET_typesb || defined TARGET_types
\text{right=C'est un triangle rectangle}
\text{acute=C'est un triangle aigu}
\text{obtuse=C'est un triangle obtus}
\text{non=Ce n'est pas un triangle}
# if defined TARGET_typesb
\text{name_instruction=Quel est le type du ``triangle'' \(A B C\) (s'il existe) vérifiant}
\text{name_choice=Le triangle }
\text{name_peri=périmètre}
# endif
# if defined TARGET_types
\text{name_instruction=Quel est le type du ``triangle'' \(A B C\) (s'il existe) dont les 3 côtés vérifient}
\text{name_choice=Le triangle }
# endif
#endif
#if defined TARGET_twosides
\text{name_instruction=Combien y a-t-il de triangles \(A B C\) avec \(A C\) entier et}
\text{name_sol=Pour que \(A B C\) soit un triangle, doit être au moins,et au plus}
\text{name_answer=Nombre de triangles}
#endif
#if defined TARGET_twosidesb
\text{name_acute=aigus, obtus}
\text{ans1=Pour que \(A B C\) soit un triangle aigu, \(A C^2\) doit être plus grand que
  \(\long^2-\short^2=\q2\) et plus petit que
  \(A B^2+B C^2=\q1\), par le théorème de Pythagore.}
\text{ans2=Pour que \(A B C\) soit un triangle, \(A C\) doit être au moins
  \max-\min+1 et au plus \ab+\bc-1. <p>
  Quand \long est le côté le plus long du triangle, \(A C\) doit être plus petit que \sq2
  par le théorème de Pythagore. Quand \(A C\) est le côté le plus long, il doit être
  plus grand que \sq1, encore par le théorème de Pythagore. </p><p>
  Donc, il y a \n3 (resp. \n2) triangles obtus ayant des côtés de longueur entière
  et dont le côté le plus long est \long (resp. \(A C\)).</p>}
\matrix{name_instruction=Combien y a-t-il de triangles
  \(A B C\), avec \(A C\) entier et}
\text{name_answer=Nombre de triangles}
#endif
