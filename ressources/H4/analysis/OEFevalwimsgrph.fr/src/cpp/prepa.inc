\integer{numa=randint(1..10)*random(1,-1)}
\rational{a=simplify(\numa/(\dena))}

\integer{numb=randint(1..10)*random(1,-1)}
\rational{b=simplify(\numb/(\denb))}

\integer{numc=randint(1..10)^2*random(1,-1)}
\rational{c=simplify(\numc/(\denc))}

\integer{numd=randint(1..10)*random(1,-1)}
\rational{d=simplify(\numd/(\dend))}

\integer{nume=randint(1..10)*random(1,-1)}
\rational{e=simplify(\nume/(\dene))}

\integer{numf=randint(1..10)*random(1,-1)}
\rational{f=simplify(\numf/(\denf))}

\integer{g=randint(2..5)*random(1,-1)}
\integer{h=randint(2..5)*random(1,-1)}

%%%% choix de la question
\integer{sensineq=random(1..2)}
\integer{strictineq=random(0..1)}
\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le )}
%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%%%
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}

\text{crochg=\strictineq=0?\crocd:\crocg}
\text{crochd=\strictineq=0?\crocg:\crocd}

%%%% préparation de la question
\text{symb=\slt,\sgt,\sle,\sge}
\text{wsymb=<,>,<=,>=}
\integer{indsymb=\sensineq+2*\strictineq}
