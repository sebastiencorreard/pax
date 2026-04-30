\integer{ff=1}
\integer{fff=2}
\integer{nbinst=4}
\matrix{lr=r1,r2}
\text{list_var2=wims(listcomplement \nomvar in \list_var)}

\text{nomvar2=randitem(\list_var2)}

\text{enonce=Après avoir lu les instructions, déterminer la valeur finale des variables
 \(\nomvar\) et \(\nomvar2\).}

\text{ligne1=\aa}
\text{ligne2=\bb}
\text{ligne3=\nomvar*\nomvar2}
\text{ligne4=\nomvar+\nomvar2}

\integer{alea=randint(1..2)}

\text{ligne33=(\alea==1)?\nomvar=\ligne3:\nomvar2=\ligne4}
\text{ligne44=(\alea==1)?\nomvar2=\ligne4:\nomvar=\ligne3}


\text{ll34=\nomvar=\ligne3
\nomvar2=\ligne4}

\text{code=\nomvar=\ligne1
\nomvar2=\ligne2
\ligne33
\ligne44}

Debug
#######################
\if{\alea==2}{
\text{tmp=\nomvar}
\text{nomvar=\nomvar2}
\text{nomvar2=\tmp}
}
#########################
\integer{resultatf=(\alea==1)?\aa*\bb:\aa+\bb}
\integer{resultatff=(\alea==1)?\resultatf+\bb:\resultatf*\aa}
