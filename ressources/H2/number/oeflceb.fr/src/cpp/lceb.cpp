target=graphe0 graphe1 graphe2 graphe3

#if defined TARGET_graphe1
# define NUM (I)
#endif

#if defined TARGET_graphe2
# define NUM (II)
#endif

#if defined TARGET_graphe3
# define NUM (III)
#endif
#include "lang_titles.inc"
#include "lang.inc"

\css{<style>
table.lceb th {background-color:lightgreen;padding:10px;width:60px;border:3px solid;}
table.lceb td {border:3px solid;padding:10px;font-size:130%;}
td.goal {border:3px solid;
padding:10px;background-color:#CCFFCC;font-weight:bold;font-size:130%;
}
td.answer {border:3px solid;padding:10px;background-color:orange;
}
pre { left:100px; right:100px; width:200px; padding:20px;
  text-align:left; border:1px solid }
.wims_oef_input {font-size:120%;}
</style>
}
\if{\confparm1=1}{
 \text{nt=4}
 \text{N=randint(20..50)}
 \text{tablettes=shuffle(3,3,4,5,6,2,2,6,4)}
 \text{tablettes=\tablettes[1..4],0,0}
 \text{nt=4}
 }
 {
\text{nt=6}
\text{tablettes=shuffle(1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,25,50,75,100)}
\text{N=randint(100..999)}
}
\text{data=\tablettes[1..6]}
\text{dataw=wims(items2words \data)}
\text{data=wims(replace internal ,0 by in \data)}
\text{data=wims(nonempty items \data)}
\text{Data=\data}
\text{lceb=wims(exec lceb \N \dataw)}
\text{lceb=wims(line 3 to -1 of \lceb)}
\text{lceb_cnt=wims(linecnt \lceb)}
\text{arbre=}
\text{noeud=}
\integer{cnt=0}
\text{Noeud=}
\text{graph=}
\text{M=}
\text{T=}
\text{noeudtext=}
\text{noeudtext1=}
\text{feuille=}
\text{M=wims(makelist 0 for x=1 to 20)}
\text{M=wims(items2lines \M)}
\text{Ddebug=\Data
\noeud}
text{feuille=wims(makelist x for x=1 to \nt)}
\for{j=1 to \lceb_cnt}{
  \text{li=wims(line \j of \lceb)}
  \text{li=wims(words2items \li)}
  \text{h1=position(\li[1],\noeud)}
  \text{h2=position(\li[3],\noeud)}
  \text{h1data=position(\li[1],\Data)}
  \integer{cnt=\cnt+1}
  \text{h0=\cnt}
  \text{noeud=wims(append item \li[5] to \noeud)}
  \text{noeudtext=wims(append item \li[5] to \noeudtext)}
  \text{noeudtext1=wims(append item \li[2] to \noeudtext1)}
  \text{Noeud=wims(append item \cnt to \Noeud)}
  \if{\h1 notsametext }{
    \if{\h1data notsametext}{
    \text{Data=\h1data[-1]!= ? wims(replace item number \h1data[-1] by in \Data) :
      wims(replace item number \h1data[1] by in \Data)}
    }
   }
  \if{\h1= or \h1data notsametext}{
    \text{Data=\h1data notsametext? wims(replace item number \h1data[1] by in \Data)}
    \integer{cnt=\cnt+1}
    \text{feuille=wims(append item \cnt to \feuille)}
    \text{h1=\cnt}
    \text{Noeud=wims(append item \cnt to \Noeud)}
    \text{noeud=wims(append item \li[1] to \noeud)}
    \text{noeudtext=wims(append item \li[1] to \noeudtext)}
    \text{noeudtext1=wims(append item \li[1] to \noeudtext1)}
  }
  \text{h2data=position(\li[3],\Data)}
  \if{\h2 notsametext }{
    \if{\h2data notsametext}{
    \text{Data=\h2data[-1]!= ? wims(replace item number \h2data[-1] by in \Data) :
      wims(replace item number \h2data[1] by in \Data)}
   }
  }

  \if{\h2= or \h2data notsametext}{
    \text{Data=\h2data notsametext ? wims(replace item number \h2data[1] by in \Data)}
    \integer{cnt=\cnt+1}
    \text{feuille=wims(append item \cnt to \feuille)}
    \text{h2=\cnt}
    \text{Noeud=wims(append item \cnt to \Noeud)}
     \text{noeud=wims(append item \li[3] to \noeud)}
     \text{noeudtext=wims(append item \li[3] to \noeudtext)}
     \text{noeudtext1=wims(append item \li[3] to \noeudtext1)}
  }
  \text{Ddebug=\Ddebug
Data=\Data
noeud=\noeud
h=\h0,h1=\h1,h2=\h2}
  \if{, isin \h2}{ \text{h2=\h2[-1]}}
  \if{, isin \h1}{ \text{h1=\h1[1]}}
  \matrix{arbre=\arbre
\h0,\h1,\h2
}
\text{graph=\graph
  \h1 -> \h0;
  \h2 -> \h0;}
\text{L=wims(makelist 0 for x=1 to \cnt)}
\text{L=wims(replace internal item number \h1 by 1 in \L)}
\text{L=wims(replace internal item number \h2 by 1 in \L)}
\text{M=wims(replace internal line number \h0 by \L in \M)}

}
\text{M=\M}
integer{cnt=wims(linecnt \M)}
\matrix{M=\M}
\text{M1=pari(M=matrix(\cnt,\cnt))}
\for{i=1 to \cnt}{
  \for{j=1 to \cnt}{ \text{u=\M[\i;\j]}
    \text{M1=pari(M[\i,\j]=\u)}
  }
}
\text{noeudtextC=\noeudtext}
\text{M1=pari(mattranspose(M))}
\for{f=1 to \cnt}{
 \if{ \f notitemof \feuille}{
  \text{noeudtextC=wims(replace item number \f by ? in \noeudtextC)}
 }
}
#if defined TARGET_graphe0
\text{tree=slib(graph/graphviz [\M1],[\noeudtext],url,[rankdir="LR" ;node [fontsize=14,width=".5", height=".5", margin=0 shape=box];])}
#endif

