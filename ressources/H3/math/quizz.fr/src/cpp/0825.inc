\title{Question 0825 Médiane d'une liste}
\keywords{mental_calculation,median}

\text{list0=simplify(8-random(0.5,1.5)),random(8,9),simplify(9+random(0.5,1.5)),simplify(9+random(1,2)),simplify(9+random(4,3))}
\text{list=shuffle(\list0)}
\real{rep=slib(stat/median \list)}
\real{rep0825=\rep}

\text{enonce0=<table class="wims_noborder"><tr><th>\list[1]</th><th>\list[2]</th><th>\list[3]</th><th>\list[4]</th><th>\list[5]</th></tr></table>}
\text{enonce=Quelle est la médiane de ces 5 notes &#63; <br> \enonce0 <br> Réponse &#58;}
\text{enonceb=}
%%%% feedback %%%%
\text{feedback0=<table class="wims_noborder"><tr><td>\list0[1]</td><td>\list0[2]</td><td>\list0[3]</td><td>\list0[4]</td><td>\list0[5]</td></tr></table>}

\text{feedback=Ci-dessous la liste par ordre croissant. \feedback0 La médiane est bien \rep0825.}
