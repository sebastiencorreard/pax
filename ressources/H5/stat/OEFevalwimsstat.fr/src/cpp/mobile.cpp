target=mobile1 mobile2 mobile3 mobile4 mobile5
#include "author.inc"
#include "lang_titles.inc"
\text{mois=Janvier,Février,Mars,Avril,Mai,Juin,Juillet,Aôut,Septembre,Octobre,Novembre,Décembre}
\text{mab=Jan.,Fév.,Mars,Avril,Mai,Juin,Juil.,Août,Sept.,Oct.,Nov.,Déc.}
\text{tempbase=10,8,8,14,18,20,24,23,20,18,14,12}
\text{temp=}
\for{i=1 to 12}{
  \real{off=random(-1,-0.5,0,0.5,1)}
  \real{t=\tempbase[\i]+\off}
  \text{temp=wims(append item \t to \temp)}
}
\text{m3lst=&nbsp;,&nbsp;}
\for{j=2 to 11}{
  \rational{m=(\temp[\j-1]+\temp[\j]+\temp[\j+1])/3}
  \real{m=round(10*\m)/10}
  \text{m3lst=wims(append item \m to \m3lst)}
}
\text{m3lst=\m3lst,&nbsp;,&nbsp;}

\text{entete=<table class="wimscenter wimsborder">
<tr><th>Mois</th>
}
\for{j=1 to 12}{
  \text{entete=\entete<td> \mab[\j] </td>}
}
#if defined TARGET_mobile1
\integer{n=randint(10..20)}
\integer{n3=\n-2}
\integer{n5=\n-4}
\integer{n7=\n-6}

\statement{<p>
On considère une série statistiques comportant \n valeurs.</p>
Combien de valeurs comportent les séries de moyennes mobiles:
<ul>
<li> <label for="reply1">d'ordre 3:</label> \embed{reply1,4}</li>
<li> <label for="reply2">d'ordre 5:</label> \embed{reply2,4}</li>
<li> <label for="reply3">d'ordre 7:</label> \embed{reply3,4}</li>
</ul>
}
\answer{ordre 3}{\n3}{type=numeric}
\answer{ordre 5}{\n5}{type=numeric}
\answer{ordre 7}{\n7}{type=numeric}
#endif
#if defined TARGET_mobile2
\text{mois=Janvier,Février,Mars,Avril,Mai,Juin,Juillet,Aôut,Septembre,Octobre,Novembre,Décembre}
\text{mab=Jan.,Fév.,Mars,Avril,Mai,Juin,Juil.,Août,Sept.,Oct.,Nov.,Déc.}
\text{tempbase=10,8,8,14,18,20,24,23,20,18,14,12}
\text{temp=}
\for{i=1 to 12}{
  \real{off=random(-1,-0.5,0,0.5,1)}
  \real{t=\tempbase[\i]+\off}
  \text{temp=wims(append item \t to \temp)}
}
\integer{k1=randint(2..11)}
\integer{k2=randint(3..10)}
\rational{m3=(\temp[\k1-1]+\temp[\k1]+\temp[\k1+1])/3}
\rational{m5=(\temp[\k2-2]+\temp[\k2-1]+\temp[\k2]+\temp[\k2+1]+\temp[\k2+2])/5}
\text{entete=\entete</tr><tr><th> Température en ° </th>}

\statement{<p>
On a relevé les températures moyennes à Nice pendant l'année:
</p>
\entete
\for{k=1 to 12}{<td> \temp[\k] </td>}
</tr></table>
<ol>
<li> <label for="reply1">Quelle est la moyenne mobile d'ordre 3 de \mois[\k1] ?</label> \embed{reply1,4} </li>
<li> <label for="reply2">Quelle est la moyenne mobile d'ordre 5 de \mois[\k2] ?</label> \embed{reply2,4} </li>
</ol>
}
\answer{ordre 3 en \mois[\k1]}{\m3}{type=numexp}
\answer{ordre 5 en \mois[\k2]}{\m5}{type=numexp}

