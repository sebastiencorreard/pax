target=loivar1 loivar2 loivar3

#include "header.inc"

\precision{10000}
\keywords{probability,random_variable,discrete_probability_distribution}

#if defined TARGET_loivar1
# define NUM 1
#endif
#if defined TARGET_loivar2
# define NUM 2
#endif
#if defined TARGET_loivar3
# define NUM 3
#endif

#include "lang_titles.inc"

%%choix de la loi P
\integer{pcum=0}
\text{pl=}
 \integer{p=randint(0..50)}
\for{i=1 to 4}{
 \integer{pcum=\pcum+\p}
 \real{p=\p/100}
 \text{pl=wims(append item \p to \pl)}
 \integer{p=randint(0..100-\pcum)}
}
\integer{p=100-\pcum}
\real{p=\p/100}
\text{pl=wims(append item \p to \pl)}
\text{pl=shuffle(\pl)}

%%choix de la variable X
\integer{nbx=randint(3..4)}
\text{xval=}
\text{val=randint(-5..-1),0,randint(1..5)}
\for{y in \val}{
  \for{i=1 to \nbx}{
    \text{xval=wims(append item \val to \xval)}
  }
}
\text{xval=shuffle(\xval)}
\text{xval=item(1..5,\xval)}
\text{sx=wims(listuniq \xval)}
\text{sx=wims(sort numeric list \sx)}
\integer{nbx=items(\sx)}

%% détermination de la loi de X
\text{px=}
\for{i=1 to \nbx}{
  \real{p=0}
  \for{j=1 to 5}{
    \if{\xval[\j]=\sx[\i]}{\real{p=\p+\pl[\j]}}
  }
  \text{px=wims(append item \p to \px)}
}

#include "lang.inc"

#if defined TARGET_loivar1
\text{mstep=wims(makelist r x for x= 1 to \nbx)}
\text{mstep=wims(nospace \mstep)}
\steps{\mstep}
\statement{\name_statement1[1] \(\Omega=\{e_1,e_2,e_3,e_4,e_5\}) \name_statement1[2] \(P\) \name_statement1[3]
\(\Omega\;\) \name_statement1[4]:
<table class="wimscenter wimsborder"><tr><th>\(e_i\)</th>
<th>\(e_1\)</th>
<th>\(e_2\)</th>
<th>\(e_3\)</th>
<th>\(e_4\)</th>
<th>\(e_5\)</th>
</tr><tr><th>\(p_i\)</th>
\for{jj=1 to 5}{
  <td>\(\pl[\jj])</td>
}
</tr></table>
\name_statement2:
<table class="wimscenter wimsborder"><tr><th>\(e_i\)</th>
<th>\(e_1)</th>
<th>\(e_2)</th>
<th>\(e_3)</th>
<th>\(e_4)</th>
<th>\(e_5)</th>
</tr><tr><th>\(X(e_i))</th>
\for{jj=1 to 5}{
  <td>\(\xval[\jj])</td>
}
</tr></table>
\name_statement3:
<table class="wimscenter wimsborder"><tr><th>\(x\)</th>
\for{ii=1 to \nbx}{
  <td>\(\sx[\ii])</td>
}
</tr><tr><th>\(P(X=x)\)</th>
\for{jj=1 to \nbx}{
  <td>\embed{reply\jj,3}</td>
}
</tr></table>
}
\hint{\name_hint[1], \(p_i=P(\{e_i\})\) \name_hint[2] \(i\in \{1,2,3,4,5\}\). }
\answer{}{\px[1]}{type=numeric}
\answer{}{\px[2]}{type=numeric}
\answer{}{\px[3]}{type=numeric}
\answer{}{\px[4]}{type=numeric}
\answer{}{\px[5]}{type=numeric}
#endif
#if defined TARGET_loivar2
\real{esp=0}
\real{variance=0}
\for{i=1 to \nbx}{
  \real{esp=\esp+\px[\i]*\sx[\i]}
  \real{variance=\variance+\px[\i]*(\sx[\i])^2}
}
\real{variance=\variance -(\esp)^2}
\integer{repc=\esp=0?1:2}
\integer{repc=\esp<0?3}
\statement{\name_statement[1] \(\Omega\;\) \name_statement[2] \(P\),
\name_statement[3] \(X\) \name_statement[4]:
<table class="wimscenter wimsborder"><tr><th>\(x\)</th>
\for{ii=1 to \nbx}{<td>\(\sx[\ii])</td>}
</tr><tr><th>\(P(X=x)\)</th>
\for{jj=1 to \nbx}{<td>\(\px[\jj])</td>}
</tr></table>
<ol>
<li>\name_question1 \(X\) : <label for="reply1">\(E(X)=\)</label>\embed{reply1,5}</li>
<li>\name_question2 \(X\) : <label for="reply2">\(V(X)=\)</label>\embed{reply2,5}</li>
<li>\name_question3 \(X\) \name_question4 :
<div class="wimscenter"> \embed{reply3}</div></li>
</ol>
}
\answer{E(X)}{\esp}{type=numeric}
\answer{V(X)}{\variance}{type=numeric}
\answer{}{\repc;\name_list_rep}{type=radio}
#endif
#if defined TARGET_loivar3
\integer{n=2}
\integer{x=randint(2..4)}
\integer{y=6-\x}
\rational{p=\x/6}
\rational{q=\y/6}
\rational{v0=(\p)^2}
\rational{v2=(\q)^2}
\rational{v1=1-\v0-\v2}
\statement{
\name_statement[1] \x \name_statement[2] \y \name_statement[3].
\name_statement[4] \n \name_statement[5], \name_statement[6]\name_comma
\name_statement[7] \(X\) \name_statement[8] <span class="wims_emph">"\name_variable"</span>.<p>
\name_statement[9] \(X\).
</p>
<table class="wimscenter wimsborder"><tr><th>\(i\)</th><th>0</th><th>1</th><th>2</th></tr>
<tr><th>\(P(X=i)\)</th><td>\embed{reply1,4}</td><td>\embed{reply2,4}</td><td>\embed{reply3,4}</td></tr>
</table>
<div class="wims_instruction">\name_consig</div>
}
\answer{\(P(X=0))}{\v0}{type=numexp}
\answer{\(P(X=1))}{\v1}{type=numexp}
\answer{\(P(X=2))}{\v2}{type=numexp}
\solution{\name_solution1 \(\frac{\x}{6}) \name_solution2 \(\frac{\y}{6}).
\name_solution3:
<ul>
<li> \name_solution4 \((\frac{\x}{6})^2) \name_solution5;</li>
<li> \name_solution4 \((\frac{\y}{6})^2) \name_solution6;</li>
<li> \name_solution4 \(1-(\frac{\x}{6})^2-(\frac{\y}{6})^2) \name_solution7.</li>
</ul>}
#endif
