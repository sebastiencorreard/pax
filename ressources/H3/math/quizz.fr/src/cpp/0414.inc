\title{Question 0414 Soustraction durées}
\keywords{time,mental_calculation}
\text{opmot=randomitem(Enlève,Ajoute)}
\text{temp=shuffle(15,30,45)}
\integer{a=\temp[1]}
\integer{h=randint(9..15)}
\integer{m=\temp[2]}
\integer{temp00=\opmot issametext Ajoute? \a+\m:\m-\a}
\if{\temp00>59}{
\integer{reph=\h+1}
\integer{repm=\temp00-60}}
{
\if{\temp00<0}{
\integer{reph=\h-1}
\integer{repm=\temp00+60}
}{
\integer{reph=\h}
\integer{repm=\temp00}
}}
\integer{rep=\reph}
\integer{repb=\repm}
\text{enonce=\opmot \(\a\) minutes à \(\h\) h \(\m\). <br> }
\text{enonceb=h}
\text{enoncec=min}
\text{feedback=}
