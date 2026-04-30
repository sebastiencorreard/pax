// horrid amateur scriblings: no need for copyrights...
// needs "rewriting"... 
// js-function ReadApplet() returns: total time
// and lines with:
// time1:freq1 \n
// time2:freq2 \n
// time3:freq1 \n
// ...
// time_max:freq_max \n

// Applet params: 
// max=number of correct hits [default 20 : minimal 5, maximal 60]
// renew=yes : every click a new image [default]
// renew=no  : only a new image if clicked on the correct image
// lang=nl,en,fr [default en]
// show_result=yes,no : show the stat-data in the applet in a primitive tabel  [default yes]

import java.applet.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;

public class VreemdeEend1 extends Applet implements Runnable{
    private static final long serialVersionUID = 1L;
    Graphics2D g;
    Image backbuffer;
    Graphics2D backg;
    Font font;
    String replystring="";
    int xsize=160;int ysize=160;int sx=80;
    //enkel plaatje 160x160 heeft 4 hokjes ...hokje is dus 80x80
    int xmax=4*xsize;int ymax=ysize;    
    int keuze[]={0,1,2,3};int kans[]={0,1};int polies[]={0,1,2,3};int kleuren[]={0,1,2,3,4,5,6,7};
    int xobject[][][]={
    {{10,70,30,70,10,10},{10,70,70,10,50,10},{10,70,70,40,10,10},{10,40,70,70,10,10}},
    {{10,70,70,10,10},{10,70,70,10,10},{10,70,70,10,10},{10,70,70,10,10}},
    {{40,70,10,40},{10,70,40,10},{10,70,10,10},{70,10,70,70}},
    {{10,70,10,10},{10,70,70,10},{10,70,70,10},{10,70,10,10}}
    };
    int yobject[][][]={
    {{10,10,40,70,70,10},{10,10,70,70,40,10},{10,10,70,40,70,10},{10,40,10,70,70,10}},
    {{10,10,70,70,10},{10,10,70,70,10},{10,10,70,70,10},{10,10,70,70,10}},
    {{10,70,70,10},{10,10,70,10},{10,40,70,10},{10,40,70,10}},
    {{10,70,70,10},{70,10,70,70},{10,10,70,10},{10,10,70,10}}
    };
    int colors[][] = {{250,0,0},{0,250,0},{0,0,250},{250,250,0},{250,0,250},{0,250,250},{0,0,0},{255,255,255}}; 

    int fout=0;int anders=0;long begin;int klaar;int goedzo=0;
    int dx;int dy;long start;int poging_counter=1;double diff;
    int max=20;String duration="" ;int counter=1;int first_try=1;
    long stop;public long totaltime=0;Font defaultFont = new Font("Courier",0, 14);
    public Image ok;public Image nok;String time="time in seconds";
    String freq="attempts";String teller="number";String ready_string="DONE";int show_result=1;int do_paint=1;
    
    public void init(){
	font  = new Font("TimesRoman",Font.BOLD,16);  
	ok=getImage(getCodeBase(), "ok.gif");nok=getImage(getCodeBase(), "nok.gif"); 
	begin=System.currentTimeMillis();klaar=0;
	String c=getParameter("max");if(c!=null && c.length()>0){max = Integer.parseInt(c, 10); if(max>60){max=60;} if(max<2){max=5;}}
	String renew=getParameter("renew");if(renew!= null && renew.equals("no")){first_try=0;}
	String lang=getParameter("language");
	if(lang != null){
	    if(lang.equals("nl")){time="tijd in seconden";freq="pogingen";teller="nummer";ready_string="KLAAR";}
	    if(lang.equals("fr")){time="temps (sec.)";freq="tentatives";teller="numero";ready_string="FINI";}
	}
	backbuffer = createImage(xmax,ymax+50); // 50 is voor ok/nok plaatje                            
        backg = (Graphics2D) backbuffer.getGraphics(); 	    
	String show=getParameter("show_result");if(show != null){if(show.equals("no")){show_result=0;}}	
	addMouseListener(
	    new MouseAdapter(){
		public void mousePressed(MouseEvent e){
		    dx = e.getX();
		    dy = e.getY();
		    if(klaar==0){
			for(int p=0;p<4;p++){
			    if(dy>0 && dy<ymax){
				if(dx>p*xsize && dx<(p+1)*xsize){
				    if(fout==p){
					stop=System.currentTimeMillis();
					diff=(double)(Math.round(1000*(stop-start)))/1000000;
					duration=duration+","+diff;
					replystring=replystring+"\n"+diff+" : "+poging_counter;
					poging_counter=1;
				        counter++;goedzo=1;do_paint=1;
					if(counter> max){klaar=1;}
					start=System.currentTimeMillis();
				    }
				    else
				    {
					goedzo=0;
					poging_counter++;
				    }
				}
			    }
			}
		    prepaint();
		    }
		    else
		    {
			ready();
		    }
		}
	    }
	);
	prepaint(); 
    }

    public static int[] Shuffle(int[] S){
	    int ll= S.length;

	    for (int i=0;i<ll;i++){
		int r = (int) (Math.random() * (i+1));
		int swap = S[r];
		S[r] = S[i];
		S[i] = swap;
	    }
	    for(int i=0;i<ll;i++){
            //System.out.println(S[i]);
	    }
        return S;
    }
    
