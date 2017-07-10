void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

class Szenario (int location,int temp,int licht)
{
  private:
  int location;

  public:
  setlocation();
  
}

if (temp>=25)  //Sommermodus
  {
    if(licht>=800)
    {
      sunmod.setlocation();  //sonnig
    }
    else if(licht<800)
    {
      cloudmod.setlocation();  //bewölkt
    }
    else if(licht<200)
    {
      nightmod.setlocation();  //nachts
    }
  }
else   //Wintermodus
  {
    if (licht>=800)  //sonnig
    {
      sunmod.setlocation();  //sonnig
    }
    else if(licht<800)
    {
      cloudmod.setlocation();  //bewölkt
    }
    else if(licht<200)
    {
      nightmod.setlocation();  //nachts
    }
  }

