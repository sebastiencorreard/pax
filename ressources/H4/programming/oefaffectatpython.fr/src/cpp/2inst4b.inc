\text{list_var2=wims(listcomplement \nomvar in \list_var)}

\text{nomvar2=randitem(\list_var2)}

\text{enonce=Après avoir lu les instructions, déterminer la valeur finale des variables
 \(\nomvar\) et \(\nomvar2\).}

\text{alea_op=+,-,*}
\text{op1=randitem(\alea_op)}
\text{op2=randitem(\alea_op)}


\text{ligne1=\aa}
\text{ligne2=\bb}
\text{ligne3= wims(nospace \nomvar \op1 \nomvar2)}
\text{ligne4=wims(nospace \nomvar \op2 \nomvar2)}

\integer{alea=randint(1..2)}

\text{ligne33=(\alea==1)?\nomvar=\ligne3:\nomvar2=\ligne4}
\text{ligne44=(\alea==1)?\nomvar2=\ligne4:\nomvar=\ligne3}


\text{ll34=\nomvar=\ligne3
\nomvar2=\ligne4}

\text{code=\nomvar=\ligne1
\nomvar2=\ligne2
\ligne33
\ligne44}

\integer{resultatf=(\alea==1)?\aa \op1 \bb:\aa \op2 \bb}
\integer{resultatff=(\alea==1)?\resultatf \op2 \bb:\resultatf \op1 \aa}

\text{ligne=\ligne1,\ligne2,\ligne3,\ligne4}

\text{nbchar=}
\for{kj=1 to \nbinst}{\integer{u=wims(charcnt \ligne[\kj])+3}
\text{nbchar=wims(append item \u to \nbchar)}}

\text{llpas=1,1,1,\nbchar[1];2,1,2,\nbchar[2];3,1,3,\nbchar[3];4,1,4,\nbchar[4]}

\integer{resultat1=\aa}
\integer{resultat2=\aa}
\integer{resultat3=(\alea==1)?\resultatf:\aa}
\integer{resultat4=(\alea==1)?\resultatf:\resultatff}
\text{resultat5=None}
\integer{resultat6=\bb}
\integer{resultat7=(\alea==1)?\bb:\resultatf}
\integer{resultat8=(\alea==1)?\resultatff:\resultatf}

\integer{resultatf=(\alea==2)?\resultat4}
\integer{resultatff=(\alea==2)?\resultat8}
