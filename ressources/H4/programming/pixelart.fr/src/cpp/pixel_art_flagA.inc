\title{Pixel Art et les Drapeaux A}
\text{prob=Pixel Art et les Drapeaux difficiles}
\integer{x1=randint(1..3)}
\matrix{pays=de la Guyanne,Guyanais,320px-Flag_of_Guyana.svg.png,if((i==19-round(3/8*j))||(i==round(3/8*j)),[255,255,255],if((i>19-round(3/8*j))||(i<round(3/8*j)),[0,158,73],if((i==19-round(3/4*j) && j<=13)||(i==round(3/4*j) && j<=13),[0,0,0],if((i>19-round(3/4*j) && (j<=13 || i<=13))||(i<round(3/4*j) && (j<=13 || i<=13)),[252,209,22],[206,17,38]))))
de la République du Congos,Congolais,Flag_of_the_Republic_of_the_Congo.svg.png,if((i<=-j+18),[0,149,67],if(i<=-j+25,[251,222,74],[218,26,53]))
de la Grèce,Grec,Flag_of_Greece.svg.png,if(i%4==1 || (1<=i && i<=10 && 1<=j && j<=10 && (i<>4 || i<>5 || j<>4 || j<>5)) ||  (i%4==2 || (1<=i && i<=10 && 1<=j && j<=10 && (i<>4 || i<>5 || j<>4 || j<>5))),[13,94,175],[255,255,255])
de la Macédoine du Nord,Macédonien,Flag_of_North_Macedonia.svg.png,if( (i>=18-3/4*j && i<=-11/10*j+22)|| (i<=18-3/4*j && i>=-11/11*j+22),[248,233,46],[216,33,38])
}

\text{nc=(\pays[\x1;5]==)?24:\pays[\x1;5]}
\text{nl=(\pays[\x1;6]==)?18:\pays[\x1;6]}

\text{DD=pari(m=matrix(\nl,\nc,i,j,\pays[\x1;4]);)}
\text{DD=(\x1==3)?pari(m=matrix(\nl,\nc,i,j,if((5<=j && j<=6 && 1<=i && i<=10)||(1<=j && j<=10 && 5<=i && i<=6),[255,255,255],m[i,j]));)}