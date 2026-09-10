target=taxi
\title{J. Couleur de taxi}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\keywords{events,modelling,probability}
\description{Exercice de modélisation}
\observation{Application de la formule de Bayes}
\integer{pV=randint(60..90)}
\integer{pB=100-\pV}
\integer{pJ=randint(70..90)}
\integer{c=random(1,2)}
\if{\c=1}{\integer{pC=\pB}\integer{pnC=\pV}}
         {\integer{pC=\pV}\integer{pnC=\pB}}
\integer{pF=100-\pJ}
\rational{p=\pC*\pJ/(\pC*\pJ+\pnC*\pF)}
\text{solarr=slib(text/approximation \p,3)} 
\text{sol=\solarr[3]} 
\text{name_coul=Bleu,Vert}
\text{coul=\name_coul[\c]}
\text{ncoul=\name_coul[3-\c]}
\text{name_context1=  Un taxi est impliqué dans un carambolage de nuit. 
  Deux compagnies de taxi, les Verts et les Bleus, opèrent en ville.}
\text{name_context2=  On dispose des informations suivantes&nbsp;}
\text{info1= \(\pV \%\) des taxis en ville sont Verts et \(\pB \%\) sont Bleus&nbsp;}
\text{info2= Un témoin a identifié le taxi responsable comme \coul.}
\text{info3=Le tribunal a testé la fiabilité des témoignages dans ce type
  de circonstances (accident de nuit) et en a conclu que
  les témoins identifient correctement les couleurs dans \(\pJ \%\) des cas
  et se trompent dans \(\pF \%\) des cas. }
\text{name_quest=Si on suppose que le risque qu'un taxi cause un carambolage la nuit est 
 le même pour tous les taxis, quelle est la probabilité pour que le taxi impliqué dans l'accident soit un \coul&nbsp;}
\text{name_consig=Donner la valeur exacte sous forme d'une fraction.}
\text{name_but=On cherche}
\text{name_proba=la probabilité pour que }
\text{name_condit=sachant que}
\text{name_is=est}
\text{name_event1= le taxi soit}
\text{name_event2= le témoin a identifié un taxi}
\text{name_sol1=Le témoin identifie le taxi impliqué dans le carambolage comme un}
\text{name_sol2= et il ne se trompe pas avec une probabilité de}
\text{name_sol3=et il se trompe avec une probabilité de}
\text{name_donc=Donc}
\text{name_and=et} 
\text{but= \name_proba \name_event1 \coul \name_condit \name_event2 \coul}
\text{name_data=D'après l'énoncé}
\text{name_data1=si un taxi est impliqué dans un carambolage dans cette ville et si on ne dispose pas d'autres informations alors   
 la probabilité que cela soit un}
\text{name_data2=  le témoin identifie le taxi impliqué dans le carambolage comme un}
\text{name_data3=c'est le cas est égale à} 
\text{name_data4=alors qu'il est en fait}
\text{name_deduc=De ces informations, on déduit que}
\statement{<p>
  \name_context1
</p>
  \name_context2:
  <ul><li>
 \info1;
</li><li>
 \info2
</li></ul>
 \info3
<div class="wims_question">
 <label for="reply1"> \name_quest?</label>
<div class="wimscenter">\embed{r1,7}</div>
<div class="wims_instruction">\name_consig</div>
</div>
}
\answer{}{\p}{type=numexp}
\solution{\name_but 
\but.<br/>
\name_data,
<ul><li> \name_data1 \coul \name_is \(\pC/100\);
</li><li> 
 \name_proba \name_data2 \coul \name_condit \name_data3 \(\pJ/100\);
</li><li>\name_proba \name_data2  \coul \name_data4 \ncoul \name_is  \(\pF/100\).</li></ul>
\name_deduc
<ul><li>
\name_sol1 \coul \name_sol2 \(\frac{\pC}{100}\times \frac{\pJ}{100}\).
</li><li>
\name_sol1 \coul \name_sol3 \(\frac{\pnC}{100}\times \frac{\pF}{100}\).
</li></ul>
\name_donc, \name_proba \name_data2 \coul \name_is
<div class="wimscenter">
\(\frac{\pC}{100}\times \frac{\pJ}{100}+\frac{\pnC}{100}\times \frac{\pF}{100}\). 
</div>
\name_and \but \name_is
<div class="wimscenter">
\(\frac{\pC\times \pJ}{\pC\times\pJ + \pnC \times \pF}\simeq \sol\).
</div>
}
\latex{
 \begin{statement}
  \name_context1 \newline
  \name_context2
 \begin{itemize}
 \item \info1
 \item \info2
 \end{itemize}
 \info3 \newline
 \name_quest? (\emph{\name_consig})
 \end{statement}
 \begin{solution}
 \name_but 
 \but.\newline
 \name_data,
 \begin{itemize}
 \item \name_data1 \coul \name_is\(\pC/100\);
 \item \name_proba \name_data2 \coul \name_condit \name_data3 \(\pJ/100\);
 \item \name_proba \name_data2 \coul \name_data4 \ncoul \name_is  \(\pF/100\).
 \end{itemize}
 \name_deduc
 \begin{itemize}
 \item
 \name_sol1 \coul \name_sol2 \(\frac{\pC}{100}\times \frac{\pJ}{100}\).
 \item
 \name_sol1 \coul \name_sol3 \(\frac{\pnC}{100}\times \frac{\pF}{100}\).
 \end{itemize}
 \name_donc, \name_proba \name_data2 \coul \name_is
 \[\frac{\pC}{100}\times \frac{\pJ}{100}+\frac{\pnC}{100}\times \frac{\pF}{100}.\] 
 \name_and \but \name_is
 \[\frac{\pC\times \pJ}{\pC\times\pJ + \pnC \times \pF}\simeq \sol.\]
 \end{solution}
}
