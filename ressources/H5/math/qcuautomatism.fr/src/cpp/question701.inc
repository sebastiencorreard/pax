\title{Question 701 S Equation et moyenne bis}
\keywords{quizz,equations,literal_calculation,mean}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }
%%% a mettre aussi en q205.inc
%%% MB %%%%
\text{notes=randomrow(10,8,16;10,7,15;11,8,16;10,9,15;10,8,16)}
\integer{m=\notes[3]-1}
\real{sol=\m*3-(\notes[1]+\notes[2]*2)}
\text{x=randomitem(x,c)}
\text{enonce=Voici une série de notes avec les coefficients associés&nbsp;&#58;
<div class="wimscenter wims_scrollable">
<table class="wimsborder">
  <tr>
    <th>Notes</th>
    <th>\notes[1]</th>
    <th>\notes[2]</th>
    <th>\notes[3]</th>
    </tr>
  <tr>
    <td>Coefficient</td>
    <td>1</td>
    <td>2</td>
    <td>\(\x\)</td>
  </tr>
</table>
</div>
On note \(&#119898;\) la moyenne de cette série. Que doit valoir \(\x\) pour que \(m=\m\)&nbsp;&#63;}
\text{imposs=Impossible} %%% jamais le cas avec les exemples
\text{aucune=Aucune des solutions proposées.}
\text{good=\sol>20?\imposs:\sol}
\text{good=\(\x=\good\)}
\text{bad1=\sol>20?16:\imposs}
\text{temp=shuffle(3,4,5)}
\text{bad2=\temp[1]}
\text{bad3=\temp[2]}
\text{bads=\(\x=\bad1\),\(\x =\bad2\),\(\x =\bad3\)}
\text{feedback=La bonne réponse est <b>"\good"</b>. On peut résoudre <span class="nowrap">\(\frac{\notes[1]+2 \times \notes[2]+\notes[3]\times \x}{1+2+\x}=\m\).</span><br>Puis interpréter le résultat.}
