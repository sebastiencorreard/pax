\title{Question 1222 Extremum sur un intervalle}
\keywords{mental_calculation,functions,affine_function,extremum}
\text{choix=random(minimale,maximale)}
\function{f=randint(1..10)+randint(-1,1)*randint(2..6)*x}
\function{ftxt=maxima(\f)}
\integer{a=randint(2..4)}
\integer{b=\a+randint(3..5)}
\integer{rep=\choix issametext minimale ? min(evalue(\f,x=\a),evalue(\f,x=\b)):max(evalue(\f,x=\a),evalue(\f,x=\b))}
%%%%% pour feedback %%%%%%
\text{var=evalue(\f,x=\a)<evalue(\f,x=\b)?croissante:décroissante}
\if{\var issametext croissante}{\integer{ant=\choix issametext minimale ? \a:\b} }
\if{\var issametext décroissante}{\integer{ant=\choix issametext minimale ? \b:\a} }
\text{enonce=Valeur \choix de \(\ftxt\) lorsque \(x \in [ \a; \b ]\).<br> Réponse &#58;}
\text{enonceb=}
\text{feedback=La fonction est \var. On cherche la valeur <b>\choix </b>, c'est donc l'image de \ant.}
