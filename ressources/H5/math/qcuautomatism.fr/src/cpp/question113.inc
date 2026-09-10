\title{Question 113 S Conversion}
\keywords{quizz,power,calculation,conversion}
\observation{Question du sujet zéro sujet-specialite-2_0.pdf publié sur EDUSCOL en juin 2025 }
\real{n=randint(2..4)+randomitem(0.02,0.01,0.03)*randomitem(1,-1)}
\real{nbad=rint(100/\n)/100}
\real{nbad2=randint(15..35)/10*\n}
\real{nbad2=rint(\nbad2*100)/100}
\real{nbad3=randint(15..35)*\n}
\real{nbad3=rint(\nbad3*100)/100}
\real{d=3.6}
\integer{p=\d*\n*10}
\real{p=\p/10}%%% arrondi au dixième

\text{enonce=Un appareil a besoin d’une énergie de \(\p \times 10^6\) Joules (J) pour se mettre en route.
<br>À combien de kiloWatts-heure (kWh) cela correspond-il&nbsp;&#63; <br><u><i>Données&nbsp;&#58;</i></u> \(1\) kWh \({}= \d \times 10^6 \) J}


%%%%

\text{good=\(\n \thinspace kWh\)}
\text{bads=\(\nbad \thinspace kWh\),\(\nbad2 \thinspace kWh\),\(\nbad3 \thinspace kWh\)}
%%% feed
\integer{nround=\n}
\text{feedback=La bonne réponse est \good.<br> On peut noter que \(\p \times 10^6\) est environ égal à \(\nround\) fois <span class="nowrap">\(\d \times 10^6 \).</span><br> La réponse la plus proche est donc <span class="nowrap">\good.</span>}
