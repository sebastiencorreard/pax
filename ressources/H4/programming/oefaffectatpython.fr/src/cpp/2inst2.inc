\integer{ff=1}
\integer{fff=2}
\integer{nbinst=2}
\matrix{lr=r1,r2}
\text{list_var2=wims(listcomplement \nomvar in \list_var)}

\text{nomvar2=randitem(\list_var2)}

\text{enonce=Après avoir lu les instructions, déterminer la valeur finale des variables
 \(\nomvar\) et \(\nomvar2\).}

\integer{alea=randint(1..2)}

\text{ligne1=\aa}
\text{ligne2=\bb}
\text{ligne3=(\alea==1)?\nomvar=\nomvar2:\nomvar2=\nomvar}
\text{ligne4=(\alea==1)?\nomvar2=\nomvar:\nomvar=\nomvar2}

\text{code=\nomvar=\ligne1
\nomvar2=\ligne2
\ligne3
\ligne4}

\integer{resultatf=(\alea==1)?\bb:\aa}
\integer{resultatff=(\alea==1)?\bb:\aa}
