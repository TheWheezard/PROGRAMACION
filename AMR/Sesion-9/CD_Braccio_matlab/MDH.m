q1 = 0;
q2 = 0;
q3 = 180;
q4 = 0;
q5 = 0;

L1 = 6.5;
L2 = 12.5;
L3 = 12.5;
L5 = 19.0;


A = [cosd(q1), 0, sind(q1), 0; 0, sind(q1), 0, -cosd(q1); 0, 1, 0, L1; 0, 0, 0, 1];
B = [cosd(q2), sind(q2), 0, L2 * cosd(q2); sind(q2),  -cosd(q2), 0, L2 * sind(q2); 0, 0, -1, 0; 0, 0, 0, 1];
C = [cosd(q3 - 90), sind(q3 - 90), 0, L3 * cosd(q3 - 90); sind(q3 - 90),  -cosd(q3 - 90), 0, L3 * sind(q3 - 90); 0, 0, -1, 0; 0, 0, 0, 1];
D = [cosd(q4), 0, sind(q4), 0; sind(q4), 0, -cosd(q4), 0; 0, 0, 1, 0; 0, 0, 0, 1];
E = [cosd(q5), sind(q5), 0, 0; sind(q5), cosd(q5), 0, 0; 0, 0, 1, L5; 0, 0, 0, 1];

T1 = zeros(4,4);
T2 = zeros(4,4);
T3 = zeros(4,4);
T = zeros(4,4);

disp('A = '); disp(A);
disp('B = '); disp(B);
disp('C = '); disp(C);
disp('D = '); disp(D);
disp('E = '); disp(E);

T1 = A * B;
T2 = T1 * C;
T3 = T2 * D;
T = T3 * E;

T1 = B * C;
T2 = C * D;
T3 = D * E;

disp('T = '); disp(T);
disp('T1 = '); disp(T1);
disp('T2 = '); disp(T2);
disp('T3 = '); disp(T3);

invA = pinv(A);
invB = pinv(B);
invC = pinv(C);

matrixaux = invB * invA;

syms x y z;
eqns = [invA(3, 1) * x + invA(3, 2) * y + invA(3, 3) * z + invA(3, 4) == T1(3, 4),
        matrixaux(1, 1) * x + matrixaux(1, 2) * y + matrixaux(1, 3) * z + matrixaux(1, 4) == C(1, 4), 
        matrixaux(2, 1) * x + matrixaux(2, 2) * y + matrixaux(2, 3) * z + matrixaux(2, 4) == C(2, 4),
        matrixaux(3, 1) * x + matrixaux(3, 2) * y + matrixaux(3, 3) * z + matrixaux(3, 4) == C(3, 4) ];

S1 = solve(eqns,[x y z]);

disp('S1 = '); disp(S1);


disp(cosd(90));
disp(cosd(pi/2));
disp(x);
disp(y);
disp(z);