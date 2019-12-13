/*................................PROBLEM 1......................................*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//the class we use often to reduce clutter of coordinates
class vertex {

   public:
      void set_coordinates(int a, int b){
         x = a; y = b;
      }
   
      int x, y;
}; 

// Base class....the main shape class
class Shape {
   public:
      void Area(){}

};

// Derived classes that also uncludes operation override for the operation '+'
class Rectangle: public Shape {
   public:
      int Area() { 
      return ( (vertex_one.x - vertex_two.x)*(vertex_one.y - vertex_two.y) ); 
      }

        //constructor function
      Rectangle(int a, int b, int c, int d)
      {
         vertex_one.x = a;
         vertex_one.y = b;

         vertex_two.x = c;
         vertex_two.y = d;
      }

    //the overwritten operator
      int operator + (Rectangle R2){

      int a,b;
      int c,d;   
          
      a = max(vertex_one.x, R2.vertex_one.x);
          
      b = min(vertex_one.y, R2.vertex_one.y);
          
      c = min(vertex_two.x, R2.vertex_two.x);
          
      d = max(vertex_two.y, R2.vertex_two.y);
          
      if(a > c || b < d) cout << "-1" <<endl;
      else 
          
      if(a == c && b == d) {
               cout<<a<<" "<<b<<" "<< "0"<<"\n";
         }

     else {
            std::cout << std::setprecision(0) << std::fixed;
            cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<abs((a-c)*(b-d))<<"\n";
         }
         return 0; 
  }

   protected:
      vertex vertex_one;
      vertex vertex_two;
};

//the derived class corresponding to circle that has the overwritten operator '+'
class Circle : public Shape {
   public:
      double Area() {

         return(3.14 * radius * radius);
         //cout << setprecision(2) << fixed;
         //cout << "3.14*radius*radius"; in case we need to print upto two decimals

      }

    //the constructor function
      Circle(int x, int y , int r)
      {
         center.x = x;
         center.y = y;

         radius = r;
      }

    //overwriting the operator '+'
      int operator + (Circle C){
         // algorithm to find the intersection points(if any) and print them out
         //also the algorithm to find area from the same points
         //using setprecision(2) we can print the values with the needed precisions
     
         double center_distance = abs(C.center.x-center.x);

          //the case where they do not intesect
         if(center_distance > (radius+C.radius)) {
             std::cout << std::setprecision(2) << std::fixed;cout << "-1"<<" ";
             cout << trunc(Area()*100)/100<< " "<< trunc(C.Area()*100)/100<<"\n"; 
             return 0;
         }

          //the case where one lies completely inside another
         if(center_distance < (radius-C.radius) || center_distance < (C.radius - radius))
         {
             std::cout << std::setprecision(2) << std::fixed;
            cout << "0"<<" "<< trunc(Area()*100)/100<< " "<< trunc(C.Area()*100)/100<<"\n";
            return 0;
         }

          //the case where one overlaps with another
         if(center_distance == 0){
             std::cout << std::setprecision(2) << std::fixed;
             cout << "0"<<" "<< trunc(Area()*100)/100<< " "<< trunc(C.Area()*100)/100<<"\n";
             return 0;
         }

          //first we find the midpoint of the intersection points and then add or substract the corresponding height
         double a = (pow(radius,2)-pow(C.radius,2)+pow(center_distance,2))/(2*center_distance);

         double p2x, p2y;

         p2x = center.x + a*(C.center.x-center.x)/center_distance;
         p2y = center.y ;

         double h = sqrt(pow(radius,2)-pow(a,2));

         double intersect_x1, intersect_x2, intersect_y1, intersect_y2;

         if(C.center.x - center.x > 0)
         {
         intersect_y1 = p2y - h*(C.center.x - center.x)/center_distance;

         intersect_y2 = p2y + h*(C.center.x - center.x)/center_distance;

         intersect_x1 = p2x ;

         intersect_x2 = p2x ;
        }

        if(C.center.x - center.x < 0)
         {
         intersect_y1 = p2y + h*(C.center.x - center.x)/center_distance;

         intersect_y2 = p2y - h*(C.center.x - center.x)/center_distance;

         intersect_x1 = p2x ;

         intersect_x2 = p2x ;
        }

     if((intersect_x1 == intersect_x2) && (intersect_y1 == intersect_y2))
      {
         std::cout << std::setprecision(2) << std::fixed;
         cout << trunc(intersect_x1*100)/100 << " "<< trunc(intersect_y1*100)/100;
         
         cout << " "<< trunc(Area()*100)/100<< " "<< trunc(C.Area()*100)/100<<"\n";
      }

     else{
         std::cout << std::setprecision(2) << std::fixed;
         
            cout << trunc(intersect_x1*100)/100 <<" "<< trunc(intersect_y1*100)/100 <<" "<< trunc(intersect_x2*100)/100  <<" ";
            cout<< trunc(intersect_y2*100)/100 ; 
      
            cout <<" "<< trunc(Area()*100)/100.00<< " "<< trunc(C.Area()*100)/100<<"\n";
            return 0;
     }
          return 0;
  }

   protected:
      vertex center;
      int radius;
};

int main(){

   int n;

   cin >> n;

    //detecting the corresponding and calling the respective operation after inputting the parameters
   for(int i = 0; i < n; i++)
   {
      char c; int a,b,c1,d,e,f,g,h;

      cin>>c;

      if(c == 'C')
      {
         cin>>a;
         cin>>b;
         cin>>c1;
         cin>>d;
         cin>>e;
         cin>>f;

         Circle C1(a,b,c1);
         Circle C2(d,e,f);

         C1+C2;
      }

      if(c == 'R')
      {
         cin>>a;
         cin>>b;
         cin>>c1;
         cin>>d;
         cin>>e;
         cin>>f;
         cin>>g;
         cin>>h;

         Rectangle R1(a,b,c1,d);
         Rectangle R2(e,f,g,h);

         R1+R2;
      }


   }

return 0;
}




