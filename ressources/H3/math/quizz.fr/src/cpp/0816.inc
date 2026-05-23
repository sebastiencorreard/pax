\title{Question 0816 Résolution de problème }
\keywords{mental_calculation,pbsolving,measurement,volume}

\integer{a=randint(2,3)} %%% nb de verres
\text{at=slib(numeration/ecriturelettre \a,fr)}
\real{contverre=random(15,20,25)}
\integer{reste=125-\a*\contverre}
\integer{t0816=\a*\contverre}
\real{rep=\reste}
\text{enonce=J'ouvre une bouteille de 1.25 L. Je remplis \at verres de \contverre cL.<br><strong>Combien de cL reste-t-il dans la bouteille &#63;</strong><br>Réponse &#58; }
\text{enonceb=cL}
\text{feedback=On a mis dans les verres \(\a \times \contverre\)cL\({}=\t0816\) cL. Reste à faire la soustraction.}
