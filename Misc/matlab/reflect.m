function [ M ] = reflect( plane )
    % assume the plane is a vector of length 4
    n = norm(plane(1:3));
    plane = plane/n;

    M = [-2 * plane(1) * plane(1) + 1  -2 * plane(2) * plane(1)      -2 * plane(3) * plane(1)        0
    -2 * plane(1) * plane(2)      -2 * plane(2) * plane(2) + 1  -2 * plane(3) * plane(2)        0
    -2 * plane(1) * plane(3)      -2 * plane(2) * plane(3)      -2 * plane(3) * plane(3) + 1    0
    -2 * plane(1) * plane(4)      -2 * plane(2) * plane(4)      -2 * plane(3) * plane(4)        1];

end

