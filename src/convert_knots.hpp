 #include <iostream>
 using namespace std;
  
  double knots_to_miles_per_minute(int knot)
  {
      const double  knots_to_feet_per_hour = 6076.0;
     const double knot_to_mph =  5280.0;
     double knots_to_miles_per_minute =(knot * knots_to_feet_per_hour/knot_to_mph)/ 60.0;
     return knots_to_miles_per_minute;
}

