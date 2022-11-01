close; clear; clc;
A = dlmread('solution.txt');

%{
plot3(A(:,2),A(:,3),A(:,4),'r');
hold on;
plot3(A(:,5),A(:,6),A(:,7),'b');
plot3(A(:,8),A(:,9),A(:,10),'g');
hold off;
grid on;
grid minor;
view(100,15);
%}

writerObj = VideoWriter('TragectoriesSimulation.avi');
writerObj.FrameRate = 50;
open(writerObj);

h1 = animatedline(A(1,2),A(1,3),A(1,4),'Color','r');
h2 = animatedline(A(1,5),A(1,6),A(1,7),'Color','b');
h3 = animatedline(A(1,8),A(1,9),A(1,10),'Color','g');
view(100,15);
xlim([0 6]);
ylim([0 6]);
zlim([0 6]);
grid on;
legend('Particle 1','Particle 2','Particle 3');
xlabel('X');
ylabel('Y');
zlabel('Z');

[n,m] = size(A);
for i = 2:n
    addpoints(h1,A(i,2),A(i,3),A(i,4));
    addpoints(h2,A(i,5),A(i,6),A(i,7));
    addpoints(h3,A(i,8),A(i,9),A(i,10));
    drawnow;
    F = getframe(gcf);
    writeVideo(writerObj,F);
    pause(0.00001);
end
close(writerObj);