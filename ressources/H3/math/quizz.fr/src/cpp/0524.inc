\title{Question 0524 Repérage}
\keywords{coordinates,number_line}
%%% adapatation de 0624

\integer{a=1}
\real{bg=0-0.15}
\real{bd=\a+1.15}
\integer{grad=randint(4,5,5)}
\real{h=1/\grad}
\real{x=\a+randint(1..(\grad-1))*\h}
\real{x=(\x==\a+0.5)? \x+randitem(-0.25,0.25):\x}
\integer{a1=1+\a}

\text{dessin=draw(300,60
xrange \bg,\bd
yrange -3,3
linewidth 1.5
segment \bg,0,\bd,0,black
segment \a-1,-1.5,\a-1,1.5,black
segment \a,-1.5,\a,1.5,black
segment \a+1,-1.5,\a+1,1.5,black
parallel \a+\h,-0.5,\a+\h,0.5,\h,0,\grad-1,black
parallel 0+\h,-0.5,0+\h,0.5,\h,0,\grad-1,black
text black,0,-1.5,large,0
text black,\a,-1.5,large,\a
text black,\a+1,-1.5,large,\a1
linewidth 2
arrow \x,-2.8,\x,-1,10,black
)}

\text{fig0524=<img src="\dessin" alt="">}
\real{rep=\x}
\text{enonce= <table><tr><td>\fig0524</td></tr><tr><td> Le nombre repéré par la flèche est </td></tr></table>}
\text{enonceb=}
\text{feedback=Une graduation vaut \h}
