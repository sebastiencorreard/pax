target= litt1 litt2 fract1 brevet01 brevet02 brevet03 brevet04 brevet05
\author{Jean-Luc, Donadoni}
\email{jluc.donadoni@laposte.net}

\text{consigne= Cliquez sur les bonnes réponses.
<div class="wims_instruction">Une seule bonne réponse par question.</div> }
#if defined TARGET_litt1
\title{QCM Calcul littéral 1}
\keywords{literal_calculation}
\matrix{enr1=wims(record 1 of litteral1)}
\matrix{enr2=wims(record 2 of litteral1)}
\matrix{enr3=wims(record 3 of litteral1)}
\matrix{enr4=wims(record 4 of litteral1)}
\matrix{enr5=wims(record 5 of litteral1)}
#endif

#if defined TARGET_litt2
\title{QCM Calcul littéral 2}
\keywords{quizz,literal_calculation}
\matrix{enr1=wims(record 1 of litteral2)}
\matrix{enr2=wims(record 2 of litteral2)}
\matrix{enr3=wims(record 3 of litteral2)}
\matrix{enr4=wims(record 4 of litteral2)}
\matrix{enr5=wims(record 5 of litteral2)}
#endif

#if defined TARGET_fract1
\title{QCM Ecriture fractionnaire 1}
\keywords{fraction}
\matrix{enr1=wims(record 1 of fraction1)}
\matrix{enr2=wims(record 2 of fraction1)}
\matrix{enr3=wims(record 3 of fraction1)}
\matrix{enr4=wims(record 4 of fraction1)}
\matrix{enr5=wims(record 5 of fraction1)}
#endif

#if defined TARGET_brevet01
\title{QCM Sujet brevet 1}
\keywords{3_shape,gcd_lcm,volume,power}
\matrix{enr1=wims(record 1 of brevet01)}
\matrix{enr2=wims(record 2 of brevet01)}
\matrix{enr3=wims(record 3 of brevet01)}
\matrix{enr4=wims(record 4 of brevet01)}
\matrix{enr5=wims(record 5 of brevet01)}
#endif

#if defined TARGET_brevet02
\title{QCM Sujet brevet 2}
\keywords{fraction,literal_calculation,area,inequations}
\matrix{enr1=wims(record 1 of brevet02)}
\matrix{enr2=wims(record 2 of brevet02)}
\matrix{enr3=wims(record 3 of brevet02)}
\matrix{enr4=wims(record 4 of brevet02)}
\matrix{enr5=wims(record 5 of brevet02)}
#endif

#if defined TARGET_brevet03
\title{QCM Sujet brevet 3}
\matrix{enr1=wims(record 1 of brevet03)}
\matrix{enr2=wims(record 2 of brevet03)}
\matrix{enr3=wims(record 3 of brevet03)}
\matrix{enr4=wims(record 4 of brevet03)}
\matrix{enr5=wims(record 5 of brevet03)}
#endif

#if defined TARGET_brevet04
\title{QCM Sujet brevet 4}
\matrix{enr1=wims(record 1 of brevet04)}
\matrix{enr2=wims(record 2 of brevet04)}
\matrix{enr3=wims(record 3 of brevet04)}
\matrix{enr4=wims(record 4 of brevet04)}
\matrix{enr5=wims(record 5 of brevet04)}
#endif

#if defined TARGET_brevet05
\title{QCM Sujet brevet 5}

\matrix{enr1=wims(record 1 of brevet05)}
\matrix{enr2=wims(record 2 of brevet05)}
\matrix{enr3=wims(record 3 of brevet05)}
\matrix{enr4=wims(record 4 of brevet05)}
\matrix{enr5=wims(record 5 of brevet05)}
#endif

\text{quest1=\enr1[1;]}
\text{quest2=\enr2[1;]}
\text{quest3=\enr3[1;]}
\text{quest4=\enr4[1;]}
\text{quest5=\enr5[1;]}

\matrix{corr1=}
\matrix{corr2=}
\matrix{corr3=}
\matrix{corr4=}
\matrix{corr5=}
\matrix{reps1=}
\matrix{reps2=}
\matrix{reps3=}
\matrix{reps4=}
\matrix{reps5=}
\matrix{rep1=}
\matrix{rep2=}
\matrix{rep3=}
\matrix{rep4=}
\matrix{rep5=}

