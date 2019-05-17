/*
  Author : Soham Chakrabarti
  
  Tap mouse to elevate the Ball.
  Change Speeds to adjust your levels in your console.
  Enjoy!
*/

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;
import java.awt.Dimension;
import java.awt.Font;
import java.util.Random;
public class FPBird extends JPanel implements MouseListener,ActionListener,KeyListener
{   int scoreB=0;
    private final int WIDTH=20;//width of Flying Object
    private final int HEIGHT=20;//height of Flying Object
     private final int locX=200;
    int velX,velX1,velX2,locY=200,speed=12,speed1=10,speed2=11,rX=1500,rX1=1500,rY1,rY,rX2=1500,rY2,rW,rH,y,velB,f=0;
    int speedY,speedY1,speedY2,velY,velY1,velY2;
    Timer t=new Timer(4,this);
    public void startGame()
    {
        t.start();
        addMouseListener(this);
        setBackground(Color.black);
		setForeground(Color.red);
		addKeyListener(this);
		setFocusable(true);
		//setTraversalKeysEnabled(false);
    }
    public void paintComponent(Graphics g)
    {   Random ran=new Random();
        super.paintComponent(g);
        g.setColor(Color.RED);
        g.fillOval(locX,locY,WIDTH,HEIGHT);
        g.setColor(Color.GREEN);
        g.fillRect(0,4,1300,20);
        g.setColor(Color.GREEN);
        g.fillRect(0,710,1300,20);
        g.setColor(Color.BLUE);
        g.fillRect(rX,rY,40,40);
        g.setColor(Color.BLUE);
        g.fillRect(rX1,rY1,40,40);
        g.setColor(Color.BLUE);
        g.fillRect(rX2,rY2,40,40);
        g.setColor(Color.GREEN);
        g.drawString("SCORE BOARD : "+scoreB, 30, 80);
        g.setFont(new Font("TimesRoman", Font.PLAIN, 10));
        if((scoreB>1000)&&(scoreB<4001))
        { 
          speed=ran.nextInt((20- 15) + 1) + 15;
          speed1=ran.nextInt((15- 10) + 1) + 10;
          speed2=ran.nextInt((25- 20) + 1) + 20;
          speedY=0;
          speedY1=0;
          speedY2=0;
          g.drawString("LEVEL UP:1 SPEED INCREASES", 560, 70);
          g.setFont(new Font("TimesRoman", Font.PLAIN, 50));}
          if((scoreB>4000)&&(scoreB<6000))
        { 
          speed=ran.nextInt((25-16) + 1) + 16;
          speed1=ran.nextInt((25- 16) + 1) + 16;
          speed2=ran.nextInt((25- 16) + 1) + 16;
          speedY=0;
          speedY1=0;
          speedY2=0;
          g.drawString("LEVEL UP:2 SPEED INCREASES", 560, 70);
          g.setFont(new Font("TimesRoman", Font.PLAIN, 50));}
           if((scoreB>6001)&&(scoreB<8000))
        { 
          speed=ran.nextInt((30- 20) + 1) + 20;;
          speed1=ran.nextInt((30- 20) + 1) + 20;;
          speed2=ran.nextInt((30- 20) + 1) + 20;;
          speedY=4;
          speedY1=6;
          speedY2=10;
          g.drawString("LEVEL UP:2 SPEED INCREASES", 560, 70);
          g.setFont(new Font("TimesRoman", Font.PLAIN, 50));}
          if(scoreB>8000)
        { speed=10;speed1=12;speed2=4;
          speedY=14;speedY1=8;speedY2=20;
          g.drawString("Maximum Level Reached", 190, 70);
          g.setFont(new Font("TimesRoman", Font.PLAIN, 20));
        }
         if(isCollision())
        { speed=0;
          speed1=0;
          speed2=0;
          speedY=0;
          speedY1=0;
          speedY2=0;
          g.setColor(Color.WHITE);
          g.drawString("GAME OVER",500, 300);
          g.setFont(new Font("TimesRoman", Font.PLAIN, 70));
          g.setColor(Color.WHITE);
          g.drawString("Score : "+scoreB,500, 400);
          g.setFont(new Font("TimesRoman", Font.PLAIN, 20));
        }
    }
    public void actionPerformed(ActionEvent e)
    {   Random ran=new Random();
        
        if(locY<5)
        {locY=5;}
        if(locY>710)
        {locY=710;}
        
       
        if((rX>1300)||(rX<0))
        {rY=ran.nextInt((700- 20) + 1) + 20;
         rX=1260;
         repaint();
         velX=speed;
         velY=speedY;
         }
        else if(rY<10){rY=10; changeStateDown(1);rX=rX-velX; rY=rY+velY; ;}
        else if (rY>680){rY=680; changeStateUp(1);rX=rX-velX; rY=rY+velY; ;}
        else{
         if(checkState()){
         rX=rX-velX;
         rY=rY+velY; }
         else{ 
         rX=rX-velX;
         rY=rY+velY; }
        }
             
       
        
        if((rX1>1300)||(rX1<0))
        {rY1=ran.nextInt((700- 20) + 1) + 20;
         rX1=1260;
         repaint();
         velY1=speedY1;
         velX1=speed1;
        }
        else if(rY1<10){rY1=10; changeStateDown(2);rX1=rX1-velX1; rY1=rY1+velY1; }
        else if (rY1>680){rY1=680; changeStateUp(2);rX1=rX1-velX1; rY1=rY1+velY1; }
        else{
          if(checkState()){
         rX1=rX1-velX1;
         rY1=rY1+velY1; }
         else{ 
         rX1=rX1-velX1;
         rY1=rY1+velY1; } 
        }
        
       if((rX2>1300)||(rX2<0))
        {rY2=ran.nextInt((700- 20) + 1) + 20;
         rX2=1260;
         repaint();
        velX2=speed2;
        velY2=speedY2;
       }
        else if(rY2<10){
            rY2=10;
            changeStateDown(3);
            rX2=rX2-velX2;
            rY2=rY2+velY2;;}
        else if (rY2>680){
            rY2=680;
            changeStateUp(3);
            rX2=rX2-velX2;
            rY2=rY2+velY2;;}
        else{
          if(checkState()){
         rX2=rX2-velX2;
         rY2=rY2+velY2; }
         else{ 
         rX2=rX2-velX2;
         rY2=rY2+velY2; }
        }
        
        locY=locY+velB;
       if(!isCollision()) 
        scoreB++;
        levels();
        repaint();
    }
    
