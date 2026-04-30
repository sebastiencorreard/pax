target=tbvarextr1 tbvarextr2 tbvarextr3 tbvarextr4 tbvarextr5
\author{Régine, Mangeard}
\email{regine@mangeard}
\format{html}

#define TITRE Tableau de variations et extremum
#if defined TARGET_tbvarextr1
# define NUM 1
#endif
#if defined TARGET_tbvarextr3
# define NUM 3
#endif
#if defined TARGET_tbvarextr4
# define NUM 4
#endif
#if defined TARGET_tbvarextr2
# define NUM 2
# endif
#if defined TARGET_tbvarextr5
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
%%%%%%%%%%%%%%%%%%%%!!!!!
integer{sens=2}

#if defined TARGET_tbvarextr1
\integer{sens=1}
#endif
#if defined TARGET_tbvarextr2
\integer{sens=2}
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
\integer{y7=\sens=1?\y10-randint(2..5):\y10+randint(2..5)}
\integer{y12=\sens=1?\y10-randint(2..10):\y10+randint(2..10)}
\text{d1=\y1}
\text{d2=\y4}
\text{d3=\y7}
\text{d4=\y10}
\text{d5=\y12}

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
  <th style="vertical-align:middle;width:15%">\(f(x))</th>
     <td style="width:12%;text-align:left;vertical-align:\pos[1]">\d1</td>
     <td style="width:8%">\monotone[1] </td>
     <td style="width:12%;vertical-align:\pos[2]">\d2</td>
     <td style="width:8%">\monotone[2] </td>
     <td style="width:12%;vertical-align:\pos[3]">\d3</td>
     <td style="width:8%">\monotone[1] </td>
     <td style="width:12%;text-align:right; vertical-align:\pos[4]">\d4 </td>
     <td style="width:8%">\monotone[2] </td>
     <td style="width:12%;vertical-align:\pos[5]">\d5</td>
      </tr>
</table>
}
#if (defined TARGET_tbvarextr1 || defined TARGET_tbvarextr2 )
# if defined TARGET_tbvarextr1
\text{typequest=maximum}
\text{q1=\xl[1]}
\text{q2=\xl[7]}
\text{q3=\xl[7]}
\text{q4=\xl[12]}
\text{q5=\xl[4]}
\text{q6=\xl[10]}
\integer{rep1=\y4}
\integer{rep2=\xl[4]}

\integer{rep3=\y10}
\integer{rep4=\xl[10]}

\integer{rep5=\y4}
\integer{rep6=\xl[4]}

\integer{rep7=\y4}
\integer{rep8=\xl[4]}
#endif
#if defined TARGET_tbvarextr2
\text{typequest=minimum}
\text{q1=\xl[1]}
\text{q2=\xl[7]}
\text{q3=\xl[7]}
\text{q4=\xl[12]}
\text{q5=\xl[4]}
\text{q6=\xl[10]}
\integer{rep1=\y4}
\integer{rep2=\xl[4]}

\integer{rep3=\y10}
\integer{rep4=\xl[10]}

\integer{rep5=\y4}
\integer{rep6=\xl[4]}

\integer{rep7=\y4}
\integer{rep8=\xl[4]}
#endif
\statement{
  On considère une fonction \(f) définie sur &#91; \xl[1];\xl[12] &#93; et donnée par
  le tableau de variations suivant:
<div class="wimscenter">\tableau</div>
<ul>
<li><label for="reply7">Quel est le \typequest sur &#91; \xl[1];\xl[12] &#93; ? </label>
  \embed{reply7,3},
  <label for="reply8">il est atteint en \(x=)</label> \embed{reply8,3}</li>
<li><label for="reply1">Quel est le \typequest sur &#91; \q1;\q2 &#93; ?</label> \embed{reply1,3},
  <label for="reply2">il est atteint en \(x=)</label> \embed{reply2,3}</li>
<li><label for="reply3">Quel est le \typequest sur &#91; \q3;\q4 &#93; ?</label> \embed{reply3,3},
  <label for="reply4">il est atteint en \(x=)</label> \embed{reply4,3}</li>
<li><label for="reply5">Quel est le \typequest sur &#91; \q5;\q6 &#93; ?</label> \embed{reply5,3},
  <label for="reply6">il est atteint en \(x=)</label> \embed{reply6,3}</li>
</ul>
}
\answer{\typequest local 1}{\rep1}{type=numeric}
\answer{\typequest local 1 en x=}{\rep2}{type=numeric}
\answer{\typequest local 2}{\rep3}{type=numeric}
\answer{\typequest local 2 en x=}{\rep4}{type=numeric}
\answer{\typequest local 3}{\rep5}{type=numeric}
\answer{\typequest local 3 en x=}{\rep6}{type=numeric}
\answer{\typequest global}{\rep7}{type=numeric}
\answer{\typequest global en x=}{\rep8}{type=numeric}
#else
# if defined TARGET_tbvarextr3
\integer{k=randint(1,2)}
\text{ql1=\k=1?\(f(\xl[2])):\(f(\xl[3]))}
\text{ql2=\k=1?\(f(\xl[3])):\(f(\xl[2]))}
\if{\sens=1}
  {\integer{repl1=\k=1?1:2}}
  {\integer{repl1=\k=1?2:1}}

