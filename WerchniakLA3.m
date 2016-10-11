%Euler's method solver
%Andy Werchniak
%1 June 2015

%Clear all values in workspace
clearvars;

%Welcome & instructions
fprintf('Welcome to the Euler''s method program.\n');
fprintf('Be sure to view all plots in full screen mode.\n\n');

%Get user input for the final value of x
%Only accept positive values
Xn=input('Enter the final value of x: ');
while(Xn<=0)
    Xn=input('Invalid value.\nEnter a value greater than 0: ');
end

%Get user input for the step size
%Only accept values that go evenly into the domain
h=input('Enter the step size: ');
while(h>=1 || rem(Xn,h)~=0)
    h=input('Enter a sufficiently small step size evenly divisible into Xn:\n');
end

%Call my function for Euler's method of the first differential equation for
%   three values of h
[x1,y1]=eulerOne(Xn,h);
[x2,y2]=eulerOne(Xn,h/2);
[x3,y3]=eulerOne(Xn,h/10);
%Use ode45 to approximate a solution to the first differential equation
[xode,yode]=ode45(@odefun1,[0 Xn], 1);

%Create vectors to plot the given solution to the first differential
%   equation
x=0:h/100:Xn;
y=1+0.5*exp(-4*x)-0.5*exp(-2*x);

%Use subplot to plot this function on top
%   make it pretty ;)
subplot(2,1,1);
hold on;
plot(x1,y1,'r','LineWidth',2);
plot(x2,y2,'b','LineWidth',2);
plot(x3,y3,'g','LineWidth',2);
plot(xode,yode,'ok','MarkerFaceColor','y');
plot(x,y,'k');
hold off;
axis tight;
title('\fontsize{16}1. f''(x,y)=2-e ^-^4^x-2y');
xlabel('Dependent variable');
xlim([0 Xn]);
ylabel('Independent variable');
legend(strcat('h= ',num2str(h)),strcat('h= ',num2str(h/2)),strcat('h= ',num2str(h/10)),'ode45 Approximation', 'Actual Function', 'Location', 'SouthEast');

%Call my function for Euler's method of the second differential equation for
%   three values of h
[X1,Y1]=eulerTwo(Xn,h);
[X2,Y2]=eulerTwo(Xn,h/2);
[X3,Y3]=eulerTwo(Xn,h/10);
%Use ode45 to approximate a solution to the second differential equation
[Xode,Yode]=ode45(@odefun2,[0 Xn], 0);

%Create vectors to plot the given solution to the second differential
%   equation
X=0:h/100:Xn;
Y=exp(X/2).*sin(5*X);

%Use subplot to plot this function on the bottom
%   make it pretty ;)
subplot(2,1,2);
hold on;
plot(X1,Y1,'r','LineWidth',2);
plot(X2,Y2,'b','LineWidth',2);
plot(X3,Y3,'g','LineWidth',2);
plot(Xode,Yode,'ok','MarkerFaceColor','y');
plot(X,Y,'k');
hold off;
axis tight;
title('\fontsize{16}2. f''(x,y)=y-0.5e ^x^/^2sin(5x)+5e^x^/^2cos(5x)');
xlabel('Dependent variable');
xlim([0 Xn]);
ylabel('Independent variable');
%Shift the legend based on the value of Xn. The system isn't perfect, but
%   it helps.
if(Xn<1.6)
    legend(strcat('h= ',num2str(h)),strcat('h= ',num2str(h/2)),strcat('h= ',num2str(h/10)),'ode45 Approximation', 'Actual Function', 'Location', 'NorthEast');
elseif (Xn>=1.6)
    legend(strcat('h= ',num2str(h)),strcat('h= ',num2str(h/2)),strcat('h= ',num2str(h/10)),'ode45 Approximation', 'Actual Function', 'Location', 'NorthWest');
end

clearvars;

% Euler's method works by using linear approximation between small
% increments to obtain a rough sketch of values for a differential
% equation. Using the equation for linear approximation, f(x+h)=
% f(x)+f'(x)*h, an initial value for f(0), and a given step size (h), we
% can iterate the formula repeatedly to obtain an approximation of solution 
% to the given differential equaion (f(x) from f'(x)) over a given interval. 
% Naturally,the smaller h is, the closer the approximation is to smooth, 
% and the more accurate the approximation. This is visible in the graphs 
% above; as we decrease h, the Euler's method approximation approaches the 
% actual function. Also visibile in the graphs is the fact that Euler's
% method works better for functions that are closer to linear. This makes
% sense, as it is approximating each step as a linear step.