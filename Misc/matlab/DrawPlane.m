function DrawPlane( pln )
    x=-10:1:10;
    a=pln(1); b=pln(2); c=pln(3); d=pln(4);
    z = (-d - a*x)/c;
    plot(x, z);
    
    %also want to plot the norm.
    x = zeros(2, 1);
    y = zeros(2, 1);
    x(1) = 0;
    y(1) = (-d - a*x(1))/c;
    x(2) = x(1) + pln(1);
    y(2) = y(1) + pln(3);
    %x = [P(1) P(1)+N(1)];
    %y = [P(3) P(3)+N(3)];
    plot(x, y);

end

