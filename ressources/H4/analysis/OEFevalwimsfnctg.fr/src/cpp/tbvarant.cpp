target=tbvarant1 tbvarant2 tbvarant3 tbvarant4 tbvarant5
\author{Régine, Mangeard}
\email{regine@mangeard}
\format{html}
#define TITRE Nombre d'antécédents
#if defined TARGET_tbvarant1
# define NUM 1
#endif
#if defined TARGET_tbvarant3
# define NUM 3
#endif
#if defined TARGET_tbvarant4
# define NUM 4
#endif
#if defined TARGET_tbvarant2
# define NUM 2
# endif
#if defined TARGET_tbvarant5
# define NUM 5
#endif
\title{TITRE NUM}
\css{<style>
  table.tab_var {margin-left:auto;margin-right:auto;
   border:solid 1px black;}
  table.tab_var tr, table.tab_var td, table.tab_var th {
   padding:7pt;margin-top:10px; margin-bottom:10px;
   text-align:center; border-collapse:collapse; min-width:10pt;
   }
  table.tab_var th { border:solid 1px black}
  table.tab_var tr { border:solid 1px black}
</style>}

\text{lstrep=<,>,on ne peut pas savoir}
\text{xl=wims(makelist x for x=-10 to 10)}
\text{xl=shuffle(\xl)}
\text{xl=item(1..12,\xl)}
\text{xl=wims(sort numeric list \xl)}


\integer{sens=randint(1,2)}
#if defined TARGET_tbvarextr1
\integer{sens=1}
#endif
\text{monotone=\sens=1?\(\nearrow),\(\searrow):\(\searrow),\(\nearrow)}
\if{\sens=2}{
  \text{pos=top,bottom,top,bottom,top}
 }{
  \text{pos=bottom,top,bottom,top,bottom}
}
\integer{y1=randint(-20..20)}
\integer{y4=\sens=1?\y1+randint(5..10):\y1-randint(5..10)}
\integer{y10=\sens=1?\y1-randint(2..5):\y1+randint(2..5)}
\integer{ya=\sens=1?\y10-randint(2..5):\y10+randint(2..5)}
\integer{yb=\sens=1?\y10-randint(2..10):\y10+randint(2..10)}
\integer{yb=\ya=\yb?\yb+1}
\if{\sens=1}{
  \integer{y7=\ya>\yb?\ya:\yb}
  \integer{y12=\ya>\yb?\yb:\ya}
}{
  \integer{y7=\ya>\yb?\yb:\ya}
  \integer{y12=\ya>\yb?\ya:\yb}
}

\text{d1=\y1}
\text{d2=\y4}
\text{d3=\y7}
\text{d4=\y10}
\text{d5=\y12}

#if (defined TARGET_tbvarant5 || defined TARGET_tbvarant3 || defined TARGET_tbvarant4)
\text{tableau=
<table class="tab_var">
<tr>
  <th style="width:15%">\(x)</th>
  <td style="width:12%;text-align:left">\xl[1]</td>
  <td style="width:8%"></td>
  <td style="width:12%">\xl[4]</td>
  <td style="width:8%"></td>
  <td style="width:12%">\xl[7]</td>
  <td style="width:8%"></td>
  <td style="width:12%">\xl[10]</td>
  <td style="width:8%"></td>
  <td style="width:12%;text-align:right">\xl[12]</td>
</tr><tr>
  <th style="width:15%; vertical-align:middle">\(f(x))</th>
  <td style="width:12%;text-align:left;vertical-align:\pos[1]">\d1 </td>
  <td style="width:8%">\monotone[1] </td>
  <td style="width:12%;vertical-align:\pos[2]">\d2 </td>
  <td style="width:8%">\monotone[2] </td>
  <td style="width:12%;vertical-align:\pos[3]">\d3 </td>
  <td style="width:8%">\monotone[1] </td>
  <td style="width:12%;text-align:right;vertical-align:\pos[4]">\d4 </td>
  <td style="width:8%">\monotone[2] </td>
  <td style="width:12%;vertical-align:\pos[5]">\d5 </td>
</tr>
</table>
}
#else
\text{tableau=
<table class="tab_var">
<tr>
  <th style="width:15%">\(x)</th>
      <td style="width:16%;text-align:left">\xl[1]</td>
      <td style="width:26%"></td>
      <td style="width:16%">\xl[4]</td>
      <td style="width:26%"></td>
      <td style="width:16%;text-align:right">\xl[7]</td>
</tr><tr>
  <th style="width:15%;vertical-align:middle">\(f(x))</th>
     <td style="width:16%;text-align:left; vertical-align:\pos[1]">\d1 </td>
     <td style="width:26%">\monotone[1] </td>
     <td style="width:16%;vertical-align:\pos[2]">\d2 </td>
     <td style="width:26%">\monotone[2]  </td>
     <td style="width:16%;vertical-align:\pos[3]">\d3 </td>
      </tr>
</table>
}
#endif

#if defined TARGET_tbvarant5
\integer{xmax=\xl[12]}
#endif
#if (defined TARGET_tbvarant1 || defined TARGET_tbvarant3 )
#if defined TARGET_tbvarant1
\integer{xmax=\xl[7]}
\if{\sens=1}{
 \real{ql1=randint(\y7*10+1..\y1*10-1)/10}
 \real{ql2=randint(\y1*10+1..\y4*10-1)/10}
 \real{ql3=random(randint(\y4*10+1..\y4*10+10)/10,randint(\y7-10..\y7-1))}
}{
 \real{ql1=randint(\y1*10+1..\y7*10-1)/10}
 \real{ql2=randint(\y4*10+1..\y1*10-1)/10}
 \real{ql3=random(randint(\y7*10+1..\y7*10+10)/10,randint(\y4-10..\y4-1))}
}
 \integer{repl1=1}
 \integer{repl2=2}
 \integer{repl3=0}
