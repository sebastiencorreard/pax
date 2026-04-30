\text{prob=Méthode de Monte-Carlo : Calcul d'intégrale}

\rational{xmin=-0.1}
\rational{xmax=1.1}
\rational{ymin=-0.1}
\rational{ymax=1.1}

\text{ineqe1=\(0<x<1\)}
\text{ineqe2=\(0<y<1\)}

\integer{nfct=randint(2..5)}
\text{fct_js=Math.pow(x,\nfct)}
\text{fct_pari=t^{\nfct}}
\text{fct_ecr=x^{\nfct}}
\rational{val_int=1/(\nfct+1)}
\rational{rrint=1/(\nfct+1)}

\rational{coordxM=0.8}
\rational{coordyM=0.25}
\rational{coordyB=1}
\rational{coordyC=1}

\rational{A_r=1}
