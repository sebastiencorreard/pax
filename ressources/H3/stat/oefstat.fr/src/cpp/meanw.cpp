target=meanw
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}
\integer{nb=\confparm1=? randint(6..9)}
\integer{nb=\confparm1=1? randint(4..6)}
\integer{nb=\confparm1=2? randint(7..8)}
\integer{nb=\confparm1=3? randint(9..12)}
\real{neff=randint(20..30)}
\text{eff=slib(stat/random \nb-1, 0,\neff)}
\text{coeff=slib(stat/random \nb-1,1,4)}
\text{moy=item(1,slib(stat/arithmean [\eff],[\coeff]))}
\text{liste=wims(sort numeric item \eff)}
\text{maxi=wims(item -1 of \liste)}
\text{mini=wims(item 1 of \liste)}
\real{etendue=\maxi-\mini}
\text{table=<th>\name_head[1]</th>}
\text{table1=<th>\name_head[2]</th>}
\for{i=1 to \nb-1}{
	\text{a=item(\i,\eff)}
	\text{b=item(\i,\coeff)}
	\text{table=\table<td>\a</td>}
	\text{table1=\table1<td>\b</td>}
}
\statement{\name_enonce:
	<table class="wimscenter wimsborder">
	 <tr>\table</tr>
	 <tr>\table1</tr>
	 </table>
<div class="wims_question">
\name_question[1]
<ul><li><label for="reply1">\name_question[2]:</label> \embed{reply 1, 6}
</li><li>
  <label for="reply2">\name_question[3]:</label> \embed{reply 2, 6}
</li><li>
  <label for="reply3">\name_question[4]:</label> \embed{reply 3, 6}
</li><li>
  <label for="reply4">\name_question[5]:</label> \embed{reply 4, 6}
</li></ul>
</div>
}

\answer{ \name_answer[1]}{\moy}{type=numeric}
\answer{ \name_answer[2]}{\maxi}{type=numeric}
\answer{ \name_answer[3]}{\mini}{type=numeric}
\answer{ \name_answer[4]}{\etendue}{type=numeric}

\feedback{\reply4-\reply2+\reply3 !=0}{
	<span class="oef_indbad">
	\name_feed
	</span>
}
