target=imagerestr minmaxrestr

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "values.inc"
#if defined TARGET_imagerestr
 \text{size=60x40x1}
# include "tablegen.inc"
#endif
#if defined TARGET_minmaxrestr
  \text{size=70x40x1}
# include "tablegen.inc"
#endif
#include "common.inc"

\text{osign=item(\orient,+,-)}
\text{non=\name_non}

\text{cuts=item(1..2,shuffle(13))}
\integer{cut1=min(\cuts)}
\integer{cut2=max(\cuts)}
\integer{cut1=\cut1=1 and \cut2=13?randint(2..12)}
\integer{lclose=\cut1=1?0:random(0,1)}
\integer{rclose=\cut2=13?0:random(0,1)}
\text{psel=}
\for{p=2 to 4}{
  \if{3*\p-2>\cut1 and 3*\p-2<\cut2}{\text{psel=\psel \p}}
}
\text{psel=wims(words2items \psel)}
\text{xvalues=-\infty,\vx,+\infty}
\text{yvalues=\YY[1],\ymiddles[1;],\ys[2],\ymiddles[2;],\ys[3],\ymiddles[3;],\ys[4],\ymiddles[4;],\YY[5]}
\text{ycut1=\cut1 notitemof 1,4,7,10,13?\yvalues[\cut1]:}
\text{ycut2=\cut2 notitemof 1,4,7,10,13?\yvalues[\cut2]:}
\text{presup=\yvalues[\cut1]}
\text{preinf=\presup}
\text{premax=\lclose=1?\presup:\non}
\text{premin=\premax}
\for{p in \psel}{
 \if{\osign(\ys[\p]) > \osign(\presup)}{
  \text{presup=\ys[\p]} \text{premax=\presup}
 }
 \if{\osign(\ys[\p]) < \osign(\preinf)}{
  \text{preinf=\ys[\p]} \text{premin=\preinf}
 }
}
if{\rclose=1}{
 \if{\yvalues[\cut2] = \presup and \premax issametext \non}{
    \text{premax=\presup}
 }
 \if{\yvalues[\cut2] = \preinf and \premin issametext \non}{
    \text{premax=\preinf}
 }
}
\if{\osign(\yvalues[\cut2]) > \osign(\presup)}{
 \text{presup=\yvalues[\cut2]}
 \text{premax=\rclose=1?\presup:\non}
}
\if{\osign(\yvalues[\cut2]) < \osign(\preinf)}{
 \text{preinf=\yvalues[\cut2]}
 \text{premin=\rclose=1?\preinf:\non}
}
\text{presup=wims(replace internal \infval by \infty in \presup)}
\text{preinf=wims(replace internal \infval by \infty in \preinf)}
\text{premax=\premax notsametext \non?\(\premax)}
\text{premin=\premin notsametext \non?\(\premin)}
\if{\orient=1}{
 \text{sup=\(\presup)}
 \text{max=\premax}
 \text{inf=\(\preinf)}
 \text{min=\premin}
}{
 \text{inf=\(\presup)}
 \text{min=\premax}
 \text{sup=\(\preinf)}
 \text{max=\premin}
}

\text{show=\xshow,\yshow}
\text{show=\ycut1 notsametext ?\show,\(\ycut1)}
\text{show=\ycut2 notsametext ?\show,\(\ycut2)}
\text{vlist=wims(listuniq \show)}
\text{bracks=\leftbrack,\rightbrack}
\text{lbr=\min issametext \non?\bracks[2]:\bracks[1]}
\text{rbr=\max issametext \non?\bracks[1]:\bracks[2]}

\statement{\intro
#include "table.inc"
<p>
 Soit \(I) = \bracks[2-\lclose]\(\xvalues[\cut1]) ,
\(\xvalues[\cut2])\bracks[1+\rclose] et soit \(f_I) la restriction de \(f)
sur \(I).
</p>
\if{\ycut1 notsametext \empty}{
 \if{\ycut2 notsametext \empty}
  {Nous avons \(f(\xvalues[\cut1]) = \ycut1) et \(f(\xvalues[\cut2]) = \ycut2).}
  {Nous avons \(f(\xvalues[\cut1]) = \ycut1).}
}{
 \if{\ycut2 notsametext \empty}{Nous avons \(f(\xvalues[\cut2]) = \ycut2).}
}
#if defined TARGET_imagerestr
 \name_question \(f_I\) ?
<div class="wimscenter">
 \embed{reply1,\size}\embed{reply2,\size},\embed{reply3,\size}\embed{reply4,\size}
</div>

}
\answer{\name_answer[1]}{\lbr;\bracks}{type=clickfill}
\answer{Inf(f)}{\inf;\vlist}{type=clickfill}
\answer{Sup(f)}{\sup}{type=clickfill}
\answer{\name_answer[2]}{\rbr;\bracks}{type=clickfill}
#endif

#if defined TARGET_minmaxrestr
\name_question
<div class="wimscenter">Inf(\(f_I)) = \embed{r1,\size}&nbsp;
Sup(\(f_I\)) = \embed{r2,\size} <br>
Min(\(f_I\)) = \embed{r3,\size}&nbsp;
Max(\(f_I\)) = \embed{r4,\size}
</div>

}

\answer{Inf(\(f_I))}{\inf;\vlist,\non}{type=clickfill}
\answer{Sup(\(f_I))}{\sup}{type=clickfill}
\answer{Min(\(f_I))}{\min}{type=clickfill}
\answer{Max(\(f_I))}{\max}{type=clickfill}

#endif
