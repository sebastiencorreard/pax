\title{Question 0304 Patron du cube}
\keywords{cube}

%%%%patron 1 : bonne réponse
\text{fig1=draw(100,100
xrange -5,85
yrange -5,85
rect 0,20,20,40,black
rect 20,20,40,40,black
rect 40,20,60,40,black
rect 60,20,80,40,black
rect 40,40,60,60,black
rect 40,0,60,20,black
)
}
\text{fig2=draw(100,100
xrange -5,85
yrange -5,85
rect 0,0,80,40,black
parallel 0,0,80,0,0,20,3,black
parallel 0,0,0,40,20,0,5,black
)
}
\text{fig3=draw(100,100
xrange -5,85
yrange -5,85
rect 0,20,60,40,black
rect 20,0,40,60,black

)
}
\text{al=shuffle(1,2,3)}
\text{temp=\fig1,\fig2,\fig3}
\integer{rep=position(1,\al)}
\integer{bad1=(1+\al)%3}
\text{enonce=Quel est le patron du cube &#63;<table><tr><td>Figure 1 <br> <img src="\temp[\al[1]]" alt=""></td><td>Figure 2 <br> <img src="\temp[\al[2]]" alt=""></td><td>Figure 3 <br> <img src="\temp[\al[3]]" alt=""></td></tr></table> }
\text{enonceb=}
\text{feedback=}