    public void keyTyped(KeyEvent e)
    {}
    public void keyPressed(KeyEvent e){}
    public void keyReleased(KeyEvent e){
            }
    public void mouseEntered(MouseEvent e)
	{}
	public void mouseExited(MouseEvent e)
	{}
	public void mousePressed(MouseEvent e)
	{ velB=-5;
     }
	public void mouseReleased(MouseEvent e)
	{velB=4;
    }
	public void mouseMoved(MouseEvent e)
	{}
	public void mouseDragged(MouseEvent e)
	{}
	public void mouseClicked(MouseEvent e)
	{}
	
	public boolean isCollision()
	{ if((locX>=rX-5)&&(locX<=(rX+45))&&(locY>=rY-5)&&(locY<=(rY+45)))
	   f=1;
	   
	 if((locX>=rX1-5)&&(locX<=(rX1+45))&&(locY>=rY1-5)&&(locY<=(rY1+45)))
	   f=1;
	 if((locX>=rX2-5)&&(locX<=(rX2+45))&&(locY>=rY2-5)&&(locY<=(rY2+45))) 
	 f=1;
	 if(locY<4) f=1;
	 if(locY>680) f=1;
      if(f==1)
      return true;
       else
     return false;
    }
    public void levels()
    {if(scoreB==2000)
        {speed=speed+6;
        speed1=speed1+6;
        speed2=speed2+6;}
     if(scoreB==4000)
        {speed=speed+6;;
        speed1=speed1+6;
        speed2=speed2+6;;}
      if(scoreB==8000)
        {speed=speed+6;
        speed1=speed1+6;
        speed2=speed2+6;}
        
    }
    public boolean checkState()
    {if(velY>0)
      return true;
    
     else if(velY1>0)
     return true;
     
     else if(velY2>0)
     return true;
     else
     return false;
    }
    public void changeStateUp(int pointerX){
        if(pointerX==1)velY=(-1)*speedY;
        if(pointerX==2)velY1=(-1)*speedY1;
        if(pointerX==3)velY2=(-1)*speedY2;}
    public void changeStateDown(int pointerY){
        if(pointerY==1)velY=speedY;
        if(pointerY==2)velY1=speedY1;
        if(pointerY==3)velY2=speedY2;}
	public static void main(String arge[])
      {
        JFrame f=new JFrame("Flappy Bird");
        f.setSize(1280,800);
        FPBird hm=new FPBird();
        hm.startGame();
        f.add(hm);
	    f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    f.setSize(1280,800);
	    f.setVisible(true);
	   }
}
