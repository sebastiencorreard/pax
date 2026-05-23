\title{Question T1121 Intervalle}
\keywords{intervals,inequalities}
%%%%%%%%%%%%%% Question 21 %%%%%%%%%%%%

\integer{x1=randint(-12..3)}
\integer{x2=randint(5..20)}
%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice ###
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{ptvirg=&#59;}

\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le \)}
\text{symboles=\slt,\sle,\sgt,\sge}
\integer{symbx1=randint(1..2)}
\integer{symbx2=randint(1..2)}
\text{croc1=\symbx1=1?\crocd:\crocg}
\text{croc2=\symbx2=1?\crocg:\crocd}
\text{brep=\croc1,\x1,\ptvirg,\x2,\croc2}
\text{badcroc1=\symbx1=2?\crocd:\crocg}
\text{badcroc2=\symbx2=2?\crocg:\crocd}
\text{bad1=\badcroc1\x1\ptvirg\x2\croc2}
\text{bad2=\croc1\x1\ptvirg\x2\badcroc2}
\text{bad3=\badcroc1\x1\ptvirg\x2\badcroc2}
\text{bad4=\badcroc1\x2\ptvirg\x1\badcroc2}
\text{bad5=\croc1\x2\ptvirg\x1\croc2}

\text{brepf=wims(replace internal , by in \brep)}
\text{eqx=\x1 \symboles[\symbx1] \(x\) \symboles[\symbx2] \x2 }
\text{lstrep=\brepf,\bad1,\bad2,\bad3,\bad4,\bad5}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\text{enonce=  Traduire par un intervalle \eqx :<br>}
\text{enonceb=<div class="wims_instruction">Faire glisser les vignettes bleues pour former la réponse.</div>}
\text{rep=\brepf;\lstrep}
\text{size=75x35x1}
\text{feedback=}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\text{lstrepcourse=shuffle(\lstrep)}
\text{k=position(\brepf,\lstrepcourse)}

\text{enoncebcourse=<div class="wims_instruction">Marquer la bonne réponse en cliquant dessus.</div>}
\text{repcourse=\k;\lstrepcourse}
