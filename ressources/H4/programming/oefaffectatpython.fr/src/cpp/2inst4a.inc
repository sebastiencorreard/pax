2inst4a.inc
%%%%%%%%%%%%%%
Debug
#######################
\if{\alea==2}{
\text{tmp=\nomvar}
\text{nomvar=\nomvar2}
\text{nomvar2=\tmp}
}
#########################

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

%%%%%%%%%%%%%%%%%%%%%%%
