q1 = 0;
q2 = 90;
q3 = 180;
q4 = 0;
q5 = 90;

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

disp('T = '); disp(T);

disp(cosd(90));
disp(cosd(pi/2));