#if defined TARGET_graphe1
\text{tree=slib(graph/graphviz [\M1],[\noeudtext1],url,[rankdir="LR" ;node [fontsize=14,width=".5", height=".5", margin=0 shape=box];])}
#endif

#if defined TARGET_graphe2  || defined TARGET_graphe3
\text{tree=slib(graph/graphviz [\M1],[\noeudtextC],url,[rankdir="LR" ;node [fontsize=14,width=".5", height=".5", margin=0 shape=box];])}
#endif
\text{tree_coord1=slib(draw/graphvizpoints 25)}
text{tree_coord=wims(line 2 to -1 of \tree_coord1)}

\matrix{tree_coord=\tree_coord1}

text{tree2=slib(graph/graphviz [\M1],[\noeudtext1],url,[rankdir="LR" ;node [fontsize=14,width=".5", height=".5", margin=0 shape=box];])}
\text{lceb1=row(2,\lceb)}
 \text{goal=NOTFOUND isin \lceb1? wims(word 1 of \lecb1) : \N}

\integer{feuille_cnt=items(\feuille)}

\text{d=}
\text{t=}
\text{Feed=}
\text{position=}
\text{rep_cnt=0}

#if defined TARGET_graphe3
\text{repg=}
\for{f=1 to \cnt}{
 \if{ \f notitemof \feuille}{
  \integer{rep_cnt=\rep_cnt+1}
  \text{position=\position
  r\rep_cnt,\tree_coord[\f+1;1] x \tree_coord[\f+1;2]}
  \text{s=\noeudtext1[\f]}
  \text{s=wims(replace internal " by in \s)}
  \text{repg=wims(append item \s to \repg)}
 }
}
\text{STEP=wims(makelist r x for x=1 to \rep_cnt)}
\text{test1=}
\steps{\STEP}

\statement{
<p>
<i>\instruction1</i> : \instruction2:
</p>
<table class="wimscenter lceb">
<tr>\for{v=1 to \nt}{<th>\data[\v]</th>}
</tr>
<tr><td class="goal" colspan="\nt">\N</td></tr>
</table>
<div class="wimscenter">
\special{imagefill \tree, \tree_coord[1;1] x \tree_coord[1;2],50x50
\position}
</div>
}
\answer{}{\repg[1];+,*,/,-}{type=clickfill}
\answer{}{\repg[2]}{type=clickfill}
\answer{}{\repg[3]}{type=clickfill}
\answer{}{\repg[4]}{type=clickfill}
\answer{}{\repg[5]}{type=clickfill}
\answer{}{\repg[6]}{type=clickfill}
\answer{}{\repg[7]}{type=clickfill}
\answer{}{\repg[8]}{type=clickfill}
\answer{}{\repg[9]}{type=clickfill}
\answer{}{\repg[10]}{type=clickfill}
\feedback{1=1}{ \name_feed
<div class="wimscenter">
\special{expandlines
\lceb
}
</div>
}
#endif

#if defined TARGET_graphe0  || defined TARGET_graphe1  || defined TARGET_graphe2
\text{repg=}
\for{f=1 to \cnt}{
 \if{ \f notin \feuille}{
  \integer{rep_cnt=\rep_cnt+1}
  \text{position=\position
  r\rep_cnt,\tree_coord[\f+1;1] x \tree_coord[\f+1;2]}
  \text{s=\noeudtext1[\f]}
  \text{s=wims(replace internal " by in \s)}
  \text{repg=wims(append item \s to \repg)}
 }
}
\text{repg=wims(makelist <span class="large">x</span> for x in \repg)}
text{STEP=wims(makelist r x for x=1 to \rep_cnt)}
steps{\STEP}
\statement{
<p>
\instruction:
</p>

<table class="wimscenter lceb">
<tr>\for{v=1 to \nt}{<th>\data[\v]</th>}
</tr>
<tr><td class="goal" colspan="\nt">\N</td></tr>
</table>
<table class="wimscenter"><tr><td>
<img src="\tree" alt="">
</td><td>
\embed{r1,12
default}
</td></tr></table>
}
\answer{}{\rr}{type=equation2}{option=limit=6}

\text{data1=\data}
\integer{repcnt=rows(\reply1)}
\matrix{rep=\reply1}
\text{rep=wims(replace internal <pre> by in \rep)}
\text{rep=wims(replace internal </pre> by in \rep)}
\matrix{lceb1=\lceb}
\text{mm=\lceb1[;1]}
\integer{mm=items(\mm)}
\text{Testg=}
\for{ a= 1 to \mm}{
   \text{test=\lceb1[\a;]}
   \text{test=wims(replace internal = by , in \test)}
   \text{test=wims(replace internal + by ,+, in \test)}
   \text{test=wims(replace internal - by ,-, in \test)}
   \text{test=wims(replace internal * by ,*, in \test)}
   \text{test=wims(replace internal / by ,/, in \test)}
   \text{test=wims(sort items \test)}
   \text{test=wims(replace internal , by xx in \test)}
   \text{Testg=\Testg,wims(nospace \test)}
}
\text{Testg=wims(nonempty items \Testg)}
\text{nn=\rep[;1]}
\integer{nn=items(\nn)}
les operations sont justes
\text{test1=}
\text{Test=}
\for{ a= 1 to \nn}{
   \text{test=\rep[\a;]}
   \text{test=wims(replace internal = by == in \test)}
   \text{test1=\test1,pari(\test)}
   \text{test=wims(replace internal == by , in \test)}
   \text{test=wims(replace internal + by ,+, in \test)}
   \text{test=wims(replace internal - by ,-, in \test)}
   \text{test=wims(replace internal * by ,*, in \test)}
   \text{test=wims(replace internal / by ,/, in \test)}
   \text{test=wims(sort items \test)}
   \text{test=wims(replace internal , by xx in \test)}
   \text{Test=\Test,wims(nospace \test)}
}
\text{Test=wims(nonempty items \Test)}
\text{test=wims(nonempty items \test1)}
\text{test1=1}
\text{test1=0 isin \test or \test issametext ? 0}

\text{test2=wims(listcomplement \Testg in \Test)}
\integer{test2=items(\test2)}
\text{test3=wims(listcomplement \Test in \Testg)}
\integer{test3=items(\test3)}
\condition{\name_condition[1]}{\test1=1}
\condition{\name_condition[2]}{\test3=0 and \test2=0}
\feedback{\test3=0 or \test2=0 or \test1<1}{
\name_feed[1]
<div class="wimscenter">
\special{expandlines
\lceb}
</div
\if{\test3>0 and \test2=0}{\name_feed[2]}
}
#endif