    public void update( Graphics g ) { 
        g.drawImage( backbuffer, 0, 0, this );
        getToolkit().sync();
    }
    public void paint( Graphics g ) {                                                                                                      
      update( g );
      if(counter == 1){start = System.currentTimeMillis();}
    }  
    
    public synchronized void ready(){
	font  = new Font("TimesRoman",Font.BOLD,14);
	backg.setFont(font);
	if(show_result == 1){// finished: show "table" with time:freq
    	    backg.setColor(Color.black);backg.fillRect(0,0,xmax,ymax+50);
	    StringTokenizer q = new StringTokenizer(replystring, "\n");
	    int m=q.countTokens();
	    String sub="";int X=10;int Y=10;
	    backg.setColor(Color.white);
	    backg.drawString("t : T",X,Y);
	    for(int s=0;s<m;s++){
		Y=Y+14;
		sub=q.nextToken(); 
		backg.drawString(sub,X,Y);
		if(Y>(ymax-14)){
		    X=X+100;
		    Y=10;
		    backg.drawString("t : T",X,Y);
		}
	    }
	    backg.drawString("t= "+time+"   T= "+freq,xsize,ysize+25);	    
	}
	else
	{
	    backg.clearRect(0,0,xmax,ymax+50);
	    backg.setColor(Color.white);
	    backg.fillRect(0,0,xmax,ymax);
	    backg.setColor(Color.black);
	    backg.drawString(ready_string,2*xsize,ymax-100);
	}
	repaint();
    }
    
    public synchronized void prepaint(){
	backg.setFont(font);
	backg.setStroke( new BasicStroke(4.0f) );
	backg.setColor(Color.black);
	backg.clearRect(xsize,ysize,2*xsize,ysize+10);
	int basis=0;int t;int p0;int p1;int p2;int p3;int geweest[]=new int[3];
	Polygon poly0;Polygon poly1;Polygon poly2;Polygon poly3;
	keuze=Shuffle(keuze);fout=keuze[0];kans=Shuffle(kans);anders=kans[0];
	kleuren=Shuffle(kleuren);int k0=kleuren[0];int k1=kleuren[1];int k2=kleuren[2];
	Color kleur1=new Color(colors[k0][0],colors[k0][1],colors[k0][2]); 
	Color kleur2=new Color(colors[k1][0],colors[k1][1],colors[k1][2]); 
	for(int p=0;p<4;p++){
	    backg.setColor(kleur1);
	    backg.fillRect(p*(xsize),1,(p+1)*(xsize),ymax-2);
	    backg.setColor(kleur2);basis=p*xsize;
	    polies=Shuffle(polies);p0=polies[0];p1=polies[1];p2=polies[2];p3=polies[3];
	    poly0=new Polygon(xobject[p0][p],yobject[p0][p],xobject[p0][p].length);
	    poly1=new Polygon(xobject[p1][p],yobject[p1][p],xobject[p1][p].length);
	    poly2=new Polygon(xobject[p2][p],yobject[p2][p],xobject[p2][p].length);
	    poly0.translate(basis,0);
	    poly1.translate(basis+sx,0);
	    poly2.translate(basis,sx);
	    if(anders == 0){backg.fillPolygon(poly0);backg.fillPolygon(poly1);backg.fillPolygon(poly2);}
	    else{backg.drawPolygon(poly0);backg.drawPolygon(poly1);backg.drawPolygon(poly2);}
	    if(fout!=p){
		poly3=new Polygon(xobject[p3][p],yobject[p3][p],xobject[p3][p].length);
		poly3.translate(basis+sx,sx);
		if(anders == 0){backg.fillPolygon(poly3);}else{backg.drawPolygon(poly3);}
	    }
	    else
	    {
		geweest[0]=p0;geweest[1]=p1;geweest[2]=p2;geweest=Shuffle(geweest);t=geweest[0];
	    	poly3=new Polygon(xobject[t][p],yobject[t][p],xobject[t][p].length);
		poly3.translate(basis+sx,sx);
		if(anders == 0){backg.fillPolygon(poly3);}else{backg.drawPolygon(poly3);}
	    }		        
	    Color kleur3=new Color(colors[k2][0],colors[k2][1],colors[k2][2]); 
	    backg.setColor(kleur3);
	    backg.drawRect(p*(xsize),1,(p+1)*(xsize),ymax-2);
	}
	if(goedzo == 1){
	    backg.drawImage(ok,2*xsize,ysize, this);
	}
	else
	{
	    backg.drawImage(nok,2*xsize,ysize, this);
	}
	backg.setColor(Color.black);
	backg.drawString(teller+" : "+counter,xsize,ysize+20);
	backg.drawString(freq+" : "+poging_counter,xsize,ysize+40);

	repaint();
    }
    
   public void start(){}

   public void stop(){}

   public void run(){}

   public String ReadApplet(){
	if(counter<max){return "error : not finished";}
	else
	{
	    double totaltime=(double) (stop-begin)/1000;
	    return totaltime+":"+max+"\n"+replystring;
        }
    }
}


