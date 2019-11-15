import processing.serial.*; //Importing the Serial library.
Serial myPort; // Creating a port variable.
int r,g,b; // initializing colours.
//string values for buttons
String T= "WATCOPTER CONTROLS";
String T1= "FWD";
String T2= "RGT";
String T3= "LFT";
String T4= "BWD";
String T6 = "UP";
String T7 = "DOWN";

void setup()
{
  size(1000,600); // Creating the display window and defining its' size.
 
  r = 0; // Setting up the colours.
  g = 0;
  b = 0;

  String portName = Serial.list()[2]; // 1 on Olivia's computer, 2 on Devika's
  myPort = new Serial(this, portName, 9600); // Initializing the serial port.
}
 
void draw() {
   
background(229,238,255); //Light Blue Background.

fill (51,125,255); // Painting the Arrows Cobalt Blue.
rect(900, 30,70,70,15); //ON/OFF button
rect(750, 250, 100, 100,100); //circle
triangle(750, 235, 800, 160, 850, 235); //FWD triangle
triangle(735, 350, 660, 300, 735, 250); //RHT triangle
triangle(865, 250, 940, 300, 865, 350); //LFT triangle
triangle(750, 365, 800, 440, 850, 365); //BWD triangle
rect(50, 135, 400, 100,5); //UP rectangle
rect(50, 335, 400, 100,5); //DOWN rectangle
textSize(32); // Defining the headline's size- 32
fill (0,0,255); // painting the headline blue.
text(T, 1000/2 - 1000/5, 50);  //placing the headline in a specific location
textSize (20); //The arrow keys text size- 20
fill (153,187,255); // painting it blue.
text(T1, 780, 220); //FWD
text(T2, 875, 310); //RHT
text(T3, 690, 310); //LFT
text(T4, 780, 400); //BWD
text(T6, 225, 195); //UP
text(T7, 210, 395); //DOWN
}


void mousePressed() {
  float x = mouseX;
  float y = mouseY;

  //forward
  if (triPoint(750,235, 800,160,850,235, x,y)) 
  {
    println("Forward");
    fill(230,25,200);
    triangle(750, 235, 800, 160, 850, 235);
    myPort.write('1');
  }
  
  //right
  else if (triPoint(735, 350, 660, 300, 735, 250, x, y)) 
  {
    println("right");
    fill(230,25,200);
    triangle(735, 350, 660, 300, 735, 250);
    myPort.write('2');
  
  }
  
  //left
  else if (triPoint(865, 250, 940, 300, 865, 350, x, y))
  {
    println("left");
    fill(230,25,200);
    triangle(865, 250, 940, 300, 865, 350);
    myPort.write('3');
  }
  
  //down
  else if (triPoint(750, 365, 800, 440, 850, 365, x, y)) 
  { 
    println("backwards");
    fill(230,25,200);
    triangle(750, 365, 800, 440, 850, 365);
    myPort.write('4');
  }
  
  //up
  else if(x >= 50 && x <= 450 && y >= 135 && y <= 235)
  {
      println("up");
      fill(230,25,200);
      rect(50, 135, 400, 100,5);
      myPort.write('5');
  }
  
  //down
  else if(x >= 50 && x <= 450 && y >= 335 && y <= 435)
  {
      println("down");
      fill(230,25,200);
      rect(50, 335, 400, 100,5);
      myPort.write('6');
  }
}

//collision detection
boolean triPoint (float x1, float y1, float x2, float y2, float x3, float y3, float mx, float my ) {
  
  //get the area of the triangle
  float areaOrig = abs( (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1) );

  //get the area of 3 triangles made between the point and the corners of the triangle
  float area1 =    abs( (x1-mx)*(y2-my) - (x2-mx)*(y1-my) );
  float area2 =    abs( (x2-mx)*(y3-my) - (x3-mx)*(y2-my) );
  float area3 =    abs( (x3-mx)*(y1-my) - (x1-mx)*(y3-my) );

  //if the sum of the three areas equals the original, mouse is inside triangle
  if (area1 + area2 + area3 == areaOrig) {
    return true;
  }
  return false;
}


void keyPressed()
{
  switch (keyCode) 
  { 
    case UP:
    myPort.write('1');
    println("Forward");
    fill(230,25,200);
    triangle(750, 235, 800, 160, 850, 235);
    break;
    case RIGHT:
    myPort.write('2');
    println("Right");
    fill(230,25,200);
    triangle(865, 250, 940, 300, 865, 350);
    break;
    case LEFT:
    myPort.write('3');
    println("Left");
    fill(230,25,200);
    triangle(735, 350, 660, 300, 735, 250);
    break;
    case DOWN:
    myPort.write('4');
    println("Backwards");
    fill(230,25,200);
    triangle(750, 365, 800, 440, 850, 365);
    break;
    case ENTER:
    myPort.write('5');
    println("Up");
    fill(230,25,200);
    rect(50, 135, 400, 100,5);
    break;
    case SHIFT:
    myPort.write('6');
    println("Down");
    fill(230,25,200);
    rect(50, 335, 400, 100,5);
    break;
    default:
    println("Salt my jerkey and call me a muskouir, You Sir are in the default!");
    break;
  }
}
