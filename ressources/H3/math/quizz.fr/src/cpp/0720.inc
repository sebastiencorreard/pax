\title{Question 0720 Repérage}
\keywords{coordinates,number_line}
%%% adapatation de 0424

\integer{a=randint(2..7)*10+randint(2,3,4)}
\real{bg=\a-0.15}
\real{bd=\a+1.15}
\integer{grad=5}
\real{h=1/\grad}
\real{x=\a+randint(1..(\grad-1))*\h}
\real{x=(\x==\a+0.5)? \x+randitem(-0.25,0.25):\x}
\integer{a1=1+\a}

\text{dessin=draw(300,60
xrange \bg,\bd
yrange -3,3
linewidth 1.5
segment \bg,0,\bd,0,black
segment \a,-1.5,\a,1.5,black
segment \a+1,-1.5,\a+1,1.5,black
parallel \a+\h,-0.5,\a+\h,0.5,\h,0,\grad-1,black
text black,\a,-1.5,large,\a
text black,\a+1,-1.5,large,\a1
linewidth 2
text black,\x,-1.5,large,A
crosshair \x,0,black

)}

\text{fig24=<img src="\dessin" alt="Repère">}
\real{rep=\x}
\text{enonce= <div class="wimscenter">\fig24</div> L'abscisse du point A est &#58;}
\text{enonceb=}
\text{feedback=Une graduation vaut \h}