\for{i=2 to 5}{\matrix{corr1=wims(append item \enr1[\i;] to \corr1)}}
\matrix{corr1=shuffle(\corr1)}
\for{i=2 to 5}{\matrix{corr2=wims(append item \enr2[\i;] to \corr2)}}
\matrix{corr2=shuffle(\corr2)}
\for{i=2 to 5}{\matrix{corr3=wims(append item \enr3[\i;] to \corr3)}}
\matrix{corr3=shuffle(\corr3)}
\for{i=2 to 5}{\matrix{corr4=wims(append item \enr4[\i;] to \corr4)}}
\matrix{corr4=shuffle(\corr4)}
\for{i=2 to 5}{\matrix{corr5=wims(append item \enr5[\i;] to \corr5)}}
\matrix{corr5=shuffle(\corr5)}

\for{i=1 to 4}{
    \integer{test=wims(char 1 of \corr1[\i])}
    \text{reponse=wims(char 3 to -1 of \corr1[\i])}
    \if{\test=1}{\matrix{rep1=wims( append item \i to \rep1)}}
    \matrix{reps1=wims(append item \reponse to \reps1)}}

\for{i=1 to 4}{
    \integer{test=wims(char 1 of \corr2[\i])}
    \text{reponse=wims(char 3 to -1 of \corr2[\i])}
    \if{\test=1}{\matrix{rep2=wims( append item \i to \rep2)}}
    \matrix{reps2=wims(append item \reponse to \reps2)}}

\for{i=1 to 4}{
    \integer{test=wims(char 1 of \corr3[\i])}
    \text{reponse=wims(char 3 to -1 of \corr3[\i])}
    \if{\test=1}{\matrix{rep3=wims( append item \i to \rep3)}}
    \matrix{reps3=wims(append item \reponse to \reps3)}}

\for{i=1 to 4}{
    \integer{test=wims(char 1 of \corr4[\i])}
    \text{reponse=wims(char 3 to -1 of \corr4[\i])}
    \if{\test=1}{\matrix{rep4=wims( append item \i to \rep4)}}
    \matrix{reps4=wims(append item \reponse to \reps4)}}

\for{i=1 to 4}{
    \integer{test=wims(char 1 of \corr5[\i])}
    \text{reponse=wims(char 3 to -1 of \corr5[\i])}
    \if{\test=1}{\matrix{rep5=wims( append item \i to \rep5)}}
    \matrix{reps5=wims(append item \reponse to \reps5)}}

\matrix{rep1=wims(nonempty items \rep1)}
\matrix{reps1=wims(nonempty items \reps1)}

\matrix{rep2=wims(nonempty items \rep2)}
\matrix{reps2=wims(nonempty items \reps2)}

\matrix{rep3=wims(nonempty items \rep3)}
\matrix{reps3=wims(nonempty items \reps3)}

\matrix{rep4=wims(nonempty items \rep4)}
\matrix{reps4=wims(nonempty items \reps4)}

\matrix{rep5=wims(nonempty items \rep5)}
\matrix{reps5=wims(nonempty items \reps5)}

\statement{\consigne
<table class="wimscenter wimsborder">
<tr><th>QUESTIONS</th><th>A</th>
<th>B</th><th>C</th>
<th>D</th></tr>

<tr><td>\quest1</td>
\for{r=1 to 4}{<td>\embed{r1,\r}</td>}</tr>

<tr><td>\quest2</td>
\for{r=1 to 4}{<td>\embed{r2,\r}</td>}</tr>

<tr><td>\quest3</td>
\for{r=1 to 4}{<td>\embed{r3,\r}</td>}</tr>

<tr><td>\quest4</td>
\for{r=1 to 4}{<td>\embed{r4,\r}</td>}</tr>

<tr><td>\quest5</td>
\for{r=1 to 4}{<td>\embed{r5,\r}</td>}</tr>
</table>}
\answer{}{\rep1;\reps1}{type=mark}{option=split noanalyzeprint}{weight=1}
\answer{}{\rep2;\reps2}{type=mark}{option=split noanalyzeprint}{weight=1}
\answer{}{\rep3;\reps3}{type=mark}{option=split noanalyzeprint}{weight=1}
\answer{}{\rep4;\reps4}{type=mark}{option=split noanalyzeprint}{weight=1}
\answer{}{\rep5;\reps5}{type=mark}{option=split noanalyzeprint}{weight=1}

\solution{Dans le tableau, les bonnes réponses sont coloriées en vert,
les mauvaises en rouge et les réponses oubliées en bleu.}
