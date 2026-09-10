target=loibinom1

#include "header.inc"

2011-08-18 (S. Lemaire) correction de l'interversion entre x et y.
           Changement de l'intervalle de variations des paramètres n et x.

\precision{100}

#include "lang_titles.inc"

\integer{n=randint(3..5)}
\integer{x=randint(1..5)}
\integer{y=6-\x}
\rational{p=\x/6}
\rational{q=\y/6}
\text{v=}
\rational{totalv=0}
\for{k=0 to \n}{
  \rational{val=binomial(\n,\k)*(\p)^\k*(\q)^(\n-\k)}
  \text{v=wims(append item \val to \v)}
  \rational{totalv=\totalv+\val}
}
\rational{v0=\p^2}
\rational{v2=\q^2}
\rational{v1=1-\v0-\v2}
\text{mstep=wims(makelist r x for x=1 to \n+1)}
\text{mstep=wims(nospace \mstep)}
\steps{\mstep}

#include "lang.inc"

\statement{<p>
\name_statement1 \if{\x=1}{\name_statement_list[1]}{\x \name_statement_list[2]} \name_and \if{\y=1}{\name_statement_list[3].}{\y \name_statement_list[4].}
\name_statement2[1] \n \name_statement2[2], \name_statement2[3],
\name_statement2[4] \(X) \name_statement2[5] <span class="wims_emph">"\name_variable"</span>.</p>
<p>\name_question \(X).</p>
<table class="wimscenter wimsborder"><tr><th>\(i)</th>
\for{i=0 to \n}
 {<th>\i</th>}
</tr>
<tr><th>\(P( X = i )\)</th>
\for{j=1 to \n+1}{<td>\embed{reply\j,8}</td>}
</tr>
</table>
<div class="wims_instruction">\name_consig</div>
}
\answer{\(P(X=0))}{\v[1]}{type=numexp}{option=noreduction}
\answer{\(P(X=1))}{\v[2]}{type=numexp}{option=noreduction}
\answer{\(P(X=2))}{\v[3]}{type=numexp}{option=noreduction}
\answer{\(P(X=3))}{\v[4]}{type=numexp}{option=noreduction}
\answer{\(P(X=4))}{\v[5]}{type=numexp}{option=noreduction}
\answer{\(P(X=5))}{\v[6]}{type=numexp}{option=noreduction}
\answer{\(P(X=6))}{\v[7]}{type=numexp}{option=noreduction}
\answer{\(P(X=7))}{\v[8]}{type=numexp}{option=noreduction}
\answer{\(P(X=8))}{\v[9]}{type=numexp}{option=noreduction}

\solution{\name_solution1 \(\frac{\x}{6}) \name_solution2 \(\frac{\y}{6}).<p>
\name_solution3:
<ul>
<li> \name_solution4 \((\frac{\y}{6})^2) \name_solution5;</li>
<li> \name_solution4 \((\frac{\x}{6})^2) \name_solution6;</li>
<li> \name_solution4 \(1-(\frac{\x}{6})^2-(\frac{\y}{6})^2) \name_solution7.</li>
</ul>}
