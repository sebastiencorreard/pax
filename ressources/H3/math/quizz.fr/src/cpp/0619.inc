\title{Question 0619 Nombre en mots}
\keywords{numeration}

\integer{choix19=randint(1,2)}
\text{mots=(\choix19==1)?millions,mille,cent:unités,dizaines,centaines}
\integer{c1=randint(1,2)}
\integer{a1=randint(2..8)}
\integer{a2=5*randint(3..14)}
\integer{c2=randint(1,2)}
\integer{a3=randint(2..9)}
\integer{a3=(\a3==\a1)? \a1+1:\a3}
%%%% MB %%%% écrire les ai en mots
\text{a1mot=slib(numeration/ecriturelettre \a1)}
\text{a2mot=slib(numeration/ecriturelettre \a2)}
\text{a3mot=slib(numeration/ecriturelettre \a3)}
%%%%%%%%%%

\if{\choix19==1}{
\text{n=(\c1==1)? \a1mot-millions-\a2mot-mille:\a1mot-millions-\a3mot-cents}
\integer{rep=(\c1==1)? \a1*1000000+\a2*1000:\a1*1000000+\a3*100}
}{
\text{n=(\c2==1)? \a1mot unités et \a3mot centaines:\a1mot dizaines et \a3mot centaines}
\integer{rep=(\c2==1)? \a1+\a3*100:\a1*10+\a3*100}
}

\text{enonce=Ecrire en chiffres, le nombre \n : }
\text{enonceb=}
\text{feedback=}
