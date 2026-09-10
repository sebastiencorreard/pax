target=cvgmono
\title{Théorème de convergence monotone}
#include "author.inc"

\format{html}

\integer{a=randint(-10..10)}
\text{limueq=La suite est convergente et \(\displaystyle\lim u_n=\a)}
\text{limuleq=La suite est convergente et \(\displaystyle\lim u_n \leq \a)}
\text{limugeq=La suite est convergente et \(\displaystyle\lim u_n \geq \a)}
\text{limule=La suite est convergente et \(\displaystyle\lim u_n < \a)}
\text{limuge=La suite est convergente et \(\displaystyle\lim u_n > \a)}
\text{limupinf=La suite tend vers \(\ +\infty)}
\text{limuminf=La suite tend vers \(\ -\infty)}
\text{rien=On ne peut rien dire}
\text{imp=Il n'existe pas de suites vérifiant les propriétés de l'énoncé.}

\text{data=La suite \((u_n)) est croissante et non majorée,1,\limupinf,\limuminf,
La suite \((u_n)) est décroissante et non majorée,200,\limupinf,\limuminf,
La suite \((u_n)) est décroissante et non minorée,2,\limupinf,\limuminf,
La suite \((u_n)) est croissante et non minorée,200,\limupinf,\limuminf,
La suite \((u_n)) est décroissante et minorée par \a,2,\limueq,\limugeq,\limuge,\limupinf,
La suite \((u_n)) est croissante et majorée par \a,2,\limueq,\limuleq,\limule,\limuminf,
La suite \((u_n)) est croissante et minorée par \a,100,\limueq,\limugeq,\limuge,\limupinf,
La suite \((u_n)) est décroissante et majorée par \a,100,\limueq,\limuleq,\limule,\limuminf,
}

\integer{i=randint(1..rows(\data))}
\text{cedata=row(\i,\data)}
\integer{nr=items(\cedata)-1}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\text{lstrep=item(3..\nr,\cedata),\rien,\imp}
\integer{rep=\rep=200?\nr}
\integer{rep=\rep=100?\nr-1}


\statement{<p>\quest.</p>
Que peut-on dire de cette suite ?
<ul class="wims_nopuce spacer">
\for{j=1 to \nr}{
  <li>\embed{reply1,\j}</li>
 }
 </ul>
}
\answer{Conclusion}{\rep;\lstrep}{type=radio}
