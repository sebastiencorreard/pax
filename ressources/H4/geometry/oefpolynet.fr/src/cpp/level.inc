\text{parm=\confparm1=?1:\confparm1}
niveau selon le nombre de faces
#if defined TARGET_31 || defined TARGET_32
\text{level=\parm=1?1,10}
\text{level=\parm=2?11,20}
\text{level=\parm=3?21,25}
\text{level=\parm=4?26,35}
\text{index=wims(record 0 of data/polyedre_off/index2)}
\text{poly=wims(select \index where column 2>=\level[1] and column 2<\level[2])}
#else
\text{level=\parm=1?randrow(4,5
6,7
7,8
8
8,9
8,10)}
\text{level=\parm=2?randrow(11
12
12,13
13,14
15,16
17
18
19)}
\text{level=\parm=3?randrow(20,21
22
24
26
27,30
32)}
\text{level=\parm=4?randrow(34,37
38,42
47,52
60
62)}
\text{index=wims(record 0 of data/polyedre_off/index2)}
\text{poly=wims(select \index where column 3 isitemof \level)}
#endif
\text{polycnt=rows(\poly)}
\text{choix=shuffle(\polycnt)}
