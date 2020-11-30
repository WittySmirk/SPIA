/* NOTE THIS IS NOT FINAL, THIS IS JUST AND EXAMPLE OF THE CURRENT MATH SO YOU CAN IMPLEMENT BASIC PHYSICS INTO YOUR PROJECTS, LATER A REAL LIBRARY/API WILL BE CREATED
    
    * GOALS
        * Create simple library that is one header file   
        * (You just through in the header into your include dir and it just works (no DLLS no nothing))
        * Example of future usage
            #include <SPIA.h>
            

            void eUpdate(E* e){
                //WHATEVER CODE UPDATES OR ANIMATES OR WHATEVER

                //DO WHATEVER IN COLLISION
                //MOST LIKELY THERE WILL BE FUNCTIONS TO UPDATE THE VARS EASIER, THIS IS JUST THE MATH WAY
                if(ePh->colBottom == true){
                    ePos.y = getOthersY - ePos.h;
                }else if(ePh->colTop == true){
                    ePos.y = getOthersY + getOthersH + ePos.h;
                }else if(ePH->colLeft == true){
                    ePos.x = getOthersX + getOthersW + ePos.w;
                }else if(ePH->colRight == true){
                    ePos.x = getOthersX - ePos.w;
                }
            }

            void eMove(E* e){
                //MOVE CODE (SPIA PROBABLY WON'T IMPLEMENT THIS FOR YOU BECAUSE IT WILL MAKE IT MORE UNIVERSAL FOR ALL GAMES)
            }

            void eDraw(E* e){
                //JUST RENDER WHERE IT IS AND USE ITS CURRENT TEXTURE
            }

            int main(voidorwhatever){}
                //INIT IT with your constants
                SPIA* pe = createSPIA(float gravity, float accel, float jumpPower);


                //Create an entity with whatever library you are using
                WHATEVERRECT ePos = WHATEVERINITALIZEFUNCTION(int x, int y);
                OR WHATEVERRECT ePos(intorfloat x, intorfloat y, intorfloat w, interorfloat h);

                //(OREVEN JUST A VECTOR OR AN ARRAY OR JUST TWO FLOATS OR INTS IT DOESN'T MATTER THAT'S THE BEAUTY OF IT)
                
                //INIT THE PHYSICS OF IT AND ADD IT TO THE LISTS OF PHYSICS OBJECTS
                
                PhisicsObj* ePh = pe->createPObj(ePos.x, ePos.y, ePos.w, ePos.h, (TPYE OF PHYSICS OBJECT) rectangle);

                //(It will automatically push it into a component system for physics objects)
                GAMELOOP {
                    //Update
                        //Check collision every frame for every entity
                        updateCol(pe);

                        eUpdate(e);
                        eMove(e);
                    //Draw
                    StartDraw();
                        //SOMEWHERE ALONG THE LINE YOU'D CREATE A TEXTURE, DRAWING IS ALL BASED OFF WHATEVER OTHER API YOU'RE USING
                        e.draw(e);
                    EndDraw();
                }
            }
        * AGAIN THIS EXAMPLE IS TEMPORARY, EVENTUALLY I WANT TO MAKE THIS LIBRARY LIKE THAT
*/

// WARNING THIS IS VERY SIMPLE, VERY PRIMITIVE
// DO NOT REPLICATE THE CODE EXACTLY, JUST USE THE MATH
// THIS IS JUST A VERY DEMO WAY OF HOW THE MATH WORKS, AND A DEMO OF HOW YOU SHOULD IMPLEMENT IT


//MATH STUFF THAT YOU CAN USE IN THE MEANTIME


#include <stdbool.h>

//JUST CREATING AN ENTITY TO AVOID AN ANNOYING ERROR IN VSCODE LOL
//DISREGARD THIS IT DOESN'T MATTER AT ALL
typedef struct {
    int pH; //Placeholder
}Entity;