\integer{k=randint(1,2)}
\text{ql3=\k=1?\(f(\xl[5])):\(f(\xl[6]))}
\text{ql4=\k=1?\(f(\xl[6])):\(f(\xl[5]))}
\if{\sens=1}
  {\integer{repl2=\k=1?2:1}}
  {\integer{repl2=\k=1?1:2}}

\integer{k=randint(1,2)}
\text{ql5=\k=1?\(f(\xl[8])):\(f(\xl[9]))}
\text{ql6=\k=1?\(f(\xl[9])):\(f(\xl[8]))}
\if{\sens=1}
  {\integer{repl3=\k=1?1:2}}
  {\integer{repl3=\k=1?2:1}}

# endif
# if defined TARGET_tbvarextr4
\integer{k=randint(1,2)}
\text{ql1=\k=1?\(f(\xl[2])):\(f(\xl[8]))}
\text{ql2=\k=1?\(f(\xl[8])):\(f(\xl[2]))}
\if{\sens=1}
  {\integer{repl1=\k=1?2:1}}
  {\integer{repl1=\k=1?1:2}}

\integer{k=randint(1,2)}
\text{ql3=\k=1?\(f(\xl[8])):\(f(\xl[6]))}
\text{ql4=\k=1?\(f(\xl[6])):\(f(\xl[8]))}
\integer{repl2=3}

\integer{k=randint(1,2)}
\text{ql5=\k=1?\(f(\xl[5])):\(f(\xl[1]))}
\text{ql6=\k=1?\(f(\xl[1])):\(f(\xl[5]))}
\integer{repl3=3}
# endif
# if defined TARGET_tbvarextr5
\text{ql1=\xl[1]}
\text{ql2=\xl[4]}
\text{repl1=\sens=1?1:2}

\text{ql3=\xl[4]}
\text{ql4=\xl[7]}
\text{repl2=\sens=1?2:1}

\text{ql5=\xl[7]}
\text{ql6=\xl[12]}
\text{repl3=3}
# endif

\integer{k=randint(1..3)}
\if{\k=1}{
  \text{ql=\ql1,\ql2,\ql3,\ql4,\ql5,\ql6}
  \text{repl=\repl1,\repl2,\repl3}
 }
\if{\k=2}{
  \text{ql=\ql3,\ql4,\ql1,\ql2,\ql5,\ql6}
  \text{repl=\repl2,\repl1,\repl3}
 }
\if{\k=3}{
  \text{ql=\ql3,\ql4,\ql5,\ql6,\ql1,\ql2}
  \text{repl=\repl2,\repl3,\repl1}
 }
\text{q1=\ql[1]}
\text{q2=\ql[2]}
\text{q3=\ql[3]}
\text{q4=\ql[4]}
\text{q5=\ql[5]}
\text{q6=\ql[6]}
\text{rep1=\repl[1]}
\text{rep2=\repl[2]}
\text{rep3=\repl[3]}

\statement{
  On considère une fonction \(f) définie sur &#91; \xl[1];\xl[12] &#93; et donnée par
  le tableau de variations suivant:
<div class="wimscenter">\tableau</div>

#if defined TARGET_tbvarextr5
  Comparer les réels suivants, sachant que \(a) et \(b) sont deux réels de l'intervalle \(I) et\(a < b):
<ul>
<li>avec \(I=) &#91; \q1;\q2 &#93; : \(f(a)) \embed{reply1} \(f(b))</li>
<li>avec \(I=) &#91; \q3;\q4 &#93; : \(f(a)) \embed{reply2} \(f(b))</li>
<li>avec \(I=) &#91; \q5;\q6 &#93; : \(f(a)) \embed{reply3} \(f(b))</li>
#else
  Comparer les réels suivants:
<ul>
<li>\q1 \embed{reply1} \q2</li>
<li>\q3 \embed{reply2} \q4</li>
<li>\q5 \embed{reply3} \q6</li>
#endif
</ul>
}
\answer{\q1 et \q2}{\rep1;\lstrep}{type=menu}
\answer{\q3 et \q4}{\rep2;\lstrep}{type=menu}
\answer{\q5 et \q6}{\rep3;\lstrep}{type=menu}
#endif
