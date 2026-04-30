\text{ligne=\ligne1,\ligne2,\ligne3,\ligne4}

\text{nbchar=}
\for{kj=1 to \nbinst}{\integer{u=wims(charcnt \ligne[\kj])+3}
\text{nbchar=wims(append item \u to \nbchar)}}

\text{llpas=1,1,1,\nbchar[1];2,1,2,\nbchar[2];3,1,3,\nbchar[3];4,1,4,\nbchar[4]}

\integer{resultat1=\aa}
\integer{resultat2=\aa/\bb}
\integer{resultat3=\resultat2+\cc}
\integer{resultat4=\resultatf}
