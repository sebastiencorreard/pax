#if defined TARGET_eqexpo6
\text{name_sol=En posant \(X=e^x\) avec \(x\neq \sing2\) (\(\sing2\) est une valeur
  interdite), l'équation de départ est équivalente à \(X^2-(\X1+\X2)X+e^{\tp}=0\).
  On résout cette équation du second degré en \(X\).
  On trouve \(X_1=\X1\) et \(X_2=\X2\).
  On résout alors, pour \(x\neq \sing2\), les équations \(e^x=\X1\) et \(e^x=\X2\),
  ce qui donne pour unique solution : \(\rep[1]\).}
#endif
#if defined TARGET_eqexpo5 || defined TARGET_eqexpo6
\text{name_tsol1=En posant \(X=e^x\), l'équation de départ est équivalente à
  \(X^2-(\X1-\X2)X-e^{\tp}=0\).
  On résout cette équation du second degré en \(X\): on trouve \(X_1=\X1\) et \(X_2=-\X2\).<br>
  On résout alors les équations \(e^x=\X1\), ce qui donne une solution \(x_1=\rep[1]\)
  et \(e^x=-\X2\) qui n'a pas de solution dans \(\,\RR\).}
\text{name_tsol2=En posant \(X = e^x\), l'équation de départ est équivalente à \(X^2-(\X1+\X2)X+e^{\tp}=0\).
  On résout cette équation du second degré en \(X\).}
\text{name_tsol3=Il n'y a pas de solution dans \(\,\RR\), donc l'équation initiale n'a pas de solution.}
\text{name_tsol4=On trouve \(X_1=\X1\) et \(X_2=\X2\).
  On résout alors les équations \(e^x=\X1\) et \(e^x=\X2\),
  ce qui donne deux solutions \(x_1=\rep[1]\) et \(x_2=\rep[2]\).}
#endif