#else
\integer{xmax=\xl[12]}
\if{\sens=1}{
 \real{ql1=randint(\y7*10+1..\y10*10-1)/10}
 \real{ql2=randint(\y1*10+1..\y4*10-1)/10}
 \real{ql3=random(randint(\y10*10+1..\y1*10-1)/10,randint(\y12*10+1..\y7*10-1)/10)}
}{
 \real{ql1=randint(\y10*10+1..\y7*10-1)/10}
 \real{ql2=randint(\y4*10+1..\y1*10-1)/10}
 \real{ql3=random(randint(\y1*10+1..\y10*10-1)/10,randint(\y7*10+1..\y12*10-1)/10)}
}
 \integer{repl1=3}
 \integer{repl2=2}
 \integer{repl3=1}
#endif
\integer{k=randint(1..3)}
\if{\k=1}{
  \text{ql=\ql1,\ql2,\ql3}
  \text{repl=\repl1,\repl2,\repl3}
}
\if{\k=2}{
  \text{ql=\ql2,\ql1,\ql3}
  \text{repl=\repl2,\repl1,\repl3}
}
\if{\k=3}{
  \text{ql=\ql2,\ql3,\ql1}
  \text{repl=\repl2,\repl3,\repl1}
}
\text{q1=\ql[1]}
\text{q2=\ql[2]}
\text{q3=\ql[3]}
\text{rep1=\repl[1]}
\text{rep2=\repl[2]}
\text{rep3=\repl[3]}
#endif
#if defined TARGET_tbvarant2
\integer{xmax=\xl[7]}
#endif
#if defined TARGET_tbvarant4
\integer{xmax=\xl[12]}
#endif

\statement{
  On considère une fonction \(f) définie sur &#91; \xl[1];\xmax &#93; et donnée par
  le tableau de variations suivant:
<div class="wimscenter">\tableau</div>

#if defined TARGET_tbvarant5
  Déterminer un intervalle ouvert I de sorte que chaque nombre de I
  possède un unique antécédent par \(f) :
<div class="wimscenter"><label for="reply1">\(I=) &#93;</label> \embed{reply1,3} ; \embed{reply2,3} &#91; </div>
}
\answer{borne gauche}{\re1}{type=numeric}
\answer{borne droite}{\re2}{type=numeric}
\condition{exemple d'intervalle}{(\re1<=\re2) and ((\sens=1 and ((\re1>=\y12 and \re2<=\y7) or (\rel1>=\y10 and \rel2 <= \y1))) or (\sens=2 and ((\re1>=\y7 and \re2<=\y12) or (\re1>=\y1 and \re2<=\y10))))}
#endif
#if (defined TARGET_tbvarant1 || defined TARGET_tbvarant3 )
  Déterminer le nombre d'antécédents des réels suivants:
<ul>
<li><label for="reply1">Nombre d'antécédents de \q1:</label>\embed{reply1,3}</li>
<li><label for="reply2">Nombre d'antécédents de \q2:</label>\embed{reply2,3}</li>
<li><label for="reply3">Nombre d'antécédents de \q3:</label>\embed{reply3,3}</li>
</ul>
}
\answer{Nb antécédents de \q1}{\rep1}{type=numeric}
\answer{Nb antécédents de \q2}{\rep2}{type=numeric}
\answer{Nb antécédents de \q3}{\rep3}{type=numeric}
#endif
#if (defined TARGET_tbvarant2 || defined TARGET_tbvarant4)
  Déterminer des réels \(i,j) et \(k) tels que
<ul>
<li><label for="reply1">\(i) n'a pas d'antécédents :</label>\embed{reply1,3}</li>
<li><label for="reply2">\(j) possède un unique antécédent:</label>\embed{reply2,3}</li>
<li><label for="reply3">\(k) possède exactement 2 antécédents:</label>\embed{reply3,3}</li>
</ul>
}
\answer{\(i)}{\re1}{type=numeric}
\answer{\(j)}{\re2}{type=numeric}
\answer{\(k)}{\re3}{type=numeric}
# if defined TARGET_tbvarant2
\condition{\(i)}{(\sens=1 and (\re1>\y4 or \re1<\y7)) or (\sens=2 and (\re1>\y7 or \re1<\y4))}
\condition{\(j)}{(\sens=1 and (\re2>=\y7 and \re2<\y1)) or (\sens=2 and (\re2>\y1 and \re2<=\y7)) or (\re2=\y4)}
\condition{\(k)}{(\sens=1 and \re3>=\y1 and \re3<\y4) or (\sens=2 and \re3>\y4 and \re3<=\y1)}
# else
\condition{\(i)}{(\sens=1 and (\re1>\y4 or \re1<\y12)) or (\sens=2 and (\re1>\y12 or \re1<\y4))}
\condition{\(j)}{(\sens=1 and ((\re2>=\y12 and \re2<\y7) or (\re2>\y10 and \re2<\y1))) or (\sens=2 and ((\re2>\y7 and \re2<=\y12) or (\re2>\y1 and \re2<\y10))) or \re2=\y4}
\condition{\(k)}{(\sens=1 and \re3>=\y1 and \re3<\y4) or (\sens=2 and \re3>\y4 and \re3<=\y1) or \re3=\y7}
# endif
#endif
