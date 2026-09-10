target=validite

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\range{-10..10}
\text{monaide=}
\for{ii = 4 to 5}{
  \text{currrecord=wims(record \ii of \glossaire)}
  \text{monaide=\monaide
	\currrecord}
}
\help{\monaide}

\integer{a=random(1..6)}

\text{A=\Alist[\a]}
\text{B=\Blist[\a]}
\text{C=\Clist[\a]}
\text{D=\Dlist[\a]}

\text{nonA=\nonAlist[\a]}
\text{nonB=\nonBlist[\a]}
\text{nonC=\nonClist[\a]}
\text{nonD=\nonDlist[\a]}

\text{val=randint(0,1),randint(0,1),randint(0,1),randint(0,1)}

\text{si=\a<4?\si1:\si2}

\text{liste=oui,1,2,3,4,5,6}

\text{elles=Léa,Lili,Julie,Leila,Lola}
\text{luis=Léo,Lulu,Jules,Malik,Luis}
\integer{i=random(1..4)}
\text{Elle=\elles[\i]}
\text{Lui=\luis[\i]}

\text{mrx=\a<4?\Lui:\Elle}

/** reglement compatible **/
/**  un  modèle : Av Bv Cv Dv Ef **/

\text{reg=
\A \name_ou \B,
\C \name_ou \D,
\si \A \name_et \si \B \alors \D,
\si \B \name_et \si \nonC \alors \D,
\si \C \name_et \si \nonA \alors \nonD ,
\si \B \name_ou \si \D \alors \A,
\A \si2 \name_et \seulement \si \D,
\A \name_et \B,
\C \name_et \nonD
}

\text{ind=shuffle(1,2,3,4,5,6,7,8,9)}
\integer{i1=\ind[1]}
\integer{i2=\ind[2]}
\integer{i3=\ind[3]}
\integer{i4=\ind[4]}

\integer{cond1=\val[1]==1 or \val[2]==1?1:2}

\integer{cond2=\val[3]==1 or \val[4]==1?1:2}

\integer{cond3=(\val[1]==0 or \val[2]==0 or \val[4]==1)?1:2}

\integer{cond4=(\val[3]==1 or \val[2]==0 or \val[4]==1)?1:2}

\integer{cond5=(\val[3]==0 or \val[1]==1 or \val[4]==0)?1:2}

\integer{cond6=(\val[2]==0 and \val[4]==0) or \val[1]==1?1:2}

\integer{cond7=(\val[1]==\val[4])?1:2}

\integer{cond8=\val[1]==1 and \val[2]==1?1:2}

\integer{cond9=\val[3]==1 and \val[4]==0?1:2}


\text{conditions=\cond1,\cond2,\cond3,\cond4,\cond5,\cond6,\cond7,\cond8,\cond9}
\integer{rep1=\conditions[\i1]}
\integer{rep2=\conditions[\i2]}
\integer{rep3=\conditions[\i3]}
\integer{rep4=\conditions[\i4]}

\statement{<div class="wims_question">

<p>\mrx \name_statement1\spacebeforecolon:
</p>
<ul>
<li>\if{\val[1]==1}{\A}{\nonA}</li>
<li>\if{\val[2]==1}{\B}{\nonB}</li>
<li>\if{\val[3]==1}{\C}{\nonC}</li>
<li>\if{\val[4]==1}{\D}{\nonD}</li>
</ul>
<p>
\name_statement2 \if{\a<4}{\masculin,}{\feminin,} \mrx \name_statement3.
</p><p>
\name_statement4 \mrx \name_statement5\spacebeforecolon:
</p>
<table class="wimscenter wimsnoborder">
<tr>
<td>1.</td>
<td>\reg[\i1]</td>
<td>\embed{reply1}</td>
</tr>
<tr>
<td>2.</td>
<td>\reg[\i2]</td>
<td>\embed{reply2}</td>
</tr>
<tr>
<td>3.</td>
<td>\reg[\i3]</td>
<td>\embed{reply3}</td>
</tr>
<tr>
<td>4.</td>
<td>\reg[\i4]</td>
<td>\embed{reply4}</td>
</tr>
</table>

</div>
}
\answer{clause 1}{\rep1;\vrai,\faux}{type=radio}
\answer{clause 2}{\rep2;\vrai,\faux}{type=radio}
\answer{clause 3}{\rep3;\vrai,\faux}{type=radio}
\answer{clause 4}{\rep4;\vrai,\faux}{type=radio}

\hint{<p>\name_hint1</p><p>\name_hint2</p>}