//VARS (USUALLY EVERY ENTITY WOULD HAVE THESE SO THAT OTHER THINGS CAN GRAB THEM (LIKE PUT THEM IN THE STRUCT IF YOUR IN C OR A CLASS IN C++))
int mS = 5; //Movement speed
int fS = 0; //How fast we're currently falling
float g = 9.8f; //Gravity
int fA = 1; //Falling acceleration (Don't suggest above 1)
int jP = 25; //Jump power (Opposite of acceleration but for jumping) (This is high for marios jump)
bool mL = false;
bool mR = false;
bool falling = true;
bool colB = false;
bool colL = false;
bool colR = false;
bool colT = false;
int ePosX = 1; // REPLACE THESE VARS WITH YOUR OWN FOR YOUR ENTITY
int ePosY = 1; // REPLACE THESE VARS WITH YOUR OWN FOR YOUR ENTITY
int ePosW = 1; // REPLACE THESE VARS WITH YOUR OWN FOR YOUR ENTITY
int ePosH = 1; // REPLACE THESE VARS WITH YOUR OWN FOR YOUR ENTITY
int whateveryourcolidingwithsx = 1; // REPLACE THESE VARS WITH WHATEVER YOUR COLIDING WITHS VARS
int whateveryourcolidingwithsy = 1; // REPLACE THESE VARS WITH WHATEVER YOUR COLIDING WITHS VARS
int whateveryourcolidingwithsw = 1; // REPLACE THESE VARS WITH WHATEVER YOUR COLIDING WITHS VARS
int whateveryourcolidingwithsh = 1; // REPLACE THESE VARS WITH WHATEVER YOUR COLIDING WITHS VARS

//In your moving function for an entity

void eInput(Entity* e){
    if(HOWEVERYOUGETKEYINPUT_A()){
        if(colR != true){
            mR = true;
        }
    } else(HOWEVERYOUGETKEYINPUT_D()){
        if(colL != true){
            mL = true;
        }
    }

    if(HOWEVERYOUKNOWITSRELEASED_A()){ 
        mR = false;
    } else(HOWEVERYOUKNOWITSRELEASED_D()){
        mL = false;
    }
}

void eMove(Entity* e){
    if(falling == true){
        //Stop falling if you're coliding
        if(colB == false){
            fS += fA;
            ePosY += fS;
        } else {
            fS = 0;
            ePosY = whateveryourcolidingwithsy - ePosH;
        }
    }

    if(mR = true){
        ePosX += mS;
    }

    if(mL = true){
        ePosX -= mS;
    }

}

void someOtherColCheck(Entity* e){
    //COLLISION DETECTION WITH OTHER ENTITY
    //IK, IK THIS IS REALLY INEFFICIENT, BUT THIS IS THE BASICS, IT WILL BE OPTIMIZED IN THE ACTUAL LIB THIS IS JUST TO START HELPING YOU WITH MATH ON PHYSICS IN THE MEAN TIME
    
    if(ePosX + ePosW >= whateveryourcolidingwithsx && ePosY >= whateveryourcolidingwithsy - ePosH && ePosY <= whateveryourcolidingwithsy + whateveryourcolidingwithsh){
        colR = true;
    }else {
        colR = false;
    }
    if(ePosX <= whateveryourcolidingwithsx + whateveryourcolidingwithsw && ePosY >= whateveryourcolidingwithsy - ePosH && ePosY <= whateveryourcolidingwithsy + whateveryourcolidingwithsh){
        colL = true;
    }else {
        colL = false;
    } 
    if(ePosY + ePosH >= whateveryourcolidingwithsy && ePosX >= whateveryourcolidingwithsx - ePosW && ePosX <= whateveryourcolidingwithsx + whateveryourcolidingwithsw){
        colB = true;
    }else {
        colB = false;
    }
    if(ePosY <= whateveryourcolidingwithsy + whateveryourcolidingwithsh && ePosX >= whateveryourcolidingwithsw - ePosW && ePosX <= whateveryourcolidingwithsx + whateveryourcolidingwithsw){
        colT = true;
    }else {
        colT = false;
    }
}

//Actual main
int main(void){
 
 //BASIC GAME LOOP STUFF, THIS DOESN'T EVEN REALLY MATTER
 bool whateverthehecksrunningcheckis = true;
 bool running = true;
 if(whateverthehecksrunningcheckis != true){
     running = false;
 }

 Entity* e;

 while(running){
    //UPDATE STUFF
    someOtherColCheck(e);

    eInput(e);
    eMove(e);

    whatevertheheckthedrawingfunctionis();
        eDraw(e);
    whateverthehecktheenddrawingfunctionis();
 }   
}