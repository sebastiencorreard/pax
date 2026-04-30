\integer{ff=1}
\integer{nbinst=4}

\integer{bb=randitem(+1,-1)*randint(2..5)}
\integer{aa=\bb*randint(2..9)}
\integer{cc=randitem(+1,-1)*randint(2..9)}
\integer{dd=randitem(+1,-1)*randint(2..4)}

\text{ligne1=\nomvar=\aa}
\text{ligne2=pari(\nomvar/\bb)}
\text{ligne3=pari(\nomvar+\cc)}
\text{ligne4=\dd*\nomvar}

\text{code=\ligne1
\nomvar=\ligne2
\nomvar=\ligne3
\nomvar=\ligne4}

\integer{resultatf=(\aa/\bb+\cc)*\dd}
