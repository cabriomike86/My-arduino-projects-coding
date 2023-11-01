void ljog()
{
    step(false, Y_DIR_PIN, Y_STEP_PIN, 200); 
 // delay(10);
 
}


void rjog()
{
    step(true, Y_DIR_PIN, Y_STEP_PIN, 200); 
 // delay(10);

}


void upjog()
{
    step(true, X_DIR_PIN, X_STEP_PIN, 200);     // run xxx mm in reverse direction

  
}


void downjog()
{
    step(false, X_DIR_PIN, X_STEP_PIN, 200);    // run xxx mm


}


void sldLjog()
{
    step(false, Z_DIR_PIN, Z_STEP_PIN, 200); 


}


void sldRjog()
{
    step(true, Z_DIR_PIN, Z_STEP_PIN, 200);


}
