\title{Question 206 T Isoler une variable}
\keywords{quizz,literal_calculation}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDUSCOL en juin 2025 }
\integer{q=randomitem(1,2,3,4)}
\if{\q=1}{\text{enon1=\(\mathcal{C} = (1 + t)^2\)}
  \text{good=\(t = \sqrt{\mathcal{C}} - 1 \)}
  \text{bads=\(t = 1-\sqrt{\mathcal{C}} \),\(t = \sqrt{\mathcal{C} - 1} \),\(t = \sqrt{1-\mathcal{C} } \)}
  \text{feedback=La bonne réponse est \good.<br> Puisque \(\mathcal{C} = (1 + t)^2\) un calcul intermédiaire est <span class="nowrap">\( \sqrt{\mathcal{C}}=t + 1 \).</span>}}
\if{\q=2}{\text{enon1=\(\mathcal{C} = (1 - t)^2\)}
  \text{good=\(t = 1-\sqrt{\mathcal{C}}  \)}
  \text{bads=\(t = \sqrt{\mathcal{C}}+1 \),\(t = \sqrt{1-\mathcal{C} } \),\(t = \sqrt{\mathcal{C}+1 } \)}
  \text{feedback=La bonne réponse est \good.<br> Puisque \good un calcul intermédiaire est <span class="nowrap">\( \sqrt{\mathcal{C}}=1-t \).</span>}}
\if{\q=3}{\text{enon1=\(\mathcal{C} = 1 - t^2\)}
  \text{good=\(t = \sqrt{1-\mathcal{C}} \)}
  \text{bads=\(t = 1-\sqrt{\mathcal{C}} \),\(t = \sqrt{\mathcal{C} - 1} \),\(t = \sqrt{\mathcal{C}}+1  \)}
  \text{feedback=La bonne réponse est \good.<br> Puisque \good un calcul intermédiaire est <span class="nowrap">\( t^2=1-\mathcal{C} \).</span>}}
\if{\q=4}{\text{enon1=\(\mathcal{C} = 1 + t^2\)}
  \text{good=\(t = \sqrt{\mathcal{C}-1} \)}
  \text{bads=\(t = 1-\sqrt{\mathcal{C}} \),\(t = \sqrt{\mathcal{C} + 1} \),\(t = \sqrt{\mathcal{C}}+1  \)}
  \text{feedback=La bonne réponse est \good.<br> Puisque \good un calcul intermédiaire est <span class="nowrap">\( \mathcal{C}-1=t^2\).</span>}}



\text{enonce=On considère la relation \enon1. On cherche à isoler la variable <span class="nowrap">\(t\).</span> On a&nbsp;&#58;}
