\title{Question T1115 Lecture graphique d'image}
\keywords{mental_calculation,functions,coordinates}

#include "T11courbe01.inc"

\text{fig15=<img src="\courbe01" alt="">}
\integer{choix15=randint(1..3)}
\integer{x15=(\choix15<3)? \valeurs[\choix15;2]:\valeurs[\choix15;4]}
\integer{temp15=\valeurs[\choix15;1]}
\text{rep=\temp15}


\text{enonce=On considère une fonction \(f) définie sur \(\mathbb{R}) dont la courbe est dessinée ci-dessous. <br><table><tr><td>\fig15 </td><td> L'image de \(\x15) par \(f) est : <br>  }
\text{enonceb= </td></tr></table>}
\text{feedback=On rappelle que l'image de \(\x15) est l'ordonnée du point de la courbe d'abscisse \(\x15).  }
\integer{size=6}
