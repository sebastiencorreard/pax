\title{Question 0418 Conversion litres }
\keywords{mental_calculation,conversion,volume}

\integer{a=randint(2..9)*randint(10,100,1000)}
\text{um=randomitem(cL,dL)}
\real{rep=\um issametext cL ?\a/100:\a/10}

\text{enonce=Complète &#58; \(\a\) \um =  }
\text{enonceb= L.}
\text{temp18=\um issametext cL ?\(100 \) cL = \(1\) L:\(10\) dL = \(1\) L}
\text{feedback=Rappel &#58; \temp18 }
