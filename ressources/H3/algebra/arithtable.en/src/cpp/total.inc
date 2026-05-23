
\answer{\name_case 1}{\r1;\(\sh[1])}{type=dragfill}
\answer{\name_case 2}{\r2;\(\sh[2])}{type=dragfill}
\answer{\name_case 3}{\r3;\(\sh[3])}{type=dragfill}
\answer{\name_case 4}{\r4;\(\sh[4])}{type=dragfill}
\answer{\name_case 5}{\r5;\(\sh[5])}{type=dragfill}
\answer{\name_case 6}{\r6;\(\sh[6])}{type=dragfill}
\answer{\name_case 7}{\r7;\(\sh[7])}{type=dragfill}
\answer{\name_case 8}{\r8;\(\sh[8])}{type=dragfill}
\answer{\name_case 9}{\r9;\(\sh[9])}{type=dragfill}
\answer{\name_case 10}{\r10;\(\sh[10])}{type=dragfill}
\answer{\name_case 11}{\r11;\(\sh[11])}{type=dragfill}
\answer{\name_case 12}{\r12;\(\sh[12])}{type=dragfill}
\answer{\name_case 13}{\r13;\(\sh[13])}{type=dragfill}
\answer{\name_case 14}{\r14;\(\sh[14])}{type=dragfill}
\answer{\name_case 15}{\r15;\(\sh[15])}{type=dragfill}
\answer{\name_case 16}{\r16;\(\sh[16])}{type=dragfill}

\text{rvals=wims(replace internal \ by \empty in
  \r1,\r2,\r3,\r4,\r5,\r6,\r7,\r8,\r9,\r10,\r11,\r12,\r13,\r14,\r15,\r16)}

\text{crows=}
\for{x=1 to \rows}{
 \text{r2=wims(replace , by \op1 in \rvals[(\x-1)*\cols+1..\x*\cols])}
 \if{\randtype issametext computed}{
  \real{cr=\rowvals[\x]-(\r2)}
 }{
  \text{cr=maxima(expand((\rowvals[\x])-(\r2)))}
 }
 \text{cr=\cr issametext ?NaN}
 \integer{cr=\modbase notsametext?\cr%\modbase}
 \text{crows=wims(append item \cr to \crows)}
}

\text{ccols=}
\for{y=1 to \cols}{
 \text{c2=wims(replace , by \op2 in \rvals[wims(values \cols*(x-1)+\y for x=1 to \rows)])}
 \if{\randtype issametext computed}{
  \real{cc=\colvals[\y]-(\c2)}
 }{
  \text{cc=maxima(expand((\colvals[\y])-(\c2)))}
 }
 \text{cc=\cc issametext ?NaN}
 \integer{cc=\modbase notsametext?\cc%\modbase}
 \text{ccols=wims(append item \cc to \ccols)}
}

\condition{\Name1 \ofrow 1 \tequals \(\rowvals[1])}{\crows[1] = 0}
\condition{\Name1 \ofrow 2 \tequals \(\rowvals[2])}{\crows[2] = 0}
#if ROWS > 2
\condition{\Name1 \ofrow 3 \tequals \(\rowvals[3])}{\crows[3] = 0}
#endif
#if ROWS > 3
\condition{\Name1 \ofrow 4 \tequals \(\rowvals[4])}{\crows[4] = 0}
#endif

\condition{\Name2 \ofcol 1 \tequals \(\colvals[1])}{\ccols[1] = 0}
\condition{\Name2 \ofcol 2 \tequals \(\colvals[2])}{\ccols[2] = 0}
#if COLS > 2
\condition{\Name2 \ofcol 3 \tequals \(\colvals[3])}{\ccols[3] = 0}
#endif
#if COLS > 3
\condition{\Name2 \ofcol 4 \tequals \(\colvals[4])}{\ccols[4] = 0}
#endif
#if COLS > 4
\condition{\Name2 \ofcol 5 \tequals \(\colvals[5])}{\ccols[5] = 0}
#endif
#if COLS > 5
\condition{\Name2 \ofcol 6 \tequals \(\colvals[6])}{\ccols[6] = 0}
#endif
#if COLS > 6
\condition{\Name2 \ofcol 7 \tequals \(\colvals[7])}{\ccols[7] = 0}
#endif
