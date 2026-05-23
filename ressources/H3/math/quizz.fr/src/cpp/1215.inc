\title{Question 1215 Coordonnées et vecteurs colinéaires}
\keywords{mental_calculation, vectors,coordinates}
%%%%%%%%%Question 8 %%%%%%%%%%%%%%%%%%%%%%%
\text{question=shuffle(2,3,5,7,6,9)}
\real{xa=\question[1]}
\real{ya=\question[2]}
\real{k=\question[3]/10}
\real{xb=\k*\xa}
\real{yb=\k*\ya}
\text{cas=random(x,y)}
\real{rep=\cas issametext x ? \xb : \yb}
\matrix{u=\xa;\ya}
\matrix{v=\cas issametext x ? x;\yb :\xb;y}
\text{txtsol1=\cas issametext x ? \(\yb= \k \times \ya\):\(\xb= \k \times \xa\)}
\text{txtsol2=\cas issametext x ? \(x= \k \times \xa\):\(y= \k \times \ya\)}
\text{enonce=\(\overrightarrow{u}\)\([\u]\) et \(\overrightarrow{v}\)\([\v]\) <br> sont colinéaires si &#58; \(\cas =\) }
\text{enonceb=}
\text{feedback=On observe que \txtsol1, <br>donc \txtsol2. }
