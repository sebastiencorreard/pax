\text{prob=Méthode de Monte-Carlo : Calcul d'intégrale complexe}

\integer{nfct=randint(1..2)}
\text{list_fct_js=1/(1+Math.pow(x,2)),x*(1-x)*Math.pow((Math.sin(200*x*(1-x))),2)}
\text{fct_js=\list_fct_js[\nfct]}
\text{list_fct_pari=1/(1+t^2),t*(1-t)*(sin(200*t*(1-t)))^2}
\text{fct_pari=\list_fct_pari[\nfct]}
\text{fct_ecr=wims(replace t by x in \fct_pari)}
\text{fct_ecr=maxima(simplify(\fct_ecr))}
\text{fct_ecr=texmath(\fct_ecr)}
\matrix{list_rrint=pi/4,0.0558}
\text{rrint=\list_rrint[\nfct]}
\text{val_int=\rrint}
\text{rrint=(\nfct==1)?\rrint}
\real{rrint=(\nfct==2)?\rrint/0.25}

\rational{coordxM=0.8}
\rational{coordyM=(\nfct==1)?0.25:0.05}
\rational{coordyB=(\nfct==1)?1:0.25}
\rational{coordyC=(\nfct==1)?1:0.25}
\rational{xmin=-0.1}
\rational{xmax=1.1}
\rational{ymin=(\nfct==1)?-0.1:-0.05}
\rational{ymax=(\nfct==1)?1.1:0.3}

\rational{A_r=(\nfct==1)?1:0.25}

\text{ineqe1=\(0<x<1\)}
\text{ineqe2=(\nfct==1)?\(0<y<1\):\(0<y<0.25\)}

\text{coeff=(\nfct==2)? ??}


\text{car=(\nfct==1)?carré:rectangle}
