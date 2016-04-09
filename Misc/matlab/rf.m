%First create our normal vector and our position.
%Note since this is to test math that will be used in direct3d we
%are working with column vectors instead of row vectors.
clc;

P = [0, 1.5, 5.0];

N = [0, 0, -1];

Rot = rotY(pi/4);

%To effectively rotate the norm we rotate it by the 3x3 portion.
N = N*Rot(1:3,1:3);

%Now let us create the plane from the points.
pln = [N -dot(N,P)]

R = reflect(pln)

%O indicates some object
O = [5 2.5 12]

hold on

DrawPlane(pln);
axis square;
%x=-10:1:10;
%a=pln(1); b=pln(2); c=pln(3); d=pln(4);
%z = (-d - a*x)/c;
%plot(x, z);
%hold on
%axis square;
%also want to plot the norm.
%x = [P(1) P(1)+N(1)];
%y = [P(3) P(3)+N(3)];
%plot(x, y);

%plot the origin.
x = 0;
y = 0;
plot(x, y, 'r*');

%Plot the object
x = O(1);
y = O(3);
plot(x, y, 'g*');

%reflect the object
Or = [O 1]*R
x = Or(1);
y = Or(3);
plot(x, y, 'b*');

hold off
