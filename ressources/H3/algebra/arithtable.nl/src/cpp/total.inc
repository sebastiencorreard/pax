
\answer{Box 1}{\r1;\(\sh[1])}{type=dragfill}
\answer{Box 2}{\r2;\(\sh[2])}{type=dragfill}
\answer{Box 3}{\r3;\(\sh[3])}{type=dragfill}
\answer{Box 4}{\r4;\(\sh[4])}{type=dragfill}
\answer{Box 5}{\r5;\(\sh[5])}{type=dragfill}
\answer{Box 6}{\r6;\(\sh[6])}{type=dragfill}
\answer{Box 7}{\r7;\(\sh[7])}{type=dragfill}
\answer{Box 8}{\r8;\(\sh[8])}{type=dragfill}
\answer{Box 9}{\r9;\(\sh[9])}{type=dragfill}
\answer{Box 10}{\r10;\(\sh[10])}{type=dragfill}
\answer{Box 11}{\r11;\(\sh[11])}{type=dragfill}
\answer{Box 12}{\r12;\(\sh[12])}{type=dragfill}
\answer{Box 13}{\r13;\(\sh[13])}{type=dragfill}
\answer{Box 14}{\r14;\(\sh[14])}{type=dragfill}
\answer{Box 15}{\r15;\(\sh[15])}{type=dragfill}
\answer{Box 16}{\r16;\(\sh[16])}{type=dragfill}

\text{rvals=wims(replace internal \ by \empty in
  \r1,\r2,\r3,\r4,\r5,\r6,\r7,\r8,\r9,\r10,\r11,\r12,\r13,\r14,\r15,\r16)}

\text{crows=}
\for{x=1 to \rows}{
 \text{r2=wims(replace , by \op1 in \rvals[(\x-1)*\cols+1..\x*\cols])}
 \text{cr=maxima(expand((\rowvals[\x])-(\r2)))}
 \text{crows=wims(append item \cr to \crows)}
}

\text{ccols=}
\for{y=1 to \cols}{
 \text{c2=wims(replace , by \op2 in \rvals[wims(values \cols*(x-1)+\y for x=1 to \rows)])}
 \text{cc=maxima(expand((\colvals[\y])-(\c2)))}
 \text{ccols=wims(append item \cc to \ccols)}
}

\condition{\Name1 of row 1 equals \(\rowvals[1])}{\crows[1] iswordof 0 0.0}
\condition{\Name1 of row 2 equals \(\rowvals[2])}{\crows[2] iswordof 0 0.0}
#if ROWS > 2
\condition{\Name1 of row 3 equals \(\rowvals[3])}{\crows[3] iswordof 0 0.0}
#endif
#if ROWS > 3
\condition{\Name1 of row 4 equals \(\rowvals[4])}{\crows[4] iswordof 0 0.0}
#endif

\condition{\Name2 of column 1 equals \(\colvals[1])}{\ccols[1] iswordof 0 0.0}
\condition{\Name2 of column 2 equals \(\colvals[2])}{\ccols[2] iswordof 0 0.0}
#if COLS > 2
\condition{\Name2 of column 3 equals \(\colvals[3])}{\ccols[3] iswordof 0 0.0}
#endif
#if COLS > 3
\condition{\Name2 of column 4 equals \(\colvals[4])}{\ccols[4] iswordof 0 0.0}
#endif
#if COLS > 4
\condition{\Name2 of column 5 equals \(\colvals[5])}{\ccols[5] iswordof 0 0.0}
#endif
#if COLS > 5
\condition{\Name2 of column 6 equals \(\colvals[6])}{\ccols[6] iswordof 0 0.0}
#endif
#if COLS > 6
\condition{\Name2 of column 7 equals \(\colvals[7])}{\ccols[7] iswordof 0 0.0}
#endif

