\title{Question 0301 Moitié ou double}
\keywords{}

%%%%%%%%%%%%%%% question 1 %%%%%
\text{cas=random(double,moitié)}
\integer{a1=\cas issametext double ?random(10..14)*10+5:randint(10..19)*100}
\integer{a2=2*\a1}
\integer{a3=\a1/2}
\integer{rep=\cas issametext moitié ? \a3: \a2}
\text{enonce= \cas issametext moitié ? La moitié de \(\a1\) &#58;:Le double de \(\a1\) &#58; }
\text{enonceb=}
\text{temp0301=\cas issametext double ? Le double de \(\a1\) est \(\a2\). : La moitié de \(\a1\) est \(\a3\).}
\text{feedback=Attention à ne pas confondre la moitié et le double. \temp0301  }