#endif
#if defined TARGET_mobile3
\text{m3lst=&nbsp;,&nbsp;}
\for{j=2 to 11}{
  \rational{m=(\temp[\j-1]+\temp[\j]+\temp[\j+1])/3}
  \real{m=round(10*\m)/10}
  \text{m3lst=wims(append item \m to \m3lst)}
}
\text{m3lst=\m3lst,&nbsp;,&nbsp;}
\text{enteteB=\entete</tr><tr><th> Moyenne mobile d'ordre 3 en ° </th>}
\text{entete=\entete</tr><tr><th> Température en ° </th>}
\text{tableau1=\enteteB}
\for{j=1 to 12}{
  \text{tableau1=\tableau1<td> \m3lst[\j+1] </td>}
}
\text{tableau1=\tableau1</tr></table>}
\text{tableau2=\enteteB}
\for{j=1 to 12}{
  \text{tableau2=\tableau2<td> \m3lst[\j] </td>}
}
\text{tableau2=\tableau2</tr></table>}
\text{tableau3=\enteteB}
\for{j=1 to 12}{
  \text{tableau3=\tableau3<td> \m3lst[\j+2] </td>}
}
\text{tableau3=\tableau3</tr></table>}
\integer{rep=randint(1..3)}
\integer{i=randint(1,2)}
\if{\rep=1}{
  \text{tab1=\tableau1}
  \text{tab2=\i=1?\tableau2:\tableau3}
  \text{tab3=\i=2?\tableau2:\tableau3}
}
\if{\rep=2}{
  \text{tab2=\tableau1}
  \text{tab1=\i=1?\tableau2:\tableau3}
  \text{tab3=\i=2?\tableau2:\tableau3}
}
\if{\rep=3}{
  \text{tab3=\tableau1}
  \text{tab1=\i=1?\tableau2:\tableau3}
  \text{tab2=\i=2?\tableau2:\tableau3}
}

\statement{<p>
On a relevé les températures moyennes à Nice pendant l'année:
</p>
\entete
\for{k=1 to 12}{<td> \temp[\k] </td>}
</tr></table>
Lequel des 3 tableaux suivants correspond-il à la série des moyennes mobiles d'ordre 3?
<div>
 \embed{reply1,1, \tab1}
 \embed{reply1,2, \tab2}
 \embed{reply1,3, \tab3}
</div>
}
\answer{tableau}{\rep;1,2,3}{type=radio}
#endif
#if defined TARGET_mobile4
\text{enteteB=\entete</tr><tr><th> Moyenne mobile d'ordre 3 en ° </th>}
\text{entete=\entete</tr><tr><th> Température en ° </th>}
\statement{<p>
On a relevé les températures moyennes à Nice pendant l'année :
</p>
\entete
\for{k=1 to 12}{<td>\temp[\k]</td>}
</tr></table>
<p>
Compléter le tableau des moyennes mobiles d'ordre 3 :
</p>
\enteteB
<td>&nbsp;</td>
\for{k=1 to 10}{
  <td>\embed{reply\k,4} </td>
}
<td>&nbsp;</td>
</tr></table>
}
\answer{MM3 \mab[2]}{\m3lst[3]}{type=numexp}
\answer{MM3 \mab[3]}{\m3lst[4]}{type=numexp}
\answer{MM3 \mab[4]}{\m3lst[5]}{type=numexp}
\answer{MM3 \mab[5]}{\m3lst[6]}{type=numexp}
\answer{MM3 \mab[6]}{\m3lst[7]}{type=numexp}
\answer{MM3 \mab[7]}{\m3lst[8]}{type=numexp}
\answer{MM3 \mab[8]}{\m3lst[9]}{type=numexp}
\answer{MM3 \mab[9]}{\m3lst[10]}{type=numexp}
\answer{MM3 \mab[10]}{\m3lst[11]}{type=numexp}
\answer{MM3 \mab[11]}{\m3lst[12]}{type=numexp}
#endif
#if defined TARGET_mobile5
\integer{cas=randint(1,2)}
\function{f=\cas=1?-0.1(x-11)^2+35:0.1(x-11)^2+15}
\text{mm3=}
\for{i=1 to 4}{
  \real{ca=evalue(\f,x=\i*2)}
  \text{mm3=wims(append item \ca to \mm3)}
}

\text{lstca=}
\integer{off=randint(2..5)}
\for{i=1 to 6}{
  \real{ca=evalue(\f,x=\i*2)}
  \integer{ca=\ca+(-1)^\i*\off*(6-\i)}
  \text{lstca=wims(append item \ca to \lstca)}
}

\text{lstca=}
\integer{off=randint(10..15)}
\integer{ca1=\mm3[1]+\off*randint(1,-1)}
\integer{ca2=\mm3[1]}
\integer{ca3=3*\mm3[1]-\ca2-\ca1}
\integer{ca4=3*\mm3[2]-\ca3-\ca2}
\integer{ca5=3*\mm3[3]-\ca4-\ca3}
\integer{ca6=3*\mm3[4]-\ca5-\ca4}
\text{lstca=\ca1,\mm3[1],\ca3,\ca4,\ca5,\ca6}
\for{i=1 to 6}{
  \real{ca=evalue(\f,x=\i*2)}
  \integer{ca=\ca+(-1)^\i*\off*(6-\i)}
  \text{lstca=wims(append item \ca to \lstca)}
}
\text{lstrep=Le CA semble en hausse,Le CA semble en baisse}
\text{m3lst=}
\for{j=2 to 5}{
  \rational{m=(\lstca[\j-1]+\lstca[\j]+\lstca[\j+1])/3}
  \real{m=round(10*\m)/10}
  \text{m3lst=wims(append item \m to \m3lst)}
}

\statement{
On considère le chiffre d'affaires réalisé par une entreprise sur
une période de 6 mois.
<table class="wimscenter wimsborder">
<tr><th>Mois</th>
\for{k=1 to 6}{<th> Mois \k </th>}
</tr><tr><th> CA en Milliers d'euros</th>
\for{k=1 to 6}{
  <td> \lstca[\k] </td>
}
</tr></table>
Compléter le tableau des moyennes mobiles d'ordre 3 (MM3):
<table class="wimscenter wimsborder">
<tr><th>Mois</th>
\for{k=1 to 6}{<th>Mois \k </th>}
</tr><tr><th>MM3</th>
<td> &nbsp;</td>
\for{k=1 to 4}{
 <td>\embed{reply\k,4} </td>
}
<td>&nbsp;</td>
</tr></table>
<div>
Peut-on alors dégager une tendance ?<br>
\embed{reply5,1}<br>
\embed{reply5,2}<br>
</div>
}
\answer{MM3 1}{\m3lst[1]}{type=numexp}
\answer{MM3 2}{\m3lst[2]}{type=numexp}
\answer{MM3 3}{\m3lst[3]}{type=numexp}
\answer{MM3 4}{\m3lst[4]}{type=numexp}
\answer{tendance}{\cas;\lstrep}{type=radio}
#endif
